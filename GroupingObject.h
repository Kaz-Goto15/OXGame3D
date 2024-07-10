#pragma once
#include "Engine/GameObject.h"

//グループ制御クラス とは名ばかり その実態はGameObjectクラスの継承クラスに何も記述しない超単純継承クラス
class GroupingObject : public GameObject
{

public:
    GroupingObject(GameObject* parent);    //コンストラクタ
    ~GroupingObject();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画
    void Release() override;    //解放
};