#pragma once
#include "Button.h"
//タイトルのボタンを管理するクラス
class TitleButton : public Button
{
public:
    TitleButton(GameObject* parent);    //コンストラクタ
    ~TitleButton();                     //デストラクタ
    std::string LinkImageFile(STATE state) override;
    void Init() override;
private:
};