#include "CubeSelectIndicator.h"
#include "./ModelLoader.h"
#include "Engine/Model.h"
#include "SystemConfig.h"

XMFLOAT3 CubeSelectIndicator::Surface2Rotate(SURFACE surface)
{
	return Surface2Rotate(surface, surface);	//�P����]�̒l��Ԃ�
}
XMFLOAT3 CubeSelectIndicator::Surface2Rotate(SURFACE surface, SURFACE side)
{
	//Vec(0,0,1)�֌���pos0,0,0�Ɉʒu���������]������0.5���炷�̂�����ʂň��肵���������A
	//�����0,0,1�֌���pos0,0.5,0�Ɉʒu������𒼐ډ�]������

	//���g�Ɠ����ʂ܂��͔��Ζʂ̏ꍇ�A�P����]�����������̒l��Ԃ�
	switch (surface)
	{
	case Cube::SURFACE_TOP:
		switch (side)	//�P����]�͉����Ɠ���
		{
		case Cube::SURFACE_TOP:		break;
		case Cube::SURFACE_BOTTOM:	break;
		case Cube::SURFACE_LEFT:    return { 0,-90,0 };
		case Cube::SURFACE_RIGHT:   return { 0,90,0 };
		case Cube::SURFACE_FRONT:   return { 0,180,0 };
		case Cube::SURFACE_BACK:	break;
		}
		return { 0,0,0 };
	case Cube::SURFACE_BOTTOM:
		switch (side)	//�P����]�͑O���Ɠ���
		{
		case Cube::SURFACE_TOP:		break;
		case Cube::SURFACE_BOTTOM:	break;
		case Cube::SURFACE_LEFT:    return { 180,90,0 };
		case Cube::SURFACE_RIGHT:   return { 180,-90,0 };
		case Cube::SURFACE_FRONT:   break;
		case Cube::SURFACE_BACK:	return { 180,180,0 };
		}
		return { 180,0,0 };
	case Cube::SURFACE_LEFT:
		switch (side)	//�P����]�͉����Ɠ���
		{
		case Cube::SURFACE_TOP:		return { -90,0,90 };
		case Cube::SURFACE_BOTTOM:	return { 90,0,90 };
		case Cube::SURFACE_LEFT:    break;
		case Cube::SURFACE_RIGHT:	break;
		case Cube::SURFACE_FRONT:   return { 180,0,90 };
		case Cube::SURFACE_BACK:	break;
		}
		return { 0,0,90 };
	case Cube::SURFACE_RIGHT:
		switch (side)	//�P����]�͉����Ɠ���
		{
		case Cube::SURFACE_TOP:		return { -90,0,-90 };
		case Cube::SURFACE_BOTTOM:	return { 90,0,-90 };
		case Cube::SURFACE_LEFT:    break;
		case Cube::SURFACE_RIGHT:	break;
		case Cube::SURFACE_FRONT:   return { 180,0,-90 };
		case Cube::SURFACE_BACK:	break;
		}
		return { 0,0,-90 };
	case Cube::SURFACE_FRONT:
		switch (side)	//�P����]�͏㑤�Ɠ���
		{
		case Cube::SURFACE_TOP:		break;
		case Cube::SURFACE_BOTTOM:	return { 90,0,180 };
		case Cube::SURFACE_LEFT:    return { 0,-90,90 };
		case Cube::SURFACE_RIGHT:   return { 0,90,-90 };
		case Cube::SURFACE_FRONT:   break;
		case Cube::SURFACE_BACK:	break;
		}
		return { -90,0,0 };
	case Cube::SURFACE_BACK:
		switch (side)	//�P����]�͉����Ɠ���
		{
		case Cube::SURFACE_TOP:		return { -90,0,180 };
		case Cube::SURFACE_BOTTOM:	break;
		case Cube::SURFACE_LEFT:    return { 0,-90,-90 };
		case Cube::SURFACE_RIGHT:   return { 0,90,90 };
		case Cube::SURFACE_FRONT:   break;
		case Cube::SURFACE_BACK:	break;
		}
		return { 90,0,0 };
	}
}

