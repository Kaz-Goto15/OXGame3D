#include "Ground.h"
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"
//�R���X�g���N�^
Ground::Ground(GameObject* parent)
	: GameObject(parent, "Ground"), hModel_(-1)
{
}

//������
void Ground::Initialize()
{
	//���f���Ǎ�
	hModel_ = Model::Load("floor2.fbx");
	assert(hModel_ >= 0);
	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(70, 0, 100));
	AddCollider(collision);

}

//�X�V
void Ground::Update()
{
}

//�`��
void Ground::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Ground::Release()
{
}