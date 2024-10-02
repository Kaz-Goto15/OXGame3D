#pragma once
#include <string>
#include "Engine/GameObject.h"
#include "Screen.h"
#include <ft2build.h>
class ButtonEx;
class Frame;

//クレジット画面を管理するクラス
class ButtonExampleScreen : public Screen
{
    enum PIC {
        PIC_BACKGROUND,
        PIC_DESCRIPTION,
        PIC_MAX
    };
    int hPict_[PIC_MAX];

    Frame* pFrame;       //枠
    float framePosY;  //フレーム中心点

    ButtonEx* backBtn;  //もどるﾎﾞﾀﾝ
    bool unselected;

    //半分にする 型をそのまんま返すためintなどは自動切り捨て
    template <class T>
    T Half(T value) {
        return (value / 2.0f);
    }

    //フォントテストをここでやっている
    //FT_Library library;
    
public:
    ButtonExampleScreen(GameObject* parent);
    ~ButtonExampleScreen();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void ButtonAct(int hAct);
};