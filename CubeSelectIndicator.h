#pragma once
#include "Engine/GameObject.h"
#include "Cube.h"
#include "./Include/EffekseeLib/EffekseerVFX.h"
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

    //�O���猩���Ƃ��̉�]����
    enum ROTATE_DIR {
        ROT_UP,
        ROT_DOWN,
        ROT_LEFT,
        ROT_RIGHT,
        ROT_CW,
        ROT_CCW
    };
private:
    ROTATE_DIR direction;
public:
    //�`�惂�[�h
    enum DRAW_MODE {
        DRAWMODE_SINGLE,
        DRAWMODE_CIRCLE
    }drawMode;
    /// <summary>
    /// �`��ʂ̕ύX
    /// </summary>
    /// <param name="surface">��enum</param>
    void SetSurface(Cube::SURFACE surface);

    //�L���[�u�̑傫���w�� �Ⴆ��3x3�Ȃ�3������
    void SetCubeScale(int scale);

    void SetDrawMode(DRAW_MODE mode) { drawMode = mode; }
    //�O�ʂ��猩�����̉�]�������w��
    void SetCubeRotate(ROTATE_DIR dir);
    //�G�t�F�N�g
    std::shared_ptr<EFFEKSEERLIB::EFKTransform> mt;
};