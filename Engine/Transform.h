#pragma once
#include <DirectXMath.h>

using namespace DirectX;


//-----------------------------------------------------------
//�ʒu�A�����A�g�嗦�Ȃǂ��Ǘ�����N���X
//-----------------------------------------------------------
class Transform
{
public:
	XMMATRIX matTranslate_;	//�ړ��s��
	XMMATRIX matRotate_;	//��]�s��	
	XMMATRIX matScale_;		//�g��s��
	XMFLOAT3 position_;		//�ʒu
	XMFLOAT3 rotate_;		//����
	XMFLOAT3 scale_;		//�g�嗦
	Transform * pParent_;	//�e�I�u�W�F�N�g�̏��
	XMFLOAT3 reSize_;		//���T�C�Y�t�B���^
	XMFLOAT3 center_;		//���S�_
	bool isCalcCenterPt_;	//���S�_��ʓr�w�肵���v�Z��L���ɂ��邩
	//�R���X�g���N�^
	Transform();

	//�f�X�g���N�^
	~Transform();

	//�e�s��̌v�Z
	//�����F�Ȃ�
	//�ߒl�F�Ȃ�
	void Calclation();

	//���[���h�s����擾
	//�����F�Ȃ�
	//�ߒl�F���̎��_�ł̃��[���h�s��
	XMMATRIX GetWorldMatrix();

	XMMATRIX GetMatrixConvertEffect(float plus);
	static XMFLOAT3 Float3Add(XMFLOAT3 a, XMFLOAT3 b)
	{
		return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	//void ConvDrawPos(float x, float y);	//Image�̎d�l��ς����̂ł���Ȃ��Ȃ����͂�

	//�A�N�Z�X�]�X�̑O�ɂ����ō��W�w��̐F�X��������ׂ��ł͂Ȃ���
	void SetPosition(XMFLOAT3 position) { position_ = position; }
	void SetPosition(float x, float y, float z) { SetPosition(XMFLOAT3(x, y, z)); }
	void SetPosition(int x, int y, int z) { SetPosition(XMFLOAT3((float)x, (float)y, (float)z)); }
	void SetRotate(XMFLOAT3 rotate) { rotate_ = rotate; }
	void SetRotate(float x, float y, float z) { SetRotate(XMFLOAT3(x, y, z)); }
	void SetRotateX(float x) { SetRotate(x, rotate_.y, rotate_.z); }
	void SetRotateY(float y) { SetRotate(rotate_.x, y, rotate_.z); }
	void SetRotateZ(float z) { SetRotate(rotate_.x, rotate_.y, z); }
	void SetScale(XMFLOAT3 scale) { scale_ = scale; }
	void SetScale(float x, float y, float z) { SetScale(XMFLOAT3(x, y, z)); }
	void SetScale(float all) { SetScale(XMFLOAT3(all, all, all)); }
	void SetScale(float all, float oX, float oY, float oZ);	//�w����W�𒆐S�Ɋg�k�i�v���؁j
	void SetReSize(XMFLOAT3 scale) { reSize_ = scale; }
	void SetReSize(float x, float y, float z) { SetReSize(XMFLOAT3(x, y, z)); }
	void SetReSize(float all) { SetReSize(XMFLOAT3(all, all, all)); }
	void IsCalcCenterPoint(bool b) { isCalcCenterPt_ = b; }
	void SetCenter(XMFLOAT3 pt) { center_ = pt; }
	void SetCenter(float x, float y, float z) { SetCenter(XMFLOAT3(x, y, z)); }
private:
	Transform CalcTrans(Transform tra);
};

