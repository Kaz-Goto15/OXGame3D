#include "TestScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Easing.h"
TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene")
{}
void TestScene::Initialize(){
	hPict_ = Image::Load("ring.png");
	ringTra.scale_ = { 0.25,0.25,0.25 };
	Image::SetTransform(hPict_, ringTra);
}
void TestScene::Update(){
	if (Input::IsKeyDown(DIK_0)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SPLASH);
	}
}
void TestScene::Draw(){
	for (int i = 0; i < 100; i++) {
		float cx = 3.6 * Easing::Calc(2, i, 100, 0, 100);
		float cy = 3.6 * -i;
		ringTra.ConvDrawPos(cx, cy);
		Image::SetTransform(hPict_, ringTra);
		Image::Draw(hPict_);
	}
}
void TestScene::Release(){}