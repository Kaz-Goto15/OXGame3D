#include "ButtonEx.h"
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
ButtonEx::ButtonEx(GameObject* parent, const std::string& name) :
	GameObject(parent, name),
	buttonTextObj_(nullptr),
	buttonTextName_(""),
	state(IDLE),
	actHandle_(-1),
	hAl(Text::HORIZONAL_ALIGNMENT::CENTER),
	vAl(Text::VERTICAL_ALIGNMENT::CENTER),
	nextIdle(false),
	ActTiming(SELECTED),
	sound(AudioManager::AUDIO_SOURCE::SE_DECIDE),

	leftBtn(nullptr),upBtn(nullptr),downBtn(nullptr),rightBtn(nullptr),
	isSelecting_(false),
	mode_(PUSH_UP)
{
	std::fill_n(hImg_, MAX, -1);
}

//デストラクタ
ButtonEx::~ButtonEx()
{
}

//初期化
void ButtonEx::Initialize()
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
void ButtonEx::Update()
{
	//強制アイドル
	if (nextIdle) {
		state = IDLE;
		nextIdle = false;
	}

	switch (state)
	{
	case ButtonEx::IDLE:		UpdateIdle();		break;
	case ButtonEx::SELECT:		UpdateSelect();		break;
	case ButtonEx::PUSH:		UpdatePush();		break;
	case ButtonEx::SELECTED:	UpdateSelected();	break;
	}
}

//描画
void ButtonEx::Draw()
{
	switch (state)
	{
	case ButtonEx::IDLE:		DrawIdle();		break;
	case ButtonEx::SELECT:		DrawSelect();	break;
	case ButtonEx::PUSH:		DrawPush();		break;
	case ButtonEx::SELECTED:	DrawSelected();	break;
	}

	//ボタンテキスト描画
	buttonTextObj_->Draw((int)transform_.position_.x, (int)transform_.position_.y, buttonTextName_.c_str(), hAl, vAl);
}

//開放
void ButtonEx::Release()
{
}

std::string ButtonEx::LinkImageFile(STATE _state)
{
	std::string AssetDir = "Default\\";
	std::string fileName;
	switch (_state)
	{
	case ButtonEx::IDLE:		fileName = "btnIdle.png";	break;
	case ButtonEx::SELECT:		fileName = "btnSelect.png";	break;
	case ButtonEx::PUSH:		fileName = "btnPush.png";	break;
	case ButtonEx::SELECTED:	fileName = "btnSelected.png";	break;
	}
	return AssetDir + fileName;
}

void ButtonEx::DrawIdle()
{
	Image::SetTransform(hImg_[IDLE], transform_);
	Image::Draw(hImg_[IDLE]);
}

void ButtonEx::DrawSelect()
{
	Image::SetTransform(hImg_[SELECT], transform_);
	Image::Draw(hImg_[SELECT]);
}

void ButtonEx::DrawPush()
{
	Image::SetTransform(hImg_[PUSH], transform_);
	Image::Draw(hImg_[PUSH]);
}

void ButtonEx::DrawSelected()
{
	Image::SetTransform(hImg_[SELECTED], transform_);
	Image::Draw(hImg_[SELECTED]);
}

std::string ButtonEx::GetDebugStr(int i)
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
			to_string((int)Half(SystemConfig::windowHeight - imageSize.y)) + ")" +
			"(" + to_string((int)Half(SystemConfig::windowWidth + imageSize.x)) + "," +
			to_string((int)Half(SystemConfig::windowHeight - imageSize.y)) + ")" +
			"(" + to_string((int)Half(SystemConfig::windowWidth - imageSize.x)) + "," +
			to_string((int)Half(SystemConfig::windowHeight + imageSize.y)) + ")" +
			"(" + to_string((int)Half(SystemConfig::windowWidth + imageSize.x)) + "," +
			to_string((int)Half(SystemConfig::windowHeight + imageSize.y)) + ")";
	case 2:
		return "windowsize: " +
			to_string(SystemConfig::windowWidth) + ", " +
			to_string(SystemConfig::windowHeight);
	case 3:
		return "windowsize: " +
			to_string(GetPrivateProfileInt("SCREEN", "Width", 800, ".\\setup.ini"));
	case 4:
		return "between:(" +
			to_string((int)(buttonTra.position_.x + Half(SystemConfig::windowWidth - imageSize.x))) + ")" +
			"(" + to_string((int)(buttonTra.position_.x + Half(SystemConfig::windowWidth + imageSize.x))) + ")" +
			"(" + to_string((int)(buttonTra.position_.y + Half(SystemConfig::windowHeight - imageSize.y))) + ")" +
			"(" + to_string((int)(buttonTra.position_.y + Half(SystemConfig::windowHeight + imageSize.y))) + ")";
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

void ButtonEx::SetAction(int hAct)
{
	actHandle_ = hAct;
}

void ButtonEx::SetTextAlignment(Text::HORIZONAL_ALIGNMENT h, Text::VERTICAL_ALIGNMENT v)
{
	hAl = h;
	vAl = v;
}

void ButtonEx::SetFont(const char* fileName, const unsigned int charWidth, const unsigned int charHeight, const unsigned int rowLength)
{
	buttonTextObj_->Initialize(fileName, charWidth, charHeight, rowLength);
}

void ButtonEx::SetFont(TEXT_SOURCE textScr)
{
	buttonTextObj_->Initialize(textScr);
}

void ButtonEx::SetText(std::string buttonName)
{
	buttonTextName_ = buttonName;
}

