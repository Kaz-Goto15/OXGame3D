#include "TitleScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Easing.h"
#include "Engine/Text.h"

#include "TitleButton.h"
#include "DebugText.h"
using std::to_string;

std::string TitleScene::TitleImgFileName(Img E_IMG)
{
	switch (E_IMG)
	{
	case Img::PIC_BACKGROUND:		return "lobby_bg_720p.png";
	case Img::PIC_TITLE:			return "result_meter.png";
	case Img::PIC_CHARACTER:		return "grayman\\hm.png";
	}
	return "null.png";
}

TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"),
	newText(nullptr),
	selectState_(S_SEL_START)
{}

void TitleScene::Initialize() {
	for (int i = 0; i < Img::MAX; i++) {
		hPict_[i] = Image::Load(TitleImgFileName(static_cast<Img>(i)));
	}
	newText = new Text();
	newText->Initialize("char_kurokaneEB_aqua1024_50.png", 50, 100, 16);
	debugText = Instantiate<DebugText>(this);
	for (int i = 0; i < 20; i++) debugText->AddStrPtr(&debugStr[i]);

	InitButton(S_SEL_START, "START", { 180,-240 });
	InitButton(S_SEL_CREDIT, "CREDIT", { 180,-80 });
	InitButton(S_SEL_OPTION, "OPTION", { 180,80 });
	InitButton(S_SEL_EXIT, "EXIT", { 180, 240 });

}
void TitleScene::Update() {
	if (Input::IsKeyDown(DIK_0)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SPLASH);
	}
	if (Input::IsKeyDown(DIK_SPACE)) {
		Run(selectState_);
	}
	if (Input::IsKeyDown(DIK_9)) {
		Invisible();
	}
}
void TitleScene::Draw() {
	std::string str = "TitleScene: ";
	newText->Draw(40, 40, str.c_str());

	for (int& h : hPict_) {
		//Image::Draw(h);
	}
	XMFLOAT3 mousePos = Input::GetMousePosition();
	//debugStr[0] = "imgSize: " + std::to_string(Image::GetWidth(hImg_)) + ", " + std::to_string(Image::GetHeight(hImg_));
	//debugStr[1] = "imgScale: " + std::to_string(nullScale_.x) + ", " + std::to_string(nullScale_.y);
	debugStr[2] = "mousePos: " + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y);
	//debugStr[3] = "state:" + to_string(newBtn->state);
	//debugStr[4] = newBtn->GetDebugStr(0);
	//debugStr[5] = newBtn->GetDebugStr(1);
	//debugStr[6] = newBtn->GetDebugStr(2);
	//debugStr[7] = newBtn->GetDebugStr(3);
	//debugStr[8] = newBtn->GetDebugStr(4);
	//debugStr[9] = newBtn->GetDebugStr(5);

}
void TitleScene::Release() {}

void TitleScene::Act(int hAct)
{
	SELECT_STATE ss = static_cast<SELECT_STATE>(hAct);
	switch (ss)
	{
	case TitleScene::S_SEL_START:
		//GameScene?
		break;
	case TitleScene::S_SEL_CREDIT:
		//CreditScene?
		break;
	case TitleScene::S_SEL_OPTION:
		//OptionScreen?
		break;
	case TitleScene::S_SEL_EXIT:
		exit(0);
	default:
		break;
	}
}

void TitleScene::Run(SELECT_STATE& ss) {
	switch (ss)
	{
	case SELECT_STATE::S_SEL_START:
		//FileList.EnDraw();
		manipTarget = MANIP_FILE_LIST;
		break;
	case SELECT_STATE::S_SEL_CREDIT:
		//credit.Show();
		manipTarget = MANIP_CREDIT;
		break;
	case SELECT_STATE::S_SEL_OPTION:
		break;
	case SELECT_STATE::S_SEL_EXIT:
		//ConfirmWIndow cw = new ConfirmWindow();
		//cw.SetMessage("デスクトップに戻りますか？");
		manipTarget = MANIP_CONFIRM_WINDOW;
		break;
	default:
		MessageBox(NULL, "Error", "致命的エラー：範囲外の選択ステート", MB_OK);
		exit(1);
	}
}

void TitleScene::InitButton(SELECT_STATE ss, std::string text, XMFLOAT2 pos)
{
	btn[ss] = Instantiate <TitleButton>(this);
	btn[ss]->SetText(text);
	btn[ss]->SetAction(ss);
	btn[ss]->SetPosition(pos.x, pos.y, 0.0f);
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