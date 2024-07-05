#include "CubeSelectIndicator.h"
#include "./ModelLoader.h"
#include "Engine/Model.h"
XMFLOAT3 CubeSelectIndicator::Surface2Rotate(Cube::SURFACE surface, bool reverse)
{
	if (!reverse) {
		//���f���ŏ����(0,1,0)�ɔz�u����
		switch (surface)
		{
		case Cube::SURFACE_TOP: return { 0,0,0 };
		case Cube::SURFACE_BOTTOM:return { 180,0,0 };
		case Cube::SURFACE_LEFT:    return { 0,0,90 };
		case Cube::SURFACE_RIGHT:   return { 0,0,-90 };
		case Cube::SURFACE_FRONT:   return { -90,0,0 };
		case Cube::SURFACE_BACK:    return { 90,0,0 };
		}
	}
	else {
		//�����������]����
		switch (surface)
		{
		case Cube::SURFACE_TOP: return { 0,180,0 };
		case Cube::SURFACE_BOTTOM:return { 180,180,0 };
		case Cube::SURFACE_LEFT:    return { 180,0,90 };
		case Cube::SURFACE_RIGHT:   return { 180,0,-90 };
		case Cube::SURFACE_FRONT:   return { 90,0,180 };
		case Cube::SURFACE_BACK:    return { -90,0,180 };
		}

	}
}

//�R���X�g���N�^
CubeSelectIndicator::CubeSelectIndicator(GameObject* parent):
	GameObject(parent, "CubeSelectIndicator"),
	hModel(-1),
	cubeSize(0),
	outerPoint(0.0f),
	rotCol(0),
	drawMode(DRAWMODE_CIRCLE),
	direction(ROTATE_DIR::ROT_UP)

{
}

//�f�X�g���N�^
CubeSelectIndicator::~CubeSelectIndicator()
{
}

//������
void CubeSelectIndicator::Initialize()
{
	hModel = ModelLoader::Load(ModelLoader::CubeSelectIndicator);
	//ModelLoader::ChangeAnim(hModel, "green");
	EFFEKSEERLIB::gEfk->AddEffect("arrow", "Effect\\arrow.efk");
	//EFFEKSEERLIB::EFKTransform t;
	//DirectX::XMStoreFloat4x4(&(t.matrix), transform_.GetWorldMatrix());
	//t.isLoop = true;    //���[�v���邩
	//t.maxFrame = 100;   //�ő�t���[���w��
	//t.speed = 1.0;      //�G�t�F�N�g���x ���G�N�X�|�[�g���̑��x��1.0
	//mt = EFFEKSEERLIB::gEfk->Play("arrow", t);

}

//�X�V
void CubeSelectIndicator::Update()
{
	//DirectX::XMStoreFloat4x4(&(mt->matrix), this->GetWorldMatrix());
}

