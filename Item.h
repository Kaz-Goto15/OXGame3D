#pragma once
#include "Engine/GameObject.h"

class Item : public GameObject
{
    int hModel_;
    int hSound_[2];
public:
    //コンストラクタ
    Item(GameObject* parent);
    ~Item();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    //何かに当たった
   //引数：pTarget 当たった相手
    void OnCollision(GameObject* pTarget) override;

    //座標Yを変更
    void SetPositionY(float setY) { transform_.position_.y = setY; }

};