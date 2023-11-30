#include "SplashScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"

SplashScene::SplashScene(GameObject* parent)
	: GameObject(parent, "SplashScene"),
	queue_(-1)
{}
void SplashScene::Initialize() {
	hLogo_[0] = Image::Load("Spl\\0.png");
	hLogo_[1] = Image::Load("Spl\\1.png");
}
void SplashScene::Update() {
	switch (state_){
	case SplashScene::S_SPLASH:		Splash();		break;
	case SplashScene::S_NEXT_SCENE:	NextScene();	break;
	}
}
void SplashScene::Draw() {
	if (isDisplaying) {
		Image::Draw(hLogo_[queue_]);
	}

}
void SplashScene::Release() {}

void SplashScene::SplashStart()
{
	drawTime_ = 0;
	queue_++;
	state_ = S_SPLASH;
}

void SplashScene::Splash()
{
	if (isDisplaying) {

	}
	else {
		queue_++;
		isDisplaying = true;
		if (!(queue_ < LOGO_COUNT)) {
			state_ = S_NEXT_SCENE;
		}
	}

}

void SplashScene::NextScene()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_TEST);
}