//ボタン画像系
void ButtonEx::CalcDivImage()
{
	using namespace SystemConfig;
	const int DEFAULT_SCALE = 1;
	XMINT2 stdWindowSize = Image::GetStdWindowSize(hImgButton_[STATE::IDLE]);

	for (int y = DIV_H::H_TOP; y < DIV_H::H_MAX; y++) {

		for (int x = DIV_W::W_LEFT; x < DIV_W::W_MAX; x++) {
			switch (y) {
			case DIV_H::H_TOP:
				buttonDivTra[y][x].position_.y = -Half(stdWindowSize.y * transform_.scale_.y - grid_) + transform_.position_.y;
				buttonDivTra[y][x].scale_.y = DEFAULT_SCALE;
				break;
			case DIV_H::H_CENTER:
				buttonDivTra[y][x].position_.y = transform_.position_.y;
				buttonDivTra[y][x].scale_.y = (stdWindowSize.y * transform_.scale_.y - grid_ - grid_) / (float)grid_;
				break;
			case DIV_H::H_BOTTOM:
				buttonDivTra[y][x].position_.y = Half(stdWindowSize.y * transform_.scale_.y - grid_) + transform_.position_.y;
				buttonDivTra[y][x].scale_.y = DEFAULT_SCALE;
				break;
			}

			switch (x) {
			case DIV_W::W_LEFT:
				buttonDivTra[y][x].position_.x = -Half(stdWindowSize.x * transform_.scale_.x - grid_) + transform_.position_.x;
				buttonDivTra[y][x].scale_.x = DEFAULT_SCALE;
				break;
			case DIV_W::W_CENTER:
				buttonDivTra[y][x].position_.x = transform_.position_.x;
				buttonDivTra[y][x].scale_.x = (stdWindowSize.x * transform_.scale_.x - grid_ - grid_) / (float)grid_;
				break;
			case DIV_W::W_RIGHT:
				buttonDivTra[y][x].position_.x = Half(stdWindowSize.x * transform_.scale_.x - grid_) + transform_.position_.x;
				buttonDivTra[y][x].scale_.x = DEFAULT_SCALE;
				break;
			}
		}
	}
}

void ButtonEx::SetButtonImages(int _grid, string path_idle, string path_select, string path_push, string path_selected)
{
	//変数更新
	grid_ = _grid;
	hImgButton_[STATE::IDLE] = Image::Load(path_idle);
	hImgButton_[STATE::SELECT] = Image::Load(path_select);
	hImgButton_[STATE::PUSH] = Image::Load(path_push);
	hImgButton_[STATE::SELECTED] = Image::Load(path_selected);

	//分割変形情報の更新
	CalcDivImage();
}

//シャドウ
void ButtonEx::SetShadowTransform(int _posX, int _posY, float _scale)
{
	shadowPos = { _posX, _posY };
	shadowScale = _scale;
}

void ButtonEx::SetDrawShadow(bool b)
{
	isDrawShadow = b;
}

void ButtonEx::SetShadowImage(string path)
{
	hImgShadow_ = Image::Load(path);
}


void ButtonEx::UpdateIdle()
{
	if (IsMovedMouse() && IsEntered()) {
		state = SELECT;
		if (IsVisibled())
			AudioManager::Play(AudioManager::AUDIO_SOURCE::SE_SELECT);
	}
}

void ButtonEx::UpdateSelect()
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

void ButtonEx::UpdatePush()
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

void ButtonEx::UpdateSelected()
{
	AudioManager::Play(sound);
	GameObject* obj = (GameObject*)GetParent();
	obj->ButtonAct(actHandle_);
	nextIdle = true;
}

bool ButtonEx::IsEntered()
{
	//デカさ：ウィンドウサイズ(可変)*ボタン比率 左上右下の判定のため1/2にしてぶち込む
	//デカさ矯正：Image呼び出し元の拡大率 これImage内拡大率じゃだめか 多分ダメ 不変なので
	//座標：画像の座標
	// ポジションを指定する
	rangeLU = {
		transform_.scale_.x * -(Half(SystemConfig::windowWidth * Image::GetWindowRatio(hImg_[IDLE]).x)) +
		Image::GetTransform(hImg_[IDLE]).position_.x * (float)SystemConfig::windowWidth / (float)Image::GetStdWindowSize(hImg_[IDLE]).x,
		transform_.scale_.y * -(Half(SystemConfig::windowHeight * Image::GetWindowRatio(hImg_[IDLE]).y)) +
		Image::GetTransform(hImg_[IDLE]).position_.y * (float)SystemConfig::windowHeight / (float)Image::GetStdWindowSize(hImg_[IDLE]).y
	};
	rangeRB = {
		transform_.scale_.x * (Half(SystemConfig::windowWidth * Image::GetWindowRatio(hImg_[IDLE]).x)) +
		Image::GetTransform(hImg_[IDLE]).position_.x * (float)SystemConfig::windowWidth / (float)Image::GetStdWindowSize(hImg_[IDLE]).x,
		transform_.scale_.y * (Half(SystemConfig::windowHeight * Image::GetWindowRatio(hImg_[IDLE]).y)) +
		Image::GetTransform(hImg_[IDLE]).position_.y * (float)SystemConfig::windowHeight / (float)Image::GetStdWindowSize(hImg_[IDLE]).y
	};

	if (Between(Input::GetMousePosition(true).x, rangeLU.x, rangeRB.x) && Between(Input::GetMousePosition(true).y, rangeLU.y, rangeRB.y)) {
		return true;
	}
	return false;
}


bool ButtonEx::Between(float value, float min, float max)
{
	return (value >= min && value <= max);
}

bool ButtonEx::IsMovedMouse()
{
	XMFLOAT3 mouseMove = Input::GetMouseMove();
	return (mouseMove.x != 0 || mouseMove.y != 0);
}
