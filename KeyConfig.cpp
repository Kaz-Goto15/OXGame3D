#include "KeyConfig.h"
#include "Engine/Debug.h"
#include "Engine/Input.h"
#include <vector>

namespace KeyConfig {

	static CsvManager csv;
	static std::string csvFileName;
	//キー置換
	//引数：replaseID	置換キーID
	//引数：keyNum	置換キー数値
	void KeyConfig::ChangeKey(KEY_ID replaseID, int keyNum)
	{
		//同じボタンがあるか確認する 同じだったら入れ替える
		for (int i = 1; i < csv.GetHeight(); i++) {
			if (csv.GetValue(2, i) == keyNum) {
				csv.Write(csvFileName, 2, i, std::to_string(csv.GetValue(2, replaseID + 1)));
				Debug::Log("入替");
			}
		}
		//置換
		csv.Write(csvFileName, 2, replaseID + 1, std::to_string(keyNum));
	}

	//キーコンフィグ初期化 ※デバッグ用　実行したら全キー変更が初期化される
	//引数戻り値無し
	void KeyConfig::InitKey()
	{


		std::vector<int> keyInit = {
			DIK_SPACE,
			DIK_LSHIFT,
			DIK_W,
			DIK_S,
			DIK_A,
			DIK_D
		};
		for (int i = 1; i < csv.GetHeight(); i++) {
			csv.Write(csvFileName,
				2,
				i,
				std::to_string(keyInit[i - 1]));
		}
	}

	//キー読込　必ず呼び出し側の初期化に書く
	//引数 csvName ファイル名
	void KeyConfig::Init(std::string csvName)
	{
		csv.Load(csvName);
		csvFileName = csvName;
	}

	//キー取得 押されているかの判定時に使用
	//引数 KEY_ID　キーID
	//戻値 int　　対応する数値を返す(dInput)
	int KeyConfig::GetKey(KEY_ID keyid)
	{
		int returnint = csv.GetValue(2, keyid + 1);
		return returnint;
	}
}