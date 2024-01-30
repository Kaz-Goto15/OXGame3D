#include "TitleButton.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

//コンストラクタ
TitleButton::TitleButton(GameObject* parent):
    GameObject(parent, "TitleButton"),
	buttonTextObj_(nullptr),
	buttonName_(""),
	scrW(0),
	scrH(0),
	state(IDLE)
{
	std::fill_n(hImg_, MAX, -1);
}

//デストラクタ
TitleButton::~TitleButton()
{
}

//初期化
void TitleButton::Initialize()
{
	int scrW = GetPrivateProfileInt("SCREEN", "Width", 800, ".\\setup.ini");		//スクリーンの幅
	int scrH = GetPrivateProfileInt("SCREEN", "Height", 600, ".\\setup.ini");	//スクリーンの高さ

	for (int i = 0; i < MAX; i++) {
		hImg_[i] = Image::Load(LinkImageFile(static_cast<STATE>(i)));
		Image::SetTransform(hImg_[i], transform_);
	}

	buttonTextObj_ = new Text;
	buttonTextObj_->Initialize("char_kurokaneEB_aqua1024_50.png", 50, 100, 16);
}

//更新
void TitleButton::Update()
{
	switch (state)
	{
	case TitleButton::IDLE:		UpdateIdle();	break;
	case TitleButton::SELECT:	UpdateSelect();	break;
	case TitleButton::PUSH:		UpdatePush();	break;
	case TitleButton::SELECTED:	UpdateSelected();	break;
	}
}

//描画
void TitleButton::Draw()
{
	//for (int i = 0; i < MAX; i++) {
	//	Image::Draw(hImg_[i]);
	//}
	Image::Draw(hImg_[state]);
	buttonTextObj_->Draw(transform_.position_.x, transform_.position_.y, buttonName_.c_str(), Text::HORIZONAL_ALIGNMENT::CENTER, Text::VERTICAL_ALIGNMENT::CENTER);
}

//開放
void TitleButton::Release()
{
}

void TitleButton::SetText(std::string buttonName)
{
    buttonName_ = buttonName;
}

std::string TitleButton::LinkImageFile(STATE _state)
{
	std::string AssetDir = "Title\\";
	std::string fileName;
	switch (_state)
	{
	case TitleButton::IDLE:		fileName = "btnIdle.png";	break;
	case TitleButton::SELECT:	fileName = "btnSelect.png";	break;
	case TitleButton::PUSH:		fileName = "btnPush.png";	break;
	case TitleButton::SELECTED:	fileName = "btnSelected.png";	break;
	}
	return AssetDir + fileName;
}

std::string TitleButton::GetDebugStr(int i)
{
	XMFLOAT3 imageSize = {
	Image::GetSize(hImg_[0]).x * transform_.scale_.x,
	Image::GetSize(hImg_[0]).y * transform_.scale_.y,
	Image::GetSize(hImg_[0]).z * transform_.scale_.z
	};

	switch (i) {
	case 0:	return "imageSize: " + std::to_string(Image::GetSize(hImg_[0]).x) + "," + std::to_string(Image::GetSize(hImg_[0]).y);
	case 1:	return "null vertex:(" +
		std::to_string((int)(1280 / 2.0f - imageSize.x / 2.0f)) + "," + std::to_string((int)(720 / 2.0f - imageSize.y / 2.0f)) + ")" +
		"(" + std::to_string((int)(1280 / 2.0f + imageSize.x / 2.0f)) + "," + std::to_string((int)(720 / 2.0f - imageSize.y / 2.0f)) + ")" +
		"(" + std::to_string((int)(1280 / 2.0f - imageSize.x / 2.0f)) + "," + std::to_string((int)(720 / 2.0f + imageSize.y / 2.0f)) + ")" +
		"(" + std::to_string((int)(1280 / 2.0f + imageSize.x / 2.0f)) + "," + std::to_string((int)(720 / 2.0f + imageSize.y / 2.0f)) + ")";
	}
	return std::string();
}

void TitleButton::UpdateIdle()
{
	if (IsEntered())state = SELECT;
}

void TitleButton::UpdateSelect()
{
	if (Input::IsMouseButtonDown(0)) {
		state = PUSH;
		return;
	}

	if (!IsEntered()) {
		state = IDLE;
		return;
	}
}

void TitleButton::UpdatePush()
{
	if (!IsEntered()) {
		state = IDLE;
		return;
	}
	if (Input::IsMouseButtonUp(0)) {
		state = SELECTED;
		return;
	}
}

void TitleButton::UpdateSelected()
{
	
}

bool TitleButton::IsEntered()
{
	XMFLOAT3 imageSize = {
		Image::GetSize(hImg_[state]).x* transform_.scale_.x,
		Image::GetSize(hImg_[state]).y * transform_.scale_.y,
		Image::GetSize(hImg_[state]).z * transform_.scale_.z
	};
	XMFLOAT3 mousePos = Input::GetMousePosition();
	if (mousePos.x >= scrW / 2.0f - imageSize.x / 2.0f &&
		mousePos.x <= scrW / 2.0f + imageSize.x / 2.0f &&
		mousePos.y >= scrH / 2.0f - imageSize.y / 2.0f &&
		mousePos.y <= scrH / 2.0f + imageSize.y / 2.0f) {
		return true;
	}
	return false;
}
