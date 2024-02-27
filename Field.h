#pragma once
#include "Engine/GameObject.h"
#include <vector>
#include <string>

using std::vector;
//フィールドオブジェクトを管理するクラス
class Field : public GameObject
{
public:
    struct FIELD_DATA {
        int hModel = -1;
        Transform transform;
    };
private:
    vector<FIELD_DATA> fieldData_;
public:
    Field(GameObject* parent);    //コンストラクタ
    ~Field();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画
    void Release() override;    //解放
    void AddData(FIELD_DATA dat) { fieldData_.push_back(dat); } //地形データ追加
    void SetFieldData(vector<FIELD_DATA> dataList) { fieldData_ = dataList; }
};