#include "SplashScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Easing.h"
#include "Engine/Input.h"
#include "DebugText.h"

SplashScene::SplashScene(GameObject* parent)
	: GameObject(parent, "SplashScene"),
	queue_(-1),
	drawTime_(0),
	fadeTime_(0),
	imageAlpha_(0),
	debugTxt(nullptr)
{
	std::fill_n(hLogo_, LOGO_COUNT, -1);
	std::fill_n(msg, 3, "");

}
void SplashScene::Initialize() {
	hLogo_[0] = Image::Load("Spl\\0.png");
	hLogo_[1] = Image::Load("Spl\\1.png");

	debugTxt = Instantiate<DebugText>(this);
	debugTxt->AddStrPtr(&msg[0]);
	debugTxt->AddStrPtr(&msg[1]);
	debugTxt->AddStrPtr(&msg[2]);
}
void SplashScene::Update() {
	switch (state_)
	{
	case SplashScene::S_SPLASH_END:		End();		break;
	case SplashScene::S_SPLASH_FADEIN:	FadeIn();	break;
	case SplashScene::S_SPLASH_IDLE:	Idle();		break;
	case SplashScene::S_SPLASH_FADEOUT:	FadeOut();	break;
	}
}
void SplashScene::Draw() {
	Image::SetAlpha(hLogo_[queue_], imageAlpha_);
	Image::Draw(hLogo_[queue_]);

	msg[0] = "STATE: " + std::to_string((int)state_);
	msg[1] = "draw: " + std::to_string(drawTime_) + " fade " + std::to_string(fadeTime_);
	msg[2] = "Q: " + std::to_string(queue_);
}
void SplashScene::Release() {}

void SplashScene::End()
{
	queue_++;
	fadeTime_ = 0;
	//全部表示したらシーン切り替え
	if (queue_ >= LOGO_COUNT) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_EASE);
	}
	else {
		drawTime_ = 0;
		state_ = S_SPLASH_FADEIN;
	}
}

void SplashScene::FadeIn()
{
	fadeTime_++;
	imageAlpha_ = (int)Easing::Calc(FADEIN_EASE_NO, fadeTime_, FADE_TIME, 0, 255);

	if (fadeTime_ > FADE_TIME) {
		drawTime_ = 0;
		state_ = S_SPLASH_IDLE;
	}
	if (Input::IsKeyDown(DIK_SPACE))Skip();
}


void SplashScene::Idle()
{
	drawTime_++;

	if (drawTime_ > DRAW_TIME) {
		fadeTime_ = 0;
		state_ = S_SPLASH_FADEOUT;
	}

	if (Input::IsKeyDown(DIK_SPACE))Skip();
}

void SplashScene::FadeOut()
{
	fadeTime_++;
	imageAlpha_ = (int)Easing::Calc(FADEOUT_EASE_NO, fadeTime_, FADE_TIME, 255, 0);

	if (fadeTime_ > FADE_TIME) {
		state_ = S_SPLASH_END;
	}

	if (Input::IsKeyDown(DIK_SPACE))Skip();
}

void SplashScene::Skip()
{
	imageAlpha_ = 0;
	state_ = S_SPLASH_END;
}
