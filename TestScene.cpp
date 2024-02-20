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
	ringTra.scale_ = { 0.05f,0.05f,0.05f};
	Image::SetTransform(hPict_, ringTra);

	newText = new Text();
	newText->Initialize(KUROKANE_AQUA_50px);
}
void TestScene::Update(){

	//S ; Change Scene - Splash
	if (Input::IsKeyDown(DIK_ESCAPE)) {
		exit(0);

	}
	//S ; Change Scene - Splash
	if (Input::IsKeyDown(DIK_S)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SPLASH);
	}

	//S ; Change Scene - Title
	if (Input::IsKeyDown(DIK_T)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}

	//AD ; Show easing_tra ease
	if (Input::IsKeyDown(DIK_A))easeNum--;
	if (Input::IsKeyDown(DIK_D))easeNum++;

}
void TestScene::Draw(){
	std::string str = "ease: " + std::to_string(easeNum);
	newText->Draw(40, 40, str.c_str());

	int drawCircleNum = 1600;
	float circleUnit = 0.225f;
	for (int i = 0; i < drawCircleNum; i++) {
		float cy = -circleUnit * Easing::Calc(easeNum, i, (float)drawCircleNum, 0, (float)drawCircleNum) + (float)drawCircleNum/2.0f * circleUnit;
		float cx = circleUnit * i - drawCircleNum/2.0f * circleUnit;
		//ringTra.ConvDrawPos(cx, cy);
		Image::SetTransform(hPict_, ringTra);
		Image::Draw(hPict_);
	}
}
void TestScene::Release(){}