//�`��
void CubeSelectIndicator::Draw()
{
	if (drawMode == DRAWMODE_SINGLE) {
		Model::SetTransform(hModel, transform_);
		Model::Draw(hModel);
	}
	else if (drawMode == DRAWMODE_CIRCLE) {
		Transform tra;
		switch (direction)
		{
		case ROTATE_DIR::ROT_UP:
		case ROTATE_DIR::ROT_DOWN:
			//X���W=�I���
			tra.position_.x = rotCol - outerPoint;

			for (int i = 0; i < cubeSize; i++) {
				for (int j = 0; j < cubeSize; j++) {
					tra.position_.y = i - outerPoint;
					tra.position_.z = j - outerPoint;

					//���E�ʕ`��
					DrawSurface(tra, Cube::SURFACE_LEFT, false);
					DrawSurface(tra, Cube::SURFACE_RIGHT, false);
				}
			}

			for (int i = 0; i < cubeSize; i++) {

				tra.position_.y = i - outerPoint;

				//�O�ʕ`��
				DrawSurface(tra, Cube::SURFACE_FRONT);
				//��ʕ`��
				DrawSurface(tra, Cube::SURFACE_BACK);

				tra.position_.z = i - outerPoint;

				//��ʕ`��
				DrawSurface(tra, Cube::SURFACE_TOP);
				//���ʕ`��
				DrawSurface(tra, Cube::SURFACE_BOTTOM);
			}

			break;

		case ROTATE_DIR::ROT_LEFT:
		case ROTATE_DIR::ROT_RIGHT:
			//Y���W=�I���
			tra.position_.y = rotCol - outerPoint;

			for (int i = 0; i < cubeSize; i++) {
				for (int j = 0; j < cubeSize; j++) {
					tra.position_.x = i - outerPoint;
					tra.position_.z = j - outerPoint;

					//�㉺�ʕ`��
					DrawSurface(tra, Cube::SURFACE_TOP, false);
					DrawSurface(tra, Cube::SURFACE_BOTTOM, false);
				}
			}

			for (int i = 0; i < cubeSize; i++) {

				tra.position_.z = i - outerPoint;

				//�E�ʕ`��
				DrawSurface(tra, Cube::SURFACE_RIGHT);
				//���ʕ`��
				DrawSurface(tra, Cube::SURFACE_LEFT);

				tra.position_.x = i - outerPoint;

				//�O�ʕ`��
				DrawSurface(tra, Cube::SURFACE_FRONT);
				//��ʕ`��
				DrawSurface(tra, Cube::SURFACE_BACK);
			}

			break;

		case ROTATE_DIR::ROT_CW:
		case ROTATE_DIR::ROT_CCW:
			//Z���W=�I���
			tra.position_.z = rotCol - outerPoint;

			for (int i = 0; i < cubeSize; i++) {
				for (int j = 0; j < cubeSize; j++) {
					tra.position_.x = i - outerPoint;
					tra.position_.y = j - outerPoint;

					//�O��ʕ`��
					DrawSurface(tra, Cube::SURFACE_FRONT, false);
					DrawSurface(tra, Cube::SURFACE_BACK, false);
				}
			}

			for (int i = 0; i < cubeSize; i++) {
				tra.position_.x = i - outerPoint;

				//��ʕ`��
				DrawSurface(tra, Cube::SURFACE_TOP);
				//���ʕ`��
				DrawSurface(tra, Cube::SURFACE_BOTTOM);

				tra.position_.y = i - outerPoint;

				//�E�ʕ`��
				DrawSurface(tra, Cube::SURFACE_RIGHT);
				//���ʕ`��
				DrawSurface(tra, Cube::SURFACE_LEFT);
			}
			break;
		}

	}
}

void CubeSelectIndicator::DrawSurface(Transform& tra, Cube::SURFACE surface, bool isOuter)
{
	if (isOuter) {
		switch (surface)
		{
		case Cube::SURFACE_TOP:		tra.position_.y = outerPoint;	break;
		case Cube::SURFACE_BOTTOM:	tra.position_.y = -outerPoint;	break;
		case Cube::SURFACE_LEFT:	tra.position_.x = -outerPoint;	break;
		case Cube::SURFACE_RIGHT:	tra.position_.x = outerPoint;	break;
		case Cube::SURFACE_FRONT:	tra.position_.z = -outerPoint;	break;
		case Cube::SURFACE_BACK:	tra.position_.z = outerPoint;	break;
		}
	}
	tra.rotate_ = Surface2Rotate(surface);
	Model::SetTransform(hModel, tra);
	Model::Draw(hModel);
}

//�J��
void CubeSelectIndicator::Release()
{
}

void CubeSelectIndicator::SetDrawPoint(XMINT3 point, Cube::SURFACE surface)
{
	SetDrawPoint(point);
	SetDrawPoint(surface);
}

void CubeSelectIndicator::SetDrawPoint(XMINT3 point)
{
	transform_.position_.x = (float)point.x - outerPoint;
	transform_.position_.y = (float)point.y - outerPoint;
	transform_.position_.z = (float)point.z - outerPoint;
}

void CubeSelectIndicator::SetDrawPoint(Cube::SURFACE surface)
{
	transform_.rotate_ = Surface2Rotate(surface);
}

void CubeSelectIndicator::SetCubeScale(int scale)
{
	cubeSize = scale;
	outerPoint = Half((float)(scale - 1));
}

