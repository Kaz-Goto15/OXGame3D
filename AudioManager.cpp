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
}

void AudioManager::Init()
{
	std::ifstream f("Data\\audioSource.json");
	data = json::parse(f);
	if (loadAllFile) {
		for (AUDIO_SOURCE as = static_cast<AUDIO_SOURCE>(0); as < AUDIO_SOURCE::MAX; as = static_cast<AUDIO_SOURCE>(as + 1)) {
			handle[as] = Audio::Load(
				data[NAMEOF_ENUM(as)]["file"],
				data[NAMEOF_ENUM(as)]["loop"],
				data[NAMEOF_ENUM(as)]["maxPlay"],
				data[NAMEOF_ENUM(as)]["attribute"]
			);
			assert(handle[as] >= 0);
		}
	}
}

void AudioManager::Load(int sourceID)
{
	AUDIO_SOURCE as = static_cast<AUDIO_SOURCE>(sourceID);
	handle[sourceID] = Audio::Load(
		data[NAMEOF_ENUM(as)]["file"],
		data[NAMEOF_ENUM(as)]["loop"],
		data[NAMEOF_ENUM(as)]["maxPlay"],
		data[NAMEOF_ENUM(as)]["attribute"]
	);
	assert(handle[sourceID] >= 0);
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
