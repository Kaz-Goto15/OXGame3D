#include "ControlSlider.h"
#include "./Engine/Input.h"
#include "./Engine/Image.h"
#include "SystemConfig.h"

//コンストラクタ
ControlSlider::ControlSlider(GameObject* parent)
    :GameObject(parent, "ControlSlider"),
	trackWidth(420),
	trackHeight(50),
	thumbSize(75)
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
	hImg_[SLIDER_BK] = Image::Load("Slider\\sliderBk.png");

	//トラックの幅
	//float trackWRatio = defScrX / trackWidth;
	//float trackHRatio = defScrY / trackHeight;
	//float trackThumbRatio = defScrX / thumbSize;
	float trackWRatio = (float)(trackWidth)/( float)(defScrX);
	float trackHRatio = (float)(trackHeight) / (float)(defScrY);
	float trackThumbWRatio = (float)(thumbSize) / (float)(defScrX);
	float trackThumbHRatio = (float)(thumbSize) / (float)(defScrY);
	//XMFLOAT3 imgSize[IMAGE::MAX];	//画像サイズ
	imgSize[SLIDER_THUMB] = Image::GetSize(hImg_[SLIDER_THUMB]);
	imgSize[SLIDER_FORE] = Image::GetSize(hImg_[SLIDER_FORE]);
	imgSize[SLIDER_BK] = Image::GetSize(hImg_[SLIDER_BK]);
	//int imgBackW = Image::GetWidth(hImg_[SLIDER_BK]);
	//int imgBackH = Image::GetHeight(hImg_[SLIDER_BK]);
	//Transform traImage[IMAGE::MAX];	//各変形情報
	for (int i = 0; i < IMAGE::MAX; i++){
		float a;
		//FOREとBKは
		//ウィンドウサイズ*トラック拡大率(デフォルトスクリーンサイズ/トラックサイズ) / 画像サイズ
		switch (i) {
		case IMAGE::SLIDER_FORE:
			//fore,bkの横幅の半分をマイナスでcenterにする
			a = (float)SystemConfig::windowWidth * (float)trackWRatio / 2.0f;
			bool b;
			traImage[i].SetCenter(0, 0, 0);
			traImage[i].position_.x = a;

			traImage[i].IsCalcCenterPoint(true);
			traImage[i].SetReSize((float)SystemConfig::windowWidth * trackWRatio / (float)imgSize[i].x,
				(float)SystemConfig::windowHeight * trackHRatio / (float)imgSize[i].x,1
				);
			break;
		case IMAGE::SLIDER_BK:
			traImage[i].scale_.x = (float)SystemConfig::windowWidth * trackWRatio / (float)imgSize[i].x;
			traImage[i].scale_.y = (float)SystemConfig::windowHeight * trackHRatio / (float)imgSize[i].x;
			break;
		case IMAGE::SLIDER_THUMB:
			traImage[i].scale_.x = (float)SystemConfig::windowWidth * trackThumbWRatio / (float)imgSize[i].x;
			traImage[i].scale_.y = (float)SystemConfig::windowHeight * trackThumbHRatio / (float)imgSize[i].x;
			break;
		}
		
		Image::SetTransform(hImg_[i], traImage[i]);
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
		traImage[SLIDER_FORE].position_.x++;
	}
	if (Input::IsKey(DIK_2)) {
		traImage[SLIDER_FORE].position_.x--;
	}
	if (Input::IsKey(DIK_3)) {
		traImage[SLIDER_FORE].position_.y++;
	}
	if (Input::IsKey(DIK_4)) {
		traImage[SLIDER_FORE].position_.y--;
	}
	if (Input::IsKey(DIK_5)) {
		traImage[SLIDER_FORE].scale_.x++;
	}
	if (Input::IsKey(DIK_6)) {
		traImage[SLIDER_FORE].scale_.x--;
	}
	if (Input::IsKey(DIK_7)) {
		rc += 0.5f;
		Image::SetRect(hImg_[SLIDER_FORE], 0, 0, rc, 20);
		traImage[SLIDER_BK].scale_.y++;
	}
	if (Input::IsKey(DIK_8)) {
		rc -= 0.5f;
		Image::SetRect(hImg_[SLIDER_FORE], 0, 0, rc, 20);
		traImage[SLIDER_BK].scale_.y--;
	}
}

//描画
void ControlSlider::Draw()
{
	Image::SetTransform(hImg_[SLIDER_FORE], traImage[SLIDER_FORE]);

	float trackWRatio = (float)(trackWidth) / (float)(defScrX);
	float trackHRatio = (float)(trackHeight) / (float)(defScrY);
	Transform frameTra;
	frameTra.SetCenter((float)SystemConfig::windowWidth * (float)trackWRatio / 2.0f,0,0);   //中心点を移動して座標決めてるので注意 具体的には符号逆転する(中心点を動かすと必然的に逆側に移動するため)
	frameTra.IsCalcCenterPoint(true);
	//int edge = 64;

	using namespace SystemConfig;
	//frame構築
	frameTra.position_.y = 0;
	frameTra.scale_.y = (float)(windowHeight - (imgSize[SLIDER_FORE].y + imgSize[SLIDER_FORE].y)) / (float)imgSize[SLIDER_FORE].y;
	frameTra.position_.x = (float)(-windowWidth + (imgSize[SLIDER_FORE].x)) / 2.0f;
	frameTra.scale_.x = 1;
	Transform tmp = frameTra;
	tmp.SetReSize((float)SystemConfig::windowWidth * trackWRatio / (float)imgSize[SLIDER_FORE].x, (float)SystemConfig::windowHeight * trackHRatio / (float)imgSize[SLIDER_FORE].x,1);
	Image::SetTransform(hImg_[SLIDER_FORE], tmp);
	Image::Draw(hImg_[SLIDER_FORE]);


	//for (int& img : hImg_) {
	//	Image::Draw(img);
	//}
	//Image::Draw(hImg_[SLIDER_BK]);
	//Image::Draw(hImg_[SLIDER_FORE]);
	//Image::Draw(hImg_[SLIDER_THUMB]);
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