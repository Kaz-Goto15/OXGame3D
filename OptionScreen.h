#pragma once
#include <string>
#include "Engine/GameObject.h"
#include "Screen.h"
class DebugText;
class ButtonGP;
//クレジット画面を管理するクラス
class OptionScreen : public Screen
{
    enum PIC {
        PIC_BACKGROUND,
        PIC_BASIC_FRAME_TEX,
        //PIC_DESCRIPTION,
        PIC_MAX
    };
    int hPict_[PIC_MAX];

    XMINT4 frameMargin;  //上右下左
    float frameScale;    //可変フレーム拡大率
    XMFLOAT3 framePos;

    DebugText* debugtext;
    ButtonGP* backBtn;
    ButtonGP* testBtn[7];
    std::string debugStr[20];
    void UpdateStr();
public:
    OptionScreen(GameObject* parent);
    ~OptionScreen();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void ButtonAct(int hAct);
};