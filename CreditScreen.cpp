#include "CreditScreen.h"

//コンストラクタ
CreditScreen::CreditScreen(GameObject* parent)
    :GameObject(parent, "CreditScreen")
{
}

//デストラクタ
CreditScreen::~CreditScreen()
{
}

//初期化
void CreditScreen::Initialize()
{
    //keyHelp.push_back(KEY_CANCEL, "戻る");
}

//更新
void CreditScreen::Update()
{
}

//描画
void CreditScreen::Draw()
{
    if (enScreen) {
        
    }
}

//開放
void CreditScreen::Release()
{
}

void CreditScreen::Show() {
    enScreen = true;
}