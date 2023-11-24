#pragma once
#include <vector>
#include "Engine/GameObject.h"
#include "SceneChange.h"
#include "Item.h"
#include "Needle.h"

//テストシーンを管理するクラス
class RivalObject : public GameObject
{
	int hModel_;
	int hPict_;	//画像番号
	bool nowPlaying = false;
	int Switch = 0;
	int time_;
	int a;

	const int LOOP_NEEDLE_ARRAY = 30;
	int randFill[10];
	Item* pItem;
	Needle* pNeedle[30];	//なんかconstint入らんわ
	int setNeedlePtr = 0;

	SceneChange* pSC;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	RivalObject(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	bool IsPlaying() { return nowPlaying; }
	void SetPlaying(bool state) { nowPlaying = state; }

	void SpawnNeedle();
	void SpawnItem();
};