#pragma once
#include "Engine/GameObject.h"

class TransitionAnimBase : public GameObject
{
    float progress_;
    float time_;
    int easeNum;
public:
    //コンストラクタ
    TransitionAnimBase(GameObject* parent);
    ~TransitionAnimBase();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};