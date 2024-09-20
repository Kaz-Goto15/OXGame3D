#pragma once
#include <string>
#include <vector>
#include "Engine/GameObject.h"
#include "Screen.h"
class DebugText;
class ButtonEx;
class ControlSlider;
class Frame;
//クレジット画面を管理するクラス
class OptionScreen : public Screen
{
    int hBg_;
    Frame* pFrame;

    DebugText* debugtext;

    enum BUTTON_PROC {
        BTN_RESET,
        BTN_BACK,
        BTN_SIZE360p,
        BTN_SIZE720p,
        BTN_SIZE900p,
        BTN_SIZE1080p,
        BTN_FULLSCREEN,
        BTN_OFF_FULLSCREEN,
        BTN_INI_SAVE,
        BTN_MAX,
    };
    struct BUTTON_DATA
    {
        std::string text;
        
    };
    std::vector<ButtonEx*> buttons;
    XMFLOAT2 btnSize;
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