#include "ButtonGPU.h"

//コンストラクタ
ButtonGPU::ButtonGPU(GameObject* parent) :
	ButtonOld(parent, "ButtonOld"),
	hButtonShadow_(-1),
	shadowXY(5)
{
}

//デストラクタ
ButtonGPU::~ButtonGPU()
{
}

std::string ButtonGPU::LinkImageFile(STATE _state)
{
	std::string AssetDir = "Default\\";
	std::string fileName;
	switch (_state)
	{
	case ButtonOld::IDLE:		fileName = "buttonDef2unselected.png";	break;
	case ButtonOld::SELECT:	fileName = "buttonDef2.png";	break;
	case ButtonOld::PUSH:		fileName = "buttonDef2.png";	break;
	case ButtonOld::SELECTED:	fileName = "buttonDef2.png";	break;
	}
	return AssetDir + fileName;
}

void ButtonGPU::Init()
{
	ActTiming = PUSH;
	hButtonShadow_ = Image::Load("Default\\buttonDef2Shadow.png");
	SetFont(GAKUMARU_32px);
}
void ButtonGPU::DrawIdle()
{
	Transform shadowTra = transform_;
	shadowTra.position_.x += shadowXY;
	shadowTra.position_.y += shadowXY;
	Image::SetTransform(hButtonShadow_, shadowTra);
	Image::Draw(hButtonShadow_);
	Image::SetTransform(hImg_[IDLE], transform_);
	Image::Draw(hImg_[IDLE]);
}

void ButtonGPU::DrawSelect()
{
	Transform shadowTra = transform_;
	shadowTra.position_.x += shadowXY;
	shadowTra.position_.y += shadowXY;
	Image::SetTransform(hButtonShadow_, shadowTra);
	Image::Draw(hButtonShadow_);
	Image::SetTransform(hImg_[SELECT], transform_);
	Image::Draw(hImg_[SELECT]);
}

void ButtonGPU::DrawPush()
{
	Transform shadowTra = transform_;
	shadowTra.position_.x += shadowXY;
	shadowTra.position_.y += shadowXY;
	Image::SetTransform(hButtonShadow_, shadowTra);
	Image::Draw(hButtonShadow_);
	Image::SetTransform(hImg_[PUSH], transform_);
	Image::Draw(hImg_[PUSH]);
}

void ButtonGPU::DrawSelected()
{
	Transform shadowTra = transform_;
	shadowTra.position_.x += shadowXY;
	shadowTra.position_.y += shadowXY;
	Image::SetTransform(hButtonShadow_, shadowTra);
	Image::Draw(hButtonShadow_);
	Image::SetTransform(hImg_[SELECTED], transform_);
	Image::Draw(hImg_[SELECTED]);
}