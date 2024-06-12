#pragma once
#include "Engine/GameObject.h"

//キューブを管理するクラス
class Cube : public GameObject
{
    enum MODEL_ENUM {
        CUBE,
        FRONT_COLOR,
        BACK_COLOR,
        LEFT_COLOR,
    };
    int hModel_;
    int hModel_col;
    enum MARK {
        MARK_BLANK = -1,
        MARK_O,
        MARK_X
    };
    enum ROTATE_DIR {
        FRONT,
        BACK,
        LEFT,
        RIGHT,
        CW,
        CCW
    };
    enum SURFACE {
        SURFACE_TOP,
        SURFACE_BOTTOM,
        SURFACE_LEFT,
        SURFACE_RIGHT,
        SURFACE_FRONT,
        SURFACE_BACK,
        SURFACE_MAX

    };

    MARK cubeData_[SURFACE_MAX];

public:
    Cube(GameObject* parent);    //コンストラクタ
    ~Cube();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画
    void Release() override;    //解放
    void RotateCube(ROTATE_DIR dir);    //前から見てその方向へ回転する
    void SetMark(SURFACE surface, MARK mark);
};