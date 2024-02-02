#pragma once
#include "Engine/GameObject.h"
//サブ画面ベース
class Screen : public GameObject
{
public:

protected:
    void DebugAction();
    GameObject* pPrevObject;
public:
    Screen(GameObject* parent, const std::string& name);
    ~Screen();
    virtual void Initialize() override = 0;
    virtual void Update() override= 0;
    virtual void Draw() override=0;
    virtual void Release() override=0;
    void SetPrevScene(GameObject* prevScene);
    void Prev();
    void Run();
};