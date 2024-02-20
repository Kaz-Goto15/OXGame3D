#include "Button.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "SystemConfig.h"
//コンストラクタ
Button::Button(GameObject* parent, const std::string& name) :
	GameObject(parent, name),
	buttonTextObj_(nullptr),
	buttonTextName_(""),
	state(IDLE),
	actHandle_(-1),
	hAl(Text::HORIZONAL_ALIGNMENT::CENTER),
	vAl(Text::VERTICAL_ALIGNMENT::CENTER),
	nextIdle(false)
{
	std::fill_n(hImg_, MAX, -1);
}

//デストラクタ
Button::~Button()
{
}

//初期化
void Button::Initialize()
{
	for (int i = 0; i < MAX; i++) {
		hImg_[i] = Image::Load(LinkImageFile(static_cast<STATE>(i)));
		Image::SetTransform(hImg_[i], transform_);
	}
	buttonTextObj_ = new Text;
	buttonTextObj_->Initialize(KUROKANE_AQUA_50px);

	Init();
}

//更新
void Button::Update()
{
	if (nextIdle) {
		state = IDLE;
		nextIdle = false;
	}
	switch (state)
	{
	case Button::IDLE:		UpdateIdle();		break;
	case Button::SELECT:	UpdateSelect();		break;
	case Button::PUSH:		UpdatePush();		break;
	case Button::SELECTED:	UpdateSelected();	break;
	}
}

//描画
void Button::Draw()
{
	switch (state)
	{
	case Button::IDLE:		DrawIdle();		break;
	case Button::SELECT:	DrawSelect();	break;
	case Button::PUSH:		DrawPush();		break;
	case Button::SELECTED:	DrawSelected();	break;
	}

	buttonTextObj_->Draw((int)transform_.position_.x, (int)transform_.position_.y, buttonTextName_.c_str(), hAl, vAl);
}

//開放
void Button::Release()
{
}

std::string Button::LinkImageFile(STATE _state)
{
	std::string AssetDir = "Default\\";
	std::string fileName;
	switch (_state)
	{
	case Button::IDLE:		fileName = "btnIdle.png";	break;
	case Button::SELECT:	fileName = "btnSelect.png";	break;
	case Button::PUSH:		fileName = "btnPush.png";	break;
	case Button::SELECTED:	fileName = "btnSelected.png";	break;
	}
	return AssetDir + fileName;
}

void Button::DrawIdle()
{
	Image::SetTransform(hImg_[IDLE], transform_);
	Image::Draw(hImg_[IDLE]);
}

void Button::DrawSelect()
{
	Image::SetTransform(hImg_[SELECT], transform_);
	Image::Draw(hImg_[SELECT]);
}

void Button::DrawPush()
{
	Image::SetTransform(hImg_[PUSH], transform_);
	Image::Draw(hImg_[PUSH]);
}

void Button::DrawSelected()
{
	Image::SetTransform(hImg_[SELECTED], transform_);
	Image::Draw(hImg_[SELECTED]);
}

