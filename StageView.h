#pragma once
#include "Engine/GameObject.h"
#include "StageData.h"
#include <vector>

using std::vector;

//エディタのステージプレビューを管理するクラス
class StageView : public GameObject
{
    STAGE_DATA* pStageData_;
    int hModel[(int)TILE_TAG::MAX];

public:
    StageView(GameObject* parent);    //コンストラクタ
    ~StageView();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画
    void Release() override;    //解放
};