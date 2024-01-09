#include "EditScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"

EditScene::EditScene(GameObject* parent)
	: GameObject(parent, "EditScene"),
	queue_(-1),
	mapSize({5,5,5})
{}
void EditScene::Initialize() {
	//pView = new StageView();
	//pTheme = new StageTheme();
	//pView->SetTheme(pTheme);
	//pEditGUI = new StageEditGUI();
	//pEditGUI->SetTheme(pTheme);
	mapData_.resize(3);
}
void EditScene::Update() {
}
void EditScene::Draw() {

}
void EditScene::Release() {}

void EditScene::EditStart()
{
	//drawTime_ = 0;
	//queue_++;
	//isDisplaying = true;
	//state_ = S_Edit;
}

void EditScene::EditMain()
{
	
	//drawTime_++;

	//if (isDisplaying) {

	//}
	//else {
	//	queue_++;
	//	isDisplaying = true;
	//	if (!(queue_ < LOGO_COUNT)) {
	//		state_ = S_NEXT_SCENE;
	//	}
	//}

}

void EditScene::EditEnd()
{
	//if(que)
}

void EditScene::NextScene()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_TEST);
}
