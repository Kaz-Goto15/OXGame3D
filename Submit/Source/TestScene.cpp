#include "TestScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Easing.h"
#include "Engine/Text.h"
#include "OptionScreen.h"
#include "CreditScreen.h"
#include "ButtonEx.h"

#include <vector>

TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene"),
	newText(nullptr)
{}
void TestScene::Initialize(){
	hPict_ = Image::Load("circle.png");
	ringTra.scale_ = { 0.05f,0.05f,0.05f};
	Image::SetTransform(hPict_, ringTra);

	newText = new Text();
	newText->Initialize(KUROKANE_AQUA_50px);
	descrText = new Text();
	descrText->Initialize(TEXT_SOURCE::GAKUMARU_16px);

	for (int i = 0; i < 5; i++) {
		btn[i] = Instantiate<ButtonEx>(this);
		btn[i]->EnDrawShadow(true);
		btn[i]->SetSize(0.2f, 0.2f);
		if (i == 0) {
			btn[i]->SetPosition(-360, 0);
		}
		else if (i == 4) {
			btn[i]->SetPosition(360, 0);
		}
		else {
			btn[i]->SetPosition(0, -180+180*(i-1));
		}
	}
	for (int i = 0; i < 5; i++) {
		switch (i)
		{
		case 0:
		case 2:
		case 4:
			btn[i]->SetNextKey(ButtonEx::DIR::DIR_UP, btn[1]);
			btn[i]->SetNextKey(ButtonEx::DIR::DIR_DOWN, btn[3]);
			break;
		case 1:
			btn[i]->SetNextKey(ButtonEx::DIR::DIR_UP, btn[3]);
			btn[i]->SetNextKey(ButtonEx::DIR::DIR_DOWN, btn[2]);
			break;
		case 3:
			btn[i]->SetNextKey(ButtonEx::DIR::DIR_UP, btn[2]);
			btn[i]->SetNextKey(ButtonEx::DIR::DIR_DOWN, btn[1]);
			break;
		}

		switch (i)
		{
		case 1:
		case 2:
		case 3:
			btn[i]->SetNextKey(ButtonEx::DIR::DIR_LEFT, btn[0]);
			btn[i]->SetNextKey(ButtonEx::DIR::DIR_RIGHT, btn[4]);
			break;
		case 0:
			btn[i]->SetNextKey(ButtonEx::DIR::DIR_LEFT, btn[4]);
			btn[i]->SetNextKey(ButtonEx::DIR::DIR_RIGHT, btn[2]);
			break;
		case 4:
			btn[i]->SetNextKey(ButtonEx::DIR::DIR_LEFT, btn[2]);
			btn[i]->SetNextKey(ButtonEx::DIR::DIR_RIGHT, btn[0]);
			break;
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if(i != j)
			btn[i]->AddLinkButton(btn[j]);
		}
	}
}
void TestScene::Update(){

	//S ; Change Scene - Splash
	if (Input::IsKeyDown(DIK_ESCAPE)) {
		exit(0);

	}
	//S ; Change Scene - Splash
	if (Input::IsKeyDown(DIK_S)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_SPLASH);
	}

	//S ; Change Scene - Title
	if (Input::IsKeyDown(DIK_T)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}

	//AD ; Show easing_tra ease
	if (Input::IsKeyDown(DIK_A))easeNum--;
	if (Input::IsKeyDown(DIK_D))easeNum++;

	//O : Option Screen
	if (Input::IsKeyDown(DIK_O)) {
		pScreen = Instantiate<OptionScreen>(GetParent());
		pScreen->SetPrevScene(this);
		pScreen->Run();
	}
	//C : Credit Screen
	if (Input::IsKeyDown(DIK_C)) {
		pScreen = Instantiate<CreditScreen>(GetParent());
		pScreen->SetPrevScene(this);
		pScreen->Run();
	}
	//P : Change Scene - Play
	if (Input::IsKeyDown(DIK_P)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}

}
void TestScene::Draw(){
	std::vector<std::string> helpStr = {
		"ESC : Exit",
		"S : Splash Scene",
		"T : Title Scene",
		"A/D : Change EaseNo",
		"O : Open Option Screen",
		"C : Open Credit Screen",
		"P : Play Scene(old:ModelTestScreen)",
		btn[0]->GetDebugStr(0),
		btn[0]->GetDebugStr(1),
		btn[0]->GetDebugStr(2),
		btn[0]->GetDebugStr(3),
		btn[0]->GetDebugStr(4),
		btn[0]->GetDebugStr(5),
		btn[0]->GetDebugStr(6),
		btn[0]->GetDebugStr(7)
	};
	for (int i = 0; i < helpStr.size(); i++) {
		descrText->Draw(-640, -360+i*24, helpStr[i].c_str(), Text::HORIZONAL_ALIGNMENT::LEFT, Text::VERTICAL_ALIGNMENT::TOP);
	}

	std::string str = "ease: " + std::to_string(easeNum);
	newText->Draw(40, 40, str.c_str());

	//イージングのテスト
	int drawCircleNum = 1600;
	int circleSize = 200;

	float convRatio = (float)drawCircleNum / (float)circleSize;
	for (int i = 0; i < drawCircleNum; i++) {
		ringTra.SetPosition(
			(i - drawCircleNum / 2.0f) / convRatio ,
			(- Easing::Calc(easeNum, i, (float)drawCircleNum, 0, (float)drawCircleNum) + (float)drawCircleNum / 2.0f)/convRatio,
			0.0f
		);
		Image::SetTransform(hPict_, ringTra);
		Image::Draw(hPict_);
	}
}
void TestScene::Release(){}