#include "ButtonOld.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "SystemConfig.h"
#include "AudioManager.h"

//1/2
template <class T>
T Half(T pValue) {
	return pValue /= 2.0f;
}
//値が範囲内か
template <class T>
bool Between(T value, T min, T max) {
	return (min <= value && value <= max);
}

//コンストラクタ
ButtonOld::ButtonOld(GameObject* parent, const std::string& name) :
	GameObject(parent, name),
	buttonTextObj_(nullptr),
	buttonTextName_(""),
	state(IDLE),
	actHandle_(-1),
	hAl(Text::HORIZONAL_ALIGNMENT::CENTER),
	vAl(Text::VERTICAL_ALIGNMENT::CENTER),
	nextIdle(false),
	ActTiming(SELECTED),
	sound(AudioManager::AUDIO_SOURCE::SE_DECIDE)
{
	std::fill_n(hImg_, MAX, -1);
}

//デストラクタ
ButtonOld::~ButtonOld()
{
}

//初期化
void ButtonOld::Initialize()
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
void ButtonOld::Update()
{
	if (nextIdle) {
		state = IDLE;
		nextIdle = false;
	}
	switch (state)
	{
	case ButtonOld::IDLE:		UpdateIdle();		break;
	case ButtonOld::SELECT:	UpdateSelect();		break;
	case ButtonOld::PUSH:		UpdatePush();		break;
	case ButtonOld::SELECTED:	UpdateSelected();	break;
	}
}

//描画
void ButtonOld::Draw()
{
	switch (state)
	{
	case ButtonOld::IDLE:		DrawIdle();		break;
	case ButtonOld::SELECT:	DrawSelect();	break;
	case ButtonOld::PUSH:		DrawPush();		break;
	case ButtonOld::SELECTED:	DrawSelected();	break;
	}

	buttonTextObj_->Draw((int)transform_.position_.x, (int)transform_.position_.y, buttonTextName_.c_str(), hAl, vAl);
}

//開放
void ButtonOld::Release()
{
}

std::string ButtonOld::LinkImageFile(STATE _state)
{
	std::string AssetDir = "Default\\";
	std::string fileName;
	switch (_state)
	{
	case ButtonOld::IDLE:		fileName = "btnIdle.png";	break;
	case ButtonOld::SELECT:	fileName = "btnSelect.png";	break;
	case ButtonOld::PUSH:		fileName = "btnPush.png";	break;
	case ButtonOld::SELECTED:	fileName = "btnSelected.png";	break;
	}
	return AssetDir + fileName;
}

void ButtonOld::DrawIdle()
{
	Image::SetTransform(hImg_[IDLE], transform_);
	Image::Draw(hImg_[IDLE]);
}

void ButtonOld::DrawSelect()
{
	Image::SetTransform(hImg_[SELECT], transform_);
	Image::Draw(hImg_[SELECT]);
}

void ButtonOld::DrawPush()
{
	Image::SetTransform(hImg_[PUSH], transform_);
	Image::Draw(hImg_[PUSH]);
}

void ButtonOld::DrawSelected()
{
	Image::SetTransform(hImg_[SELECTED], transform_);
	Image::Draw(hImg_[SELECTED]);
}

std::string ButtonOld::GetDebugStr(int i)
{
	XMFLOAT3 imageSize = {
	Image::GetSize(hImg_[0]).x * transform_.scale_.x,
	Image::GetSize(hImg_[0]).y * transform_.scale_.y,
	Image::GetSize(hImg_[0]).z * transform_.scale_.z
	};
	using std::to_string;
	Transform buttonTra = Image::GetTransform(hImg_[0]);
	switch (i) {
	case 0:
		return "imageSize: " + 
			to_string(Image::GetSize(hImg_[0]).x) + "," + 
			to_string(Image::GetSize(hImg_[0]).y);
	case 1:
		return "null vertex:(" +
			to_string((int)Half(SystemConfig::windowWidth - imageSize.x)) + "," + 
			to_string((int)Half(SystemConfig::windowHeight - imageSize.y )) + ")" +
		"(" + to_string((int)Half(SystemConfig::windowWidth + imageSize.x )) + "," +
			to_string((int)Half(SystemConfig::windowHeight - imageSize.y )) + ")" +
		"(" + to_string((int)Half(SystemConfig::windowWidth - imageSize.x )) + "," +
			to_string((int)Half(SystemConfig::windowHeight + imageSize.y )) + ")" +
		"(" + to_string((int)Half(SystemConfig::windowWidth + imageSize.x )) + "," + 
			to_string((int)Half(SystemConfig::windowHeight + imageSize.y )) + ")";
	case 2:
		return "windowsize: " + 
			to_string(SystemConfig::windowWidth) + ", " + 
			to_string(SystemConfig::windowHeight);
	case 3:
		return "windowsize: " + 
			to_string(GetPrivateProfileInt("SCREEN", "Width", 800, ".\\setup.ini"));
	case 4:
		return "between:(" +
		to_string((int)(buttonTra.position_.x + Half(SystemConfig::windowWidth  - imageSize.x ))) + ")" +
		"(" + to_string((int)(buttonTra.position_.x + Half(SystemConfig::windowWidth  + imageSize.x ))) + ")" +
		"(" + to_string((int)(buttonTra.position_.y + Half(SystemConfig::windowHeight  - imageSize.y ))) + ")" +
		"(" + to_string((int)(buttonTra.position_.y + Half(SystemConfig::windowHeight  + imageSize.y ))) + ")";
	case 5:
		return "buttonPos: " + 
			to_string(buttonTra.position_.x) + "," + to_string(buttonTra.position_.y);
	case 7:
		return "range: " +
			to_string(rangeLU.x) + "," + to_string(rangeLU.y) + "," + to_string(rangeRB.x) + "," + to_string(rangeRB.y);
	//case 6:	return "clip: " + std::to_string(clip.x) + "," + std::to_string(clip.y) + "," + std::to_string(clip.z) + "," + std::to_string(clip.w);
	}
	return "invalid num";
}

