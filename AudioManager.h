#pragma once
namespace AudioManager
{
	enum AUDIO_SOURCE {
		TST,
		SE_DECIDE,
		SE_CANCEL,
		SE_THROW,
		SE_HIT,
		SE_DAMAGED,
		BGM_LOBBY,
		BGM_PLAY_0,
		MAX
	};

	void Init();
	void Play(int sourceID);
	void Stop(int sourceID);
	void SetPitch(int sourceID, float pitch);
};

