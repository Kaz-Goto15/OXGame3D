#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

#include "SelectRect.h"
#include "SelectTriangle.h"
#include "SceneChange.h"

#include "GameData.h"
//メニューを管理するクラス
class MenuSelect : public GameObject
{
    Text* pText;
    std::string testring;
    int selectNo;
    float lineSpace;
    float toLocateY;
    XMFLOAT3 selectVec;
    int quantity;
    SceneChange* pSC;
    SelectRect* pSelectRect;
    SelectTriangle* pSelectTriangle;
    int hSound_[2];


public:
    //コンストラクタ
    MenuSelect(GameObject* parent);

    //デストラクタ
    ~MenuSelect();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //現在地点から選択ポイントへ移動
    void PointMove();

    double GetLineSpace() { return lineSpace; }
    int GetSelectNo() { return selectNo; }
    void SetToLocateY(float y_) { toLocateY = y_; }
    void SetSelectNo(int send_);
    void ExeTrig();

    float GetSelectVec(int i);
    std::string GetInfoRect();
    std::string GetInfoTriangle();
};