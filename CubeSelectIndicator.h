#pragma once
#include "Engine/GameObject.h"
#include "Cube.h"
#include "./Include/EffekseeLib/EffekseerVFX.h"
//キューブを管理するクラス
class CubeSelectIndicator : public GameObject
{
private:
    int hModel;
    int cubeSize;
    float outerPoint;   //最も外側のキューブの中心座標
    int rotCol;

    XMFLOAT3 Surface2Rotate(Cube::SURFACE surface);

    template<class T>
    T Half(T value) { return value / 2.0f; }

public:
    CubeSelectIndicator(GameObject* parent);    //コンストラクタ
    ~CubeSelectIndicator();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画
    void Release() override;    //解放

    //前から見たときの回転方向
    enum ROTATE_DIR {
        ROT_UP,
        ROT_DOWN,
        ROT_LEFT,
        ROT_RIGHT,
        ROT_CW,
        ROT_CCW
    };
private:
    ROTATE_DIR direction;
public:
    //描画モード
    enum DRAW_MODE {
        DRAWMODE_SINGLE,
        DRAWMODE_CIRCLE
    }drawMode;
    /// <summary>
    /// 描画面の変更
    /// </summary>
    /// <param name="surface">面enum</param>
    void SetSurface(Cube::SURFACE surface);

    //キューブの大きさ指定 例えば3x3なら3を入れる
    void SetCubeScale(int scale);

    void SetDrawMode(DRAW_MODE mode) { drawMode = mode; }
    //前面から見た時の回転方向を指定
    void SetCubeRotate(ROTATE_DIR dir);
    //エフェクト
    std::shared_ptr<EFFEKSEERLIB::EFKTransform> mt;
};