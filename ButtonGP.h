#pragma once
#include "Button.h"
//タイトルのボタンを管理するクラス
class ButtonGP : public Button
{
public:
    ButtonGP(GameObject* parent);    //コンストラクタ
    ~ButtonGP();                     //デストラクタ
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