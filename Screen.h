#pragma once
#include "Engine/GameObject.h"
//サブ画面ベース
class Screen : public GameObject
{
public:

    void Show();
    void Hide();

private:
    bool debug;
    void DebugAction();
public:
    Screen(GameObject* parent);
    ~Screen();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    virtual void CloseAnim();
    void Close();
    
};