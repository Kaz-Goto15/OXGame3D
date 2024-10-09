#include "TitleScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Easing.h"
#include "Engine/Text.h"

#include "ButtonEx.h"
//#include "DebugText.h"
#include "CreditScreen.h"
#include "OptionScreen.h"
#include "SystemConfig.h"

#include "AudioManager.h"

using std::to_string;
using std::string;

std::string TitleScene::State2Str(SELECT_STATE state)
{
	switch (state)
	{
	case TitleScene::S_SEL_START:	return "START";
	case TitleScene::S_SEL_CREDIT:	return "CREDIT";
	case TitleScene::S_SEL_OPTION:	return "OPTION";
	case TitleScene::S_SEL_EXIT:	return "EXIT";
	}
	return "NULL";
}

//ファイル名と紐づけ
std::string TitleScene::TitleImgFileName(Img E_IMG)
{
	string dir = "Title\\";
	switch (E_IMG)
	{
	case Img::PIC_BACKGROUND:		return dir + "bg2.png";
	case Img::PIC_TITLE:			return dir + "titleox.png";
	case Img::PIC_WHITE:			return dir + "white.png";
	}
	return "null.png";
}

TitleScene::TitleScene(GameObject* parent) :
	GameObject(parent, "TitleScene"),
	state_(S_STANDBY),
	selectState_(S_SEL_START),
	//フェード
	DEFAULT_PROGRESS(0),
	progress(DEFAULT_PROGRESS), MOVE_FRAMES(60),
	OBJ_FADE_EASE_NUMBER(23),
	//透明度
	ALPHA_ZERO(0), ALPHA_MAX(255),
	//タイトルロゴ
	TITLE_PROGRESS_POINT(60),
	TITLE_Y_FADE({0,-60}),
	//ボタン
	BUTTON_X_SPACE(270),
	BUTTON_Y_FADE({ 400,250 }),
	//テキスト
	txtPressStart(nullptr),
	TEXT_POSITION({0,240}),
	FIRST_TEXT_DESCR("Press 'Space' to continue"),

	//遷移系オブジェクト
	pSceneManager(nullptr),
	pScreen(nullptr)
{
	std::fill(hPict_, hPict_ + PIC_MAX, -1);
	std::fill(btn, btn + S_SEL_MAX, nullptr);
}

void TitleScene::Initialize() {
	//BGMロード
	AudioManager::Load(AudioManager::AUDIO_SOURCE::BGM_LOBBY);

	//画像ロード
	for (int i = 0; i < Img::PIC_MAX; i++) {
		hPict_[i] = Image::Load(TitleImgFileName(static_cast<Img>(i)));
	}

	//スタンバイ時のテキスト
	txtPressStart = new Text();
	txtPressStart->Initialize(GAKUMARU_16px);

	//ボタン情報の初期化
	//第3引数のYは変更されるためなんでもいい
	int btnX = -BUTTON_X_SPACE * Half((int)S_SEL_MAX);	//ボタン数/2で一番左のボタンの座標を設定
	if (IsEven(S_SEL_MAX))btnX += Half(BUTTON_X_SPACE);	//偶数の場合、x=0にボタンが来ないため余白の半分をずらす
	for (SELECT_STATE state = static_cast<SELECT_STATE>(0); state < S_SEL_MAX; state = static_cast<SELECT_STATE>(state + 1)) {
		InitButton(state, State2Str(state), { btnX, 0 });
			btnX += BUTTON_X_SPACE;
	}
	for (int i = 0; i < S_SEL_MAX;i++) {
		//左右キーボタン移動
		if(i-1 >= 0)btn[i]->SetNextKey(ButtonEx::DIR::DIR_LEFT, btn[i - 1]);
		else btn[i]->SetNextKey(ButtonEx::DIR::DIR_LEFT, btn[SELECT_STATE::S_SEL_MAX-1]);

		if(i+1 < SELECT_STATE::S_SEL_MAX)btn[i]->SetNextKey(ButtonEx::DIR::DIR_RIGHT, btn[i + 1]);
		else btn[i]->SetNextKey(ButtonEx::DIR::DIR_RIGHT, btn[0]);

		//ボタン集合リンク
		for (int j = 0; j < S_SEL_MAX; j++) {
			if (i != j)
				btn[i]->AddLinkButton(btn[j]);
		}
	}

}

