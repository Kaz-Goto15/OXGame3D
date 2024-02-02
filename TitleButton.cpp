#include "TitleButton.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "TitleScene.h"

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
	//SetCurrentDirectory("Assets");
	scrW = GetPrivateProfileInt("SCREEN", "Width", 800, ".\\setup.ini");		//スクリーンの幅
	scrH = GetPrivateProfileInt("SCREEN", "Height", 600, ".\\setup.ini");	//スクリーンの高さ

	for (int i = 0; i < MAX; i++) {
		hImg_[i] = Image::Load(LinkImageFile(static_cast<STATE>(i)));
		Image::SetTransform(hImg_[i], transform_);
	}
	transform_.scale_ = { 0.5f, 0.5f,1.0f };
	//Image::SetRect(hImg_[0], clip.x, clip.y, clip.z, clip.w);
	buttonTextObj_ = new Text;
	buttonTextObj_->Initialize("char_kurokaneEB_aqua1024_50.png", 50, 100, 16);
}

//更新
void TitleButton::Update()
{
	if (Input::IsKeyDown(DIK_T)) {
		hAl = Text::HORIZONAL_ALIGNMENT::RIGHT;
		vAl = Text::VERTICAL_ALIGNMENT::BOTTOM;
	}
	if (Input::IsKeyDown(DIK_Y)) {
		hAl = Text::HORIZONAL_ALIGNMENT::CENTER;
		vAl = Text::VERTICAL_ALIGNMENT::BOTTOM;
	}
	if (Input::IsKeyDown(DIK_U)) {
		hAl = Text::HORIZONAL_ALIGNMENT::LEFT;
		vAl = Text::VERTICAL_ALIGNMENT::BOTTOM;
	}
	if (Input::IsKeyDown(DIK_G)) {
		hAl = Text::HORIZONAL_ALIGNMENT::RIGHT;
		vAl = Text::VERTICAL_ALIGNMENT::CENTER;
	}
	if (Input::IsKeyDown(DIK_H)) {
		hAl = Text::HORIZONAL_ALIGNMENT::CENTER;
		vAl = Text::VERTICAL_ALIGNMENT::CENTER;
	}
	if (Input::IsKeyDown(DIK_J)) {
		hAl = Text::HORIZONAL_ALIGNMENT::LEFT;
		vAl = Text::VERTICAL_ALIGNMENT::CENTER;
	}
	if (Input::IsKeyDown(DIK_B)) {
		hAl = Text::HORIZONAL_ALIGNMENT::RIGHT;
		vAl = Text::VERTICAL_ALIGNMENT::TOP;
	}
	if (Input::IsKeyDown(DIK_N)) {
		hAl = Text::HORIZONAL_ALIGNMENT::CENTER;
		vAl = Text::VERTICAL_ALIGNMENT::TOP;
	}
	if (Input::IsKeyDown(DIK_M)) {
		hAl = Text::HORIZONAL_ALIGNMENT::LEFT;
		vAl = Text::VERTICAL_ALIGNMENT::TOP;
	}
	if (Input::IsKey(DIK_9)) {
		clip.x++;
	}
	if (Input::IsKey(DIK_0)) {
		clip.x--;
	}
	if (Input::IsKey(DIK_O)) {
		clip.y++;
	}
	if (Input::IsKey(DIK_P)) {
		clip.y--;
	}
	if (Input::IsKey(DIK_L)) {
		clip.z++;
	}
	if (Input::IsKey(DIK_SEMICOLON)) {
		clip.z--;
	}
	if (Input::IsKey(DIK_PERIOD)) {
		clip.w++;
	}
	if (Input::IsKey(DIK_SLASH)) {
		clip.w--;
	}

	//Image::SetRect(hImg_[0], clip.x, clip.y, clip.z, clip.w);
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
	Image::SetTransform(hImg_[state], transform_);
	Image::Draw(hImg_[state]);
	buttonTextObj_->Draw(transform_.position_.x, transform_.position_.y, buttonName_.c_str(), Text::HORIZONAL_ALIGNMENT::CENTER, Text::VERTICAL_ALIGNMENT::CENTER);
	//buttonTextObj_->Draw(transform_.position_.x, transform_.position_.y, buttonName_.c_str(), hAl, vAl);
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

	Transform buttonTra = Image::GetTransform(hImg_[0]);
	switch (i) {
	case 0:	return "imageSize: " + std::to_string(Image::GetSize(hImg_[0]).x) + "," + std::to_string(Image::GetSize(hImg_[0]).y);
	case 1:	return "null vertex:(" +
		std::to_string((int)(scrW / 2.0f - imageSize.x / 2.0f)) + "," + std::to_string((int)(scrH / 2.0f - imageSize.y / 2.0f)) + ")" +
		"(" + std::to_string((int)(scrW / 2.0f + imageSize.x / 2.0f)) + "," + std::to_string((int)(scrH / 2.0f - imageSize.y / 2.0f)) + ")" +
		"(" + std::to_string((int)(scrW / 2.0f - imageSize.x / 2.0f)) + "," + std::to_string((int)(scrH / 2.0f + imageSize.y / 2.0f)) + ")" +
		"(" + std::to_string((int)(scrW / 2.0f + imageSize.x / 2.0f)) + "," + std::to_string((int)(scrH / 2.0f + imageSize.y / 2.0f)) + ")";
	case 2: return "windowsize: " + std::to_string(scrW) + ", " + std::to_string(scrH);
	case 3: return "windowsize: " + std::to_string(GetPrivateProfileInt("SCREEN", "Width", 800, ".\\setup.ini"));
	case 4:	return "between:(" +
		      std::to_string((int)(buttonTra.position_.x + scrW/2.0f - imageSize.x / 2.0f)) + ")" +
		"(" + std::to_string((int)(buttonTra.position_.x + scrW / 2.0f + imageSize.x / 2.0f)) + ")" +
		"(" + std::to_string((int)(buttonTra.position_.y + scrH / 2.0f - imageSize.y / 2.0f)) + ")" +
		"(" + std::to_string((int)(buttonTra.position_.y + scrH / 2.0f + imageSize.y / 2.0f)) + ")";
	case 5:	return "buttonPos: " + std::to_string(buttonTra.position_.x) + "," + std::to_string(buttonTra.position_.y);
	case 6:	return "clip: " + std::to_string(clip.x) + "," + std::to_string(clip.y) + "," + std::to_string(clip.z) + "," + std::to_string(clip.w);
	}
	return "invalid num";
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

void TitleButton::SetAction(int hAct)
{
	actHandle_ = hAct;
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
	TitleScene* ts = (TitleScene*)GetParent();
	ts->Act(actHandle_);
}

bool TitleButton::IsEntered()
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
			buttonTra.position_.x + scrW / 2.0f - imageSize.x / 2.0f,
			buttonTra.position_.x + scrW / 2.0f + imageSize.x / 2.0f) &&
		Between(mousePos.y,
			buttonTra.position_.y + scrH / 2.0f - imageSize.y / 2.0f,
			buttonTra.position_.y + scrH / 2.0f + imageSize.y / 2.0f)
		){
			return true;
		}
		return false;
}

bool TitleButton::Between(float value, float min, float max)
{
	return (value >= min && value <= max);
}
