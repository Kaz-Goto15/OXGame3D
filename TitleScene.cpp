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
	case TitleScene::BACKGROUND:	return "lobby_bg_720p.png";
	case TitleScene::TITLE:			return "result_meter.png";
	case TitleScene::CHARACTER:		return "grayman\\hm.png";
	}
	return "null.png";
}

TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"),
	newText(nullptr)
{}
void TitleScene::Initialize() {
	hPict_ = Image::Load("circle.png");
	ringTra.scale_ = { 0.05,0.05,0.05 };
	Image::SetTransform(hPict_, ringTra);
	newText = new Text();
	newText->Initialize("char_kurokaneEB_aqua1024_50.png", 50, 100, 16);
}
void TitleScene::Update() {
	if (Input::IsKeyDown(DIK_0)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SPLASH);
	}
	if (Input::IsKeyDown(DIK_A))easeNum--;
	if (Input::IsKeyDown(DIK_D))easeNum++;
}
void TitleScene::Draw() {
	std::string str = "ease: " + std::to_string(easeNum);
	newText->Draw(40, 40, str.c_str());

	int drawCircleNum = 1600;
	float circleUnit = 0.225f;
	for (int i = 0; i < drawCircleNum; i++) {
		float cy = -circleUnit * Easing::Calc(easeNum, i, drawCircleNum, 0, drawCircleNum) + drawCircleNum / 2.0f * circleUnit;
		float cx = circleUnit * i - drawCircleNum / 2.0f * circleUnit;
		ringTra.ConvDrawPos(cx, cy);
		Image::SetTransform(hPict_, ringTra);
		Image::Draw(hPict_);
	}
}
void TitleScene::Release() {}