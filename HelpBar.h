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

    struct HELPBAR_RESOURCE {
        int key;
        string overview;
    };
    void Show();
    void Hide();
    void AddInput(HELPBAR_RESOURCE si);

private:
    bool enScreen_;
    int hPictBar_;
    vector<HELPBAR_RESOURCE> supportInputList_;
public:
    HelpBar(GameObject* parent);
    ~HelpBar();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};