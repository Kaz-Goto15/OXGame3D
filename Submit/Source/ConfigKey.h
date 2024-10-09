#pragma once
#include "Engine/GameObject.h"
#include "Engine/CsvManager.h"
#include <vector>
//キーコンの字表示を管理するクラス
class ConfigKey : public GameObject
{
    std::vector<std::vector <std::string>> textStrings;
public:
    //コンストラクタ
    ConfigKey(GameObject* parent);

    //デストラクタ
    ~ConfigKey();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};