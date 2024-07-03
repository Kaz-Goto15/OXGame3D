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
public:
    enum MARK {
        MARK_BLANK = -1,
        MARK_O,
        MARK_X,
        MARK_MAX
    };

    enum ROTATE_DIR {
        ROT_UP,
        ROT_DOWN,
        ROT_LEFT,
        ROT_RIGHT,
        ROT_CW,
        ROT_CCW
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

private:
    int hModelCube;                 //キューブ自体のモデルデータハンドル
    int hModelMark[MARK_MAX];       //マークのモデルデータハンドル
    MARK cubeData_[SURFACE_MAX];    //キューブ側面のマークデータ
    XMFLOAT3 Surface2Rotate(SURFACE surface);
public:
    Cube(GameObject* parent);    //コンストラクタ
    ~Cube();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画
    void Release() override;    //解放

    void SwapData(ROTATE_DIR dir);    //前から見た回転方向を指定し、各面のデータを入れ替える
    void SetPoint(XMINT3 point, float outerPoint);  //最も外側のキューブの
    void SetMark(SURFACE surface, MARK mark);
    MARK GetMark(SURFACE surface) { return cubeData_[surface]; }
};