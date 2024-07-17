#include "Cube.h"
#include "./ModelLoader.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
XMFLOAT3 Cube::Surface2Rotate(SURFACE surface)
{
    //モデルで上方向(0,1,0)に配置する
    switch (surface)
    {
    case Cube::SURFACE_TOP: return { 0,0,0 };
    case Cube::SURFACE_BOTTOM:return { 180,0,0 };
    case Cube::SURFACE_LEFT:    return { 0,0,90 };
    case Cube::SURFACE_RIGHT:   return { 0,0,-90 };
    case Cube::SURFACE_FRONT:   return { -90,0,0 };
    case Cube::SURFACE_BACK:    return { 90,0,0 };
    }
}

//コンストラクタ
Cube::Cube(GameObject* parent):
    GameObject(parent, "Cube"),
    hModelCube(-1)
{
    std::fill_n(hModelMark, MARK_MAX, -1);
    std::fill_n(cubeData_, SURFACE_MAX, MARK_BLANK);
}

//デストラクタ
Cube::~Cube()
{
}

//初期化
void Cube::Initialize()
{
    hModelCube = ModelLoader::Load(ModelLoader::MODEL::Cube);
    hModelMark[MARK_O] = ModelLoader::Load(ModelLoader::MODEL::MARK_O);
    hModelMark[MARK_X] = ModelLoader::Load(ModelLoader::MODEL::MARK_X);

    hModelMark[MARK_1] = ModelLoader::Load(ModelLoader::MODEL::MARK_1);
}

//更新
void Cube::Update()
{
    if (isMove) {
        if (Input::IsKey(DIK_LALT)) {
            if (Input::IsKey(DIK_U))transform_.rotate_.z++;
            if (Input::IsKey(DIK_J))transform_.rotate_.z--;
            if (Input::IsKey(DIK_K))transform_.rotate_.x++;
            if (Input::IsKey(DIK_H))transform_.rotate_.x--;
            if (Input::IsKey(DIK_Y))transform_.rotate_.y++;
            if (Input::IsKey(DIK_I))transform_.rotate_.y--;
        }
        else {

            if (Input::IsKey(DIK_U))transform_.position_.z += 0.01f;
            if (Input::IsKey(DIK_J))transform_.position_.z-= 0.01f;
            if (Input::IsKey(DIK_K))transform_.position_.x+= 0.01f;
            if (Input::IsKey(DIK_H))transform_.position_.x-= 0.01f;
            if (Input::IsKey(DIK_Y))transform_.position_.y+= 0.01f;
            if (Input::IsKey(DIK_I))transform_.position_.y-= 0.01f;
        }
    }
}

//描画
void Cube::Draw()
{
    //オブジェクトの持つ変形情報から描画
    //キューブは立方体なので回転しても影響を受けないが親オブジェクトの回転でワンチャンバグるから一番最初に代入
    //transform_.rotate_ = { 0,0,0 };
    Model::SetTransform(hModelCube, transform_);
    if (!Input::IsKey(DIK_3))
    Model::Draw(hModelCube);

    //マーク描画
    for (SURFACE surface = static_cast<SURFACE>(0); surface < SURFACE_MAX; surface = static_cast<SURFACE>(surface + 1)) {
        if (cubeData_[surface] != MARK_BLANK) {
            transform_.rotate_ = Surface2Rotate(surface);
            Model::SetTransform(hModelMark[cubeData_[surface]], transform_);
            Model::Draw(hModelMark[cubeData_[surface]]);
        }
    }
}

//開放
void Cube::Release()
{
}

void Cube::SwapData(ROTATE_DIR dir)
{
    MARK temp = cubeData_[SURFACE_FRONT];
    switch (dir)
    {
    case Cube::ROT_UP:
        temp = cubeData_[SURFACE_FRONT];
        cubeData_[SURFACE_FRONT] = cubeData_[SURFACE_BOTTOM];
        cubeData_[SURFACE_BOTTOM] = cubeData_[SURFACE_BACK];
        cubeData_[SURFACE_BACK] = cubeData_[SURFACE_TOP];
        cubeData_[SURFACE_TOP] = temp;
        break;
    case Cube::ROT_DOWN:
        temp = cubeData_[SURFACE_FRONT];
        cubeData_[SURFACE_FRONT] = cubeData_[SURFACE_TOP];
        cubeData_[SURFACE_TOP] = cubeData_[SURFACE_BACK];
        cubeData_[SURFACE_BACK] = cubeData_[SURFACE_BOTTOM];
        cubeData_[SURFACE_BOTTOM] = temp;
        break;
    case Cube::ROT_LEFT:
        temp = cubeData_[SURFACE_FRONT];
        cubeData_[SURFACE_FRONT] = cubeData_[SURFACE_RIGHT];
        cubeData_[SURFACE_RIGHT] = cubeData_[SURFACE_BACK];
        cubeData_[SURFACE_BACK] = cubeData_[SURFACE_LEFT];
        cubeData_[SURFACE_LEFT] = temp;
        break;
    case Cube::ROT_RIGHT:
        temp = cubeData_[SURFACE_FRONT];
        cubeData_[SURFACE_FRONT] = cubeData_[SURFACE_LEFT];
        cubeData_[SURFACE_LEFT] = cubeData_[SURFACE_BACK];
        cubeData_[SURFACE_BACK] = cubeData_[SURFACE_RIGHT];
        cubeData_[SURFACE_RIGHT] = temp;
        break;
    case Cube::ROT_CW:
        temp = cubeData_[SURFACE_TOP];
        cubeData_[SURFACE_TOP] = cubeData_[SURFACE_LEFT];
        cubeData_[SURFACE_LEFT] = cubeData_[SURFACE_BOTTOM];
        cubeData_[SURFACE_BOTTOM] = cubeData_[SURFACE_RIGHT];
        cubeData_[SURFACE_RIGHT] = temp;
        break;
    case Cube::ROT_CCW:
        temp = cubeData_[SURFACE_TOP];
        cubeData_[SURFACE_TOP] = cubeData_[SURFACE_RIGHT];
        cubeData_[SURFACE_RIGHT] = cubeData_[SURFACE_BOTTOM];
        cubeData_[SURFACE_BOTTOM] = cubeData_[SURFACE_LEFT];
        cubeData_[SURFACE_LEFT] = temp;
        break;
    default:
        break;
    }
}

void Cube::SetMark(SURFACE surface, MARK mark)
{
    cubeData_[surface] = mark;
}

void Cube::SetPoint(XMINT3 point, float outerPoint)
{
    transform_.position_.x = (float)point.x - outerPoint;
    transform_.position_.y = (float)point.y - outerPoint;
    transform_.position_.z = (float)point.z - outerPoint;
}
/*
上方向(x軸時計)
　上後　　　　前上
左前右　→　左下右
　下　　　　　後　

下方向(x軸反時計)
　上後　　　　後下
左前右　→　左上右
　下　　　　　前　

左方向(y軸時計)
　上後　　　　上左
左前右　→　前右後
　下　　　　　下　

右方向(y軸反時計)
　上後　　　　上右
左前右　→　後左前
　下　　　　　下　

時計方向(z軸反時計)
　上後　　　　左後
左前右　→　下前上
　下　　　　　右　

反時計方向(z軸時計)
　上後　　　　右後
左前右　→　上前下
　下　　　　　左　
*/