#pragma once
#include "ButtonOld.h"
//タイトルのボタンを管理するクラス
class ButtonGPU : public ButtonOld
{
public:
    ButtonGPU(GameObject* parent);    //コンストラクタ
    ~ButtonGPU();                     //デストラクタ
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