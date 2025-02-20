#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class GameSceneObject : public GameObject
{
protected:
    enum OBJECT_ATTRIBUTE {
        OBJ_FIELD,
        OBJ_ENTITY
    };
    bool isLand = false;
public:
    GameSceneObject(GameObject* parent, const std::string& name);    //コンストラクタ
    ~GameSceneObject();                     //デストラクタ
    virtual void Initialize() override = 0; //初期化
    virtual void Update() override = 0;     //更新
    virtual void Draw() override = 0;       //描画
    virtual void Release() override = 0;    //解放
};