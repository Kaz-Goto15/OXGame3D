#pragma once
#include "Engine/GameObject.h"

class Text;
class TitleButton;
class DebugText;
class SceneManager;
class Screen;

class TitleScene : public GameObject
{
	enum Img {
		PIC_BACKGROUND,
		PIC_TITLE,
		PIC_CHARACTER,
		//SEL_CHOOSE,
		PIC_MAX
	};
	enum SELECT_STATE {
		S_SEL_START,
		S_SEL_CREDIT,
		S_SEL_OPTION,
		S_SEL_EXIT,
		S_SEL_MAX
	};
	int easeNum = 41;
	int hPict_[Img::PIC_MAX];
	Transform ringTra;
	std::string TitleImgFileName(Img E_IMG);

	SELECT_STATE selectState_;
	//void Run(SELECT_STATE& ss);

	TitleButton* btn[S_SEL_MAX];
	DebugText* debugText;
	std::string debugStr[20];
	void InitButton(SELECT_STATE ss, std::string text, XMFLOAT2 pos);

	SceneManager* pSceneManager;
	Screen* pScreen;
	int hSound_;
public:
	TitleScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void ButtonAct(int hAct);
};