#pragma once
#include <string>
#include <vector>
#include "Engine/GameObject.h"
#include "Screen.h"
#include "Cube.h"
class Cube;
class CubeSelectIndicator;
class DebugText;

using std::vector;
//管理するクラス
class ModelTestScreen : public Screen
{
    int hImgBG;
    int hModel;

    const int PIECES = 3;
    vector<vector<vector<Cube*>>> cube;
    vector<vector<vector<Transform>>> cubePrevTra;
    vector<vector<vector<Transform>>> cubeNextTra;
    CubeSelectIndicator* indicator;
    enum ROTATE_DIR {
        FRONT,
        BACK,
        LEFT,
        RIGHT,
        CW,
        CCW
    };
    enum MODE {
        MODE_SET,       //○×を設置
        MODE_ROTATE,    //キューブを回転
        MODE_VIEW       //回転
    }mode;
    enum CONTROL {
        CONTROL_IDLE,
        CONTROL_1P,
        CONTROL_2P
    };
    CONTROL control, nextTurn;
    struct SelectData {
        int x, y, z;
        Cube::SURFACE surface;
        SelectData() {
            x = 1;
            y = 1;
            z = 0;
            surface = Cube::SURFACE::SURFACE_FRONT;
        }
    }selectData;
    void CalcCubeTrans();

    bool isMoving = false;

    const int angleOfRotate = 90;
    ROTATE_DIR dir;
    int rotateNo;
    int rotTime = 0; 

    //移動関連
    enum DIR {
        X,
        Y,
        Z
    };
    void MoveSelectParts(DIR dir, bool plus, Cube::SURFACE outSurface);
    void MoveSelect();
    void MoveIndicator();

    //値が範囲内か
    template <class T>
    bool Between(T value, T min, T max) {
        return (min <= value && value <= max);
    }

    //カメラ関連
    Transform camTra;                       //カメラ変形情報
    float rotSpdX, rotSpdY;                 //カメラ回転速度
    bool isEnded;                           //ゲーム終了フラグ
    const int CAM_DISTANCE = 10;            //カメラ距離 固定
    //const float DC_VALUE = 0.05f;         //カメラ減速値
    const float TH_ZEROSPEED = 0.3f;        //カメラ速度0にする閾値
    const float DC_RATIO = 1.2f;            //カメラ減速割合
    const float AT_RATIO = 0.5f;        //カメラ移動量に対する回転距離単位
    const float MAX_CAM_ROTATE_X = 89.9999f;    //カメラX回転の最高角度制限
    const float MIN_CAM_ROTATE_X = -89.9999f;   //カメラX回転の最低角度制限
    const int LIMIT_CAM_ROTATE_Y = 180;         //カメラY回転の角度制限(オーバーフロー回避)
    const int DEFAULT_SPEED = 0;                //カメラのデフォルト速度(0)

    //デバッグテキスト
    std::string debugStr[20];
    DebugText* debugtext;
    void UpdateStr();

    /// <summary>
    /// キューブ回転のトリガー 初期化処理とフラグ管理
    /// 
    /// </summary>
    /// <param name="dir">回転方向 前上から見て前(下)後(上))左右時計反時計</param>
    /// <param name="no">回転する行/列 [0][0][0]を基準とし、0,1,2で指定</param>
    /// <param name="angle">何度回転させるか</param>
    void RotateCube(ROTATE_DIR dir, int no, float angle = 90.0f);
    void TurnEnd();
    void Judge();

    /// カメラ関連の処理
    void RotateCamera();
    void FinishCamera();
    
public:
    ModelTestScreen(GameObject* parent);
    ~ModelTestScreen();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};

/*
SET,ROTATE
SPACE:設置
LSHIFT:切替
WASD:上下左右移動/回転方向切替
E:(ROTATEのみ)軸切替
右クリック:VIEWへ移行
VIEW
SET,ROTATEで使うキー:前回モードへ移行 Spaceでいいんじゃね
右クリック押下中にドラッグ:視点回転


*/