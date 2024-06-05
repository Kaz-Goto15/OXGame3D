#pragma once
#include <string>
#include "Engine/GameObject.h"
#include "Screen.h"
class Cube;
class DebugText;
//クレジット画面を管理するクラス
class ModelTestScreen : public Screen
{
    int hModel;

    DebugText* debugtext;
    std::string debugStr[20];

    void UpdateStr();
public:
    ModelTestScreen(GameObject* parent);
    ~ModelTestScreen();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void ButtonAct(int hAct);
};