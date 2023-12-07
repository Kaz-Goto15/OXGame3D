#pragma once
#include "Engine/GameObject.h"

class Text;

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
	int easeNum = 41;
	int hPict_[Img::MAX];
	Transform ringTra;
	Text* newText;
	std::string TitleImgFileName(Img E_IMG);

	SELECT_STATE selectState_;

	void Run(SELECT_STATE& ss);

public:
	TitleScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};