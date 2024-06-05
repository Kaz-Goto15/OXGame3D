#include "ModelTestScreen.h"
#include "Engine/Input.h"

#include "SystemConfig.h"
#include "DebugText.h"
#include "Cube.h"
#include "./Engine/Camera.h"
//コンストラクタ
ModelTestScreen::ModelTestScreen(GameObject* parent) :
    Screen(parent, "ModelTestScreen"),
    hModel(-1),
    debugtext(nullptr)
{
}

//デストラクタ
ModelTestScreen::~ModelTestScreen()
{
}

//初期化
void ModelTestScreen::Initialize()
{
    cube.resize(3, vector<vector<Cube*>>(3, vector<Cube*>(3, nullptr)));

    for (auto& cx : cube) {
        for (auto& cy : cx) {
            for (auto& cz : cy) {
                cz = Instantiate<Cube>(this);
            }
        }
    }
    for (int x = 0; x < cube.size();x++) {
        for (int y = 0; y < cube[0].size();y++) {
            for (int z = 0; z < cube[0][0].size();z++) {
                cube[x][y][z]->SetPosition(x - 1, y - 1, z - 1);
            }
        }
    }

    debugtext = Instantiate<DebugText>(this);
    for (int i = 0; i < 20; i++) {
        debugtext->AddStrPtr(&debugStr[i]);
    }
}

//更新
void ModelTestScreen::Update()
{
    //もどる
    if (Input::IsKeyDown(DIK_P)) {
        Prev();
    }

    //kaiten
    int column = 0;
    if (Input::IsKey(DIK_LSHIFT)) {
        if (Input::IsKey(DIK_LALT))column = 2;
        else column = 1;
    }
    if (Input::IsKey(DIK_Q)) {
        CubeRotate(CCW,column, 45);
    }
    if (Input::IsKey(DIK_E)) {
        CubeRotate(CW, column, 45);
    }
    if (Input::IsKey(DIK_W)) {
        CubeRotate(BACK, column, 45);
    }
    if (Input::IsKey(DIK_S)) {
        CubeRotate(FRONT, column, 45);
    }
    if (Input::IsKey(DIK_A)) {
        CubeRotate(LEFT, column, 45);
    }
    if (Input::IsKey(DIK_D)) {
        CubeRotate(RIGHT,column, 45);
    }
    UpdateStr();
}

void ModelTestScreen::UpdateStr()
{
    using std::to_string;
    debugStr[0] = "scrH:" + to_string(SystemConfig::windowHeight) + "scrW:" + to_string(SystemConfig::windowWidth);
}

//描画
void ModelTestScreen::Draw()
{

}

//開放
void ModelTestScreen::Release()
{
}

void ModelTestScreen::CubeRotate(ROTATE rot, int col, float value)
{
    switch (rot)
    {
    case ModelTestScreen::FRONT:
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                cube[col][y][z]->SetParent(cube[col][1][1]);
                //cube[col][y][z]->SetParent(cube[col][1][1]);
            }
        }
        cube[col][1][1]->SetRotate(value, 0, 0);
        break;
    case ModelTestScreen::BACK:
        break;
    case ModelTestScreen::LEFT:
        break;
    case ModelTestScreen::RIGHT:
        break;
    case ModelTestScreen::CW:
        break;
    case ModelTestScreen::CCW:
        break;
    default:
        break;
    }
}
