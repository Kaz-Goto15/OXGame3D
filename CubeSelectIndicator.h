#pragma once
#include "Engine/GameObject.h"
#include "Cube.h"
#include "./Include/EffekseeLib/EffekseerVFX.h"

using ROTATE_DIR = Cube::ROTATE_DIR;
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

    //描画モード
    enum DRAW_MODE {
        DRAWMODE_SINGLE,
        DRAWMODE_CIRCLE
    };

private:
    Cube::ROTATE_DIR direction;
    void SetPosition(float x, float y, float z) {}  //SetPositionを無効化
    void SetPosition(int x, int y, int z) {}  //SetPositionを無効化
    DRAW_MODE drawMode;

public:
    //=================== 単一描画 ===================

    /// 単一描画の情報を変更
    /// point:キューブの場所 左下前が0,0,0 右上奥が2,2,2
    /// surface:描画面
    void SetDrawPoint(XMINT3 point, Cube::SURFACE surface);

    /// 単一描画の情報を変更 面情報は更新しないバージョン
    /// point:キューブの場所 左下前が0,0,0 右上奥が2,2,2
    void SetDrawPoint(XMINT3 point);

    /// 単一描画の情報を変更 選択場所は更新しないバージョン
    /// surface:描画面
    void SetDrawPoint(Cube::SURFACE surface);

    //キューブの大きさ指定 例えば3x3なら3を入れる
    void SetCubeScale(int scale);

    void SetDrawMode(DRAW_MODE mode) { drawMode = mode; }

    //=================== 円形描画 ===================
    //前面から見た時の回転方向を指定
    void SetCubeRotate(Cube::ROTATE_DIR dir);
    
    //回転列 左下前がX0Y0Z0
    void SetRotateColumn(int col) { rotCol = col; }
    //エフェクト
    std::shared_ptr<EFFEKSEERLIB::EFKTransform> mt;
};