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
		SetVolBGM(GetPrivateProfileInt("System", "vol_bgm", volBGM, ".\\systemConf.ini"));		//スクリーンの幅
		SetVolSE(GetPrivateProfileInt("System", "vol_se", volSE, ".\\systemConf.ini"));			//スクリーンの高さ
		SetFPS(GetPrivateProfileInt("System", "fps", 60, ".\\systemConf.ini"));					//FPS（画面更新速度）
		EnableFullScreen(GetPrivateProfileInt("System", "enFullScreen", 0, ".\\systemConf.ini"));//フルスクリーンの有効無効
	}
}