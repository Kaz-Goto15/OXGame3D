#include "Screen.h"
#include "Engine/Image.h"

//コンストラクタ
Screen::Screen(GameObject* parent) :
    GameObject(parent, "Screen"),
{
    parent->Leave();
}

//デストラクタ
Screen::~Screen()
{
}

//初期化
void Screen::Initialize()
{
}

//更新
void Screen::Update()
{
}

//描画
void Screen::Draw()
{
    if (enScreen_) {
        Image::Draw(hPictBar_);

    }
}

//開放
void Screen::Release()
{
}

void Screen::Close()
{
    this->Leave();
    GetParent()->Enter();
    CloseAnim();
    KillMe();
}

void Screen::AddInput(Screen_RESOURCE si) {
    supportInputList_.push_back(si);
}