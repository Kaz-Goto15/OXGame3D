#include "Ground.h"
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"
//コンストラクタ
Ground::Ground(GameObject* parent)
	: GameObject(parent, "Ground"), hModel_(-1)
{
}

//初期化
void Ground::Initialize()
{
	//モデル読込
	hModel_ = Model::Load("floor2.fbx");
	assert(hModel_ >= 0);
	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(70, 0, 100));
	AddCollider(collision);

}

//更新
void Ground::Update()
{
}

//描画
void Ground::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Ground::Release()
{
}