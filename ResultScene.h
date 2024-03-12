#pragma once
#include "Engine/GameObject.h"

class ResultScene : public GameObject
{
	int temp;
	int count;
	const int MAX_COUNT = 300;
public:
	ResultScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};