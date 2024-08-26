#pragma once
#include <string>
#include "Engine/GameObject.h"
#include "Screen.h"
class ButtonGP;
//クレジット画面を管理するクラス
class CreditScreen : public Screen
{
    enum PIC {
        PIC_BACKGROUND,
        PIC_BASIC_FRAME_TEX,
        PIC_DESCRIPTION,
        PIC_MAX
    };
    int hPict_[PIC_MAX];

    XMINT4 frameMargin;  //上右下左
    float frameScale;    //可変フレーム拡大率
    XMFLOAT3 framePos;  //フレーム中心点
    int frameLength;    //フレーム画像を分割したときの1辺の長さ
    ButtonGP* backBtn;  //もどるﾎﾞﾀﾝ

    //半分にする 型をそのまんま返すためintなどは自動切り捨て
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