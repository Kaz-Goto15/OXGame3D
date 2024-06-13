#pragma once
#include <string>
#include <vector>
#include "Engine/GameObject.h"
#include "Screen.h"
#include "Cube.h"
class Cube;
class DebugText;

using std::vector;
//管理するクラス
class ModelTestScreen : public Screen
{
    int hModel;

    DebugText* debugtext;
    std::string debugStr[20];
    vector<vector<vector<Cube*>>> cube;
    vector<vector<vector<Transform>>> cubePrevTra;
    vector<vector<vector<Transform>>> cubeNextTra;
    void UpdateStr();

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
            x = 0;
            y = 0;
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
SET,ROTATEで使うキー:前回モードへ移行
右クリック押下中にドラッグ:視点回転


*/