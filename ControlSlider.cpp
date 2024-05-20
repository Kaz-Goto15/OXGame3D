#include "ControlSlider.h"
#include "./Engine/Input.h"
#include "./Engine/Image.h"
#include "SystemConfig.h"

//コンストラクタ
ControlSlider::ControlSlider(GameObject* parent)
    :GameObject(parent, "ControlSlider"),
	trackWidth(420),
	trackHeight(50)
{
}

//デストラクタ
ControlSlider::~ControlSlider()
{
}

//初期化
void ControlSlider::Initialize()
{
	//画像読込
	hImg_[SLIDER_THUMB] = Image::Load("Slider\\sliderThumb.png");
	hImg_[SLIDER_FORE] = Image::Load("Slider\\sliderFore.png");
	hImg_[SLIDER_BK] = Image::Load("Slider\\sliderBack.png");

	//トラックの幅
	float trackWRatio = defScrX / trackWidth;
	float trackHRatio = defScrY / trackHeight;
	XMFLOAT3 imgSize[IMAGE::MAX];
	imgSize[SLIDER_THUMB] = Image::GetSize(hImg_[SLIDER_THUMB]);
	imgSize[SLIDER_FORE] = Image::GetSize(hImg_[SLIDER_FORE]);
	imgSize[SLIDER_BK] = Image::GetSize(hImg_[SLIDER_BK]);
	//int imgBackW = Image::GetWidth(hImg_[SLIDER_BK]);
	//int imgBackH = Image::GetHeight(hImg_[SLIDER_BK]);
	Transform traImage[IMAGE::MAX];
	for (int i = 0; i < IMAGE::MAX; i++)
		traImage[hImg_[i]].scale_.x = (float)SystemConfig::windowWidth * trackWRatio / (float)imgSize[i].x;
		traImage[hImg_[i]].scale_.y = (float)SystemConfig::windowHeight * trackHRatio / (float)imgSize[i].x;
	}
	//traImageBack.scale_.x = (float)SystemConfig::windowWidth * trackWRatio / (float)imgBackW;
	//traImageBack.scale_.y = (float)SystemConfig::windowHeight * trackHRatio / (float)imgBackH;
	
	/*
	FOREとBKは同じサイズじゃないといけない？違うサイズの場合リサイズするか処理を止める必要がある
	*/
}

//更新
void ControlSlider::Update()
{
	if (IsEntered()) {
		//マウスのみにしますか?はい
		//押されてるときに
		if (Input::IsMouseButtonDown(0)) {

		}
	}

	if (Input::IsKey(DIK_1)) {
		transform_.position_.x++;
	}
	if (Input::IsKey(DIK_2)) {
		transform_.position_.x--;
	}
	if (Input::IsKey(DIK_3)) {
		transform_.position_.y++;
	}
	if (Input::IsKey(DIK_4)) {
		transform_.position_.y--;
	}
}

//描画
void ControlSlider::Draw()
{
	for (int& img : hImg_) {
		Image::Draw(img);
	}
}

//開放
void ControlSlider::Release()
{
}

bool ControlSlider::IsEntered()
{
	////1280x720で生成されたものを現在のスクリーンサイズから
	//Transform buttonTra = Image::GetTransform(hImg_[state]);
	//
	//XMFLOAT3 imageSize = {
	//	Image::GetSize(hImg_[state]).x * transform_.scale_.x,
	//	Image::GetSize(hImg_[state]).y * transform_.scale_.y,
	//	Image::GetSize(hImg_[state]).z * transform_.scale_.z
	//};
	//XMFLOAT3 mousePos = Input::GetMousePosition();
	//if (
	//	Between(mousePos.x,
	//		buttonTra.position_.x + SystemConfig::screenWidth / 2.0f - imageSize.x / 2.0f,
	//		buttonTra.position_.x + SystemConfig::screenWidth / 2.0f + imageSize.x / 2.0f) &&
	//	Between(mousePos.y,
	//		buttonTra.position_.y + SystemConfig::screenHeight / 2.0f - imageSize.y / 2.0f,
	//		buttonTra.position_.y + SystemConfig::screenHeight / 2.0f + imageSize.y / 2.0f)
	//	) {
	//	return true;
	//}
	return false;
}