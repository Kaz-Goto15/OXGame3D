#pragma once
namespace AudioManager
{
	enum AUDIO_SOURCE {
		TST,
		MAX
	};

	void Init();
	void Play(int sourceID);
	void Stop(int sourceID);
	void SetPitch(int sourceID, float pitch);
};

