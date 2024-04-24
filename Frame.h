#pragma once
#include "Engine/GameObject.h"

//枠を管理するクラス
class Frame : public GameObject
{
    enum FRAME_W {
        W_LEFT= 0,
        W_CENTER,
        W_RIGHT,
        W_MAX,
    };
    enum FRAME_H {
        H_TOP = 0,
        H_CENTER,
        H_BOTTOM,
        H_MAX
    };
    std::string fileName;
    int edge;
    int hFrameImg_;
    Transform tra[FRAME_H::H_MAX][FRAME_W::W_MAX];

    //上右下左でマージンを指定
    void TransformFrame(XMINT4 margin) { TransformFrame(margin.x, margin.y, margin.z, margin.w); }
    //上右下左でマージンを指定
    void TransformFrame(int up, int right, int down, int left);

public:
    Frame(GameObject* parent);    //コンストラクタ
    ~Frame();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画
    void Release() override;    //解放

    void SetMargin(int up, int right, int down, int left);

    template <class T>
    float Half(T value) { return (float)value / 2.0f; }
};