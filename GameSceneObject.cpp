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