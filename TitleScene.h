#pragma once
#include "Engine/GameObject.h"

class Text;

class TitleScene : public GameObject
{
	enum Img {
		BACKGROUND,
		TITLE,
		CHARACTER,
		MAX
	};
	int easeNum = 41;
	int hPict_[Img::MAX];
	Transform ringTra;
	Text* newText;
	std::string TitleImgFileName(Img E_IMG);
public:
	TitleScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};