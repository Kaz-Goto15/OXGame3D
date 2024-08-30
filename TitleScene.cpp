#include "TitleScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Easing.h"
#include "Engine/Text.h"

#include "ButtonGP.h"
//#include "DebugText.h"
#include "CreditScreen.h"
#include "OptionScreen.h"

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
				btn[i]->SetPosition(pos);
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
		pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
		break;
	case TitleScene::S_SEL_CREDIT:
		pScreen = Instantiate<CreditScreen>(GetParent());
		pScreen->SetPrevScene(this);
		pScreen->Run();
		break;
	case TitleScene::S_SEL_OPTION:

		pScreen = Instantiate<OptionScreen>(GetParent());
		pScreen->SetPrevScene(this);
		pScreen->Run();

		break;
	case TitleScene::S_SEL_EXIT:
		exit(0);
	default:
		break;
	}
}

void TitleScene::InitButton(SELECT_STATE ss, std::string text, XMINT2 pos)
{
	btn[ss] = Instantiate <ButtonGP>(this);
	btn[ss]->SetText(text);
	btn[ss]->SetAction(ss);
	btn[ss]->SetPosition(pos.x, pos.y, 0);
	btn[ss]->Leave();
	btn[ss]->Invisible();
}

/*
BUTTON STATE
IDLE:
 選択外のアニメーション
 カーソルが来た時にSELECTに移動

 ボタンで選ばれたときSELECTに移動

SELECT:
 選択中のアニメーション
 マウスボタンが押されたらPUSHに移動
 カーソルが外れたらIDLEに移動
 ボタンが押されたらSELECTEDに移動(keydown upではなく)
 ボタンが他に行ったときIDLEに移動

PUSH:
 押下中アニメーション

 カーソルが外れたらIDLEに移動
 マウスボタンが離されたとき、SELECTEDに移動

SELECTED:
 選択されたアニメーション
 処理を行う
 処理が終わったらIDLEに移動

 マウスは自分で処理できる
 ボタンがきついか



カーソルがぼたん上に来た時の処理：btn_select
ボタン上で押し、押し続けている時の処理：btn_push
ボタン上で押し、離したときの処理：btn_selected
離されたとき・ボタン上に無い時の処理：btn_idle


選択中のBTN_ENUM

白inでボタンフェードイン 選択可能
 ボタン：選択外/選択中/選択中かつ押されている/選択後の処理中
 押されたときの処理を考える
 ボタンを登録するときにGenerate(cmd);
 表示は親のほうでTitleBtn.count()分のforでDraw
 ボタンが押されたら親のRun(COMMAND cmd);を呼ぶ
main
background
select: logo (白フェード)
start/option/edit/exit
start→screenで新たに記述
option→screen
edit→ブラックアウトからeditscene
exit→そのまんまexit(0)でおけ

fadein イージング番号に沿って透明度変更　0→100でidle SPACE:end
idle 指定時間待機　指定時間超過でfadeoutへ SPACE:end
fadeout イージング番号に沿って透明度変更　100→0でendへ SPACE:end
end 表示するものがあればfadein なければタイトルシーンへ
*/