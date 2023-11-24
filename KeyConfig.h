#pragma once
#include <string>
#include <sstream>
#include "Engine/Input.h"
#include "Engine/CsvManager.h"
#include "GameData.h"

//ゲームで使用するキー
enum KEY_ID
{
	KEY_ID_SELECT = 0,
	KEY_ID_CANSEL,
	KEY_ID_UP_JUMP,
	KEY_ID_DOWN,
	KEY_ID_LEFT,
	KEY_ID_RIGHT,
};

namespace KeyConfig
{

	//キー置換
	//引数：replaseID	置換キーID
	//引数：keyNum	置換キー数値
	void ChangeKey(KEY_ID replaseID, int keyNum);

	//キーコンフィグ初期化 ※デバッグ用　実行したら全キー変更が初期化される
	//引数戻り値無し
	void InitKey();

	//キー読込　必ず呼び出し側の初期化に書く
	void Init(std::string csvName);

	//キー取得 押されているかの判定時に使用
	//引数 KEY_ID　キーID
	//戻値 int　　対応する数値を返す(dInput)
	int GetKey(KEY_ID keyid);
};

