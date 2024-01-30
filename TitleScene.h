#pragma once
#include "Engine/GameObject.h"

class Text;
class TitleButton;
class DebugText;

class TitleScene : public GameObject
{
	enum Img {
		PIC_BACKGROUND,
		PIC_TITLE,
		PIC_CHARACTER,
		SEL_CHOOSE,
		MAX
	};
	enum SELECT_STATE {
		S_SEL_START,
		S_SEL_CREDIT,
		S_SEL_OPTION,
		S_SEL_EXIT,
	};
	enum MANIP_TARGET {
		MANIP_MAIN,
		MANIP_FILE_LIST,
		MANIP_CREDIT,
		MANIP_OPTION,
		MANIP_CONFIRM_WINDOW,

	};
	int easeNum = 41;
	int hPict_[Img::MAX];
	Transform ringTra;
	Text* newText;
	std::string TitleImgFileName(Img E_IMG);

	SELECT_STATE selectState_;
	MANIP_TARGET manipTarget;
	void Run(SELECT_STATE& ss);

	TitleButton* newBtn;
	DebugText* debugText;
	std::string debugStr[20];

public:
	TitleScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};