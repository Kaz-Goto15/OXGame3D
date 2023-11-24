#pragma once
#include <vector>

#include "Engine/GameObject.h"
#include "Engine/Text.h"
#include "CsvManager.h"
#include "MenuSelect.h"
#include "SceneChange.h"
#include "KeyConfig.h"
#include "Engine/Text.h"

enum RESULT_IMG {
	RESULT_IMG_BG = 0,
	//RESULT_IMG_FRAME,
	RESULT_IMG_TIME,
	RESULT_IMG_SPEED,
	RESULT_IMG_METER,
	RESULT_IMG_HIT,
	RESULT_IMG_SCORE,
	RESULT_IMG_EOF,
};
//テストシーンを管理するクラス
class ResultScene : public GameObject
{
	/*
	背景
	//枠
	スコア画像ズ×3→4
	
	*/
	//SPD(経過時間*距離-30000*被弾数)
	int score = GameData::GetSpeed() * ((1800 - GameData::GetTime()) * GameData::GetMeters() - 30000 * GameData::GetHits());
	int hPict_[RESULT_IMG_EOF];
	Transform imgTrans_[RESULT_IMG_EOF];
	Text* pText[RESULT_IMG_EOF];
	std::string drawText[RESULT_IMG_EOF] = {
		 "",
		 GameData::GetTimeString() + "s",
		 "x" + GameData::GetSpeedString(),
		GameData::GetMeterString() + "m",
		std::to_string(GameData::GetHits()),
		std::to_string(score)
	};
	int phase_;
	int drawImgPhase_;
	int waitTime;
	const int WAIT_FRAME = 40;
	bool keyResponse;
	SceneChange* pSC;
	int hSound_;

	bool isFinal;
	int finalPhase_;
	std::vector<int> dispContent[RESULT_IMG_EOF];
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ResultScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//imageload
	void LoadImg(int hpict, std::string imgFile);
};