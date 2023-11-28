#pragma once
#include "Engine/GameObject.h"

class SplashScene : public GameObject
{
public:
	SplashScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:
	static const int LOGO_COUNT = 2;
	int hLogo_[LOGO_COUNT];
	bool isDisplaying = false;
	int queue_;
	enum STATE {
		S_SPLASH,
		S_NEXT_SCENE,
	}state_ = S_SPLASH;

	void Splash();
	void NextScene();
};