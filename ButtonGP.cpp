#include "ButtonGP.h"

//コンストラクタ
ButtonGP::ButtonGP(GameObject* parent) :
	Button(parent, "Button")
{
}

//デストラクタ
ButtonGP::~ButtonGP()
{
}

std::string ButtonGP::LinkImageFile(STATE _state)
{
	std::string AssetDir = "Default\\";
	std::string fileName;
	switch (_state)
	{
	case Button::IDLE:		fileName = "buttonDef2unselected.png";	break;
	case Button::SELECT:	fileName = "buttonDef2.png";	break;
	case Button::PUSH:		fileName = "buttonDef2.png";	break;
	case Button::SELECTED:	fileName = "buttonDef2.png";	break;
	}
	return AssetDir + fileName;
}

void ButtonGP::Init()
{
	ActTiming = PUSH;
	hButtonShadow_ = Image::Load("buttonDef2Shadow.png");
	transform_.scale_ = { 0.5f, 0.5f,1.0f };
}
void ButtonGP::DrawIdle()
{
	Transform shadowTra = transform_;
	shadowTra.position_.x += 10;
	shadowTra.position_.y += 10;
	Image::SetTransform(hButtonShadow_, shadowTra);
	Image::Draw(hButtonShadow_);
	Image::SetTransform(hImg_[IDLE], transform_);
	Image::Draw(hImg_[IDLE]);
}

void ButtonGP::DrawSelect()
{
	Transform shadowTra = transform_;
	shadowTra.position_.x += 10;
	shadowTra.position_.y += 10;
	Image::SetTransform(hImg_[SELECT], transform_);
	Image::Draw(hImg_[SELECT]);
}

void ButtonGP::DrawPush()
{
	Transform shadowTra = transform_;
	shadowTra.position_.x += 10;
	shadowTra.position_.y += 10;
	Image::SetTransform(hImg_[PUSH], transform_);
	Image::Draw(hImg_[PUSH]);
}

void ButtonGP::DrawSelected()
{
	Transform shadowTra = transform_;
	shadowTra.position_.x += 10;
	shadowTra.position_.y += 10;
	Image::SetTransform(hImg_[SELECTED], transform_);
	Image::Draw(hImg_[SELECTED]);
}