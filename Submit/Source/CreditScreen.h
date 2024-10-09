#pragma once
#include <string>
#include "Engine/GameObject.h"
#include "Screen.h"
class ButtonEx;
class Frame;

//�N���W�b�g��ʂ��Ǘ�����N���X
class CreditScreen : public Screen
{
    enum PIC {
        PIC_BACKGROUND,
        PIC_DESCRIPTION,
        PIC_MAX
    };
    int hPict_[PIC_MAX];

    Frame* pFrame;       //�g
    float framePosY;  //�t���[�����S�_

    ButtonEx* backBtn;  //���ǂ�����
    bool unselected;

    //�����ɂ��� �^�����̂܂�ܕԂ�����int�Ȃǂ͎����؂�̂�
    template <class T>
    T Half(T value) {
        return (value / 2.0f);
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