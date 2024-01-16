#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Sample : public GameObject
{

public:
    Sample(GameObject* parent);    //コンストラクタ
    ~Sample();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画
    void Release() override;    //解放
};