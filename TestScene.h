#pragma once
#include "Engine/GameObject.h"

class Text;
class Screen;
class ButtonEx;
class TestScene : public GameObject
{
	int easeNum = 41;
	int hPict_ = -1;
	Transform ringTra;
	Text* newText;
	Text* descrText;
	Screen* pScreen;
	ButtonEx* btn;
public:
	TestScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};