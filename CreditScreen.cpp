#include "CreditScreen.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

//コンストラクタ
CreditScreen::CreditScreen(GameObject* parent)
    :Screen(parent, "CreditScreen")
{
}

//デストラクタ
CreditScreen::~CreditScreen()
{
}

//初期化
void CreditScreen::Initialize()
{
    hPict_[PIC_BACKGROUND] = Image::Load("black.png");
    hPict_[PIC_BASIC_FRAME_TEX] = Image::Load("frame.png");
    hPict_[PIC_DESCRIPTION] = Image::Load("descr.png");
    Image::SetAlpha(hPict_[PIC_BACKGROUND], 128);
    //keyHelp.push_back(KEY_CANCEL, "戻る");
}

//更新
void CreditScreen::Update()
{
    if (Input::IsKeyDown(DIK_P)) {
        Prev();
    }
}

//描画
void CreditScreen::Draw()
{
    for (int i = 0; i < PIC_MAX; i++) {
        Image::SetTransform(hPict_, transform_);
        Image::Draw(hPict_);
    }
}

//開放
void CreditScreen::Release()
{
}