//�R���X�g���N�^
CubeSelectIndicator::CubeSelectIndicator(GameObject* parent):
	GameObject(parent, "CubeSelectIndicator"),
	mt(nullptr), DEFAULT_EFFECT_SPEED(1.0f),
	arrowState(EFFECT_STATE::STOP),nowArrowFrame(0),ARROW_FRAME(100),EFF_ID_ARROW("arrow"),
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
	// 
	//�G�t�F�N�g
	EFFEKSEERLIB::gEfk->AddEffect(EFF_ID_ARROW, "Effect\\arrow.efk");
	t.speed = DEFAULT_EFFECT_SPEED;      //�G�t�F�N�g���x ���G�N�X�|�[�g���̑��x��1.0
	t.isLoop = false;

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

		switch (arrowState)
		{
		case CubeSelectIndicator::STOP:
			arrowState = EFFECT_STATE::NEXT_START;
			break;
		case CubeSelectIndicator::NEXT_START:
			StartDrawArrow(direction, rotCol);
			arrowState = EFFECT_STATE::DRAWING;
			break;
		case CubeSelectIndicator::DRAWING:
			nowArrowFrame++;
			if (nowArrowFrame > ARROW_FRAME) {
				nowArrowFrame = 0;
				StartDrawArrow(direction, rotCol);
			}
			break;
		}
	}
}

//=================== �G�t�F�N�g ===================

void CubeSelectIndicator::StopDrawArrow()
{
	EFFEKSEERLIB::gEfk->SetFPS(FBXSDK_FLOAT_MAX);	//FPS�𒴑��ɂ���
	t.maxFrame = 1;   //�ő�t���[����1�ɂ��đ��I��
	t.speed = FBXSDK_FLOAT_MAX;	//���x���ő�ɂ���

	arrowState = EFFECT_STATE::STOP;
	nowArrowFrame = 0;
}

