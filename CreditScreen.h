#pragma once
#include <string>
#include "Engine/GameObject.h"
#include "Screen.h"
class ButtonGP;
class Frame;

//クレジット画面を管理するクラス
class CreditScreen : public Screen
{
    enum PIC {
        PIC_BACKGROUND,
        PIC_DESCRIPTION,
        PIC_MAX
    };
    int hPict_[PIC_MAX];

    Frame* pFrame;       //枠
    float framePosY;  //フレーム中心点
    int frameGrid_;    //フレーム画像を分割したときの1辺の長さ

    ButtonGP* backBtn;  //もどるﾎﾞﾀﾝ


    //半分にする 型をそのまんま返すためintなどは自動切り捨て
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