#include "OptionScreen.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

#include "SystemConfig.h"
#include "DebugText.h"
#include "ButtonEx.h"
//#include "ControlSlider.h"
#include "Frame.h"

using KEY = SystemConfig::KEY;
//コンストラクタ
OptionScreen::OptionScreen(GameObject* parent) :
	Screen(parent, "OptionScreen"),
	hBg_(-1),
	pFrame(nullptr),
	btnSize({0.2f,0.2f}),
	debugtext(nullptr)
{
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

	//ボタン初期化
	string buttonTexts[] = { "RESET", "BACK", "640x360", "1280x720", "1600x900", "1920x1080","fullscreen on", "fullscreen off","save setting" };
	for (int i = 0; i < BUTTON_PROC::BTN_MAX; i++){
		buttons.push_back(Instantiate<ButtonEx>(this));
		buttons[i]->SetText(buttonTexts[i]);
		buttons[i]->SetActionHandle(i);
		buttons[i]->EnDecideKey(true);
		if (i <= BTN_BACK) {    //フレーム外のボタンならば
			buttons[i]->SetPosition(-180 + i * 360, 266);
			buttons[i]->SetSize(0.2f, 0.18f);
		}
		else {
			buttons[i]->SetFont(TextLoader::TEXT_SOURCE::GAKUMARU_16px);
			buttons[i]->SetSize(btnSize.x, btnSize.y);
			int tmp = i - BTN_BACK - 1;
			if (tmp < 3)buttons[i]->SetPosition(-320, -180 + tmp * 150);
			else if (tmp < 6)buttons[i]->SetPosition(0, -180 + (tmp - 3) * 150);
			else if (tmp < 9)buttons[i]->SetPosition(320, -180 + (tmp - 6) * 150);
		}
	}

	//ボタン集合リンク・ボタン移動
	for (int i = 0; i < BUTTON_PROC::BTN_MAX; i++) {
		if (i <= BTN_BACK) {
			buttons[i]->SetNextKey(ButtonEx::DIR_UP, buttons[BTN_SIZE900p]);
			switch (i)
			{
			case OptionScreen::BTN_RESET:
				buttons[i]->SetNextKey(ButtonEx::DIR_RIGHT, buttons[BTN_BACK]);
				break;
			case OptionScreen::BTN_BACK:
				buttons[i]->SetNextKey(ButtonEx::DIR_LEFT, buttons[BTN_RESET]);
				break;
			}
		}
		else {
			int tmp = i - BTN_BACK - 1;
			//上処理
			if (tmp % 3 != 0) {
				buttons[i]->SetNextKey(ButtonEx::DIR_UP, buttons[i - 1]);
			}

			//下処理
			if (tmp % 3 != 2) {
				//outOfRange
				if (i + 1 < BTN_MAX) {
					buttons[i]->SetNextKey(ButtonEx::DIR_DOWN, buttons[i + 1]);
				}
			}
			else {
				buttons[i]->SetNextKey(ButtonEx::DIR_DOWN, buttons[BTN_BACK]);
			}

			//右処理
			if (tmp < 6) {
				//outOfRange
				if (i + 3 < BTN_MAX) {
					buttons[i]->SetNextKey(ButtonEx::DIR_RIGHT, buttons[i + 3]);
				}
			}

			//左処理
			if (tmp >= 3) {
				buttons[i]->SetNextKey(ButtonEx::DIR_LEFT, buttons[i - 3]);
			}
		}

		for (int j = 0; j < BUTTON_PROC::BTN_MAX; j++) {
			if (i != j)

				buttons[i]->AddLinkButton(buttons[j]);
		}
	}

	//pSlider = Instantiate<ControlSlider>(this);

	//デバッグ用
	debugtext = Instantiate<DebugText>(this);
	for (int i = 0; i < 20; i++) {
		debugtext->AddStrPtr(&debugStr[i]);
	}

}

//更新
void OptionScreen::Update()
{

	//全て未選択のときの処理
	bool unselected = true;
	for (auto& b : buttons) {
		if (b->GetState() == ButtonEx::STATE::SELECT) {
			unselected = false;
			break;
		}
	}
	if (unselected &&
		(Input::IsKeyDown(SystemConfig::GetKey(SystemConfig::KEY::KEY_LEFT)) ||
			Input::IsKeyDown(SystemConfig::GetKey(SystemConfig::KEY::KEY_RIGHT)) || 
			Input::IsKeyDown(SystemConfig::GetKey(SystemConfig::KEY::KEY_UP)) || 
			Input::IsKeyDown(SystemConfig::GetKey(SystemConfig::KEY::KEY_DOWN)) )
		) {
		buttons[0]->ChangeState(ButtonEx::STATE::SELECT);
	}

	//Escでももどる
	if (Input::IsKeyDown(SystemConfig::GetKey(KEY::KEY_ESC))) {
		Prev();
	}

	UpdateStr();
}

void OptionScreen::UpdateStr()
{
	//コピペで使いやすいようにちょっとだけ汎用化しました
	using std::to_string;
	debugStr[0] = "screen=" + to_string(SystemConfig::windowWidth) + "x" + to_string(SystemConfig::windowHeight);
	debugStr[1] = "mouse=(" + to_string((int)Input::GetMousePosition(true).x) + ", " + to_string((int)Input::GetMousePosition(true).y) + ")";
	debugStr[2] = "scale(optionscreen):" + to_string(transform_.scale_.x);
	debugStr[3] = "monitor=:" + to_string(GetSystemMetrics(SM_CXSCREEN)) + "x" + to_string(GetSystemMetrics(SM_CYSCREEN));
	//debugStr[4] = pSlider->GetDebugStr(1);
	//debugStr[5] = pSlider->GetDebugStr(2);
	//debugStr[6] = pSlider->GetDebugStr(3);
	debugStr[8] = buttons[0]->GetDebugStr(7);
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
	switch (hAct)
	{
	case OptionScreen::BTN_RESET:
		SystemConfig::SetWindowSize(1280, 720);
		SystemConfig::SetFullScreen(false);
		break;
	case OptionScreen::BTN_BACK:            Prev();				break;
	case OptionScreen::BTN_SIZE360p:        SystemConfig::SetWindowSize(640, 360); break;
	case OptionScreen::BTN_SIZE720p:        SystemConfig::SetWindowSize(1280, 720); break;
	case OptionScreen::BTN_SIZE900p:        SystemConfig::SetWindowSize(1600, 900); break;
	case OptionScreen::BTN_SIZE1080p:       SystemConfig::SetWindowSize(1920, 1080); break;
	case OptionScreen::BTN_FULLSCREEN:      SystemConfig::SetFullScreen(true);  break;
	case OptionScreen::BTN_OFF_FULLSCREEN:  SystemConfig::SetFullScreen(false); break;
	case OptionScreen::BTN_INI_SAVE:        SystemConfig::SaveConfig(); break;
	}
}
