#pragma once
#include "Entity.h"
class TestEntity : public Entity
{
public:
    TestEntity(GameObject* parent);    //コンストラクタ
    ~TestEntity();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画
    void Release() override;    //解放
};

