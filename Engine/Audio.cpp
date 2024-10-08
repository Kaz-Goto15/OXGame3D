//#pragma once
#include <xaudio2.h>
#include <vector>
#include <cmath>
#include "Audio.h"
#include "../SystemConfig.h"
#include "Debug.h"
#include <assert.h>

#define SAFE_DELETE_ARRAY(p) if(p){delete[] p; p = nullptr;}

namespace Audio
{
	//XAudio�{��
	IXAudio2* pXAudio = nullptr;

	//�}�X�^�[�{�C�X
	IXAudio2MasteringVoice* pMasteringVoice = nullptr;

	//�t�@�C�����ɕK�v�ȏ��
	struct AudioData
	{
		//�T�E���h���
		XAUDIO2_BUFFER buf = {};

		//�\�[�X�{�C�X
		IXAudio2SourceVoice** pSourceVoice = nullptr;

		//�����Đ��ő吔
		int svNum;

		//�t�@�C����
		std::string fileName;

		//�I�[�f�B�I����
		ATTRIBUTE attribute;

	};
	std::vector<AudioData>	audioDatas;
}

//������
void Audio::Initialize()
{
	//Confirm(true, CoInitializeEx((LPVOID)nullptr, (DWORD)(int)COINIT_MULTITHREADED), "Initialize");
	CoInitializeEx(0, COINIT_MULTITHREADED);
	XAudio2Create(&pXAudio);
	pXAudio->CreateMasteringVoice(&pMasteringVoice);
}

//�T�E���h�t�@�C��(.wav�j�����[�h
int Audio::Load(std::string fileName, bool isLoop, int svNum, ATTRIBUTE at)
{
	Debug::Log(fileName + " �� Load �����s����܂���",true);

	fileName = "Audio\\" + fileName;
	bool isSucc = true;
	//���łɓ����t�@�C�����g���ĂȂ����`�F�b�N
	for (int i = 0; i < audioDatas.size(); i++)
	{
		if (audioDatas[i].fileName == fileName)
		{
			return i;
		}
	}

	//�`�����N�\����
	struct Chunk
	{
		char	id[5] = ""; 		// ID
		unsigned int	size = 0;	// �T�C�Y
	};

	//�t�@�C�����J��
	HANDLE hFile;
	hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD dwBytes = 0;

	Chunk riffChunk = { 0 };
	Confirm(&isSucc, ReadFile(hFile, &riffChunk.id, 4, &dwBytes, NULL), "open" + fileName);
	Confirm(&isSucc, ReadFile(hFile, &riffChunk.size, 4, &dwBytes, NULL), "open" + fileName);

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


	//�t�H�[�}�b�g��ǂݎ��
	//https://learn.microsoft.com/ja-jp/windows/win32/api/mmeapi/ns-mmeapi-waveformatex
	WAVEFORMATEX fmt;
	Confirm(&isSucc, ReadFile(hFile, &fmt.wFormatTag,		2, &dwBytes, NULL), "format tag");				//�`��
	Confirm(&isSucc, ReadFile(hFile, &fmt.nChannels,		2, &dwBytes, NULL), "format channel");			//�`�����l���i���m����/�X�e���I�j
	Confirm(&isSucc, ReadFile(hFile, &fmt.nSamplesPerSec,	4, &dwBytes, NULL), "format sps");				//�T���v�����O��
	Confirm(&isSucc, ReadFile(hFile, &fmt.nAvgBytesPerSec,	4, &dwBytes, NULL), "format byte per sec");		//1�b������̃o�C�g��
	Confirm(&isSucc, ReadFile(hFile, &fmt.nBlockAlign,		2, &dwBytes, NULL), "format block align");		//�u���b�N�z�u
	Confirm(&isSucc, ReadFile(hFile, &fmt.wBitsPerSample,	2, &dwBytes, NULL), "bit per sample");			//�T���v��������̃r�b�g��



	//�g�`�f�[�^�̓ǂݍ���
	Chunk data = { 0 };
	while (true)
	{
		//���̃f�[�^��ID�𒲂ׂ�
		Confirm(&isSucc, ReadFile(hFile, &data.id, 4, &dwBytes, NULL), "next data id");

		//�udata�v�������烋�[�v�𔲂��Ď��ɐi��
		if (strcmp(data.id, "data") == 0 || data.id[0] == '\0') {
			break;
		}
		//����ȊO�̏��Ȃ�T�C�Y���ׂēǂݍ��ށ��g��Ȃ�
		else
		{
			//�T�C�Y���ׂ�
			Confirm(&isSucc, ReadFile(hFile, &data.size, 4, &dwBytes, NULL), "next data size");
			char* pBuffer = new char[data.size];

			//���ʂɓǂݍ���
			Confirm(&isSucc, ReadFile(hFile, pBuffer, (DWORD)data.size, &dwBytes, NULL), "next data excess");
		}
	}

	//�f�[�^�`�����N�̃T�C�Y���擾
	Confirm(&isSucc, ReadFile(hFile, &data.size, 4, &dwBytes, NULL), "data chunk size");

	//�g�`�f�[�^��ǂݍ���
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

	for (int i = 0; i < audioDatas.size(); i++) {
		std::string str = std::to_string(i) + ": " + audioDatas[i].fileName;
		Debug::Log(str, true);
	}
}

//�Đ�
void Audio::Play(int ID)
{
	Debug::Log(std::to_string(ID) + "�� �� Play �����s����܂���", true);
	for (int i = 0; i < audioDatas.size(); i++) {
		std::string str = std::to_string(i) + ": " + audioDatas[i].fileName;
		Debug::Log(str, true);
	}
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

//�V�[�����Ƃ̉��
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

//�{�̂̉��
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
