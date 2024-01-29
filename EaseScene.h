#pragma once
#include "Engine/GameObject.h"

class Text;

class EaseScene : public GameObject
{
	int easeNum = 3;
	int hPict_ = -1;
	Transform ringTra;
	XMFLOAT3 camPos;
	Text* newText, *newmsgText;
	int progress = 0;
	int hModel_ = -1;
	int hImg_ = -1;
	XMFLOAT3 nullScale_;
public:
	EaseScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};