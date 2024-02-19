#include "AudioManager.h"

#include <fstream>
#include <string>
#include "Engine/Audio.h"
#include "Include/nameof.hpp"
#include "Include/json.hpp"

using json = nlohmann::json;
using namespace nameof;

namespace AudioManager {

	int handle[AUDIO_SOURCE::MAX];
}
	void AudioManager::Init()
	{
		std::ifstream f("audioSource.json");
		json data = json::parse(f);

		for (AUDIO_SOURCE as = static_cast<AUDIO_SOURCE>(0); as < AUDIO_SOURCE::MAX; as = static_cast<AUDIO_SOURCE>(as + 1)) {
			std::string s = data[NAMEOF_ENUM(as)]["file"];
			handle[as] = Audio::Load(
				data[NAMEOF_ENUM(as)]["file"],
				data[NAMEOF_ENUM(as)]["loop"],
				data[NAMEOF_ENUM(as)]["maxPlay"]
			);
			assert(handle[as] >= 0);
		}
	}
	void AudioManager::Play(int sourceID)
	{
		Audio::Play(handle[sourceID]);
	}
	void AudioManager::Stop(int sourceID)
	{
		Audio::Stop(handle[sourceID]);
	}
	void AudioManager::SetPitch(int sourceID, float pitch)
	{
		Audio::SetPitch(handle[sourceID], pitch);
	}


//https://qiita.com/yohm/items/0f389ba5c5de4e2df9cf
