#include "TitleButton.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

//コンストラクタ
TitleButton::TitleButton(GameObject* parent):
    GameObject(parent, "TitleButton"),
	buttonTextObj_(nullptr),
	buttonName_("")
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
	XMFLOAT3 mousePos = Input::GetMousePosition();
}

void TitleButton::UpdateSelect()
{
}

void TitleButton::UpdatePush()
{
}

void TitleButton::UpdateSelected()
{
}

