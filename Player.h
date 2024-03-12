#pragma once
#include "Engine/GameObject.h"

class Player : public GameObject
{
    enum STATE {
        S_IDLE,
        S_MOVE,
        S_JUMP,
        S_FALL,
        S_DAMAGED,
        S_THROW,
        S_DOWN
    }state_;

    enum AUDIO_ASSET {
        SE_JUMP,
        SE_LAND,
        SE_THROW,
        SE_MAX
    };

    float velY;
    float maxVel;
    int hSound_[SE_MAX]; //サウンド番号
    int hModel_;
    bool nowFly;

    float knockback;
    bool hasHealth;

    float nowIFrame, iFrame;
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
private:
    void UpdateAct(STATE state_);   
    void ChangeState(STATE state);  //状態遷移

};