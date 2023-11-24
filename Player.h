#pragma once
#include "Engine/GameObject.h"

class Player : public GameObject
{
    int hModel_;
    float velY;
    float maxVel;
    int hSound_[3]; //サウンド番号
    bool nowFly;

    float knockback;
    bool hasHealth;
public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
    void OnCollision(GameObject* pTarget);
    float GetPositionY();
};
