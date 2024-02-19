#pragma once
namespace AudioManager
{
	enum AUDIO_SOURCE {
		TST,
		SE_BUTTON,
		BGM_LOBBY,
		MAX
	};

	void Init();
	void Play(int sourceID);
	void Stop(int sourceID);
	void SetPitch(int sourceID, float pitch);
};

