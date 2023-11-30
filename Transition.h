#pragma once

#include "Engine/GameObject.h"

enum TRANSITION_ID {
    E_LATTICE = 0,
    E_FADEOUT_BLACK,
    E_FADEIN_BLACK,
    E_FADEOUT_WHITE,
    E_FADEIN_WHITE,
};
enum STATE {
    S_IDLE,
    S_RUN
};
//フィルタ効果の集合を管理
namespace Transition {

    void Initialize();
    void Load();
    void Run(TRANSITION_ID tID, float sec, int easeNum = 1);
}

//class Transition : public GameObject
//{
//    //絶対ここ何かしらの方法で定数じゃなくてもいけるよな 今は手動でいい 直すと時間が足りない
//    TransitionAnim* pChangeAnim[32][18];
//    int animpts;
//    int nowFrame;
//    bool fade_;
//    bool mvSwitch;
//    bool tileReset;
//    SCENE_ID sceneName;
//
//    int hPict_;
//    int scID;
//    int waitTime;
//    double sinx;
//    double val;
//public:
//    Transition(GameObject* parent);
//    ~Transition();
//    void Initialize() override;
//    void Update() override;
//    void Draw() override;
//    void Release() override;
//
//    void SetFade(bool _fade) { fade_ = _fade; }
//    //SetFadeは廃棄予定
//    void SetState(SCENE_CHANGE_ID _mode, bool _fade) {
//
//    }
//    bool IsFinished();
//
//    void ChangeScene(SCENE_ID sceneName_);
//    void ModifySC(SCENE_CHANGE_ID sc, int _wait = 0);
//    void Init();
//};