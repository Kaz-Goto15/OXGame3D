#include "Health.h"
#include "Engine/Image.h"
#include "GameData.h"
#include <cmath>
#include "Engine/Debug.h"
//コンストラクタ
Health::Health(GameObject* parent)
	:GameObject(parent, "Health")
{
	std::fill(hPict_, hPict_ + 4, -1);
	health_ = 0;
	tmpHealth_ = 0;
	maxHealth_ = 0;
	moveBar_ = 0;
}

//デストラクタ
Health::~Health(){}

//初期化
void Health::Initialize()
{
	health_ = GameData::GetHealth();
	tmpHealth_ = GameData::GetTempHealth();
	maxHealth_ = GameData::GetMaxHealth();
	moveBar_ = health_;

	std::string fileName_[] = { "ui_noHP.png", "ui_tmpHP.png", "ui_HP.png", "ui_HPFrame.png" };
	//画像ロード
	for (int i = 0; i < sizeof(fileName_) / sizeof(fileName_[0]); i++) {
		hPict_[i] = Image::Load(fileName_[i]);
		assert(hPict_[i] >= 0);
		if (i < 3)Image::SetRect(hPict_[i], 0, 0, 1024, 64);
	}

	transform_.position_ = { -0.55, 0.8, 0 };
	transform_.scale_ = { 0.5,0.5,0.5 };
	textTra.position_ = { 1280 * (0.5f+ transform_.position_.x / 2), 720 * (0.5f + (-1 * transform_.position_.y) / 2), 0};
	pText = new Text;
	pText->Initialize("char_gakusanmarugo_half.png", 16, 32, 16);
}

//更新
void Health::Update()
{
	health_ = GameData::GetHealth();
	tmpHealth_ = GameData::GetTempHealth();
	hpRatio = 1024 * health_ / maxHealth_;
	tmpRatio = 1024 * tmpHealth_ / maxHealth_;
	Image::SetRect(hPict_[1], 1024-tmpRatio, 0, 1024, 64);
	Image::SetRect(hPict_[2], 1024 - hpRatio, 0, 1024, 64);
}

//描画
void Health::Draw()
{
	for (int i = 0; i < sizeof(hPict_) / sizeof(hPict_[0]); i++) {
		Image::SetTransform(hPict_[i], transform_);
		Image::Draw(hPict_[i]);
	}
	hpView = std::to_string(health_) + "/" + std::to_string(maxHealth_);
	pText->Draw(textTra.position_.x, textTra.position_.y, hpView.c_str());
	Debug::Log("std::to_string(textTra.position_.x)", false);
	Debug::Log(std::to_string(textTra.position_.x), true);
	Debug::Log("std::to_string(textTra.position_.y)", false);
	Debug::Log(std::to_string(textTra.position_.y), true);
}

//開放
void Health::Release()
{
}