void TitleScene::Update() {


	//スタンバイ時のみ更新 それ以外はボタン押下で処理
	if (In(state_, { S_STANDBY,S_STANDBY_WAIT })) {
		//決定キーまたは左クリック
		if(Input::IsKeyDown(DIK_SPACE) || Input::IsMouseButtonDown(0)) {
			//BGM再生
			AudioManager::Play(AudioManager::AUDIO_SOURCE::BGM_LOBBY);
			//ボタンの更新開始、描画開始
			for (int i = 0; i < S_SEL_MAX; i++) {
				btn[i]->Enter();
				btn[i]->Visible();
			}

			state_ = S_MAIN;				//ステートをMAINにする
			progress = DEFAULT_PROGRESS;	//進捗を0にもどす

			//タイトルと背景を完全表示
			Image::SetAlpha(hPict_[PIC_TITLE], ALPHA_MAX);
			Image::SetAlpha(hPict_[PIC_BACKGROUND], ALPHA_MAX);
		}
	}
	else if (state_ == S_MAIN) {
		//全て未選択のときの処理
		bool unselected = true;
		for (auto& b : btn) {
			if (b->GetState() == ButtonEx::STATE::SELECT) {
				unselected = false;
				break;
			}
		}
		if(unselected &&
			(Input::IsKeyDown(SystemConfig::GetKey(SystemConfig::KEY::KEY_LEFT)) ||
				Input::IsKeyDown(SystemConfig::GetKey(SystemConfig::KEY::KEY_RIGHT)) )
		) {
			btn[0]->ChangeState(ButtonEx::STATE::SELECT);
		}

	}
}
void TitleScene::Draw() {
	switch (state_)
	{
	case TitleScene::S_STANDBY:
		//進捗がタイトルキー2個目より少なかったら1plus
		if(progress < TITLE_PROGRESS_POINT)progress++;
		//タイトル表示まで
		if (Between(progress, DEFAULT_PROGRESS, TITLE_PROGRESS_POINT)) {
			//透明度を徐々にさげる(不透過率を上げる)
			int alpha = Easing::Calc(1, progress, TITLE_PROGRESS_POINT, ALPHA_ZERO, ALPHA_MAX);

			Image::SetAlpha(hPict_[PIC_TITLE],alpha);
			txtPressStart->SetAlpha(alpha);
		}
		//不透過になったらWAITステートに移行してアクションを待機する
		else {
			state_ = S_STANDBY_WAIT;
			//タイトルと文字は255(透明度0%)を想定しているが万が一何かの拍子で254(透明度0.39%)になってたら悲しいので念のため不透過にする
			Image::SetAlpha(hPict_[PIC_TITLE], ALPHA_MAX);
			txtPressStart->SetAlpha(ALPHA_MAX);
		}
		//描画処理はSTANDBYとWAITは同じなのでbreakせずそのまま受け流す
		[[fallthrough]];
	case TitleScene::S_STANDBY_WAIT:

		//描画
		Image::Draw(hPict_[PIC_TITLE]);
		txtPressStart->Draw(TEXT_POSITION.x, TEXT_POSITION.y, FIRST_TEXT_DESCR);
		break;

	case TitleScene::S_MAIN:
		if (progress < MOVE_FRAMES) {
			progress++;
			//背景
			Image::Draw(hPict_[PIC_BACKGROUND]);

			//タイトル移動
			Transform tra;
			tra.position_.y = Easing::Calc(OBJ_FADE_EASE_NUMBER, progress, MOVE_FRAMES, TITLE_Y_FADE.x, TITLE_Y_FADE.y);
			Image::SetTransform(hPict_[PIC_TITLE], tra);
			Image::Draw(hPict_[PIC_TITLE]);

			//ボタン移動
			for (int i = 0; i < S_SEL_MAX; i++) {
				//もっといい計算方法でできるかも
				XMFLOAT3 pos = btn[i]->GetPosition();
				pos.y = Easing::Calc(OBJ_FADE_EASE_NUMBER, progress, MOVE_FRAMES, BUTTON_Y_FADE.x, BUTTON_Y_FADE.y);
				btn[i]->SetPosition(pos.x, pos.y);
			}

			//白
			Image::SetAlpha(hPict_[PIC_WHITE],
				Easing::Calc(1, progress, MOVE_FRAMES, ALPHA_MAX, ALPHA_ZERO)
			);
			Image::Draw(hPict_[PIC_WHITE]);

			break;
		}
		Image::Draw(hPict_[PIC_BACKGROUND]);
		Image::Draw(hPict_[PIC_TITLE]);
		break;
	}

	XMFLOAT3 mousePos = Input::GetMousePosition();
}

void TitleScene::Release() {}

void TitleScene::ButtonAct(int hAct)
{
	SELECT_STATE ss = static_cast<SELECT_STATE>(hAct);
	switch (ss)
	{
	case TitleScene::S_SEL_START:
		//ゲームプレイシーンへ移行
		pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
		break;
	case TitleScene::S_SEL_CREDIT:
		//クレジットシーンを呼び出す
		pScreen = Instantiate<CreditScreen>(GetParent());
		pScreen->SetPrevScene(this);
		pScreen->Run();
		break;
	case TitleScene::S_SEL_OPTION:
		//オプションスクリーンを呼び出す
		pScreen = Instantiate<OptionScreen>(GetParent());
		pScreen->SetPrevScene(this);
		pScreen->Run();

		break;
	case TitleScene::S_SEL_EXIT:
		//終了
		exit(0);
		break;
	}
}

void TitleScene::InitButton(SELECT_STATE ss, std::string text, XMINT2 pos)
{
	btn[ss] = Instantiate <ButtonEx>(this);
	btn[ss]->SetText(text);										//テキスト指定
	btn[ss]->SetFont(TextLoader::TEXT_SOURCE::GAKUMARU_32px);	//フォント指定
	btn[ss]->SetActionHandle(ss);								//ボタン押下時に返すハンドルを設定
	btn[ss]->SetPosition(pos.x, pos.y);							//位置指定
	btn[ss]->SetSize(0.2f, 0.2f);								//サイズ指定
	btn[ss]->EnDrawShadow(true);								//シャドウを有効化
	btn[ss]->EnDecideKey(true);									//決定キーによる実行を許可
	btn[ss]->Leave();											//更新しない
	btn[ss]->Invisible();										//描画しない
}