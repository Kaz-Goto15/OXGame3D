#include "CreditScreen.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

#include "SystemConfig.h"
#include "ButtonGP.h"

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
    hPict_[PIC_BASIC_FRAME_TEX] = Image::Load("Screen/frame256_2.png");
    hPict_[PIC_DESCRIPTION] = Image::Load("Screen/descr2.png");
    Image::SetAlpha(hPict_[PIC_BACKGROUND], 128);
    
    frameMargin = { 50,50,150,50 };   //コンストラクタでやるとxが-1になる 原因不明のためこっちで
    backBtn = Instantiate<ButtonGP>(this);
    backBtn->SetText("BACK");
    backBtn->SetAction(0);
    backBtn->SetPosition(0, 280, 0);
    backBtn->SetScale(0.75f);
    backBtn->SetSound(AudioManager::SE_CANCEL);
    
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
            break;
        case CreditScreen::PIC_BASIC_FRAME_TEX:
            frameTra = creditTra;
            Image::SetRect(hPict_[PIC_BASIC_FRAME_TEX], 0, 0, frameLength, frameLength);

            using namespace SystemConfig;
            //frame構築
            for (int y = 0; y < 3; y++) {
                switch (y) {
                case 0:
                    frameTra.position_.y = Half((float)(- windowHeight + (frameMargin.x + frameMargin.z + frameLength)));
                    frameTra.scale_.y = 1;
                    break;
                case 1:
                    frameTra.position_.y = 0;
                    frameTra.scale_.y = (float)(windowHeight - (frameMargin.x + frameMargin.z + frameLength + frameLength)) / (float)frameLength;
                    break;
                case 2:
                    frameTra.position_.y = Half((float)(windowHeight - (frameMargin.x + frameMargin.z + frameLength)));
                    frameTra.scale_.y = 1;
                    break;
                }
                for (int x = 0; x < 3; x++) {
                    switch (x) {
                    case 0:
                        frameTra.position_.x = Half((float)(-windowWidth + (frameMargin.y + frameMargin.w + frameLength)));
                        frameTra.scale_.x = 1;
                        break;
                    case 1:
                        frameTra.position_.x = 0;
                        frameTra.scale_.x = (float)(windowWidth - (frameMargin.y + frameMargin.w + frameLength + frameLength)) / (float)frameLength;
                        break;
                    case 2:
                        frameTra.position_.x = Half((float)(windowWidth - (frameMargin.y + frameMargin.w + frameLength)));
                        frameTra.scale_.x = 1;
                        break;
                    }

                    Image::SetRect(hPict_[PIC_BASIC_FRAME_TEX], x * frameLength, y * frameLength, frameLength, frameLength);
                    Transform tmp = frameTra;

                    tmp.SetReSize(frameScale);

                    Image::SetTransform(hPict_[p], tmp);
                    Image::Draw(hPict_[p]);
                }
            }
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
