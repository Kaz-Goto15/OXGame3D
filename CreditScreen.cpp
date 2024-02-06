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
    hPict_ = Image::Load("black.png");
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
    Image::SetTransform(transform_);
    Image::Draw(hPict_);
}

//開放
void CreditScreen::Release()
{
}