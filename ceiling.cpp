#include "ceiling.h"
#include "Engine/Model.h"
//コンストラクタ
ceiling::ceiling(GameObject* parent)
	: GameObject(parent, "ceiling"), hModel_(-1)

{
}

//初期化
void ceiling::Initialize()
{

	//モデル読込
	hModel_ = Model::Load("floor.fbx");
	assert(hModel_ >= 0);

	 //天井位置・コライダー
	transform_.position_.x = 40;
    transform_.position_.y = 18.0f;
	BoxCollider* collision = new BoxCollider(XMFLOAT3(-40, -5.8f, 0), XMFLOAT3(70, 0, 100));
	AddCollider(collision);

}

//更新
void ceiling::Update()
{
}

//描画
void ceiling::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void ceiling::Release()
{
}
