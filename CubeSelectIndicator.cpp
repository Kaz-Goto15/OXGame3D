#include "CubeSelectIndicator.h"
#include "./ModelLoader.h"
#include "Engine/Model.h"

XMFLOAT3 CubeSelectIndicator::Surface2Rotate(Cube::SURFACE surface)
{
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

//�R���X�g���N�^
CubeSelectIndicator::CubeSelectIndicator(GameObject* parent)
    :GameObject(parent, "CubeSelectIndicator")
{
    hModel = -1;
    cubeSize = 0;
    drawMode = DRAWMODE_CIRCLE;
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
    EFFEKSEERLIB::EFKTransform t;
    DirectX::XMStoreFloat4x4(&(t.matrix), transform_.GetWorldMatrix());
    t.isLoop = true;    //���[�v���邩
    t.maxFrame = 100;   //�ő�t���[���w��
    t.speed = 1.0;      //�G�t�F�N�g���x ���G�N�X�|�[�g���̑��x��1.0
    mt = EFFEKSEERLIB::gEfk->Play("arrow", t);

}

//�X�V
void CubeSelectIndicator::Update()
{
    DirectX::XMStoreFloat4x4(&(mt->matrix), this->GetWorldMatrix());
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
        case CubeSelectIndicator::ROT_UP:
            break;
        case CubeSelectIndicator::ROT_DOWN:
            break;
        case CubeSelectIndicator::ROT_LEFT:
        case CubeSelectIndicator::ROT_RIGHT:
            break;
        case CubeSelectIndicator::ROT_CW:
        case CubeSelectIndicator::ROT_CCW:
            tra.position_.z = rotCol - Half((float)(cubeSize - 1));
            for (int i = 0; i < cubeSize; i++) {
                tra.position_.x = i - Half((float)(cubeSize - 1));

                //��ʕ`��
                tra.position_.y = abs(Half((float)(cubeSize - 1)));
                tra.rotate_ = Surface2Rotate(Cube::SURFACE_TOP);
                Model::SetTransform(hModel, tra);
                Model::Draw(hModel);

                //���ʕ`��
                tra.position_.y = -abs(Half((float)(cubeSize - 1)));
                tra.rotate_ = Surface2Rotate(Cube::SURFACE_BOTTOM);
                Model::SetTransform(hModel, tra);
                Model::Draw(hModel);

                tra.position_.y = i - Half((float)(cubeSize - 1));

                //�E�ʕ`��
                tra.position_.x = abs(Half((float)(cubeSize - 1)));
                tra.rotate_ = Surface2Rotate(Cube::SURFACE_RIGHT);
                Model::SetTransform(hModel, tra);
                Model::Draw(hModel);

                //���ʕ`��
                tra.position_.x = -abs(Half((float)(cubeSize - 1)));
                tra.rotate_ = Surface2Rotate(Cube::SURFACE_LEFT);
                Model::SetTransform(hModel, tra);
                Model::Draw(hModel);
            }
            break;
        }

    }
}

//�J��
void CubeSelectIndicator::Release()
{
}

void CubeSelectIndicator::SetSurface(Cube::SURFACE surface)
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
    EFFEKSEERLIB::EFKTransform t;

    //tra.position_.x = abs((cubeSize - 1) / 2.0f);
    //tra.rotate_ = Surface2Rotate(Cube::SURFACE_RIGHT);
    //DirectX::XMStoreFloat4x4(&(t.matrix), tra.GetWorldMatrix());
    //mt = EFFEKSEERLIB::gEfk->Play("arrow", t);
    tra.position_.x = -abs((cubeSize - 1) / 2.0f);
    //tra.position_ = { 0,0,0 };
    tra.rotate_ = Surface2Rotate(Cube::SURFACE_TOP);
    DirectX::XMStoreFloat4x4(&(t.matrix), tra.GetWorldMatrix());
    t.isLoop = false;    //���[�v���邩
    t.maxFrame = 100;   //�ő�t���[���w��
    t.speed = 1.0;      //�G�t�F�N�g���x ���G�N�X�|�[�g���̑��x��1.0
    mt = EFFEKSEERLIB::gEfk->Play("arrow", t);

    //transform_ = tra;
    
}
