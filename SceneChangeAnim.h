#pragma once
#include "Engine/GameObject.h"
struct MVSINGLE
{
    float x;
    float y;
};
//メニューを管理するクラス
class SceneChangeAnim : public GameObject
{
    int hPict_;    //画像番号
    XMFLOAT3 fromVec, toVec;
    float sinx;
    bool fade_, move_;
    MVSINGLE mv;
    bool animStats = true;
    
public:
    //コンストラクタ
    SceneChangeAnim(GameObject* parent);

    //デストラクタ
    ~SceneChangeAnim();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    std::string GetInfo();

    void ModifyRect(int x, int y, bool _fade);

    void AnimPlaying(bool animplay) { animStats = animplay; }
};