#include "SystemConfig.h"
#include <assert.h>
#include <Windows.h>
//#include <stdlib.h>

namespace SystemConfig {
	int volBGM = 0;
	int volSE = 0;
	int FPS = 0;
	bool isFullScreen = false;

	void SetVolBGM(int vol) {
		volBGM = vol;
		assert(vol < 0 || vol > 100);
	}
	int GetVolBGM() { return volBGM; }

	void SetVolSE(int vol) {
		volSE = vol;
		assert(vol < 0 || vol > 100);
	}
	int GetVolSE() { return volSE; }

	void SetFPS(int fps) { FPS = fps; }
	int GetFPS() { return FPS; }

	void EnableFullScreen(bool b) { isFullScreen = b; }
	bool IsFullScreen() { return isFullScreen; }

	void Init() {
		SetCurrentDirectory("Assets");
		const char* section = "System";
		const char* iniFile = ".\\systemConf.ini";

		SetVolBGM(GetPrivateProfileInt(section, "vol_bgm", volBGM, iniFile));		//スクリーンの幅
		SetVolSE(GetPrivateProfileInt(section, "vol_se", volSE, iniFile));			//スクリーンの高さ
		SetFPS(GetPrivateProfileInt(section, "fps", 60, iniFile));					//FPS（画面更新速度）
		EnableFullScreen(GetPrivateProfileInt(section, "enFullScreen", 0, iniFile));//フルスクリーンの有効無効
	}
}