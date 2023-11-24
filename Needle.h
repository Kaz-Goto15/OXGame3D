#pragma once
#include "Engine/GameObject.h"

class Needle : public GameObject
{
    int hModel_;
    int time_;
    float a;

public:
    //コンストラクタ
    Needle(GameObject* parent);

    //デストラクタ
    ~Needle();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //何かに当たった
   //引数：pTarget 当たった相手
    void OnCollision(GameObject* pTarget) override;

    //positionY設定
    void SetPositionY(float setY) { transform_.position_.y = setY; }
};