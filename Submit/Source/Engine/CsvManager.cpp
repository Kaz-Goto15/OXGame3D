#include <Windows.h>
#include "CsvManager.h"
#include "Debug.h"

//コンストラクタ
CsvManager::CsvManager()
{
	data_.clear();
}

//デストラクタ
CsvManager::~CsvManager()
{
	//全データを開放
	for (int y = 0; y < data_.size(); y++)
	{
		for (int x = 0; x < data_[y].size(); x++)
		{
			data_[y][x].clear();
		}
	}
}

//CSVファイルのロード
bool CsvManager::Load(std::string fileName)
{
	//ファイルを開く
	HANDLE hFile;
	hFile = CreateFile(fileName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	//開けなかった
	if (hFile == INVALID_HANDLE_VALUE)
	{
		std::string message = "「" + fileName + "」が開けません。\n開いている場合は閉じてください。";
		MessageBox(NULL, message.c_str(), "BaseProjDx9エラー", MB_OK);

		return false;
	}

	//ファイルのサイズ（文字数）を調べる
	DWORD fileSize = GetFileSize(hFile, NULL);

	//すべての文字を入れられる配列を用意
	char* temp;
	temp = new char[fileSize];

	//ファイルの中身を配列に読み込む
	DWORD dwBytes = 0;
	ReadFile(hFile, temp, fileSize, &dwBytes, NULL);

	//開いたファイルを閉じる
	CloseHandle(hFile);
	//1行のデータを入れる配列
	std::vector<std::string>	line;

	//調べる文字の位置
	DWORD index = 0;

	//最後の文字まで繰り返す
	while (index < fileSize)
	{
		//index文字目から「,」か「改行」までの文字列を取得
		std::string val;
		GetToComma(&val, temp, &index);

		//文字数が0だったということは行末
		if (val.length() - 1 == 0)
		{
			//_dataに1行分追加
			data_.push_back(line);

			//1行データをクリア
			line.clear();

			//index++;
			continue;
		}

		//1行分のデータに追加
		line.push_back(val);
	}

	//読み込んだデータは開放する
	delete[] temp;

	//成功
	return true;
}

//「,」か「改行」までの文字列を取得
void CsvManager::GetToComma(std::string* result, std::string data, DWORD* index)
{
	//「,」まで一文字ずつresultに入れる
	while (data[*index] != ',' && data[*index] != '\n' && data[*index] != '\r')
	{
		*result += data[*index];
		(*index)++;
	}

	//最後に「\0」を付ける
	*result += '\0';
	(*index)++;
}

//指定した位置のデータを文字列で取得
std::string CsvManager::GetString(DWORD x, DWORD y)
{
	if (x < 0 || x >= GetWidth() || y < 0 || y >= GetHeight())
		return "";

	return data_[y][x];
}

//指定した位置のデータを整数で取得
int CsvManager::GetValue(DWORD x, DWORD y)
{
	return atoi(GetString(x, y).c_str());
}

//ファイルの列数を取得
size_t CsvManager::GetWidth()
{
	return data_[0].size();
}

//ファイルの行数を取得
size_t CsvManager::GetHeight()
{
	return data_.size();
}

bool CsvManager::Write(std::string fileName, DWORD x, DWORD y, std::string repData)
{
	//ファイルを開く
	HANDLE hFile2;
	hFile2 = CreateFile(fileName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	//開けなかった
	if (hFile2 == INVALID_HANDLE_VALUE)
	{
		std::string message = "「" + fileName + "」が開けません。\n開いている場合は閉じてください。";
		MessageBox(NULL, message.c_str(), "BaseProjDx9エラー", MB_OK);

		return false;
	}

	////ファイルのサイズ（文字数）を調べる
	//DWORD fileSize = GetFileSize(hFile, NULL);
	//
	////すべての文字を入れられる配列を用意
	//char* temp;
	//temp = new char[fileSize];
	//
	////ファイルの中身を配列に読み込む
	DWORD dwBytes = 0;
	//ReadFile(hFile, temp, fileSize, &dwBytes, NULL);
	//
	if (x < 0 || x >= GetWidth() || y < 0 || y >= GetHeight())return false;
	//38232 
	data_[y][x] = repData;
	data_[y][x] += " ";
	//Debug::Log(data_[y][x]);


	//tempの値をどうにかして変える　data_を順にtemp2に書いていけばいいのでは？

	std::string writedata;

	for (int i = 0; i < GetHeight(); i++) {
		for (int j = 0; j < GetWidth(); j++) {
			writedata += data_[i][j];
			writedata.pop_back();
			if (static_cast<unsigned long long>(j) + 1 != GetWidth())writedata += ",";
		}

		//if (static_cast<unsigned long long>(i) + 1 != GetHeight())
		writedata += "\r\n";
	}
	writedata += "\0";
	Debug::Log(writedata,true);
	Debug::Log("みてるか?");
	//ファイルの中身を配列に読み込む
	////dwBytes = 0;
	WriteFile(hFile2, writedata.c_str(), writedata.size(), &dwBytes, NULL);

	//開いたファイルを閉じる
	CloseHandle(hFile2);
	//読み込んだデータは開放する
	//delete[] temp;
	//成功
	return true;

}
