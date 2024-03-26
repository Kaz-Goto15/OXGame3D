//#pragma once
#include <xaudio2.h>
#include <vector>
#include <cmath>
#include "Audio.h"
#include "../SystemConfig.h"
#include <assert.h>

#define SAFE_DELETE_ARRAY(p) if(p){delete[] p; p = nullptr;}

namespace Audio
{
	//XAudio本体
	IXAudio2* pXAudio = nullptr;

	//マスターボイス
	IXAudio2MasteringVoice* pMasteringVoice = nullptr;

	//ファイル毎に必要な情報
	struct AudioData
	{
		//サウンド情報
		XAUDIO2_BUFFER buf = {};

		//ソースボイス
		IXAudio2SourceVoice** pSourceVoice = nullptr;

		//同時再生最大数
		int svNum;

		//ファイル名
		std::string fileName;

		//オーディオ属性
		ATTRIBUTE attribute;

	};
	std::vector<AudioData>	audioDatas;
}

//初期化
void Audio::Initialize()
{
	//Confirm(true, CoInitializeEx((LPVOID)nullptr, (DWORD)(int)COINIT_MULTITHREADED), "Initialize");
	CoInitializeEx(0, COINIT_MULTITHREADED);
	XAudio2Create(&pXAudio);
	pXAudio->CreateMasteringVoice(&pMasteringVoice);
}

//サウンドファイル(.wav）をロード
int Audio::Load(std::string fileName, bool isLoop, int svNum, ATTRIBUTE at)
{
	fileName = "Audio\\" + fileName;
	bool isSucc = true;
	//すでに同じファイルを使ってないかチェック
	for (int i = 0; i < audioDatas.size(); i++)
	{
		if (audioDatas[i].fileName == fileName)
		{
			return i;
		}
	}

	//チャンク構造体
	struct Chunk
	{
		char	id[5] = ""; 		// ID
		unsigned int	size = 0;	// サイズ
	};

	//ファイルを開く
	HANDLE hFile;
	hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD dwBytes = 0;

	Chunk riffChunk = { 0 };
	Confirm(&isSucc, ReadFile(hFile, &riffChunk.id, 4, &dwBytes, NULL), "open");
	Confirm(&isSucc, ReadFile(hFile, &riffChunk.size, 4, &dwBytes, NULL), "open");

	char wave[4] = "";
	Confirm(&isSucc, ReadFile(hFile, &wave, 4, &dwBytes, NULL), "wave");

	Chunk formatChunk = { 0 };
	int count = 0;
	while (formatChunk.id[0] != 'f') {
		count++;
		Confirm(&isSucc, ReadFile(hFile, &formatChunk.id, 4, &dwBytes, NULL), "format chunk id");
		assert (count < 100);
	}
	Confirm(&isSucc, ReadFile(hFile, &formatChunk.size, 4, &dwBytes, NULL), "format chunk size");


	//フォーマットを読み取る
	//https://learn.microsoft.com/ja-jp/windows/win32/api/mmeapi/ns-mmeapi-waveformatex
	WAVEFORMATEX fmt;
	Confirm(&isSucc, ReadFile(hFile, &fmt.wFormatTag,		2, &dwBytes, NULL), "format tag");				//形式
	Confirm(&isSucc, ReadFile(hFile, &fmt.nChannels,		2, &dwBytes, NULL), "format channel");			//チャンネル（モノラル/ステレオ）
	Confirm(&isSucc, ReadFile(hFile, &fmt.nSamplesPerSec,	4, &dwBytes, NULL), "format sps");				//サンプリング数
	Confirm(&isSucc, ReadFile(hFile, &fmt.nAvgBytesPerSec,	4, &dwBytes, NULL), "format byte per sec");		//1秒あたりのバイト数
	Confirm(&isSucc, ReadFile(hFile, &fmt.nBlockAlign,		2, &dwBytes, NULL), "format block align");		//ブロック配置
	Confirm(&isSucc, ReadFile(hFile, &fmt.wBitsPerSample,	2, &dwBytes, NULL), "bit per sample");			//サンプル当たりのビット数



	//波形データの読み込み
	Chunk data = { 0 };
	while (true)
	{
		//次のデータのIDを調べる
		Confirm(&isSucc, ReadFile(hFile, &data.id, 4, &dwBytes, NULL), "next data id");

		//「data」だったらループを抜けて次に進む
		if (strcmp(data.id, "data") == 0 || data.id[0] == '\0') {
			break;
		}
		//それ以外の情報ならサイズ調べて読み込む→使わない
		else
		{
			//サイズ調べて
			Confirm(&isSucc, ReadFile(hFile, &data.size, 4, &dwBytes, NULL), "next data size");
			char* pBuffer = new char[data.size];

			//無駄に読み込む
			Confirm(&isSucc, ReadFile(hFile, pBuffer, (DWORD)data.size, &dwBytes, NULL), "next data excess");
		}
	}

	//データチャンクのサイズを取得
	Confirm(&isSucc, ReadFile(hFile, &data.size, 4, &dwBytes, NULL), "data chunk size");

	//波形データを読み込む
	char* pBuffer = new char[data.size];
	Confirm(&isSucc, ReadFile(hFile, pBuffer, (DWORD)data.size, &dwBytes, NULL), "read wave data");
	CloseHandle(hFile);


	AudioData ad;

	ad.fileName = fileName;
	
	ad.buf.pAudioData = (BYTE*)pBuffer;
	ad.buf.Flags = XAUDIO2_END_OF_STREAM;

	if (isLoop)	ad.buf.LoopCount = XAUDIO2_LOOP_INFINITE;

	ad.buf.AudioBytes = data.size;


	ad.pSourceVoice = new IXAudio2SourceVoice * [svNum];

	for (int i = 0; i < svNum; i++)
	{
		pXAudio->CreateSourceVoice(&ad.pSourceVoice[i], &fmt);
	}
	ad.svNum = svNum;
	ad.attribute = at;
	audioDatas.push_back(ad);

	//SAFE_DELETE_ARRAY(pBuffer);
	if (isSucc == false)return NULL_HANDLE;
	return (int)audioDatas.size() - 1;
}

