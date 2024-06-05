#pragma once
#include "Engine/GameObject.h"

//キューブを管理するクラス
class Cube : public GameObject
{
    int hModel_;
public:
    Cube(GameObject* parent);    //コンストラクタ
    ~Cube();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画
    void Release() override;    //解放
};