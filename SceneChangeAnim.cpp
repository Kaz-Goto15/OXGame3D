#include "SceneChangeAnim.h"
#include "Engine/Image.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include <iostream>
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
//コンストラクタ
SceneChangeAnim::SceneChangeAnim(GameObject* parent)
	:GameObject(parent, "SceneChangeAnim"), hPict_(-1), fromVec(0, 0, 0), toVec(0, 0, 0), sinx(0.4f)
{
	fade_ = false;
	move_ = true;
	//ここの率1/2にする 絶対にもっと簡略化できるけどまあ
	mv = { 1.0f / 8.0f , 1.0f / 4.5f };
}

//デストラクタ
SceneChangeAnim::~SceneChangeAnim()
{
}

//初期化
void SceneChangeAnim::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("light82sqrt2re.png");
	assert(hPict_ >= 0);
	//transform_.scale_ = XMFLOAT3(0.25f, 0.25f, 1.0f);
	transform_.position_.x = mv.x / 2.0f;
	//transform_.position_.y = mv.y / 2.0f;
	transform_.rotate_.z = 45.0f;
	transform_.scale_ = XMFLOAT3(1.0f, 1.0f, 1.0f);
}

//更新
void SceneChangeAnim::Update()
{
	if (animStats) {
		if (move_) {

			//拡大率とめる
			if (sinx > M_PI / 2) {
				sinx = (float)M_PI / 2;
				move_ = false;
			}
			//拡大率うごく
			if (fade_) {
				//true 埋まる
				transform_.scale_.y = std::sin(sinx);
				//Debug::Log("scale:");
				//Debug::Log(transform_.scale_.y,true);

			}
			else {
				//false きえる
				transform_.scale_.y = 1.0f - std::sin(sinx);
				//Debug::Log("scale:");
				//Debug::Log(transform_.scale_.y,true);
			}

			//進行度ふえる
			sinx += 0.0625f;
		}
	}
	//Debug KAITEN FX 食べデブ
	/*
	if (1) {
		if (Input::IsKey(DIK_I)) {
			transform_.rotate_.x += 1.0f;
			Debug::Log(transform_.rotate_.x);
		}
		if (Input::IsKey(DIK_K)) {
			transform_.rotate_.x -= 1.0f;
			Debug::Log(transform_.rotate_.x);
		}
		if (Input::IsKey(DIK_J)) {
			transform_.rotate_.y += 1.0f;
			Debug::Log(transform_.rotate_.y);
		}
		if (Input::IsKey(DIK_L)) {
			transform_.rotate_.y -= 1.0f;
			Debug::Log(transform_.rotate_.y);
		}
		if (Input::IsKey(DIK_U)) {
			transform_.rotate_.z += 1.0f;
			Debug::Log(transform_.rotate_.z);
		}
		if (Input::IsKey(DIK_O)) {
			transform_.rotate_.z -= 1.0f;
			Debug::Log(transform_.rotate_.z);
		}

		if (Input::IsKeyDown(DIK_D)) {
			transform_.position_.x += mv.x;
			Debug::Log("x:");
			Debug::Log(transform_.position_.x,true);
		}
		if (Input::IsKeyDown(DIK_A)) {
			transform_.position_.x -= mv.x;
			Debug::Log("x:");
			Debug::Log(transform_.position_.x, true);
		}
		if (Input::IsKeyDown(DIK_W)) {
			transform_.position_.y += mv.y;
			Debug::Log("y:");
			Debug::Log(transform_.position_.y, true);
		}
		if (Input::IsKeyDown(DIK_S)) {
			transform_.position_.y -= mv.y;
			Debug::Log("y:");
			Debug::Log(transform_.position_.y, true);
		}
		if (Input::IsKey(DIK_Q)) {
			transform_.scale_.y += 0.01f;
			Debug::Log("sy:");
			Debug::Log(transform_.scale_.y, true);
		}
		if (Input::IsKey(DIK_E)) {
			transform_.scale_.y -= 0.01f;
			Debug::Log("sy:");
			Debug::Log(transform_.scale_.y, true);
		}

	}
	*/
	//debug camera ←他で使う可能性があるから残す
	/*
	if (1) {
		if (Input::IsKeyDown(DIK_1)) {
			camPos_.x++;
			Camera::SetPosition(camPos_);
		}
		if (Input::IsKeyDown(DIK_2)) {
			camPos_.x--;
			Camera::SetPosition(camPos_);
		}
		if (Input::IsKeyDown(DIK_3)) {
			camPos_.y++;
			Camera::SetPosition(camPos_);
		}
		if (Input::IsKeyDown(DIK_4)) {
			camPos_.y--;
			Camera::SetPosition(camPos_);
		}
		if (Input::IsKeyDown(DIK_5)) {
			camPos_.z++;
			Camera::SetPosition(camPos_);
		}
		if (Input::IsKeyDown(DIK_6)) {
			camPos_.z--;
			Camera::SetPosition(camPos_);
		}

		if (Input::IsKeyDown(DIK_7)) {
			camTarget_.x++;
			Camera::SetTarget(camTarget_);
		}
		if (Input::IsKeyDown(DIK_8)) {
			camTarget_.x--;
			Camera::SetTarget(camTarget_);
		}
		if (Input::IsKeyDown(DIK_9)) {
			camTarget_.y++;
			Camera::SetTarget(camTarget_);
		}
		if (Input::IsKeyDown(DIK_0)) {
			camTarget_.y--;
			Camera::SetTarget(camTarget_);
		}
		if (Input::IsKeyDown(DIK_MINUS)) {
			camTarget_.z++;
			Camera::SetTarget(camTarget_);
		}
		if (Input::IsKeyDown(DIK_CIRCUMFLEX)) {
			camTarget_.z--;
			Camera::SetTarget(camTarget_);
		}
	}
	*/
}

//描画
void SceneChangeAnim::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void SceneChangeAnim::Release()
{
}

std::string SceneChangeAnim::GetInfo() {
	//return " vecYSub: " + std::to_string(vecYSub) + " transPosY: " + std::to_string(transform_.position_.y) +
	//	" fromVecY: " + std::to_string(fromVec.y) + " toVecY: " + std::to_string(toVec.y);
	return " x: " + std::to_string(transform_.rotate_.z) + " y: " + std::to_string(transform_.rotate_.y) +
		" z: " + std::to_string(transform_.rotate_.z);
}

void SceneChangeAnim::ModifyRect(int x, int y, bool _fade)
{
	transform_.position_.x += mv.x * (float)(-8+(float)x );
	transform_.position_.y += mv.y * (float)(5 - y -1);
	fade_ = _fade;
	if (_fade) {
		transform_.scale_.y = 0.0f;
	}
}
