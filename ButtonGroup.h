#pragma once
#include "Engine/GameObject.h"
#include "Button.h"

//ボタン集合を管理するクラス
class ButtonGroup : public GameObject
{

public:
    ButtonGroup(GameObject* parent);    //コンストラクタ
    ~ButtonGroup();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画
    void Release() override;    //解放

    void AddButton(int handle, Button* btn);
};


/*

button
・マウスは独立している
・生成の際に押された際のアクションをハンドルで指定する
・他ボタンオブジェクトと互換性無し
・介するための何かが無ければキー実装した際に２つ選択される

buttonGroup?
・現在フォーカスボタンを指定する?
・変わった際のみそれ以外を強制的にIDLE状態にする?
*/