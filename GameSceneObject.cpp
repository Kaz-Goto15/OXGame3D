#include "GameSceneObject.h"

//コンストラクタ
GameSceneObject::GameSceneObject(GameObject* parent, const std::string& name)
    :GameObject(parent, name)
{
}

//デストラクタ
GameSceneObject::~GameSceneObject()
{
}

//初期化
void GameSceneObject::Initialize()
{
}

//更新
void GameSceneObject::Update()
{
}

//描画
void GameSceneObject::Draw()
{
}

//開放
void GameSceneObject::Release()
{
}