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
}

//描画
void ControlSlider::Draw()
{
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