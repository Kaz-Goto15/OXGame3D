#pragma once
#include "Engine/GameObject.h"

//クレジット画面を管理するクラス
class CreditScreen : public GameObject
{

    bool enScreen;
    int hPict_;
public:
    CreditScreen(GameObject* parent);
    ~CreditScreen();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    void Show();
    void Hide();
};