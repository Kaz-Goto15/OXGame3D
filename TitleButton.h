#pragma once
#include "Button.h"
//タイトルのボタンを管理するクラス
class TitleButton : public Button
{
public:
    TitleButton(GameObject* parent);    //コンストラクタ
    ~TitleButton();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画
    void Release() override;    //解放
    std::string LinkImageFile(STATE state) override;
private:
};