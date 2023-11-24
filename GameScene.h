#pragma once
#include "Engine/GameObject.h"
#include "SceneChange.h"
#include "Engine/Text.h"
#include "GameData.h"
#include "KeyConfig.h"
#include "Effect.h"

#include "Player.h"
#include "RivalObject.h"

#include "SelectRect.h"
#include "Health.h"
//テストシーンを管理するクラス
class GameScene : public GameObject
{
	int hPict_;	//画像番号
	int hSound_[3]; //サウンド番号
	XMFLOAT3 camPos_, camTarget_;	//カメラ 座標/タゲ

	SceneChange* pSC;
	Text* pText;
	std::string despString;
	//デバッグ
	Text* debugTxt;
	bool gamePlaying_, gameStart_;
	Effect* pEffect_ = nullptr;
	Player* pPlayer_ = nullptr;
	RivalObject* pRivalObject_ = nullptr;
	int waitTime_;

	int gameType_;
	
	//トゲとアイテム沸かし用
	int needleMeter_, itemMeter_;
	int speedMeter_;

	//エンドレス用
	Health* pHealth_ = nullptr;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	GameScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	/// <summary>
	/// 現在ゲームが開始中か(開始前の接地時横移動+ジャンプを除いた空中でキー操作を受け付けるか)を返す
	/// </summary>
	/// <returns>true ゲーム進行中 false: 開始前・時間切れ・接地</returns>
	bool IsPlayed() { return gamePlaying_; }
};