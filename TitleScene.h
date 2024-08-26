#pragma once
#include "Engine/GameObject.h"

class Text;
class ButtonGP;
class DebugText;
class SceneManager;
class Screen;

class TitleScene : public GameObject
{
	enum Img {
		PIC_BACKGROUND,
		PIC_TITLE,
		PIC_WHITE,
		//SEL_CHOOSE,
		PIC_MAX
	};
	enum STATE {
		S_STANDBY,
		S_MAIN,
		S_SELECT,
	}state_;
	enum SELECT_STATE {
		S_SEL_START,
		S_SEL_CREDIT,
		S_SEL_OPTION,
		S_SEL_EXIT,
		S_SEL_MAX
	}selectState_;

	const int DEFAULT_PROGRESS;
	int progress;
	int maxProgress;
	int btnFadeEaseNo;
	const int ALPHA_ZERO, ALPHA_MAX;
	const int TitleProgPt[2] = { 60, 120 };
	const int titlePosYMove[2] = { 0, -60 };
	const int buttonXSpace = 270;
	const int buttonPosYMove[2] = { 400,240 };	//座標のこの書き方は解像度変えたときにバグるので修正したい
	int hPict_[Img::PIC_MAX];

	Text* txtPressStart;
	const XMINT2 txtPos = { 0,240 };
	const char* txt = "Press 'Space' to continue";

	Transform ringTra;
	std::string TitleImgFileName(Img E_IMG);
	//void Run(SELECT_STATE& ss);

	ButtonGP* btn[S_SEL_MAX];
	DebugText* debugText;
	std::string debugStr[20];
	void InitButton(SELECT_STATE ss, std::string text, XMINT2 pos);

	SceneManager* pSceneManager;
	Screen* pScreen;
	int hSound_;
	bool Between(float val, float min, float max) { return (min <= val && val <= max); }
public:
	TitleScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void ButtonAct(int hAct);
};