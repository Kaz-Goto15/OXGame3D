#pragma once
#include "Engine/GameObject.h"
#include <string>
#include <vector>
using std::string;
using std::vector;
//クレジット画面を管理するクラス
class HelpBar : public GameObject
{
public:

    struct SUPPORT_INPUT {
        int keyNum;
        string keyHelp;
    };
private:
    bool enScreen_;
    int hPictBar_;
    vector<SUPPORT_INPUT> supportInputList_;
public:
    HelpBar(GameObject* parent);
    ~HelpBar();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    void Show();
    void Hide();
    void AddInput(SUPPORT_INPUT si);
};