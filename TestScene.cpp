#include "TestScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Easing.h"
#include "Engine/Text.h"

TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene"),
	newText(nullptr)
{}
void TestScene::Initialize(){
	hPict_ = Image::Load("circle.png");
	ringTra.scale_ = { 0.05,0.05,0.05 };
	Image::SetTransform(hPict_, ringTra);
	newText = new Text();
	newText->Initialize("char_kurokaneEB_aqua1024_50.png", 50, 100, 16);
}
void TestScene::Update(){
	if (Input::IsKeyDown(DIK_0)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SPLASH);
	}
	if (Input::IsKeyDown(DIK_A))easeNum--;
	if (Input::IsKeyDown(DIK_D))easeNum++;
}
void TestScene::Draw(){
	std::string str = "ease: " + std::to_string(easeNum);
	newText->Draw(40, 40, str.c_str());

	int drawCircleNum = 200;
	float circleUnit = 1.8f;
	for (int i = 0; i < drawCircleNum; i++) {
		float cy = -circleUnit * Easing::Calc(easeNum, i, drawCircleNum, 0, drawCircleNum) + drawCircleNum/2 * circleUnit;
		float cx = circleUnit * i - drawCircleNum/2 * circleUnit;
		ringTra.ConvDrawPos(cx, cy);
		Image::SetTransform(hPict_, ringTra);
		Image::Draw(hPict_);
	}
}
void TestScene::Release(){}