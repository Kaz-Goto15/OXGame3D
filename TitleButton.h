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
    Text::HORIZONAL_ALIGNMENT hAl;
    Text::VERTICAL_ALIGNMENT vAl;
    int actHandle_;
    XMINT4 clip = { 0,0,128,128 };
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

    //自身(ボタン)と親の選択ステートを紐づける
    void SetAction(int hAct);

    //処理終了と銘打っているが、強制的にIDLE状態にする関数
    void EndAct() { state = IDLE; }
private:
    void UpdateIdle();
    void UpdateSelect();
    void UpdatePush();
    void UpdateSelected();

    bool IsEntered();
    bool Between(float value, float min, float max);
};