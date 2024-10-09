#pragma once
#include "Engine/GameObject.h"
#include "Engine/Image.h"

enum EFFECT_ID {
    EFFECT_GO = 0,
    EFFECT_GAME_END,
    EFFECT_TIME_UP,
    EFFECT_EOF,
};
//シーン切替を挟まない表現を管理するクラス
class Effect : public GameObject
{
    int hPict_[8];
    int effectID = 0;
    int nowFrame;
    Transform ImgTrans_[8];
    float sinx;
    float scaleVal;
    int clipping;
public:
    //コンストラクタ
    Effect(GameObject* parent);

    //デストラクタ
    ~Effect();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //effect set
    void SetEffect(EFFECT_ID efid);

    //effect imageload
    void LoadImg(int hpict, std::string imgFile);
    //effect Init
    void Init();
};
