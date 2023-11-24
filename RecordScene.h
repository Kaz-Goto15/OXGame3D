#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"
#include "CsvManager.h"
#include "MenuSelect.h"
#include "SceneChange.h"
#include "KeyConfig.h"

#include "Effect.h"

//テストシーンを管理するクラス
class RecordScene : public GameObject
{
	int hPict_;    //画像番号
	Text* pTextName[5]; //ここどうにかして自動化したい
	Text* pTextOV;
	int quantity;
	CsvManager csv;
	MenuSelect* pMenuSelect;

	//テキスト周り
	std::string OVText;
	int keepNo;
	int OVTextLen;

	//デバッグ
	Text* debugTxt;
	Text* debugTxt2;
	Text* debugTxt3;

	SceneChange* pSC;
	SceneChange* pSCd;

	//エフェクトここでデバッグする
	Effect* debugEf;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	RecordScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};