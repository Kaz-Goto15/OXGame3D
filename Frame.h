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
    enum MODE {
        AUTO_ASPECT,    //画面サイズに応じて枠が変形します。Frameクラスのscale.x,yを各方向の画面サイズに対する割合として範囲を指定します。
        CONST_MARGIN,   //画面端からの距離を指定します。FrameクラスのTransform全てを無視します。画面サイズが変化した場合、画面端から枠までの距離は変わりませんが、中の面積は変化します。自身のmUp,mRight,mDown,mLeftを参照します。
        CONST_SIZE,   //固定値でサイズを指定します。FrameクラスのScaleを無視します。画面サイズが変化した場合、枠は変形しませんが、枠の座標のみ変化します。自身のwidth, heightを参照します。
    };
    std::string filePath;
    int grid;
    int hImgFrame;
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
    void ChangeTheme(std::string _filePath, int _grid);

    /// <summary>
    /// 枠描画のモードを変更
    /// </summary>
    /// <param name="_mode">モード選択(固定値)</param>
    /// <param name="value1">MARGINの場合：上余白指定 SIZEの場合：</param>
    /// <param name="value2"></param>
    /// <param name="value3"></param>
    /// <param name="value4"></param>
    void ChangeMode(MODE _mode, int value1, int value2, int value3, int value4);
    void ChangeMode(MODE _mode, float xRatio, float yRatio);

    template <class T>
    float Half(T value) { return (float)value / 2.0f; }
};