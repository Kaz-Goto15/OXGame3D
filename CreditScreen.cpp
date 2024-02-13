#include "CreditScreen.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

#include "SystemConfig.h"
#include "DebugText.h"

//コンストラクタ
CreditScreen::CreditScreen(GameObject* parent):
    Screen(parent, "CreditScreen"),
    frameMargin(0,0,0,0),
    frameScale(1.0f),
    debugtext(nullptr)
{
    std::fill_n(hPict_, PIC_MAX, -1);
    std::fill_n(debugStr, 20, "");
}

//デストラクタ
CreditScreen::~CreditScreen()
{
}

//初期化
void CreditScreen::Initialize()
{
    hPict_[PIC_BACKGROUND] = Image::Load("black.png");
    hPict_[PIC_BASIC_FRAME_TEX] = Image::Load("frame256.png");
    hPict_[PIC_DESCRIPTION] = Image::Load("descr.png");
    Image::SetAlpha(hPict_[PIC_BACKGROUND], 128);
    //keyHelp.push_back(KEY_CANCEL, "戻る");
    
    debugtext = Instantiate<DebugText>(this);
    for (int i = 0; i < 20; i++) {
        debugtext->AddStrPtr(&debugStr[i]);
    }
    frameMargin = { 50,50,200,50 };   //コンストラクタでやるとxが-1になる 原因不明のためこっちで
}

//更新
void CreditScreen::Update()
{
    //もどる
    if (Input::IsKeyDown(DIK_P)) {
        Prev();
    }

    //枠が各祝する
    if (Input::IsKey(DIK_6)) {
        frameScale -= 0.01f;
    }
    if (Input::IsKey(DIK_7)) {
        frameScale += 0.01f;
    }
}

//描画
void CreditScreen::Draw()
{
    for (int i = 0; i < PIC_MAX; i++) {
        if (i == PIC_BASIC_FRAME_TEX) {
            Transform frameTra;
            frameTra.SetCenter(0, 0, 0);
            frameTra.IsCalcCenterPoint(true);
            int edge = 64;
            Image::SetRect(hPict_[PIC_BASIC_FRAME_TEX], 0, 0, edge, edge);

            using namespace SystemConfig;
            //frame構築
            for (int y = 0; y < 3; y++) {
                switch (y) {
                case 0:
                    frameTra.position_.y = (float)(-screenHeight + (frameMargin.x + frameMargin.z + edge)) / 2.0f;
                    frameTra.scale_.y = 1;
                    break;
                case 1:
                    frameTra.position_.y = 0;
                    frameTra.scale_.y = (float)(screenHeight - (frameMargin.x + frameMargin.z + edge + edge)) / (float)edge;
                    break;
                case 2:
                    frameTra.position_.y = (float)(screenHeight - (frameMargin.x + frameMargin.z + edge)) / 2.0f;
                    frameTra.scale_.y = 1;
                    break;
                }
                for (int x = 0; x < 3; x++) {
                    switch (x) {
                    case 0:
                        frameTra.position_.x = (float)(-screenWidth + (frameMargin.y + frameMargin.w + edge)) / 2.0f;
                        frameTra.scale_.x = 1;
                        break;
                    case 1:
                        frameTra.position_.x = 0;
                        frameTra.scale_.x = (float)(screenWidth - (frameMargin.y + frameMargin.w + edge + edge)) / (float)edge;
                        break;
                    case 2:
                        frameTra.position_.x = (float)(screenWidth - (frameMargin.y + frameMargin.w + edge)) / 2.0f;
                        frameTra.scale_.x = 1;
                        break;
                    }

                    Image::SetRect(hPict_[PIC_BASIC_FRAME_TEX], x * edge, y * edge, edge, edge);
                    Transform tmp = frameTra;
                    tmp.SetReSize(frameScale);

                    Image::SetTransform(hPict_[PIC_BASIC_FRAME_TEX], tmp);
                    Image::Draw(hPict_[PIC_BASIC_FRAME_TEX]);
                }
            }
        }
        else {
            Image::SetTransform(hPict_[i], transform_);
            Image::Draw(hPict_[i]);
        }
    }
    //debugStr[9] = "scr:" + std::to_string(screenWidth) + "," + std::to_string(screenHeight);
    //debugStr[10] = "mousePos: " + std::to_string(Input::GetMousePosition().x-640) + ", " + std::to_string(Input::GetMousePosition().y-360);
}

//開放
void CreditScreen::Release()
{
}