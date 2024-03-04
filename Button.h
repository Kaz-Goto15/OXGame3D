#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"
#include "AudioManager.h"

//ボタンを管理するクラス
class Button : public GameObject
{
protected:
    enum STATE {
        IDLE,
        SELECT,
        PUSH,
        SELECTED,
        MAX
    };
    Text* buttonTextObj_;
    std::string buttonTextName_;
    int hImg_[MAX];
    Text::HORIZONAL_ALIGNMENT hAl;
    Text::VERTICAL_ALIGNMENT vAl;
    int actHandle_;
    //XMINT4 clip = { 0,0,128,128 };
    bool nextIdle;
    STATE ActTiming;
    AudioManager::AUDIO_SOURCE sound;
public:
    STATE state;

    Button(GameObject* parent, const std::string& name= "Button");    //コンストラクタ
    ~Button();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画
    void Release() override;    //解放


    //自身(ボタン)と親の選択ステートを紐づける
    void SetAction(int hAct);

    void SetSound(AudioManager::AUDIO_SOURCE audioSource) { sound = audioSource; }
    //テキスト設定系
    void SetTextAlignment(Text::HORIZONAL_ALIGNMENT h, Text::VERTICAL_ALIGNMENT v);
    void SetFont(const char* fileName, const unsigned int charWidth, const unsigned int charHeight, const unsigned int rowLength);
    void SetText(std::string buttonName);
protected:
    //初期化追加時の処理
    virtual void Init() {}
    //画像リンク ボタン画像を変えたい場合これ継承してオーバーライドする
    virtual std::string LinkImageFile(STATE state);
    //ボタンアニメーション系
    virtual void DrawIdle();
    virtual void DrawSelect();
    virtual void DrawPush();
    virtual void DrawSelected();
private:
    //各Update関数
    void UpdateIdle();
    void UpdateSelect();
    void UpdatePush();
    void UpdateSelected();
    //ボタンの描画範囲内にマウスカーソルがあるか
    bool IsEntered();
    //値が範囲内か
    bool Between(float value, float min, float max);
    //マウスが1pxでも動いたか
    bool IsMovedMouse();
public:
    std::string GetDebugStr(int i);
};