#include "AudioManager.h"

#include <fstream>
#include <string>
#include "Engine/Audio.h"
//#include "Include/nameof.hpp"
#include "Include/json.hpp"

using json = nlohmann::json;
//using namespace nameof;

namespace AudioManager {
	int handle[AUDIO_SOURCE::MAX];
	void Init()
	{
		std::ifstream f("audioSource.json");
		json data = json::parse(f);

		for (AUDIO_SOURCE as = static_cast<AUDIO_SOURCE>(0); as < AUDIO_SOURCE::MAX; as = static_cast<AUDIO_SOURCE>(as + 1)) {

			//std::string s = data[NAMEOF_ENUM(as)]["file"];

			//handle[0] = Audio::Load(
			//	//data.at(NAMEOF_ENUM(as)).get_to("file"),
			//	//data.at(NAMEOF_ENUM(as)).get_to("loop"),
			//	//data.at(NAMEOF_ENUM(as)).get_to("maxPlay")
			//	s,
			//	false,1
			//	//data[NAMEOF_ENUM(as)]["file"].get<std::string>(),
			//	//data[NAMEOF_ENUM(as)]["loop"].get<bool>(),
			//	//data[NAMEOF_ENUM(as)]["maxPlay"].get<int>()
			//);
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
