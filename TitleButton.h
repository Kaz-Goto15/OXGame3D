#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"
//タイトルのボタンを管理するクラス
class TitleButton : public GameObject
{
    enum STATE {
        IDLE,
        SELECT,
        PUSH,
        SELECTED,
        MAX
    };
    Text* buttonTextObj_;
    std::string buttonName_;
    int hImg_[MAX];
    int scrW, scrH;
public:
    STATE state;
    TitleButton(GameObject* parent);    //コンストラクタ
    ~TitleButton();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画
    void Release() override;    //解放
    void SetText(std::string buttonName);
    std::string LinkImageFile(STATE state);

    std::string GetDebugStr(int i);
private:
    void UpdateIdle();
    void UpdateSelect();
    void UpdatePush();
    void UpdateSelected();

    bool IsEntered();
};