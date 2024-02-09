#pragma once
#include "Engine/GameObject.h"

//ボタン集合を管理するクラス
class ButtonGroup : public GameObject
{

public:
    ButtonGroup(GameObject* parent);    //コンストラクタ
    ~ButtonGroup();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画
    void Release() override;    //解放

    void AddB
};