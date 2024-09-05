#include "CreditScreen.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

#include "SystemConfig.h"
#include "ButtonGP.h"
#include "Frame.h"
//コンストラクタ
CreditScreen::CreditScreen(GameObject* parent):
    Screen(parent, "CreditScreen"),
    frameMargin(0,0,0,0),
    frameScale(1.0f),
    framePos(0,50,0),
    frameLength(64)
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
    hPict_[PIC_BACKGROUND] = Image::Load("Screen/black.png");
    hPict_[PIC_DESCRIPTION] = Image::Load("Screen/descr2.png");
    Image::SetAlpha(hPict_[PIC_BACKGROUND], 128);
    
    frameMargin = { 50,50,150,50 };   //コンストラクタでやるとxが-1になる 原因不明のためこっちで
    backBtn = Instantiate<ButtonGP>(this);
    backBtn->SetText("BACK");
    backBtn->SetAction(0);
    backBtn->SetPosition(0, 280, 0);
    backBtn->SetScale(0.75f);
    backBtn->SetSound(AudioManager::SE_CANCEL);
    
    frame = Instantiate<Frame>(this);
    //frame->ChangeMode(Frame::MODE::CONST_MARGIN, 50, 50, 100, 50);
    frame->ChangeMode(Frame::MODE::AUTO_ASPECT, 0.5f, 0.75f);
    frame->SetPosition(50, 100,0);

}

//更新
void CreditScreen::Update()
{
    if (SystemConfig::IsDebug()) {
        //もどる
        if (Input::IsKeyDown(DIK_P)) {
            Prev();
        }

        //枠が拡縮する
        //if (Input::IsKey(DIK_6)) {
        //    frameScale -= 0.01f;
        //}
        //if (Input::IsKey(DIK_7)) {
        //    frameScale += 0.01f;
        //}
        //if (Input::IsKey(DIK_8)) {
        //    framePos.y -= 1.0f;
        //}
        //if (Input::IsKey(DIK_9)) {
        //    framePos.y += 1.0f;
        //}
    }
}

//描画
void CreditScreen::Draw()
{
    Transform creditTra;
    creditTra.SetCenter(framePos);
    creditTra.IsCalcCenterPoint(true);
    Transform frameTra;

    for (PIC p = static_cast<PIC>(0); p < PIC_MAX; p = static_cast<PIC>(p + 1)) {
        switch (p)
        {
        case CreditScreen::PIC_BACKGROUND:
            Image::SetTransform(hPict_[p], transform_);
            Image::Draw(hPict_[p]);

            //フレーム描画
            frame->DrawFrame();
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
