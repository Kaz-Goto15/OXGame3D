#include "AudioManager.h"
#include "Engine/Audio.h"
#include "Include/nameof.hpp"
#include "Include/json.hpp"

using json = nlohmann::json;
using namespace nameof;

namespace AudioManager {
	int handle[AUDIO_SOURCE::MAX];
	std::ifstream(i"file.json");
	json j;
	void Init()
	{
		for (int i = 0; i < AUDIO_SOURCE::MAX; i++) {
			//handle[i] = Audio::Load()
			//SetVolSE(GetPrivateProfileInt(section, "vol_se", volSE, iniFile));
		}
	}
	void Play(int sourceID)
	{
		Audio::Play(handle[sourceID]);
	}
	void Stop(int sourceID)
	{
		Audio::Stop(handle[sourceID]);
	}
	void SetPitch(int sourceID, float pitch)
	{
		Audio::SetPitch(handle[sourceID], pitch);
	}
}


//https://qiita.com/yohm/items/0f389ba5c5de4e2df9cf
