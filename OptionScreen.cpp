#include "OptionScreen.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

#include "SystemConfig.h"
#include "DebugText.h"
#include "ButtonGP.h"
#include "ControlSlider.h"
#include "Frame.h"

using KEY = SystemConfig::KEY;
//コンストラクタ
OptionScreen::OptionScreen(GameObject* parent) :
    Screen(parent, "OptionScreen"),
    hBg_(-1),
    pFrame(nullptr),
    backBtn(nullptr),
    debugtext(nullptr),
    pSlider(nullptr)
{
    std::fill_n(testBtn, 7, nullptr);
    std::fill_n(debugStr, 20, "");
}

//デストラクタ
OptionScreen::~OptionScreen()
{
}

//初期化
void OptionScreen::Initialize()
{
    //背景
    hBg_ = Image::Load("Screen/black.png");
    Image::SetAlpha(hBg_, 128);

    //フレーム
    pFrame = Instantiate<Frame>(this);
    pFrame->ChangeTheme("Screen/frame256.png", 64);
    pFrame->ChangeMode(Frame::MODE::AUTO_ASPECT, 0.8f, 0.8f, 0.f, 0.f);

    backBtn = Instantiate<ButtonGP>(this);
    backBtn->SetText("BACK");
    backBtn->SetAction(0);
    backBtn->SetPosition(0, 266, 0);
    backBtn->SetScale(2, 0.66f, 1);

    string testText[] = { "640x360", "1280x720", "1600x900", "1920x1080","fs on", "fs off","iniSave" };
    for (int i = 0; i < 7; i++) {
        testBtn[i] = Instantiate<ButtonGP>(this);
        testBtn[i]->SetText(testText[i]);
        //testBtn[i]->SetTextSize
        testBtn[i]->SetAction(i + 1);
        if (i < 3)testBtn[i]->SetPosition(-320, -180 + i * 150, 0);
        else if (i < 6)testBtn[i]->SetPosition(0, -180 + (i - 3) * 150, 0);
        else if (i < 9)testBtn[i]->SetPosition(320, -180 + (i - 6) * 150, 0);
        //testBtn[i]->SetPosition(0, -600 + i * 200, 0);
        //testBtn[i]->SetScale(1, 0.66f, 1);
    }

    pSlider = Instantiate<ControlSlider>(this);

    //デバッグ用
    debugtext = Instantiate<DebugText>(this);
    for (int i = 0; i < 20; i++) {
        debugtext->AddStrPtr(&debugStr[i]);
    }

}

//更新
void OptionScreen::Update()
{
    //もどる
    if (Input::IsKeyDown(SystemConfig::GetKey(KEY::KEY_ESC))) {
        Prev();
    }

    UpdateStr();
}

void OptionScreen::UpdateStr()
{
    //コピペで使いやすいように汎用化しました
    using std::to_string;
    debugStr[0] = "screen=" + to_string(SystemConfig::windowWidth) + "x" + to_string(SystemConfig::windowHeight);
    debugStr[1] = "mouse=(" + to_string((int)Input::GetMousePosition(true).x) + ", " + to_string((int)Input::GetMousePosition(true).y) + ")";
    debugStr[2] = "scale(optionscreen):" + to_string(transform_.scale_.x);
    debugStr[3] = "monitor=:" + to_string(GetSystemMetrics(SM_CXSCREEN)) + "x" + to_string(GetSystemMetrics(SM_CYSCREEN));
    debugStr[4] = pSlider->GetDebugStr(1);
    debugStr[5] = pSlider->GetDebugStr(2);
    debugStr[6] = pSlider->GetDebugStr(3);
    debugStr[8] = backBtn->GetDebugStr(7);
}

//描画
void OptionScreen::Draw()
{
    //背景
    Image::SetTransform(hBg_, transform_);
    Image::Draw(hBg_);
    //枠
    pFrame->DrawFrame();
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
    case 1: SystemConfig::SetWindowSize(640, 360); break;
    case 2: SystemConfig::SetWindowSize(1280, 720); break;
    case 3: SystemConfig::SetWindowSize(1600, 900); break;
    case 4: SystemConfig::SetWindowSize(1920, 1080); break;
    case 5: SystemConfig::SetFullScreen(true);  break;
    case 6: SystemConfig::SetFullScreen(false); break;
    case 7: SystemConfig::SaveConfig(); break;
    }
}
