#include "TitleButton.h"
#include "TitleScene.h"

//コンストラクタ
TitleButton::TitleButton(GameObject* parent):
    Button(parent, "TitleButton")
{
}

//デストラクタ
TitleButton::~TitleButton()
{
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

void TitleButton::Init()
{
	transform_.scale_ = { 0.5f, 0.5f,1.0f };
}