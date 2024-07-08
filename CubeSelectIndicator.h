#pragma once
#include "Engine/GameObject.h"
#include "Cube.h"
#include "./Include/EffekseeLib/EffekseerVFX.h"
#include <string>

using std::string;
using ROTATE_DIR = Cube::ROTATE_DIR;
using SURFACE = Cube::SURFACE;
//�L���[�u���Ǘ�����N���X
class CubeSelectIndicator : public GameObject
{
public:
    CubeSelectIndicator(GameObject* parent);    //�R���X�g���N�^
    ~CubeSelectIndicator();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���
private:
    void SetPosition(float x, float y, float z) {}  //SetPosition�𖳌���
    void SetPosition(int x, int y, int z) {}        //SetPosition�𖳌���

    //=================== �G�t�F�N�g ===================
    //
    // �ǂ���烋�[�v��true�ɂ�����ԂŃG�t�F�N�g�`��J�n�𑖂点���Ƃ��A�r����false�ɂ��ĕ`����I���Ă�
    // �܂�true�ɖ߂��ƕ`�悳��� ���̂��߈ꐶ��������G�t�F�N�g�������Č��݃t���[��������悤�ɂ��Ď蓮���[�v���s��
    //
    //==================================================
private:
    std::shared_ptr<EFFEKSEERLIB::EFKTransform> mt;
    EFFEKSEERLIB::EFKTransform t;
    const float DEFAULT_EFFECT_SPEED;
    enum EFFECT_STATE {
        STOP,
        NEXT_START,
        DRAWING
    }arrowState;
    int nowArrowFrame;
    const int ARROW_FRAME;
    const string EFF_ID_ARROW;

    //�G�t�F�N�g���~�߂�
    // FPS�ƍő�t���[����ύX���Ē������ŃG�t�F�N�g�𗬂����ƂŎ������Ă��邽�߁A
    // �ĕ`��͎��̃t���[���ȍ~�ł��Ȃ��ƌ��ʖ��� ����
    void StopDrawArrow();

    //�G�t�F�N�g���Đ�����
    void StartDrawArrow(Cube::ROTATE_DIR dir, int rotCol);
    void DrawArrow(Transform& tra); //����StartDrawArrow�֐���Parts

private:
    int hModel;
    int cubeSize;
    float outerPoint;   //�ł��O���̃L���[�u�̒��S���W
    int rotCol;
    //�z�u�ʂƖ��̉�]
    //surface:�`���
    //side:������������̂�`��ʂ��炻�̖ʂ̕������w���悤�ɂ���
    XMFLOAT3 Surface2Rotate(SURFACE surface, SURFACE side);
    XMFLOAT3 Surface2Rotate(SURFACE surface);

    template<class T>
    T Half(T value) { return value / 2.0f; }

private:
    void DrawSurface(Transform& tra, Cube::SURFACE surface, bool isOuter = true);
public:

    //�`�惂�[�h
    enum DRAW_MODE {
        DRAWMODE_SINGLE,
        DRAWMODE_CIRCLE
    };

private:
    Cube::ROTATE_DIR direction;
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

    void SetDrawMode(DRAW_MODE mode);

    //=================== �~�`�`�� ===================
    
    //�O�ʂ��猩�����̉�]�������w��
    void SetCubeRotate(Cube::ROTATE_DIR dir);
    
    //��]�� �����O��X0Y0Z0
    void SetRotateColumn(int col);

public:
    void DebugDraw(SURFACE sur, SURFACE sid);
};

//�G�t�F�N�g�̍Đ���~�֐��̔ėp���͂��Ă��Ȃ� �����̃G�t�F�N�g�g�p���Ă���킯�ł͂Ȃ��̂Ō��󂵂Ȃ��ق����͂₢