void ButtonOld::SetAction(int hAct)
{
	actHandle_ = hAct;
}

void ButtonOld::SetTextAlignment(Text::HORIZONAL_ALIGNMENT h, Text::VERTICAL_ALIGNMENT v)
{
	hAl = h;
	vAl = v;
}

void ButtonOld::SetFont(const char* fileName, const unsigned int charWidth, const unsigned int charHeight, const unsigned int rowLength)
{
	buttonTextObj_->Initialize(fileName, charWidth, charHeight, rowLength);
}

void ButtonOld::SetFont(TEXT_SOURCE textScr)
{
	buttonTextObj_->Initialize(textScr);
}

void ButtonOld::SetText(std::string buttonName)
{
	buttonTextName_ = buttonName;
}

void ButtonOld::UpdateIdle()
{
	if (IsMovedMouse() && IsEntered()) {
		state = SELECT;
		if(IsVisibled())
		AudioManager::Play(AudioManager::AUDIO_SOURCE::SE_SELECT);
	}
}

void ButtonOld::UpdateSelect()
{
	if (Input::IsMouseButtonDown(0)) {
		if (ActTiming == SELECTED) {
			state = PUSH;
			return;
		}
		else if (ActTiming == PUSH) {
			UpdateSelected();
		}
	}

	if (IsMovedMouse() && !IsEntered()) {
		state = IDLE;
		return;
	}
}

void ButtonOld::UpdatePush()
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

void ButtonOld::UpdateSelected()
{
	AudioManager::Play(sound);
	GameObject* obj = (GameObject*)GetParent();
	obj->ButtonAct(actHandle_);
	nextIdle = true;
}

bool ButtonOld::IsEntered()
{
	//デカさ：ウィンドウサイズ(可変)*ボタン比率 左上右下の判定のため1/2にしてぶち込む
	//デカさ矯正：Image呼び出し元の拡大率 これImage内拡大率じゃだめか 多分ダメ 不変なので
	//座標：画像の座標
	// ポジションを指定する
	rangeLU = {
		transform_.scale_.x * - (Half(SystemConfig::windowWidth * Image::GetWindowRatio(hImg_[IDLE]).x)) + 
		Image::GetTransform(hImg_[IDLE]).position_.x * (float)SystemConfig::windowWidth / (float)Image::GetStdWindowSize(hImg_[IDLE]).x,
		transform_.scale_.y * -(Half(SystemConfig::windowHeight * Image::GetWindowRatio(hImg_[IDLE]).y)) + 
		Image::GetTransform(hImg_[IDLE]).position_.y * (float)SystemConfig::windowHeight / (float)Image::GetStdWindowSize(hImg_[IDLE]).y
	};
	rangeRB = {
		transform_.scale_.x* (Half(SystemConfig::windowWidth * Image::GetWindowRatio(hImg_[IDLE]).x)) + 
		Image::GetTransform(hImg_[IDLE]).position_.x * (float)SystemConfig::windowWidth / (float)Image::GetStdWindowSize(hImg_[IDLE]).x,
		transform_.scale_.y* (Half(SystemConfig::windowHeight * Image::GetWindowRatio(hImg_[IDLE]).y)) + 
		Image::GetTransform(hImg_[IDLE]).position_.y * (float)SystemConfig::windowHeight / (float)Image::GetStdWindowSize(hImg_[IDLE]).y
	};

	if (Between(Input::GetMousePosition(true).x, rangeLU.x, rangeRB.x) && Between(Input::GetMousePosition(true).y, rangeLU.y, rangeRB.y)) {
		return true;
	}
	return false;
}


bool ButtonOld::Between(float value, float min, float max)
{
	return (value >= min && value <= max);
}

bool ButtonOld::IsMovedMouse()
{
	XMFLOAT3 mouseMove = Input::GetMouseMove();
	return (mouseMove.x != 0 || mouseMove.y != 0);
}
