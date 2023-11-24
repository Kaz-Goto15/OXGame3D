#pragma once
#include "Engine/GameObject.h"
#include "SceneChangeAnim.h"
#include "Engine/SceneManager.h"

enum SCENE_CHANGE_ID {
    SC_LATTICE = 0,
    SC_BLACK,
    SC_WHITE,
};
//シンチェの集合を管理するクラス
class SceneChange : public GameObject
{
    //絶対ここ何かしらの方法で定数じゃなくてもいけるよな 今は手動でいい 直すと時間が足りない
    SceneChangeAnim* pChangeAnim[32][18];
    int animpts;
    int nowFrame;
    bool fade_;
    bool mvSwitch;
    bool tileReset;
    SCENE_ID sceneName;

    int hPict_;
    int scID;
    int waitTime;
    double sinx;
    double val;
public:
    //コンストラクタ
    SceneChange(GameObject* parent);

    //デストラクタ
    ~SceneChange();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void SetFade(bool _fade) { fade_ = _fade; }
    //SetFadeは廃棄予定
    void SetState(SCENE_CHANGE_ID _mode, bool _fade) {
        
    }
    bool IsFinished();

    void ChangeScene(SCENE_ID sceneName_);
    void ModifySC(SCENE_CHANGE_ID sc, int _wait = 0);
    void Init();
};