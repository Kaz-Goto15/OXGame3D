#pragma once
#include "Engine/GameObject.h"

class DebugText;

//枠を管理するクラス
class Frame : public GameObject
{
    //DebugText* debugText;
    //std::string debStr[5];
    //int hPt;
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
public:
    enum MODE {
        AUTO_ASPECT,    //(未実装)画面サイズに応じて枠が変形します。Frameクラスのscale.x,yを各方向の画面サイズに対する割合として範囲を指定します。
        CONST_MARGIN,   //画面端からの距離を指定します。    FrameクラスのTransform全てを無視します。           画面サイズが変化した場合、画面端から枠までの距離は変わりませんが、中の面積は変化します。自身のmUp,mRight,mDown,mLeftを参照します。
        CONST_SIZE,     //(未実装)positionを中心として、固定値でサイズを指定します。奇数の場合、左上が1px多くなります。FrameクラスのScaleを無視します。 画面サイズが変化した場合、枠は変形しませんが、枠の座標のみ変化します。自身のwidth, heightを参照します。
    };
private:
    MODE mode_;
    std::string filePath_;
    int grid_;
    int hImgFrame_;
    int mUp, mRight, mDown, mLeft;
    int sWidth, sHeight;
    Transform tra[FRAME_H::H_MAX][FRAME_W::W_MAX];

    void Init();
    void UpdateDrawData();

    template <class T>
    float Half(T value) { return (float)value / 2.0f; }

public:
    Frame(GameObject* parent);    //コンストラクタ
    ~Frame();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画(何も書かない)
    void Release() override;    //解放

    void DrawFrame();           //描画(呼び出し元で呼び出す)
    void ChangeTheme(std::string _filePath, int _grid);

    /// <summary>
    /// 枠描画のモードを変更
    /// </summary>
    /// <param name="_mode">モード選択(固定値)</param>
    /// <param name="value1">MARGINの場合：上余白指定 SIZEの場合：横幅</param>
    /// <param name="value2">MARGINの場合：右余白指定 SIZEの場合：縦幅</param>
    /// <param name="value3">MARGINの場合：下余白指定 SIZEの場合：無(値は無視される)</param>
    /// <param name="value4">MARGINの場合：左余白指定 SIZEの場合：無(値は無視される)</param>
    void ChangeMode(MODE _mode, int value1, int value2, int value3=0, int value4=0);

    /// <summary>
    /// 枠描画のモードを変更
    /// </summary>
    /// <param name="_mode">モード選択(固定値)</param>
    /// <param name="xRatio">X割合指定</param>
    /// <param name="yRatio">Y割合指定</param>
    void ChangeMode(MODE _mode, float xRatio, float yRatio);
};