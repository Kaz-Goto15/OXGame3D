#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//HPを管理するクラス
class Health : public GameObject
{
    int hPict_[4];
    int health_, hpRatio;
    int tmpHealth_, tmpRatio;
    int maxHealth_;
    int moveBar_,moveProgress;
    Text* pText;
    std::string hpView;
    Transform textTra;
public:
    //コンストラクタ
    Health(GameObject* parent);
    ~Health();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    void SetTmpHealth(int _tmpHealth) { tmpHealth_ = _tmpHealth; }
    void SetHealth(int _health) { health_ = _health; moveProgress = 0; }
};