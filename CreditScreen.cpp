#include "CreditScreen.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

#include "SystemConfig.h"
#include "ButtonEx.h"
#include "Frame.h"

//コンストラクタ
CreditScreen::CreditScreen(GameObject* parent):
    Screen(parent, "CreditScreen"),
    pFrame(nullptr),
    framePosY(-55),
    frameGrid_(64),
    backBtn(nullptr)
{
    std::fill_n(hPict_, PIC_MAX, -1);
}

//デストラクタ
CreditScreen::~CreditScreen()
{
}

//初期化
void CreditScreen::Initialize()
{
    //画像
    hPict_[PIC_BACKGROUND] = Image::Load("Screen/black.png");
    hPict_[PIC_DESCRIPTION] = Image::Load("Screen/descr2.png");
    Image::SetAlpha(hPict_[PIC_BACKGROUND], 128);

    //もどるボタン
    backBtn = Instantiate<ButtonEx>(this);
    backBtn->SetButtonImages(32, "btnDefIdle32.png", "btnDefSelect32.png", "btnDefPush32.png", "btnDefSelected32.png");
    backBtn->SetShadowImage("btnDefShadow32.png");
    backBtn->SetText("BACK");
    backBtn->SetPosition(0, 280);
    backBtn->EnDrawShadow(true);
    backBtn->SetActionHandle(0);
    backBtn->SetSize(0.2f, 0.15f);
    backBtn->SetSelectedAudio(AudioManager::SE_CANCEL);
    
    //フレーム
    pFrame = Instantiate<Frame>(this);
    pFrame->ChangeMode(Frame::MODE::AUTO_ASPECT, 0.8f, 0.75f,0.0f,framePosY);

}

//更新
void CreditScreen::Update()
{
    if (SystemConfig::IsDebug()) {
        //もどる
        if (Input::IsKeyDown(DIK_P)) {
            ButtonAct(0);
        }
    }
}

//描画
void CreditScreen::Draw()
{
    Transform creditTra;
    creditTra.position_.y = framePosY;
    Transform frameTra;

    for (PIC p = static_cast<PIC>(0); p < PIC_MAX; p = static_cast<PIC>(p + 1)) {
        switch (p)
        {
        case CreditScreen::PIC_BACKGROUND:
            Image::SetTransform(hPict_[p], transform_);
            Image::Draw(hPict_[p]);

            //フレーム描画
            pFrame->DrawFrame();
            break;
        case CreditScreen::PIC_DESCRIPTION:
            Image::SetTransform(hPict_[p], creditTra);
            Image::Draw(hPict_[p]);
            break;
        }
    }
}

//開放
void CreditScreen::Release()
{
}

void CreditScreen::ButtonAct(int hAct)
{
    if (hAct == 0) {
        Prev();
    }
}