void CubeSelectIndicator::StartDrawArrow(Cube::ROTATE_DIR dir, int rotCol)
{
	Transform tra;

	EFFEKSEERLIB::gEfk->SetFPS(SystemConfig::GetFPS());
	t.maxFrame = ARROW_FRAME;			//�ő�t���[���w��
	t.speed = DEFAULT_EFFECT_SPEED;     //�G�t�F�N�g���x�����Z�b�g

	switch (dir)
	{
	case Cube::ROT_UP:
		tra.position_.x = rotCol - outerPoint;

		for (int y = 0; y < cubeSize; y += cubeSize - 1) {
			for (int z = 0; z < cubeSize; z += cubeSize - 1) {
				tra.position_.y = y - outerPoint;
				tra.position_.z = z - outerPoint;

				if (z == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_FRONT, SURFACE::SURFACE_TOP);
					DrawArrow(tra);
				}
				if (z == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_BACK, SURFACE::SURFACE_BOTTOM);
					DrawArrow(tra);
				}
				if (y == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_BOTTOM, SURFACE::SURFACE_FRONT);
					DrawArrow(tra);
				}
				if (y == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_TOP, SURFACE::SURFACE_BACK);
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
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_FRONT, SURFACE::SURFACE_BOTTOM);
					DrawArrow(tra);
				}
				if (z == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_BACK, SURFACE::SURFACE_TOP);
					DrawArrow(tra);
				}
				if (y == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_BOTTOM, SURFACE::SURFACE_BACK);
					DrawArrow(tra);
				}
				if (y == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_TOP, SURFACE::SURFACE_FRONT);
					DrawArrow(tra);
				}
			}
		}

		break;

	case Cube::ROT_LEFT:
		tra.position_.y = rotCol - outerPoint;

		for (int x = 0; x < cubeSize; x += cubeSize - 1) {
			for (int z = 0; z < cubeSize; z += cubeSize - 1) {
				tra.position_.x = x - outerPoint;
				tra.position_.z = z - outerPoint;

				if (z == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_FRONT, SURFACE::SURFACE_LEFT);
					DrawArrow(tra);
				}
				if (z == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_BACK, SURFACE::SURFACE_RIGHT);
					DrawArrow(tra);
				}
				if (x == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_LEFT, SURFACE::SURFACE_BACK);
					DrawArrow(tra);
				}
				if (x == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_RIGHT, SURFACE::SURFACE_FRONT);
					DrawArrow(tra);
				}
			}
		}

		break;

	case Cube::ROT_RIGHT:
		tra.position_.y = rotCol - outerPoint;

		for (int x = 0; x < cubeSize; x += cubeSize - 1) {
			for (int z = 0; z < cubeSize; z += cubeSize - 1) {
				tra.position_.x = x - outerPoint;
				tra.position_.z = z - outerPoint;

				if (z == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_FRONT, SURFACE::SURFACE_RIGHT);
					DrawArrow(tra);
				}
				if (z == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_BACK, SURFACE::SURFACE_LEFT);
					DrawArrow(tra);
				}
				if (x == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_LEFT, SURFACE::SURFACE_FRONT);
					DrawArrow(tra);
				}
				if (x == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_RIGHT, SURFACE::SURFACE_BACK);
					DrawArrow(tra);
				}
			}
		}

		break;
	case Cube::ROT_CW:
		tra.position_.z = rotCol - outerPoint;

		for (int x = 0; x < cubeSize; x += cubeSize - 1) {
			for (int y = 0; y < cubeSize; y += cubeSize - 1) {
				tra.position_.x = x - outerPoint;
				tra.position_.y = y - outerPoint;

				if (y == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_BOTTOM, SURFACE::SURFACE_LEFT);
					DrawArrow(tra);
				}
				if (y == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_TOP, SURFACE::SURFACE_RIGHT);
					DrawArrow(tra);
				}
				if (x == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_LEFT, SURFACE::SURFACE_TOP);
					DrawArrow(tra);
				}
				if (x == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_RIGHT, SURFACE::SURFACE_BOTTOM);
					DrawArrow(tra);
				}
			}
		}

		break;

	case Cube::ROT_CCW:
		tra.position_.z = rotCol - outerPoint;

		for (int x = 0; x < cubeSize; x += cubeSize - 1) {
			for (int y = 0; y < cubeSize; y += cubeSize - 1) {
				tra.position_.x = x - outerPoint;
				tra.position_.y = y - outerPoint;

				if (y == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_BOTTOM, SURFACE::SURFACE_RIGHT);
					DrawArrow(tra);
				}
				if (y == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_TOP, SURFACE::SURFACE_LEFT);
					DrawArrow(tra);
				}
				if (x == 0) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_LEFT, SURFACE::SURFACE_BOTTOM);
					DrawArrow(tra);
				}
				if (x == cubeSize - 1) {
					tra.rotate_ = Surface2Rotate(Cube::SURFACE_RIGHT, SURFACE::SURFACE_TOP);
					DrawArrow(tra);
				}
			}
		}

		break;

	}
}

void CubeSelectIndicator::DrawArrow(Transform& tra)
{
	DirectX::XMStoreFloat4x4(&(t.matrix), tra.GetWorldMatrix());
	mt = EFFEKSEERLIB::gEfk->Play("arrow", t);
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
	StopDrawArrow();
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

void CubeSelectIndicator::SetDrawMode(DRAW_MODE mode)
{
	drawMode = mode;
	StopDrawArrow();
}

//=================== �~�`�`�� ===================
void CubeSelectIndicator::SetCubeRotate(ROTATE_DIR dir)
{
	if (direction != dir) {
		direction = dir;
		StopDrawArrow();
	}
}

void CubeSelectIndicator::SetRotateColumn(int col)
{
	if (rotCol != col) {
		rotCol = col;
		StopDrawArrow();
	}
}

void CubeSelectIndicator::DebugDraw(SURFACE sur, SURFACE sid)
{
	Transform tra;
	tra.rotate_ = Surface2Rotate(sur, sid);
	
	DirectX::XMStoreFloat4x4(&(t.matrix), tra.GetWorldMatrix());
	mt = EFFEKSEERLIB::gEfk->Play(EFF_ID_ARROW, t);
}
