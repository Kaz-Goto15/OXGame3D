#pragma once
#include <string>
//-----------------------------------------------------------
namespace SE
{
	namespace System
	{

	}
	//初期化
	void Initialize();

	//サウンドファイル(.wav）をロード
	//すでに同じ名前のファイルをロード済みの場合は、既存のデータの番号を返す
	//引数：fileName	ファイル名
	//引数：svNum　		同時に鳴らす最大数（省略可）
	//戻値：そのデータに割り当てられた番号
	int Load(std::string fileName, int svNum = 1);

	//再生
	//引数：handle	鳴らしたいサウンドの番号
	void Play(int ID);

	//すべて開放
	void Release();

	void SetPitch(int ID, float pitch);
};
