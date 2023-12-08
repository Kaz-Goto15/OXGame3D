#include "HelpBar.h"
#include "Engine/Image.h"

//コンストラクタ
HelpBar::HelpBar(GameObject* parent)
    :GameObject(parent, "HelpBar")
{
}

//デストラクタ
HelpBar::~HelpBar()
{
}

//初期化
void HelpBar::Initialize()
{
    hPictBar_ = Image::Load("bar.png");
}

//更新
void HelpBar::Update()
{
}

//描画
void HelpBar::Draw()
{
    if (enScreen_) {
        Image::Draw(hPictBar_);

    }
}

//開放
void HelpBar::Release()
{
}

void HelpBar::Show() {
    enScreen_ = true;
}
void HelpBar::Hide() {
    enScreen_ = false;
}

void HelpBar::AddInput(SUPPORT_INPUT si) {
    supportInputList_.push_back(si);
}