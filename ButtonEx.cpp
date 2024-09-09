#include "ButtonEx.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "SystemConfig.h"
#include "AudioManager.h"
#include <vector>

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

//SQLのIn句と同じ
template <class T>
bool In(T val, std::vector<T> search) {
	for (auto& word : search) {
		if (val == word)return true;
	}
	return false;
}

void ButtonEx::SetNextKey(DIR dir, ButtonEx* _pBtn)
{
	nextBtn[dir] = _pBtn;
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

	nextBtn{nullptr,nullptr,nullptr,nullptr},
	isSelecting_(false),
	mode_(PUSH_UP),
	//ボタン画像系
	DEFAULT_BUTTON_IMG{"btnDefIdle.png","btnDefSelect.png","btnDefPush.png","btnDefSelected.png"},
	hImgButton_{-1,-1,-1,-1},
	grid_(64),
	//シャドウ系
	DEFAULT_SHADOW_IMG("btnDefShadow.png"),
	hImgShadow_(-1),
	isDrawShadow(false),
	shadowAlpha_(128),
	shadowPos({5,5}),
	shadowScale(1.0f)
{
}

//デストラクタ
ButtonEx::~ButtonEx()
{
}

//初期化
void ButtonEx::Initialize()
{
	//画像セット
	SetButtonImages(grid_,
		DEFAULT_BUTTON_IMG[STATE::IDLE],
		DEFAULT_BUTTON_IMG[STATE::SELECT],
		DEFAULT_BUTTON_IMG[STATE::PUSH],
		DEFAULT_BUTTON_IMG[STATE::SELECTED]);

	//テキストオブジェクト
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

	//如何なる時もキー移動時にそれを選択中に、自身をアイドルにする
	if (Input::IsKeyDown(SystemConfig::GetKey(SystemConfig::KEY::KEY_DOWN))) {
		if (nextBtn[DIR::DIR_DOWN] != nullptr) {
			nextBtn[DIR::DIR_DOWN]->state = SELECT;
			state = IDLE;
		}
	}
	if (Input::IsKeyDown(SystemConfig::GetKey(SystemConfig::KEY::KEY_UP))) {
		if (nextBtn[DIR::DIR_UP] != nullptr) {
			nextBtn[DIR::DIR_UP]->state = SELECT;
			state = IDLE;
		}
	}
	if (Input::IsKeyDown(SystemConfig::GetKey(SystemConfig::KEY::KEY_LEFT))) {
		if (nextBtn[DIR::DIR_LEFT] != nullptr) {
			nextBtn[DIR::DIR_LEFT]->state = SELECT;
			state = IDLE;
		}
	}
	if (Input::IsKeyDown(SystemConfig::GetKey(SystemConfig::KEY::KEY_RIGHT))) {
		if (nextBtn[DIR::DIR_RIGHT] != nullptr) {
			nextBtn[DIR::DIR_RIGHT]->state = SELECT;
			state = IDLE;
		}
	}

	//各ステート更新
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
	//シャドウが有効化なら描画
	if (isDrawShadow)DrawDivShadow();

	//各ステート描画
	/*
	switch (state)
	{
	case ButtonEx::IDLE:		DrawIdle();		break;
	case ButtonEx::SELECT:		DrawSelect();	break;
	case ButtonEx::PUSH:		DrawPush();		break;
	case ButtonEx::SELECTED:	DrawSelected();	break;
	}
	*/
	//ボタンテキスト描画
	buttonTextObj_->Draw((int)transform_.position_.x, (int)transform_.position_.y, buttonTextName_.c_str(), hAl, vAl);
}

//開放
void ButtonEx::Release()
{
}

std::string ButtonEx::GetDebugStr(int i)
{
	XMFLOAT3 imageSize = {
	Image::GetSize(hImgButton_[STATE::IDLE]).x * transform_.scale_.x,
	Image::GetSize(hImgButton_[STATE::IDLE]).y * transform_.scale_.y,
	Image::GetSize(hImgButton_[STATE::IDLE]).z * transform_.scale_.z
	};
	using std::to_string;
	Transform buttonTra = Image::GetTransform(hImgButton_[STATE::IDLE]);
	switch (i) {
	case 0:
		return "imageSize: " +
			to_string(Image::GetSize(hImgButton_[STATE::IDLE]).x) + "," +
			to_string(Image::GetSize(hImgButton_[STATE::IDLE]).y);
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
	case 4:
		return "between:(" +
			to_string((int)(buttonTra.position_.x + Half(SystemConfig::windowWidth - imageSize.x))) + ")" +
			"(" + to_string((int)(buttonTra.position_.x + Half(SystemConfig::windowWidth + imageSize.x))) + ")" +
			"(" + to_string((int)(buttonTra.position_.y + Half(SystemConfig::windowHeight - imageSize.y))) + ")" +
			"(" + to_string((int)(buttonTra.position_.y + Half(SystemConfig::windowHeight + imageSize.y))) + ")";
	case 5:
		return "buttonPos: " +
			to_string(buttonTra.position_.x) + "," + to_string(buttonTra.position_.y);
	case 6:return "mouse=(" + to_string((int)Input::GetMousePosition(true).x) + ", " + to_string((int)Input::GetMousePosition(true).y) + ")";
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

	rangeLU = {
		buttonDivTra[DIV_H::H_TOP][DIV_W::W_LEFT].position_.x - grid_ / 2,
		buttonDivTra[DIV_H::H_TOP][DIV_W::W_LEFT].position_.y - grid_ / 2
	};
	rangeRB = {
		buttonDivTra[DIV_H::H_BOTTOM][DIV_W::W_RIGHT].position_.x + grid_ / 2,
		buttonDivTra[DIV_H::H_BOTTOM][DIV_W::W_RIGHT].position_.y + grid_ / 2
	};
}

void ButtonEx::DrawDivImage(STATE _state)
{
	for (int h = DIV_H::H_TOP; h < DIV_H::H_MAX; h++) {
		for (int w = DIV_W::W_LEFT; w < DIV_W::W_MAX; w++) {
			Image::SetRect(hImgButton_[_state], w * grid_, h * grid_, grid_, grid_);
			Image::SetTransform(hImgButton_[_state], buttonDivTra[h][w]);
			Image::Draw(hImgButton_[_state]);
		}
	}
}

void ButtonEx::SetButtonImages(int _grid, string path_idle, string path_select, string path_push, string path_selected)
{
	std::string BUTTON_DIR_PATH = "Button\\";
	//変数更新
	grid_ = _grid;
	hImgButton_[STATE::IDLE] = Image::Load(BUTTON_DIR_PATH+path_idle);
	hImgButton_[STATE::SELECT] = Image::Load(BUTTON_DIR_PATH + path_select);
	hImgButton_[STATE::PUSH] = Image::Load(BUTTON_DIR_PATH + path_push);
	hImgButton_[STATE::SELECTED] = Image::Load(BUTTON_DIR_PATH + path_selected);

	//分割変形情報の更新
	CalcDivImage();
}

void ButtonEx::SetSize(float x, float y)
{
	transform_.scale_.x = x;
	transform_.scale_.y = y;
	CalcDivImage();
}

//シャドウ
void ButtonEx::SetShadowTransform(int _posX, int _posY, float _scale)
{
	shadowPos = { _posX, _posY };
	shadowScale = _scale;
}

void ButtonEx::EnDrawShadow(bool b)
{
	isDrawShadow = b;
}

void ButtonEx::SetShadowImage(string path)
{
	hImgShadow_ = Image::Load(path);
}

void ButtonEx::DrawDivShadow()
{
	XMINT2 stdWindowSize = Image::GetStdWindowSize(hImgButton_[STATE::IDLE]);
	for (int y = DIV_H::H_TOP; y < DIV_H::H_MAX; y++) {
		for (int x = DIV_W::W_LEFT; x < DIV_W::W_MAX; x++) {
			Transform shadowTra = buttonDivTra[y][x];

			//拡大率により変形する部分に乗算
			/*
			switch (y) {
			case DIV_H::H_TOP:
				shadowTra.position_.y = -Half(stdWindowSize.y * transform_.scale_.y * shadowScale - grid_) + transform_.position_.y;
				break;
			case DIV_H::H_CENTER:
				shadowTra.scale_.y = (stdWindowSize.y * transform_.scale_.y * shadowScale - grid_ - grid_) / (float)grid_;
				break;
			case DIV_H::H_BOTTOM:
				shadowTra.position_.y = Half(stdWindowSize.y * transform_.scale_.y * shadowScale - grid_) + transform_.position_.y;
				break;
			}

			switch (x) {
			case DIV_W::W_LEFT:
				shadowTra.position_.x = -Half(stdWindowSize.x * transform_.scale_.x * shadowScale - grid_) + transform_.position_.x;
				break;
			case DIV_W::W_CENTER:
				shadowTra.scale_.x = (stdWindowSize.x * transform_.scale_.x * shadowScale - grid_ - grid_) / (float)grid_;
				break;
			case DIV_W::W_RIGHT:
				shadowTra.position_.x = Half(stdWindowSize.x * transform_.scale_.x * shadowScale - grid_) + transform_.position_.x;
				break;
			}
			*/
			//座標調整
			//shadowTra.position_.x += shadowPos.x;
			//shadowTra.position_.y += shadowPos.y;

			//描画
			Image::SetRect(hImgShadow_, x * grid_, y * grid_, grid_, grid_);
			Image::SetTransform(hImgShadow_, shadowTra);
			Image::Draw(hImgShadow_);

		}
	}
}


void ButtonEx::DrawIdle()
{
	DrawDivImage(STATE::IDLE);
}

void ButtonEx::DrawSelect()
{
	DrawDivImage(STATE::SELECT);
}

void ButtonEx::DrawPush()
{
	DrawDivImage(STATE::PUSH);
}

void ButtonEx::DrawSelected()
{
	DrawDivImage(STATE::SELECTED);
}


void ButtonEx::UpdateIdle()
{
	//範囲内かつ動いていれば選択中へ移行
	//ボタンの描画が許可されていたら選択された音をならす
	if (IsMovedMouse() && IsEntered()) {
		state = SELECT;
		if (IsVisibled())
			AudioManager::Play(AudioManager::AUDIO_SOURCE::SE_SELECT);
	}
}

void ButtonEx::UpdateSelect()
{
	//ボタン押下時、押下中へ移行
	if (Input::IsMouseButtonDown(0)) {
		if (ActTiming == SELECTED) {
			state = PUSH;
			return;
		}
		else if (ActTiming == PUSH) {
			UpdateSelected();
		}
	}

	//動いておりかつ範囲外ならアイドルへ移行
	if (IsMovedMouse() && !IsEntered()) {
		state = IDLE;
		return;
	}

	//if(In(mode_, {PUSH_ONLY_SELECT, PUSH_UP_SELECT}))
}

void ButtonEx::UpdatePush()
{
	//範囲外にいるならばアイドルへ移行
	if (!IsEntered()) {
		state = IDLE;
		return;
	}

	//離したならば選択後へ移行
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
	XMINT2 stdWindowSize = Image::GetStdWindowSize(hImgButton_[STATE::IDLE]);

	//3x3分割の左上と右下にグリッドの半分をずらした値と比較 マウス座標は画面サイズに応じてコンバート
	if (Between(Input::GetMousePosition(true).x * stdWindowSize.x / (float)SystemConfig::windowWidth, rangeLU.x, rangeRB.x) && 
		Between(Input::GetMousePosition(true).y * stdWindowSize.y / (float)SystemConfig::windowHeight, rangeLU.y, rangeRB.y)) {
		return true;
	}
	return false;
}

bool ButtonEx::IsMovedMouse()
{
	XMFLOAT3 mouseMove = Input::GetMouseMove();
	return (mouseMove.x != 0 || mouseMove.y != 0);
}
