#include "Entity.h"
#include <cmath>
//コンストラクタ
Entity::Entity(GameObject* parent, const std::string& name)
    :GameSceneObject(parent, name)
{
}

//デストラクタ
Entity::~Entity()
{
}

//初期化
void Entity::Initialize()
{
}

//更新
void Entity::Update()
{
    using std::sqrtf;
    using std::powf;
    XMFLOAT3 playerPos = FindObject("Player")->GetPosition();   //これ死ぬほどコスト
    if (sqrtf(powf(playerPos.x - transform_.position_.x, 2.f) + powf(playerPos.y - transform_.position_.y, 2.0f) + powf(playerPos.z - transform_.position_.z, 2.0f))
        < 5)Visible();
    else Invisible();
}

//描画
void Entity::Draw()
{
}

//開放
void Entity::Release()
{
}