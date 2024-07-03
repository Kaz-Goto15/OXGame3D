#pragma once
#include "Engine/GameObject.h"

//�L���[�u���Ǘ�����N���X
class Cube : public GameObject
{
    enum MODEL_ENUM {
        CUBE,
        FRONT_COLOR,
        BACK_COLOR,
        LEFT_COLOR,
    };
public:
    enum MARK {
        MARK_BLANK = -1,
        MARK_O,
        MARK_X,
        MARK_MAX
    };

    enum ROTATE_DIR {
        ROT_UP,
        ROT_DOWN,
        ROT_LEFT,
        ROT_RIGHT,
        ROT_CW,
        ROT_CCW
    };

    enum SURFACE {
        SURFACE_TOP,
        SURFACE_BOTTOM,
        SURFACE_LEFT,
        SURFACE_RIGHT,
        SURFACE_FRONT,
        SURFACE_BACK,
        SURFACE_MAX
    };

private:
    int hModelCube;                 //�L���[�u���̂̃��f���f�[�^�n���h��
    int hModelMark[MARK_MAX];       //�}�[�N�̃��f���f�[�^�n���h��
    MARK cubeData_[SURFACE_MAX];    //�L���[�u���ʂ̃}�[�N�f�[�^
    XMFLOAT3 Surface2Rotate(SURFACE surface);
public:
    Cube(GameObject* parent);    //�R���X�g���N�^
    ~Cube();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���

    void SwapData(ROTATE_DIR dir);    //�O���猩����]�������w�肵�A�e�ʂ̃f�[�^�����ւ���
    void SetPoint(XMINT3 point, float outerPoint);  //�ł��O���̃L���[�u��
    void SetMark(SURFACE surface, MARK mark);
    MARK GetMark(SURFACE surface) { return cubeData_[surface]; }
};