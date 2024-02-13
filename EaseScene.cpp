#include "EaseScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Easing.h"
#include "Engine/Text.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "DebugText.h"

using std::to_string;
bool EaseScene::IsEntered()
{
	msg[9] = "imageSize: " + to_string(Image::GetSize(hImg_).x )+ "," + to_string(Image::GetSize(hImg_).y);
	XMFLOAT3 imageSize = {
		Image::GetSize(hImg_).x * nullScale_.x,
		Image::GetSize(hImg_).y * nullScale_.y,
		Image::GetSize(hImg_).z * nullScale_.z
	};

	msg[7] = "null vertex:(" +
		      to_string((int)(screenWidth/2.0f - imageSize.x / 2.0f)) + "," + to_string((int)(screenHeight / 2.0f - imageSize.y / 2.0f)) + ")" +
		"(" + to_string((int)(screenWidth / 2.0f + imageSize.x / 2.0f)) + "," + to_string((int)(screenHeight / 2.0f - imageSize.y / 2.0f)) + ")" +
		"(" + to_string((int)(screenWidth / 2.0f - imageSize.x / 2.0f)) + "," + to_string((int)(screenHeight / 2.0f + imageSize.y / 2.0f)) + ")" +
		"(" + to_string((int)(screenWidth / 2.0f + imageSize.x / 2.0f)) + "," + to_string((int)(screenHeight / 2.0f + imageSize.y / 2.0f)) + ")";
	if (mousePos.x >= screenWidth / 2.0f - imageSize.x / 2.0f &&
		mousePos.x <= screenWidth / 2.0f + imageSize.x / 2.0f &&
		mousePos.y >= screenHeight / 2.0f - imageSize.y / 2.0f &&
		mousePos.y <= screenHeight / 2.0f + imageSize.y / 2.0f) {
		return true;
	}
	return false;
}

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
	debugText = Instantiate<DebugText>(this);
	for (int i = 0; i < 20; i++) {
		debugText->AddStrPtr(&msg[i]);
	}

	hModel_ = Model::Load("needle.fbx");
	hImg_ = Image::Load("null.png");

	nullScale_ = { 1,1,1 };
}
void EaseScene::Update() {

	mousePos = Input::GetMousePosition();
	isEntered = IsEntered();

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
		//ringTra.ConvDrawPos(cx, cy);
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

	msg[0] = "mTrPos: " + std::to_string(modelPos.x) + ", " + std::to_string(modelPos.y) + ", " + std::to_string(modelPos.z);
	msg[1] = "trPos: " + std::to_string(transform_.position_.x) + ", " + std::to_string(transform_.position_.y) + ", " + std::to_string(transform_.position_.z);
	XMFLOAT3 campos = Camera::GetPosition();
	msg[2] = "cam: " + std::to_string(campos.x) + ", " + std::to_string(campos.y) + ", " + std::to_string(campos.z);
	msg[3] = "imgSize: " + std::to_string(Image::GetWidth(hImg_)) + ", " + std::to_string(Image::GetHeight(hImg_));
	msg[4] = "imgScale: " + std::to_string(nullScale_.x) + ", " + std::to_string(nullScale_.y);
	msg[5] = "mousePos: " + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y);
	msg[6] = "scr: " + std::to_string(screenWidth) + ", " + std::to_string(screenHeight);
	msg[8] = "enter:" + to_string(isEntered);
	Image::Draw(hImg_);
}
void EaseScene::Release() {}