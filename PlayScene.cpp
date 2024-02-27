#include "PlayScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Easing.h"
#include "Engine/Text.h"
#include "MapLoader.h"

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{}
void PlayScene::Initialize() {
	pField_ = Instantiate<Field>(this);
	vector<Field::FIELD_DATA> fieldData;
	MapLoader::Load(this,&fieldData, &pActiveFieldList_, &pEntityList_, MapLoader::MAP::M_001);

	pField_->SetFieldData(fieldData);
}
void PlayScene::Update() {

}
void PlayScene::Draw() {
}
void PlayScene::Release() {}