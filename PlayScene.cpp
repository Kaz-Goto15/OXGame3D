#include "PlayScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Easing.h"
#include "Engine/Text.h"
#include "MapLoader.h"

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),
	hBackground_(-1)
{}
void PlayScene::Initialize() {
	temp = Image::Load("Temp\\play.png");

	pField_ = Instantiate<Field>(this);
	vector<Field::FIELD_DATA> fieldData;
	MapLoader::Load(this,hBackground_, &fieldData, &pActiveFieldList_, &pEntityList_, MapLoader::MAP::M_001);

	pField_->SetFieldData(fieldData);;
}
void PlayScene::Update() {
	count++;
	if (count > MAX_COUNT) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
	}
}
void PlayScene::Draw() {
	Image::Draw(hBackground_);
}
void PlayScene::Release() {}