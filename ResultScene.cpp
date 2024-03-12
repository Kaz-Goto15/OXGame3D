#include "ResultScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"

ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene")
{}
void ResultScene::Initialize() {
	temp = Image::Load("Temp\\result.png");
}
void ResultScene::Update() {
	count++;
	if (count > MAX_COUNT) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}

}
void ResultScene::Draw() {
	Image::Draw(temp);
}
void ResultScene::Release() {}