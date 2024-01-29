#include "TitleButton.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

//コンストラクタ
TitleButton::TitleButton(GameObject* parent):
    GameObject(parent, "TitleButton"),
	buttonTextObj_(nullptr),
	buttonName_(""),
	scrW(0),
	scrH(0)
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
	}
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
	for (int i = 0; i < MAX; i++) {
		Image::Draw(hImg_[i]);
	}
	Text::Draw()
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
