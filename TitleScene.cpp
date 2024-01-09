#include "TitleScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Easing.h"
#include "Engine/Text.h"
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
}
void TitleScene::Update() {
	if (Input::IsKeyDown(DIK_0)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SPLASH);
	}
	if (Input::IsKeyDown(DIK_SPACE)) {
		Run(selectState_);
	}
}
void TitleScene::Draw() {
	std::string str = "TitleScene: ";
	newText->Draw(40, 40, str.c_str());

	for (int& h : hPict_) {
		Image::Draw(h);
	}
}
void TitleScene::Release() {}

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
