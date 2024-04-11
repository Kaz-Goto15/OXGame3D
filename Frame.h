#pragma once
#include "Engine/GameObject.h"

//枠を管理するクラス
class Frame : public GameObject
{
    const int FRAME_ここ何
    int hFrameImg_;
    Transform tra[3][3];
public:
    Frame(GameObject* parent);    //コンストラクタ
    ~Frame();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画
    void Release() override;    //解放
    
    //上右下左でマージンを指定
    void TransformFrame(XMINT4 margin) { TransformFrame(margin.x, margin.y, margin.z, margin.w); }
    //上右下左でマージンを指定
    void TransformFrame(int up, int right, int down, int left);


    template <class T>
    T Half(T* value) { return value / 2.0f };
};