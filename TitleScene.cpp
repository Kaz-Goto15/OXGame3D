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
	progress(DEFAULT_PROGRESS), maxProgress(60),
	btnFadeEaseNo(23),
	//透明度
	ALPHA_ZERO(0), ALPHA_MAX(255),
	//タイトルロゴ
	TITLE_PROGRESS_POINT({60,120}),
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
	AudioManager::Load(AudioManager::AUDIO_SOURCE::BGM_LOBBY);
	for (int i = 0; i < Img::PIC_MAX; i++) {
		hPict_[i] = Image::Load(TitleImgFileName(static_cast<Img>(i)));
	}

	txtPressStart = new Text();
	txtPressStart->Initialize(GAKUMARU_16px);

	InitButton(S_SEL_START,	"START",	{ (int)(-BUTTON_X_SPACE * 1.5),BUTTON_Y_FADE.y });
	InitButton(S_SEL_CREDIT,"CREDIT",	{ (int)(-BUTTON_X_SPACE *0.5)	,BUTTON_Y_FADE.x });
	InitButton(S_SEL_OPTION,"OPTION",	{ (int)(BUTTON_X_SPACE *0.5)	,BUTTON_Y_FADE.x });
	InitButton(S_SEL_EXIT,	"EXIT",		{ (int)(BUTTON_X_SPACE *1.5)	,BUTTON_Y_FADE.x });

	//debugText = Instantiate<DebugText>(this);
	//for (int i = 0; i < 20; i++) debugText->AddStrPtr(&debugStr[i]);

}
void TitleScene::Update() {
	if (state_ == S_STANDBY) {
		//決定キーまたは左クリック
		if(Input::IsKeyDown(DIK_SPACE) || Input::IsMouseButtonDown(0)) {
			AudioManager::Play(AudioManager::AUDIO_SOURCE::BGM_LOBBY);
			//ボタン描画(多重)
			for (int i = 0; i < S_SEL_MAX; i++) {
				btn[i]->Enter();
				btn[i]->Visible();
			}

			state_ = S_MAIN;
			progress = 0;
			Image::SetAlpha(hPict_[PIC_TITLE], ALPHA_MAX);
			Image::SetAlpha(hPict_[PIC_BACKGROUND], ALPHA_MAX);
		}
	}
}
void TitleScene::Draw() {
	switch (state_)
	{
	case TitleScene::S_STANDBY:
		//進捗が
		if(progress < TITLE_PROGRESS_POINT.y)progress++;
		if (Between(progress, DEFAULT_PROGRESS, TITLE_PROGRESS_POINT.x)) {
			//いずれ別クラスで上に黒を被せる方式にしたい
			Image::SetAlpha(hPict_[PIC_TITLE],
				Easing::Calc(1, progress, TITLE_PROGRESS_POINT.x, ALPHA_ZERO, ALPHA_MAX)
			);

			Image::Draw(hPict_[PIC_TITLE]);
			txtPressStart->SetAlpha(Easing::Calc(1, progress, TITLE_PROGRESS_POINT.x, ALPHA_ZERO, ALPHA_MAX));
			txtPressStart->Draw(TEXT_POSITION.x, TEXT_POSITION.y, FIRST_TEXT_DESCR);
			break;
		}
		else if (Between(progress, TITLE_PROGRESS_POINT.x, TITLE_PROGRESS_POINT.y)) {
			//Image::SetAlpha(hPict_[PIC_BACKGROUND],
			//	Easing::Calc(1, progress, TITLE_PROGRESS_POINT[1], ALPHA_ZERO, ALPHA_MAX)
			//);
			Image::SetAlpha(hPict_[PIC_TITLE], ALPHA_MAX);
			txtPressStart->SetAlpha(ALPHA_MAX);
			//Image::Draw(hPict_[PIC_BACKGROUND]);
			Image::Draw(hPict_[PIC_TITLE]);
			txtPressStart->Draw(TEXT_POSITION.x, TEXT_POSITION.y, FIRST_TEXT_DESCR);
			break;
		}
		else {
			//state_ = S_MAIN;
			//progress = 0;
		}
		break;
	case TitleScene::S_MAIN:
		if (progress < maxProgress) {
			progress++;
			//背景
			Image::Draw(hPict_[PIC_BACKGROUND]);
			//タイトル
			Transform tra;
			tra.position_.y = Easing::Calc(btnFadeEaseNo, progress, maxProgress, TITLE_Y_FADE.x, TITLE_Y_FADE.y);
			Image::SetTransform(hPict_[PIC_TITLE], tra);
			Image::Draw(hPict_[PIC_TITLE]);
			//ボタン描画(多重)
			for (int i = 0; i < S_SEL_MAX; i++) {
				//もっといい計算方法でできるかも
				XMFLOAT3 pos = btn[i]->GetPosition();
				pos.y = Easing::Calc(btnFadeEaseNo, progress, maxProgress, BUTTON_Y_FADE.x, BUTTON_Y_FADE.y);
				btn[i]->SetPosition(pos);
			}
			//白 いずれ別クラスで実装したい(描画順の関係でボタンが上にいくため)
			Image::SetAlpha(hPict_[PIC_WHITE],
				Easing::Calc(1, progress, maxProgress, ALPHA_MAX, ALPHA_ZERO)
			);
			Image::Draw(hPict_[PIC_WHITE]);

			break;
		}
		Image::Draw(hPict_[PIC_BACKGROUND]);
		Image::Draw(hPict_[PIC_TITLE]);
		break;
	case TitleScene::S_SELECT:
		Image::Draw(hPict_[PIC_BACKGROUND]);
		Image::Draw(hPict_[PIC_TITLE]);
		break;
	}

	XMFLOAT3 mousePos = Input::GetMousePosition();
	//debugStr[0] = "imgSize: " + std::to_string(Image::GetWidth(hImg_)) + ", " + std::to_string(Image::GetHeight(hImg_));
	//debugStr[1] = "imgScale: " + std::to_string(nullScale_.x) + ", " + std::to_string(nullScale_.y);
	//debugStr[2] = "mousePos: " + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y);
	//debugStr[3] = btn[0]->GetDebugStr(6);

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


ボタンとして追加するか？
12
34　で追加したとき

1のとき 上下左右 0+2 0+1
2のとき 上下左右 0+2-1 0
3のとき 上下左右-2 0 0+1
4のとき 上下左右-2 0-1 0

12
(3)4　で追加したとき

1のとき 上下左右 0+3 0+1
2のとき 上下左右 0+2-1 0
3にいく時の入力 --+3-3--
4のとき 上下左右-2 0-3 0

1のとき 上下左右 0+2 0+1
2のとき 上下左右 0+2-1 0
3にいく時の入力 --+1-2--
4のとき 上下左右-2 0-1 0

下入力+2 上入力-2 3以上のとき下入力入れない 2以下のとき上入れない
右+1
fadein イージング番号に沿って透明度変更　0→100でidle SPACE:end
idle 指定時間待機　指定時間超過でfadeoutへ SPACE:end
fadeout イージング番号に沿って透明度変更　100→0でendへ SPACE:end
end 表示するものがあればfadein なければタイトルシーンへ
*/