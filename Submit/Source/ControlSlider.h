#pragma once
#include "Engine/GameObject.h"

//�X���C�_�[���Ǘ�����N���X
class ControlSlider : public GameObject
{
private:
    int trackWidth, trackHeight;  //�g���b�N��H,W
    int thumbSize;  //�{�^���T�C�Y
    const int defScrX = 1280;
    const int defScrY = 720;
    int value, minValue, maxValue; //�l�A�ő�ŏ�
    POINT thumbPos; //�� �T���ʒu
    float rc = 0;
    //������O���b�h�`���ɂ��ł���悤��
    //bool freeMove;
    //int gridNum;

    enum IMAGE {
        SLIDER_BK,
        SLIDER_FORE,
        SLIDER_THUMB,
        MAX
    };
    int hImg_[IMAGE::MAX];
    XMFLOAT3 imgSize[IMAGE::MAX];	//�摜�T�C�Y
    Transform traImage[IMAGE::MAX];	//�e�ό`���
    XMFLOAT2 sliderRangeLU, sliderRangeRB;
    float trackWRatio= 0, trackHRatio = 0;

    //1/2
    template <class T>
    T Half(T pValue) {
        return pValue /= 2.0f;
    }
    //�l���͈͓���
    template <class T>
    bool Between(T value, T min, T max) {
        return (min <= value && value <= max);
    }
public:
    int GetValue() { return value; }
    bool IsEntered();   //�}�E�X�͈͓����𔻒�
    void SetImage(IMAGE img, std::string fileName);
    void SetHeight(int height);
    void SetWidth(int width);
protected:
    //virtual void InitValue() = 0;   //���ɍő�ŏ��ƌ��ݒl������������R�[�h������

public:
    ControlSlider(GameObject* parent);    //�R���X�g���N�^
    ~ControlSlider();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���
    std::string GetDebugStr(int debugNum);
};

/*
�f�t�H���g�̃E�B���h�E�T�C�Y�ƃg���b�N���A�g���b�N�������w��
�E�B���h�E�T�C�Y�ƃg���b�N���A�E�B���h�E�T�C�Y�ƃg���b�N�������炻�ꂼ�ꊄ�����v�Z
scale,pos�����ߍ��W�w��

�E�w����W�𒆐S�ɂ���֐��A�����E���� void SetCenterPos(float x, float y, hAlignment);
�E�����Ɗ�����w�肵�ĕ��w�肷��֐� void SetLength(int len, int stdWidth = SysCon::windowWidth);
�E�͈͓�����Ԃ��֐� IsEntered(); owari
*/