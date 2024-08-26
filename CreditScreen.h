#pragma once
#include <string>
#include "Engine/GameObject.h"
#include "Screen.h"
class ButtonGP;
//�N���W�b�g��ʂ��Ǘ�����N���X
class CreditScreen : public Screen
{
    enum PIC {
        PIC_BACKGROUND,
        PIC_BASIC_FRAME_TEX,
        PIC_DESCRIPTION,
        PIC_MAX
    };
    int hPict_[PIC_MAX];

    XMINT4 frameMargin;  //��E����
    float frameScale;    //�σt���[���g�嗦
    XMFLOAT3 framePos;  //�t���[�����S�_
    int frameLength;    //�t���[���摜�𕪊������Ƃ���1�ӂ̒���
    ButtonGP* backBtn;  //���ǂ�����

    //�����ɂ��� �^�����̂܂�ܕԂ�����int�Ȃǂ͎����؂�̂�
    template <class T>
    T Half(T value) {
        return (value / 2);
    }

public:
    CreditScreen(GameObject* parent);
    ~CreditScreen();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void ButtonAct(int hAct);
};