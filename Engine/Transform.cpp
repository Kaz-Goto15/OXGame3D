#include "Transform.h"



Transform::Transform(): pParent_(nullptr)
{
	position_ = XMFLOAT3(0, 0, 0);
	rotate_ = XMFLOAT3(0, 0, 0);
	scale_ = XMFLOAT3(1, 1, 1);
	reSize_ = XMFLOAT3(1, 1, 1);
	center_ = XMFLOAT3(0, 0, 0);
	matTranslate_ = XMMatrixIdentity();
	matRotate_ = XMMatrixIdentity();
	matScale_ = XMMatrixIdentity();
	isCalcCenterPt_ = false;
}


Transform::~Transform()
{
}

void Transform::Calclation()
{
	//�ړ��s��(���S�_���l�����邩�̏���)
	if (isCalcCenterPt_) {
		//XMFLOAT3 tmpPos = {
		//	(position_.x - center_.x) * (scale_.x * reSize_.x),// + center_.x,
		//	(position_.y - center_.y) * (scale_.y * reSize_.y),// + center_.y,
		//	(position_.z - center_.z) * (scale_.z * reSize_.z),// + center_.z
		//};
		XMFLOAT3 tmpPos = {
			(position_.x - center_.x) * (reSize_.x),// + center_.x,
			(position_.y - center_.y) * (reSize_.y),// + center_.y,
			(position_.z - center_.z) * (reSize_.z),// + center_.z
		};
		matTranslate_ = XMMatrixTranslation(tmpPos.x, tmpPos.y, tmpPos.z);
	}
	else {
		matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);
	}

	//��]�s��
	XMMATRIX rotateX, rotateY, rotateZ;
	rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
	matRotate_ = rotateZ * rotateX * rotateY;

	//�g��k��
	matScale_ = XMMatrixScaling(scale_.x * reSize_.x, scale_.y * reSize_.y, scale_.z * reSize_.z);
}

XMMATRIX Transform::GetWorldMatrix() 
{
	Calclation();
	if (pParent_)
	{
		return  matScale_ * matRotate_ * matTranslate_ * pParent_->GetWorldMatrix();
	}

	return  matScale_ * matRotate_ * matTranslate_;
}

XMMATRIX Transform::GetMatrixConvertEffect()
{
	//�ړ��s��
	matTranslate_ = XMMatrixTranslation(position_.x - 16.0f/9.0f, position_.y - 16.0f / 9.0f, position_.z - 16.0f / 9.0f);

	//��]�s��
	XMMATRIX rotateX, rotateY, rotateZ;
	rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
	matRotate_ = rotateZ * rotateX * rotateY;

	//�g��k��
	matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);

	return matScale_ * matRotate_ * matTranslate_;
}

//void Transform::ConvDrawPos(float x, float y)
//{
//	position_.x = x / 40 * 0.062f;
//	position_.y = y / -40 * 0.110f;
//	position_.z = 0;
//}

void Transform::SetScale(float all, float oX, float oY, float oZ)
{
	XMFLOAT3 oPos = { 0,0,0 };
	XMVECTOR oVec = XMLoadFloat3(&oPos);
	XMFLOAT3 pointPos = { oX,oY,oZ };
	XMVECTOR pointVec = XMLoadFloat3(&pointPos);
	XMFLOAT3 nowPos = position_;
	XMVECTOR nowVec = XMLoadFloat3(&nowPos);
	XMFLOAT3 nextPos;
	XMVECTOR tmpVec, tmpVec2;
	XMFLOAT3 tmpFloat;

	//�ړ��@�\(to�Ώ̓_)���g��@�\���ړ��ꏊ�v�Z���ړ��@�\(to�V�z�u�_)
	SetPosition(oPos);
	SetScale(all);

	tmpVec = nowVec - pointVec;
	XMStoreFloat3(&tmpFloat, tmpVec);
	tmpFloat.x *= all;
	tmpFloat.y *= all;
	tmpFloat.z *= all;
	tmpVec2 = XMLoadFloat3(&tmpFloat);
	tmpVec = pointVec + tmpVec2;
	XMStoreFloat3(&nextPos, tmpVec);
	SetPosition(nextPos);
}

Transform Transform::CalcTrans(Transform tra)
{
	Transform ret;
	XMFLOAT3 oPos = { 0,0,0 };
	XMVECTOR oVec = XMLoadFloat3(&oPos);
	XMVECTOR pointVec = XMLoadFloat3(&center_);
	XMVECTOR nowVec = XMLoadFloat3(&position_);
	XMFLOAT3 nextPos;
	XMVECTOR tmpVec, tmpVec2;
	XMFLOAT3 tmpFloat;

	//�ړ��@�\(to�Ώ̓_)���g��@�\���ړ��ꏊ�v�Z���ړ��@�\(to�V�z�u�_)
	ret.position_ = oPos;
	ret.scale_ = {
		scale_.x * reSize_.x,
		scale_.y * reSize_.y,
		scale_.z * reSize_.z
	};

	tmpVec = nowVec - pointVec;
	XMStoreFloat3(&tmpFloat, tmpVec);
	tmpFloat = ret.scale_;
	tmpVec2 = XMLoadFloat3(&tmpFloat);
	tmpVec = pointVec + tmpVec2;
	XMStoreFloat3(&nextPos, tmpVec);
	ret.position_ = nextPos;
	return ret;
}

