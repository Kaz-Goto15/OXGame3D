#pragma once
#include "Engine/GameObject.h"

class Text;
class DebugText;

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
	static const int DRAW_TIME = 30;
	static const int FADE_TIME = 60;
	static const int FADEIN_EASE_NO = 23, FADEOUT_EASE_NO = 22;
	static const int ALPHA_MAX = 265, ALPHA_ZERO = 0;

	int hLogo_[LOGO_COUNT];
	int queue_, drawTime_, fadeTime_;
	int imageAlpha_;
	enum STATE {
		S_SPLASH_END,
		S_SPLASH_FADEIN,
		S_SPLASH_IDLE,
		S_SPLASH_FADEOUT,
	}state_ = S_SPLASH_END;

	void End();
	void FadeIn();
	void Idle();
	void FadeOut();

	void Skip();
	DebugText* debugTxt;
	std::string msg[3];
};

/*
fadein �C�[�W���O�ԍ��ɉ����ē����x�ύX�@0��100��idle SPACE:end
idle �w�莞�ԑҋ@�@�w�莞�Ԓ��߂�fadeout�� SPACE:end
fadeout �C�[�W���O�ԍ��ɉ����ē����x�ύX�@100��0��end�� SPACE:end
end �\��������̂������fadein �Ȃ���΃^�C�g���V�[����
*/