//再生
void Audio::Play(int ID)
{
	for (int i = 0; i < audioDatas[ID].svNum; i++)
	{
		XAUDIO2_VOICE_STATE state;
		audioDatas[ID].pSourceVoice[i]->GetState(&state);

		if (state.BuffersQueued == 0)
		{
			audioDatas[ID].pSourceVoice[i]->SubmitSourceBuffer(&audioDatas[ID].buf);

			switch (audioDatas[ID].attribute)
			{
			case BGM:
				audioDatas[ID].pSourceVoice[i]->SetVolume((float)SystemConfig::GetVolBGM()/100.0f);
				break;
			case SE:
				audioDatas[ID].pSourceVoice[i]->SetVolume((float)SystemConfig::GetVolSE()/100.0f);
				break;
			case OTHER:
				audioDatas[ID].pSourceVoice[i]->SetVolume(0);
				break;
			}
			audioDatas[ID].pSourceVoice[i]->Start();
			break;
		}
	}
}

//teisi
void Audio::Stop(int ID)
{
	for (int i = 0; i < audioDatas[ID].svNum; i++)
	{
		audioDatas[ID].pSourceVoice[i]->Stop();
		audioDatas[ID].pSourceVoice[i]->FlushSourceBuffers();
	}
}

//シーンごとの解放
void Audio::Release()
{
	for (int i = 0; i < audioDatas.size(); i++)
	{
		for (int j = 0; j < audioDatas[i].svNum; j++)
		{
			audioDatas[i].pSourceVoice[j]->DestroyVoice();
		}
		SAFE_DELETE_ARRAY(audioDatas[i].buf.pAudioData);
	}
	audioDatas.clear();
}

//本体の解放
void Audio::AllRelease()
{
	CoUninitialize();
	if (pMasteringVoice)
	{
		pMasteringVoice->DestroyVoice();
	}
	pXAudio->Release();
}

void Audio::SetPitch(int ID, float pitch)
{
	float convertPitch = std::pow(2.0f,pitch);

	for (int i = 0; i < audioDatas[ID].svNum; i++)
	{
		XAUDIO2_VOICE_STATE state;
		audioDatas[ID].pSourceVoice[i]->GetState(&state);

		if (state.BuffersQueued == 0)
		{
			audioDatas[ID].pSourceVoice[i]->SetFrequencyRatio(convertPitch);
			break;
		}
	}
}

bool Audio::Confirm(bool *prevSucc, BOOL b, std::string msg = "fail")
{
	if (!prevSucc)return false;
	if (b == FALSE) {
		MessageBox(NULL, msg.c_str(), "Audio Error", MB_OK);
		exit(0);
		return false;
	}
	return true;
}

bool Audio::Confirm(bool prevSucc, BOOL b, std::string msg)
{
	return Confirm(&prevSucc, b, msg);
}

bool Audio::IsPlaying(int ID)
{
	for (int i = 0; i < audioDatas[ID].svNum; i++)
	{
		XAUDIO2_VOICE_STATE state;
		audioDatas[ID].pSourceVoice[i]->GetState(&state);
		if (state.pCurrentBufferContext == &(audioDatas[ID].buf)) {
			return true;
		}
		else {
			return false;
		}
	}
}
