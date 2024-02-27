#pragma once
#include "GameSceneObject.h"

//◆◆◆を管理するクラス 
class Entity : public GameSceneObject
{

public:
    Entity(GameObject* parent, const std::string& name);    //コンストラクタ
    ~Entity();                     //デストラクタ
    virtual void Initialize() override = 0; //初期化
    virtual void Update() override = 0;     //更新
    virtual void Draw() override = 0;       //描画
    virtual void Release() override = 0;    //解放
};