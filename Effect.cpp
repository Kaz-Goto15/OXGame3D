#include "Effect.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include <iostream>
#include "Engine/Debug.h"

//コンストラクタ
Effect::Effect(GameObject* parent)
    :GameObject(parent, "Effect")
{
    nowFrame = 0;
    std::fill(hPict_, hPict_ + EFFECT_EOF, -1);
    sinx = 0;
    scaleVal = 0;
    clipping = 0;
}

//デストラクタ
Effect::~Effect()
{
}

//初期化
void Effect::Initialize()
{

}

//更新
void Effect::Update()
{
    if (effectID == EFFECT_GO) {
        if (nowFrame == 0) {
            ImgTrans_[0].scale_ = { 0,0,1 };

            //ここでscaleValを設定しておく
            scaleVal = 0.1f;
        }

        if (nowFrame == 1 || nowFrame == 2) {
            sinx += 0.1f;
            //sinx += 0.0625f;
            if (sinx > M_PI / 2) {
                sinx = (float)(M_PI / 2);
                nowFrame = 3;
            }
            else {
                nowFrame = 1;
            }
            ImgTrans_[0].scale_.x = std::sin(sinx);
            ImgTrans_[0].scale_.y = std::sin(sinx);
        }

        if (nowFrame > 30) {
            ImgTrans_[0].scale_.x += scaleVal;
            ImgTrans_[0].scale_.y += scaleVal;
            scaleVal -= 0.02f;
            if (ImgTrans_[0].scale_.x <= 0) {
                KillAllChildren();
                KillMe();
            }
        }
        nowFrame++;
    }

    if (effectID == EFFECT_GAME_END || effectID == EFFECT_TIME_UP) {
        if(nowFrame == 0){
            ImgTrans_[1].scale_ = { 0,0,1 };
            nowFrame++;
        }

        //1280未満で+128、その後1281以上で1280固定
        if (clipping < 1280) {
            clipping += 64;
            if (clipping > 1280) {
                clipping = 1280;
            }
            Image::SetRect(hPict_[0], 0, 0, clipping, 720);
            ImgTrans_[0].position_.x = -(640.0f - (float)clipping / 2.0f) / 640.0f;
        }
        if (clipping > 640  && sinx < 2 * M_PI / 3 ) {
            sinx += 0.1f;
            ImgTrans_[1].scale_.x = 2 * std::sqrt(3.0f) * std::sin(sinx) / 3;
            ImgTrans_[1].scale_.y = 2 * std::sqrt(3.0f) * std::sin(sinx) / 3;
        }
        else if (sinx > 2 * M_PI / 3) {
            sinx = (float)(2 * M_PI / 3);
        }

        //消す必要ないけど一応時間で消そう
        if (clipping == INT_MAX) {
            KillAllChildren();
            KillMe();
        }
    }

}

//描画
void Effect::Draw()
{
    Image::SetTransform(hPict_[0], ImgTrans_[0]);
    Image::Draw(hPict_[0]);
    if (hPict_[1] >= 0) {
        Image::SetTransform(hPict_[1], ImgTrans_[1]);
        Image::Draw(hPict_[1]);
    }
}

//開放
void Effect::Release()
{
}

void Effect::SetEffect(EFFECT_ID efid)
{
    effectID = efid;
    Init();
}

void Effect::LoadImg(int hpict, std::string imgFile)
{
    hPict_[hpict] = Image::Load(imgFile);
    assert(hPict_[hpict] >= 0);
}

void Effect::Init()
{
    switch (effectID)
    {
    case EFFECT_GO:  LoadImg(0, "go.png"); break;
    case EFFECT_GAME_END:
        LoadImg(0, "telopBG.png");
        Image::SetRect(hPict_[0], 0, 0, 0, 720);
        LoadImg(1, "gameend.png");
        break;
    case EFFECT_TIME_UP:
        LoadImg(0, "telopBG.png");
        Image::SetRect(hPict_[0], 0, 0, 0, 720);
        LoadImg(1, "timeup.png");
        break;
    }

}
