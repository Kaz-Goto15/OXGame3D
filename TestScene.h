#pragma once
#include "Engine/GameObject.h"

class Text;

class TestScene : public GameObject
{
	int easeNum = 1;
	int hPict_ = -1;
	Transform ringTra;
	Text* newText;
public:
	TestScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};