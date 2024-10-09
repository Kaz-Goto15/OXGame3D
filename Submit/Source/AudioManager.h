#pragma once
namespace AudioManager
{
	enum AUDIO_SOURCE {
		SE_SELECT,
		SE_DECIDE,
		SE_CANCEL,
		SE_THROW,
		SE_HIT,
		SE_DAMAGED,
		SE_HEAL,
		SE_CLEAR,
		BGM_LOBBY,
		BGM_PLAY_0,
		SE_CLAP,
		SE_SET,
		SE_ROTATE,
		BGM_GAME,
		SE_CHANGE,
		MAX
	};

	void Init();
	void Load(int sourceID);
	void Load(AUDIO_SOURCE source);
	void Play(int sourceID);
	void Stop(int sourceID);
	void Release();
	void SetPitch(int sourceID, float pitch);
	bool isLoadAllFile();

	template<typename... Args>
	void Load(int sourceID, Args... args) {
		Load(args...);
	}

	template<typename... Args>
	void Load(AUDIO_SOURCE source, Args... args) {
		Load(args...);
	}

};

