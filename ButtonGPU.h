#pragma once
#include "ButtonOld.h"
//�^�C�g���̃{�^�����Ǘ�����N���X
class ButtonGPU : public ButtonOld
{
public:
    ButtonGPU(GameObject* parent);    //�R���X�g���N�^
    ~ButtonGPU();                     //�f�X�g���N�^
    std::string LinkImageFile(STATE state) override;
    void Init() override;
private:
    void DrawIdle() override;
    void DrawSelect() override;
    void DrawPush() override;
    void DrawSelected() override;
    int hButtonShadow_;
    int shadowXY;
};