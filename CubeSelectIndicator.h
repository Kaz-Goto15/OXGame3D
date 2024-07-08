#pragma once
#include "Engine/GameObject.h"
#include "Cube.h"
#include "./Include/EffekseeLib/EffekseerVFX.h"
#include <string>

using std::string;
using ROTATE_DIR = Cube::ROTATE_DIR;
using SURFACE = Cube::SURFACE;
//キューブを管理するクラス
class CubeSelectIndicator : public GameObject
{
public:
    CubeSelectIndicator(GameObject* parent);    //コンストラクタ
    ~CubeSelectIndicator();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画
    void Release() override;    //解放
private:
    void SetPosition(float x, float y, float z) {}  //SetPositionを無効化
    void SetPosition(int x, int y, int z) {}        //SetPositionを無効化

    //=================== エフェクト ===================
    //
    // どうやらループをtrueにした状態でエフェクト描画開始を走らせたとき、途中でfalseにして描画を終えても
    // またtrueに戻すと描画される そのため一生発生するエフェクトを除いて現在フレームを見るようにして手動ループを行う
    //
    //==================================================
private:
    std::shared_ptr<EFFEKSEERLIB::EFKTransform> mt;
    EFFEKSEERLIB::EFKTransform t;
    const float DEFAULT_EFFECT_SPEED;
    enum EFFECT_STATE {
        STOP,
        NEXT_START,
        DRAWING
    }arrowState;
    int nowArrowFrame;
    const int ARROW_FRAME;
    const string EFF_ID_ARROW;

    //エフェクトを止める
    // FPSと最大フレームを変更して超高速でエフェクトを流すことで実現しているため、
    // 再描画は次のフレーム以降でやらないと効果無し 注意
    void StopDrawArrow();

    //エフェクトを再生する
    void StartDrawArrow(Cube::ROTATE_DIR dir, int rotCol);
    void DrawArrow(Transform& tra); //実質StartDrawArrow関数のParts

private:
    int hModel;
    int cubeSize;
    float outerPoint;   //最も外側のキューブの中心座標
    int rotCol;
    //配置面と矢印の回転
    //surface:描画面
    //side:方向があるものを描画面からその面の方向を指すようにする
    XMFLOAT3 Surface2Rotate(SURFACE surface, SURFACE side);
    XMFLOAT3 Surface2Rotate(SURFACE surface);

    template<class T>
    T Half(T value) { return value / 2.0f; }

private:
    void DrawSurface(Transform& tra, Cube::SURFACE surface, bool isOuter = true);
public:

    //描画モード
    enum DRAW_MODE {
        DRAWMODE_SINGLE,
        DRAWMODE_CIRCLE
    };

private:
    Cube::ROTATE_DIR direction;
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

    void SetDrawMode(DRAW_MODE mode);

    //=================== 円形描画 ===================
    
    //前面から見た時の回転方向を指定
    void SetCubeRotate(Cube::ROTATE_DIR dir);
    
    //回転列 左下前がX0Y0Z0
    void SetRotateColumn(int col);

public:
    void DebugDraw(SURFACE sur, SURFACE sid);
};

//エフェクトの再生停止関数の汎用化はしていない 複数のエフェクト使用しているわけではないので現状しないほうがはやい