void CubeSelectIndicator::SetCubeRotate(ROTATE_DIR dir)
{
	direction = dir;

	Transform tra;// = transform_;

	//EFFEKSEERLIB::gEfk->SetFPS(1000000);
	//t.maxFrame = 1;   //�ő�t���[���w��

	EFFEKSEERLIB::gEfk->SetFPS(60);

	tra.position_.z = -outerPoint;
	t.isLoop = false;    //���[�v���邩
	t.maxFrame = 100;   //�ő�t���[���w��
	t.speed = 1.0;      //�G�t�F�N�g���x ���G�N�X�|�[�g���̑��x��1.0

	//yajirusi
	for (int i = 0; i < cubeSize; i++) {
		for (int j = 0; j < cubeSize; j++) {
			tra.position_.x = -outerPoint + i;
			tra.position_.y = -outerPoint + j;
			//tra.rotate_ = Surface2Rotate(dir);
			DirectX::XMStoreFloat4x4(&(t.matrix), tra.GetWorldMatrix());
			//if(i!=0 && j!=0)
			mt = EFFEKSEERLIB::gEfk->Play("arrow", t);

			//�ő�t���[����ύX���ĕ`�����߂���j���ƍŏ��ɕ`�悵���G�t�F�N�g�����f����Ȃ��󋵂ɂȂ�������
			// ��xFPS��0�ɂ��ċ����ɕ`����~�߂Ă���
			//EFFEKSEERLIB::gEfk->SetFPS(1000000);
			//t.maxFrame = 1;   //�ő�t���[���w��
			//mt = EFFEKSEERLIB::gEfk->Play()
		}
	}
}

void CubeSelectIndicator::StopEffect()
{
	EFFEKSEERLIB::gEfk->SetFPS(FBXSDK_FLOAT_MAX);
	t.maxFrame = 1;   //�ő�t���[���w��
}

void CubeSelectIndicator::StartDrawArrow(Cube::ROTATE_DIR dir, int rotCol)
{
	Transform tra;
	switch (dir)
	{
	case Cube::ROT_UP:
		break;
	case Cube::ROT_DOWN:
		break;
	case Cube::ROT_LEFT:
		break;
	case Cube::ROT_RIGHT:
		break;
	case Cube::ROT_CW:
		break;
	case Cube::ROT_CCW:
		break;
	default:
		break;
	}
	auto DrawArrow = [=](Transform& transform) {
		DirectX::XMStoreFloat4x4(&(t.matrix), transform.GetWorldMatrix());
		mt = EFFEKSEERLIB::gEfk->Play("arrow", t);
		};

	switch (dir)
	{
	case Cube::ROT_UP:
		tra.position_.x = rotCol - outerPoint;
		
		for (int y = 0; y < cubeSize; y += cubeSize-1) {
			for (int z = 0; z < cubeSize; z += cubeSize-1) {
				tra.position_.y = y - outerPoint;
				tra.position_.z = z - outerPoint;

				if (z == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_FRONT, true);
					DrawArrow(tra);
				}
				if (z == cubeSize-1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_BACK, true);
					DrawArrow(tra);
				}
				if (y == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_BOTTOM, true);
					DrawArrow(tra);
				}
				if (y == cubeSize -1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_TOP, true);
					DrawArrow(tra);
				}
			}
		}
		break;
	case Cube::ROT_DOWN:
		tra.position_.x = rotCol - outerPoint;

		for (int y = 0; y < cubeSize; y += cubeSize - 1) {
			for (int z = 0; z < cubeSize; z += cubeSize - 1) {
				tra.position_.y = y - outerPoint;
				tra.position_.z = z - outerPoint;

				if (z == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_FRONT, false);
					DrawArrow(tra);
				}
				if (z == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_BACK, false);
					DrawArrow(tra);
				}
				if (y == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_BOTTOM, false);
					DrawArrow(tra);
				}
				if (y == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_TOP, false);
					DrawArrow(tra);
				}
			}
		}

		break;
	case Cube::ROT_LEFT:
		tra.position_.y = rotCol - outerPoint;

		//�������ʂɋt�]�����Ă����� �X�O�x��]���Ȃ��Ƃ����Ȃ��̂�
		S2R��x���Ή������邩enum�ł���邩
		for (int x = 0; x < cubeSize; x += cubeSize - 1) {
			for (int z = 0; z < cubeSize; z += cubeSize - 1) {
				tra.position_.x = x - outerPoint;
				tra.position_.z = z - outerPoint;

				if (z == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_FRONT, false);
					DrawArrow(tra);
				}
				if (z == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_BACK, false);
					DrawArrow(tra);
				}
				if (x == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_FRONT, false);
					DrawArrow(tra);
				}
				if (x == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_TOP, false);
					DrawArrow(tra);
				}
			}
		}

		break;
		break;
	case Cube::ROT_RIGHT:
		break;
	case Cube::ROT_CW:
		break;
	case Cube::ROT_CCW:
		break;
	default:
		break;
	}
}
