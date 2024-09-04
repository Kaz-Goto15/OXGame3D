#pragma once
#include "Engine/GameObject.h"

class DebugText;

//�g���Ǘ�����N���X
class Frame : public GameObject
{
    //DebugText* debugText;
    //std::string debStr[5];
    //int hPt;
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
public:
    enum MODE {
        AUTO_ASPECT,    //(������)��ʃT�C�Y�ɉ����Ęg���ό`���܂��BFrame�N���X��scale.x,y���e�����̉�ʃT�C�Y�ɑ΂��銄���Ƃ��Ĕ͈͂��w�肵�܂��B
        CONST_MARGIN,   //��ʒ[����̋������w�肵�܂��B    Frame�N���X��Transform�S�Ă𖳎����܂��B           ��ʃT�C�Y���ω������ꍇ�A��ʒ[����g�܂ł̋����͕ς��܂��񂪁A���̖ʐς͕ω����܂��B���g��mUp,mRight,mDown,mLeft���Q�Ƃ��܂��B
        CONST_SIZE,     //(������)position�𒆐S�Ƃ��āA�Œ�l�ŃT�C�Y���w�肵�܂��B��̏ꍇ�A���オ1px�����Ȃ�܂��BFrame�N���X��Scale�𖳎����܂��B ��ʃT�C�Y���ω������ꍇ�A�g�͕ό`���܂��񂪁A�g�̍��W�̂ݕω����܂��B���g��width, height���Q�Ƃ��܂��B
    };
private:
    MODE mode_;
    std::string filePath_;
    int grid_;
    int hImgFrame_;
    int mUp, mRight, mDown, mLeft;
    int sWidth, sHeight;
    Transform tra[FRAME_H::H_MAX][FRAME_W::W_MAX];

    void Init();
    void UpdateDrawData();

    template <class T>
    float Half(T value) { return (float)value / 2.0f; }

public:
    Frame(GameObject* parent);    //�R���X�g���N�^
    ~Frame();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��(���������Ȃ�)
    void Release() override;    //���

    void DrawFrame();           //�`��(�Ăяo�����ŌĂяo��)
    void ChangeTheme(std::string _filePath, int _grid);

    /// <summary>
    /// �g�`��̃��[�h��ύX
    /// </summary>
    /// <param name="_mode">���[�h�I��(�Œ�l)</param>
    /// <param name="value1">MARGIN�̏ꍇ�F��]���w�� SIZE�̏ꍇ�F����</param>
    /// <param name="value2">MARGIN�̏ꍇ�F�E�]���w�� SIZE�̏ꍇ�F�c��</param>
    /// <param name="value3">MARGIN�̏ꍇ�F���]���w�� SIZE�̏ꍇ�F��(�l�͖��������)</param>
    /// <param name="value4">MARGIN�̏ꍇ�F���]���w�� SIZE�̏ꍇ�F��(�l�͖��������)</param>
    void ChangeMode(MODE _mode, int value1, int value2, int value3=0, int value4=0);

    /// <summary>
    /// �g�`��̃��[�h��ύX
    /// </summary>
    /// <param name="_mode">���[�h�I��(�Œ�l)</param>
    /// <param name="xRatio">X�����w��</param>
    /// <param name="yRatio">Y�����w��</param>
    void ChangeMode(MODE _mode, float xRatio, float yRatio);
};