std::string Button::GetDebugStr(int i)
{
	XMFLOAT3 imageSize = {
	Image::GetSize(hImg_[0]).x * transform_.scale_.x,
	Image::GetSize(hImg_[0]).y * transform_.scale_.y,
	Image::GetSize(hImg_[0]).z * transform_.scale_.z
	};

	Transform buttonTra = Image::GetTransform(hImg_[0]);
	switch (i) {
	case 0:	return "imageSize: " + std::to_string(Image::GetSize(hImg_[0]).x) + "," + std::to_string(Image::GetSize(hImg_[0]).y);
	case 1:	return "null vertex:(" +
		std::to_string((int)(SystemConfig::screenWidth / 2.0f - imageSize.x / 2.0f)) + "," + std::to_string((int)(SystemConfig::screenHeight / 2.0f - imageSize.y / 2.0f)) + ")" +
		"(" + std::to_string((int)(SystemConfig::screenWidth / 2.0f + imageSize.x / 2.0f)) + "," + std::to_string((int)(SystemConfig::screenHeight / 2.0f - imageSize.y / 2.0f)) + ")" +
		"(" + std::to_string((int)(SystemConfig::screenWidth / 2.0f - imageSize.x / 2.0f)) + "," + std::to_string((int)(SystemConfig::screenHeight / 2.0f + imageSize.y / 2.0f)) + ")" +
		"(" + std::to_string((int)(SystemConfig::screenWidth / 2.0f + imageSize.x / 2.0f)) + "," + std::to_string((int)(SystemConfig::screenHeight / 2.0f + imageSize.y / 2.0f)) + ")";
	case 2: return "windowsize: " + std::to_string(SystemConfig::screenWidth) + ", " + std::to_string(SystemConfig::screenHeight);
	case 3: return "windowsize: " + std::to_string(GetPrivateProfileInt("SCREEN", "Width", 800, ".\\setup.ini"));
	case 4:	return "between:(" +
		std::to_string((int)(buttonTra.position_.x + SystemConfig::screenWidth / 2.0f - imageSize.x / 2.0f)) + ")" +
		"(" + std::to_string((int)(buttonTra.position_.x + SystemConfig::screenWidth / 2.0f + imageSize.x / 2.0f)) + ")" +
		"(" + std::to_string((int)(buttonTra.position_.y + SystemConfig::screenHeight / 2.0f - imageSize.y / 2.0f)) + ")" +
		"(" + std::to_string((int)(buttonTra.position_.y + SystemConfig::screenHeight / 2.0f + imageSize.y / 2.0f)) + ")";
	case 5:	return "buttonPos: " + std::to_string(buttonTra.position_.x) + "," + std::to_string(buttonTra.position_.y);
	//case 6:	return "clip: " + std::to_string(clip.x) + "," + std::to_string(clip.y) + "," + std::to_string(clip.z) + "," + std::to_string(clip.w);
	}
	return "invalid num";
}

void Button::SetAction(int hAct)
{
	actHandle_ = hAct;
}

void Button::SetTextAlignment(Text::HORIZONAL_ALIGNMENT h, Text::VERTICAL_ALIGNMENT v)
{
	hAl = h;
	vAl = v;
}

void Button::SetFont(const char* fileName, const unsigned int charWidth, const unsigned int charHeight, const unsigned int rowLength)
{
	buttonTextObj_->Initialize(fileName, charWidth, charHeight, rowLength);
}

void Button::SetText(std::string buttonName)
{
	buttonTextName_ = buttonName;
}

void Button::UpdateIdle()
{
	if(IsMovedMouse() && IsEntered())state = SELECT;
}

void Button::UpdateSelect()
{
	if (Input::IsMouseButtonDown(0)) {
		state = PUSH;
		return;
	}

	if (IsMovedMouse() && !IsEntered()) {
		state = IDLE;
		return;
	}
}

void Button::UpdatePush()
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

void Button::UpdateSelected()
{
	GameObject* obj = (GameObject*)GetParent();
	obj->ButtonAct(actHandle_);
	nextIdle = true;
}

bool Button::IsEntered()
{
	Transform buttonTra = Image::GetTransform(hImg_[state]);

	XMFLOAT3 imageSize = {
		Image::GetSize(hImg_[state]).x * transform_.scale_.x,
		Image::GetSize(hImg_[state]).y * transform_.scale_.y,
		Image::GetSize(hImg_[state]).z * transform_.scale_.z
	};
	XMFLOAT3 mousePos = Input::GetMousePosition();
	if (
		Between(mousePos.x,
			buttonTra.position_.x + SystemConfig::screenWidth / 2.0f - imageSize.x / 2.0f,
			buttonTra.position_.x + SystemConfig::screenWidth / 2.0f + imageSize.x / 2.0f) &&
		Between(mousePos.y,
			buttonTra.position_.y + SystemConfig::screenHeight / 2.0f - imageSize.y / 2.0f,
			buttonTra.position_.y + SystemConfig::screenHeight / 2.0f + imageSize.y / 2.0f)
		) {
		return true;
	}
	return false;
}

bool Button::Between(float value, float min, float max)
{
	return (value >= min && value <= max);
}

bool Button::IsMovedMouse()
{
	XMFLOAT3 mouseMove = Input::GetMouseMove();
	return (mouseMove.x != 0 || mouseMove.y != 0);
}
