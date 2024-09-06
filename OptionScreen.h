#pragma once
#include <string>
#include "Engine/GameObject.h"
#include "Screen.h"
class DebugText;
class ButtonGP;
class ControlSlider;
class Frame;
//クレジット画面を管理するクラス
class OptionScreen : public Screen
{
    int hBg_;
    Frame* pFrame;
    ButtonGP* backBtn;

    DebugText* debugtext;
    ButtonGP* testBtn[7];
    std::string debugStr[20];
    ControlSlider* pSlider;
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