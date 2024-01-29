#include "EaseScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Easing.h"
#include "Engine/Text.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"

EaseScene::EaseScene(GameObject* parent)
	: GameObject(parent, "EaseScene"),
	newText(nullptr),
	camPos({-5,5,1})
{}
void EaseScene::Initialize() {
	hPict_ = Image::Load("circle.png");
	ringTra.scale_ = { 0.02,0.02,0.02 };
	Image::SetTransform(hPict_, ringTra);

	newText = new Text();
	newText->Initialize("char_kurokaneEB_aqua1024_50.png", 50, 100, 16);
	newmsgText = new Text();
	newmsgText->Initialize("char_gakusanmarugo_half.png", 16, 32, 16);

	hModel_ = Model::Load("needle.fbx");
	hImg_ = Image::Load("null.png");

	nullScale_ = { 1,1,1 };
}
void EaseScene::Update() {

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

	//UIOJKL ; Ctl Camera
	if (Input::IsKeyDown(DIK_U))camPos.x--;
	if (Input::IsKeyDown(DIK_O))camPos.x++;
	if (Input::IsKeyDown(DIK_I))camPos.y--;
	if (Input::IsKeyDown(DIK_K))camPos.y++;
	if (Input::IsKeyDown(DIK_J))camPos.z--;
	if (Input::IsKeyDown(DIK_L))camPos.z++;

	//7890 : set size : null.png width+-/height+-
	if (Input::IsKeyDown(DIK_7))nullScale_.x += 0.05f;
	if (Input::IsKeyDown(DIK_8))nullScale_.x -= 0.05f;
	if (Input::IsKeyDown(DIK_9))nullScale_.y += 0.05f;
	if (Input::IsKeyDown(DIK_0))nullScale_.y -= 0.05f;
	Transform imageTra;
	imageTra.scale_ = nullScale_;
	Image::SetTransform(hImg_, imageTra);

	progress++;
	if (progress >= 100)progress = 0;
}
void EaseScene::Draw() {
	std::string str = "ease: " + std::to_string(easeNum);
	newText->Draw(40, 40, str.c_str());


	int drawCircleNum = 1600;
	float circleUnit = 0.1f;
	XMFLOAT3 easeSamplePt = { -300,-250,0 };
	for (int i = 0; i < drawCircleNum; i++) {
		float cy = -circleUnit * Easing::Calc(easeNum, i, drawCircleNum, 0, drawCircleNum) + drawCircleNum / 2.0f * circleUnit;
		float cx = circleUnit * i - drawCircleNum / 2.0f * circleUnit;
		cx += easeSamplePt.x;
		cy += easeSamplePt.y;
		ringTra.ConvDrawPos(cx, cy);
		Image::SetTransform(hPict_, ringTra);
		Image::Draw(hPict_);
	}

	XMFLOAT3 modelPos = { 0,0,0 };
	modelPos.x = progress / 100.0f;
	modelPos.z = Easing::Calc(easeNum, progress, 100, -1, 1);
	Transform modelTra;

	modelTra.position_.x = modelPos.z;
	modelTra.position_.z = -1;
	Model::SetTransform(hModel_, modelTra);
	Model::Draw(hModel_);

	modelTra.position_.x = 1;
	modelTra.position_.z = modelPos.z;
	Model::SetTransform(hModel_, modelTra);
	Model::Draw(hModel_);

	modelTra.position_.x = -modelPos.z;
	modelTra.position_.z = 1;
	Model::SetTransform(hModel_, modelTra);
	Model::Draw(hModel_);

	modelTra.position_.x = -1;
	modelTra.position_.z = -modelPos.z;
	Model::SetTransform(hModel_, modelTra);
	Model::Draw(hModel_);

	Camera::SetPosition(camPos);

	std::string msgstr = "mTrPos: " + std::to_string(modelPos.x) + ", " + std::to_string(modelPos.y) + ", " + std::to_string(modelPos.z);
	newmsgText->Draw(40, 100, msgstr.c_str());

	std::string msgstr2 = "trPos: " + std::to_string(transform_.position_.x) + ", " + std::to_string(transform_.position_.y) + ", " + std::to_string(transform_.position_.z);
	newmsgText->Draw(40, 135, msgstr2.c_str());
	XMFLOAT3 campos = Camera::GetPosition();
	std::string msgstr3 = "cam: " + std::to_string(campos.x) + ", " + std::to_string(campos.y) + ", " + std::to_string(campos.z);
	newmsgText->Draw(40, 170, msgstr3.c_str());
	std::string msgstr4 = "imgSize: " + std::to_string(Image::GetWidth(hImg_)) + ", " + std::to_string(Image::GetHeight(hImg_));
	newmsgText->Draw(40, 215, msgstr4.c_str());

	std::string msgstr4 = "imgScale: " + std::to_string(nullScale_.x) + ", " + std::to_string(nullScale_.y);
	newmsgText->Draw(40, 215, msgstr4.c_str());

	Image::Draw(hImg_);
}
void EaseScene::Release() {}