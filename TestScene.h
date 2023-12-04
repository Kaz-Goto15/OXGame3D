#pragma once
#include "Engine/GameObject.h"

class TestScene : public GameObject
{
	int easeNum = 1;
	int hPict_ = -1;
	Transform ringTra;
public:
	TestScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};