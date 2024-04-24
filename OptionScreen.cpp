#include "OptionScreen.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

#include "SystemConfig.h"
#include "DebugText.h"
#include "ButtonGP.h"

//コンストラクタ
OptionScreen::OptionScreen(GameObject* parent) :
    Screen(parent, "OptionScreen"),
    frameMargin(0, 0, 0, 0),
    frameScale(1.0f),
    framePos(0, 50, 0),
    debugtext(nullptr)
{
    std::fill_n(hPict_, PIC_MAX, -1);
    std::fill_n(debugStr, 20, "");
}

//デストラクタ
OptionScreen::~OptionScreen()
{
}

//初期化
void OptionScreen::Initialize()
{
    hPict_[PIC_BACKGROUND] = Image::Load("Screen/black.png");
    hPict_[PIC_BASIC_FRAME_TEX] = Image::Load("Screen/frame256.png");
    //hPict_[PIC_DESCRIPTION] = Image::Load("descr.png");
    Image::SetAlpha(hPict_[PIC_BACKGROUND], 128);

    debugtext = Instantiate<DebugText>(this);
    for (int i = 0; i < 20; i++) {
        debugtext->AddStrPtr(&debugStr[i]);
    }
    frameMargin = { 50,50,150,50 };   //コンストラクタでやるとxが-1になる 原因不明のためこっちで
    backBtn = Instantiate<ButtonGP>(this);
    backBtn->SetText("BACK");
    backBtn->SetAction(0);
    backBtn->SetPosition(0, 266, 0);
    backBtn->SetScale(2, 0.66f, 1);

    string testText[] = { "640,360", "1280x720", "1600x900", "fs on", "fs off"};
    for (int i = 0; i < 5; i++) {
        testBtn[i] = Instantiate<ButtonGP>(this);
        testBtn[i]->SetText(testText[i]);
        testBtn[i]->SetAction(i+1);
        testBtn[i]->SetPosition(0, 50 + i * 50, 0);
        testBtn[i]->SetScale(1, 0.66f, 1);
    }
}

//更新
void OptionScreen::Update()
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
    if (Input::IsKey(DIK_8)) {
        framePos.y -= 1.0f;
    }
    if (Input::IsKey(DIK_9)) {
        framePos.y += 1.0f;
    }
}

//描画
void OptionScreen::Draw()
{
    for (int i = 0; i < PIC_MAX; i++) {
        if (i == PIC_BASIC_FRAME_TEX) {
            Transform frameTra;
            frameTra.SetCenter(framePos);   //中心点を移動して座標決めてるので注意 具体的には符号逆転する(中心点を動かすと必然的に逆側に移動するため)
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

                    Image::SetTransform(hPict_[i], tmp);
                    Image::Draw(hPict_[i]);

                    //                XMFLOAT3 tmpPos = {
                    //(tmp.position_.x - tmp.center_.x) * (tmp.scale_.x * tmp.reSize_.x),// + center_.x,
                    //(tmp.position_.y - tmp.center_.y) * (tmp.scale_.y * tmp.reSize_.y),// + center_.y,
                    //(tmp.position_.z - tmp.center_.z) * (tmp.scale_.z * tmp.reSize_.z),// + center_.z
                    //                };
                    //                debugStr[y * 3 + x] =
                    //                    "frame" + std::to_string(y * 3 + x) + ": " + std::to_string(x) + ", " + std::to_string(y) +
                    //                    " tra: pos(" + std::to_string((int)tmp.position_.x) + "," + std::to_string((int)tmp.position_.y) +
                    //                    ") scl(" + std::to_string(tmp.scale_.x) + "," + std::to_string(tmp.scale_.y) + ")" +
                    //                    "cv(" + std::to_string(tmpPos.x) + "," + std::to_string(tmpPos.y)
                    //                    ;

                }
                //debugStr[9] = "scr:" + std::to_string(screenWidth) + "," + std::to_string(screenHeight);
                //debugStr[10] = "mousePos: " + std::to_string(Input::GetMousePosition().x - 640) + ", " + std::to_string(Input::GetMousePosition().y - 360);
                //debugStr[11] = "center:" + std::to_string(framePos.x) + "," + std::to_string(framePos.y);
                //debugStr[12] = "resize:" + std::to_string(frameScale);
            }
        }
        else {
            Image::SetTransform(hPict_[i], transform_);
            Image::Draw(hPict_[i]);
        }

    }

}

//開放
void OptionScreen::Release()
{
}

void OptionScreen::ButtonAct(int hAct)
{
    if (hAct == 0) {
        Prev();
    }

    //test
    switch (hAct) {
    case 1: SystemConfig::SetScreenSize(640, 360); break;
    case 2: SystemConfig::SetScreenSize(1280, 720); break;
    case 3: SystemConfig::SetScreenSize(1600, 900); break;
    case 4: SystemConfig::SetFullScreen(true);  break;
    case 5: SystemConfig::SetFullScreen(false); break;

    }
}
