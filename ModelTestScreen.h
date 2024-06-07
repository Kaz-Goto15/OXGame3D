#pragma once
#include <string>
#include <vector>
#include "Engine/GameObject.h"
#include "Screen.h"
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
public:
    ModelTestScreen(GameObject* parent);
    ~ModelTestScreen();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};