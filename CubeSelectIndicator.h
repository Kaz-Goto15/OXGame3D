#pragma once
#include "Engine/GameObject.h"
#include "Cube.h"
#include "./Include/EffekseeLib/EffekseerVFX.h"

using ROTATE_DIR = Cube::ROTATE_DIR;
//�L���[�u���Ǘ�����N���X
class CubeSelectIndicator : public GameObject
{
private:
    int hModel;
    int cubeSize;
    float outerPoint;   //�ł��O���̃L���[�u�̒��S���W
    int rotCol;

    XMFLOAT3 Surface2Rotate(Cube::SURFACE surface);

    template<class T>
    T Half(T value) { return value / 2.0f; }

public:
    CubeSelectIndicator(GameObject* parent);    //�R���X�g���N�^
    ~CubeSelectIndicator();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���

    //�`�惂�[�h
    enum DRAW_MODE {
        DRAWMODE_SINGLE,
        DRAWMODE_CIRCLE
    };

private:
    Cube::ROTATE_DIR direction;
    void SetPosition(float x, float y, float z) {}  //SetPosition�𖳌���
    void SetPosition(int x, int y, int z) {}  //SetPosition�𖳌���
    DRAW_MODE drawMode;

public:
    //=================== �P��`�� ===================

    /// �P��`��̏���ύX
    /// point:�L���[�u�̏ꏊ �����O��0,0,0 �E�㉜��2,2,2
    /// surface:�`���
    void SetDrawPoint(XMINT3 point, Cube::SURFACE surface);

    /// �P��`��̏���ύX �ʏ��͍X�V���Ȃ��o�[�W����
    /// point:�L���[�u�̏ꏊ �����O��0,0,0 �E�㉜��2,2,2
    void SetDrawPoint(XMINT3 point);

    /// �P��`��̏���ύX �I���ꏊ�͍X�V���Ȃ��o�[�W����
    /// surface:�`���
    void SetDrawPoint(Cube::SURFACE surface);

    //�L���[�u�̑傫���w�� �Ⴆ��3x3�Ȃ�3������
    void SetCubeScale(int scale);

    void SetDrawMode(DRAW_MODE mode) { drawMode = mode; }

    //=================== �~�`�`�� ===================
    //�O�ʂ��猩�����̉�]�������w��
    void SetCubeRotate(Cube::ROTATE_DIR dir);
    
    //��]�� �����O��X0Y0Z0
    void SetRotateColumn(int col) { rotCol = col; }
    //�G�t�F�N�g
    std::shared_ptr<EFFEKSEERLIB::EFKTransform> mt;
};