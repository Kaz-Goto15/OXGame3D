#include "AudioManager.h"

#include <fstream>
#include <string>
#include "Include/nameof.hpp"
#include "Include/json.hpp"

#include "Engine/Audio.h"

using json = nlohmann::json;
using namespace nameof;

namespace AudioManager {
	int handle[AUDIO_SOURCE::MAX];
	json data;
	bool loadAllFile = false;	//初期化時に全音声ファイルを読み込むか
	const char dataFile[] = "Data\\audioSource.json";	//ファイル
}

void AudioManager::Init()
{
	std::ifstream f(dataFile);
	data = json::parse(f);
	if (loadAllFile) {
		for (int scrID = 0; scrID < AUDIO_SOURCE::MAX; scrID++) {
			Load(scrID);
		}
	}
}

void AudioManager::Load(int sourceID)
{
	Load(static_cast<AUDIO_SOURCE>(sourceID));
}

void AudioManager::Load(AUDIO_SOURCE source)
{
	handle[source] = Audio::Load(
		data[NAMEOF_ENUM(source)]["file"],
		data[NAMEOF_ENUM(source)]["loop"],
		data[NAMEOF_ENUM(source)]["maxPlay"],
		data[NAMEOF_ENUM(source)]["attribute"]
	);
	assert(handle[source] >= 0);
}

void AudioManager::Play(int sourceID)
{
	if (!loadAllFile) {
		Load(sourceID);
	}
	Audio::Play(handle[sourceID]);
}

void AudioManager::Stop(int sourceID)
{
	Audio::Stop(handle[sourceID]);
}

void AudioManager::Release()
{
	Audio::Release();
}

void AudioManager::SetPitch(int sourceID, float pitch)
{
	Audio::SetPitch(handle[sourceID], pitch);
}

bool AudioManager::isLoadAllFile()
{
	return loadAllFile;
}

//https://qiita.com/yohm/items/0f389ba5c5de4e2df9cf
