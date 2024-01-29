#pragma once
#include "Engine/GameObject.h"

class Text;
class DebugText;

class EaseScene : public GameObject
{
	int easeNum = 3;
	int hPict_ = -1;
	Transform ringTra;
	XMFLOAT3 camPos;
	Text* newText;
	DebugText *debugText;
	std::string msg[20];
	int progress = 0;
	int hModel_ = -1;
	int hImg_ = -1;
	XMFLOAT3 nullScale_;
	XMFLOAT3 mousePos;
	bool isEntered = false;
	bool IsEntered();
	int screenWidth = GetPrivateProfileInt("SCREEN", "Width", 800, ".\\setup.ini");		//スクリーンの幅
	int screenHeight = GetPrivateProfileInt("SCREEN", "Height", 600, ".\\setup.ini");	//スクリーンの高さ
public:
	EaseScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};