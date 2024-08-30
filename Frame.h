#pragma once
#include "Engine/GameObject.h"

//�g���Ǘ�����N���X
class Frame : public GameObject
{
    enum FRAME_W {
        W_LEFT= 0,
        W_CENTER,
        W_RIGHT,
        W_MAX,
    };
    enum FRAME_H {
        H_TOP = 0,
        H_CENTER,
        H_BOTTOM,
        H_MAX
    };
    enum MODE {
        AUTO_ASPECT,    //��ʃT�C�Y�ɉ����Ęg���ό`���܂��BFrame�N���X��scale.x,y���e�����̉�ʃT�C�Y�ɑ΂��銄���Ƃ��Ĕ͈͂��w�肵�܂��B
        CONST_MARGIN,   //��ʒ[����̋������w�肵�܂��BFrame�N���X��Transform�S�Ă𖳎����܂��B��ʃT�C�Y���ω������ꍇ�A��ʒ[����g�܂ł̋����͕ς��܂��񂪁A���̖ʐς͕ω����܂��B���g��mUp,mRight,mDown,mLeft���Q�Ƃ��܂��B
        CONST_SIZE,   //�Œ�l�ŃT�C�Y���w�肵�܂��BFrame�N���X��Scale�𖳎����܂��B��ʃT�C�Y���ω������ꍇ�A�g�͕ό`���܂��񂪁A�g�̍��W�̂ݕω����܂��B���g��width, height���Q�Ƃ��܂��B
    };
    std::string filePath;
    int grid;
    int hImgFrame;
    Transform tra[FRAME_H::H_MAX][FRAME_W::W_MAX];

    //��E�����Ń}�[�W�����w��
    void TransformFrame(XMINT4 margin) { TransformFrame(margin.x, margin.y, margin.z, margin.w); }
    //��E�����Ń}�[�W�����w��
    void TransformFrame(int up, int right, int down, int left);

public:
    Frame(GameObject* parent);    //�R���X�g���N�^
    ~Frame();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���

    void SetMargin(int up, int right, int down, int left);
    void ChangeTheme(std::string _filePath, int _grid);

    /// <summary>
    /// �g�`��̃��[�h��ύX
    /// </summary>
    /// <param name="_mode">���[�h�I��(�Œ�l)</param>
    /// <param name="value1">MARGIN�̏ꍇ�F��]���w�� SIZE�̏ꍇ�F</param>
    /// <param name="value2"></param>
    /// <param name="value3"></param>
    /// <param name="value4"></param>
    void ChangeMode(MODE _mode, int value1, int value2, int value3, int value4);
    void ChangeMode(MODE _mode, float xRatio, float yRatio);

    template <class T>
    float Half(T value) { return (float)value / 2.0f; }
};