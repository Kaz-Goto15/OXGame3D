#include "SystemConfig.h"
#include <assert.h>
#include <Windows.h>
#include <string>
#include "./Include/inicpp.h"
//#include <stdlib.h>

namespace SystemConfig {
	int screenWidth = 800;
	int screenHeight = 600;
	int volBGM = 0;
	int volSE = 0;
	int FPS = 0;
	bool isFullScreen = false;
	bool debug = false;
	ini::IniFile confIni;

	const char* section = "System";
	const char* directory = "Assets";
	const char* filePath = ".\\systemConf.ini";

	void SetVolBGM(int vol) {
		volBGM = vol;
		assert(0 <=vol && vol <= 100);
		confIni[section]["vol_bgm"] = vol;
	}
	int GetVolBGM() { return volBGM; }

	void SetVolSE(int vol) {
		volSE = vol;
		assert(0 <= vol && vol <= 100);
		confIni[section]["vol_se"] = vol;
	}
	int GetVolSE() { return volSE; }

	void SetFPS(int fps) {
		FPS = fps;
		confIni[section]["fps"] = fps;
	}
	int GetFPS() { return FPS; }

	void SetFullScreen(bool b) {
		isFullScreen = b;
		confIni[section]["enFullScreen"] = b;
	}

	bool IsFullScreen() { return isFullScreen; }

	void SetScrHeight(int h)
	{
		screenHeight = h;
		confIni[section]["height"] = h;
	}

	void SetScrWidth(int w)
	{
		screenWidth = w;
		confIni[section]["width"] = w;
	}

	void SaveConfig()
	{
		SetCurrentDirectory(directory);
		confIni.save(filePath);
	}

	void Init() {
		confIni.load(filePath);
		screenWidth = confIni[section]["width"].as<int>();
		screenHeight = confIni[section]["height"].as<int>();
		volBGM = confIni[section]["vol_bgm"].as<int>();
		volSE = confIni[section]["vol_se"].as<int>();
		FPS = confIni[section]["fps"].as<int>();
		isFullScreen = confIni[section]["enFullScreen"].as<int>();
		debug = confIni[section]["debug"].as<int>();
		//screenWidth = GetPrivateProfileInt("Screen", "width", screenWidth, iniFile);		//スクリーンの幅
		//screenHeight = GetPrivateProfileInt("Screen", "height", screenHeight, iniFile);	//スクリーンの高さ
		//SetVolBGM(GetPrivateProfileInt(section, "vol_bgm", volBGM, iniFile));		//BGM
		//SetVolSE(GetPrivateProfileInt(section, "vol_se", volSE, iniFile));			//SE
		//SetFPS(GetPrivateProfileInt(section, "fps", 60, iniFile));					//FPS（画面更新速度）
		//SetFullScreen(GetPrivateProfileInt(section, "enFullScreen", 0, iniFile));//フルスクリーンの有効無効
		//debug = GetPrivateProfileInt(section, "debug", 0, iniFile);
	}

	bool IsDebug()
	{
		return debug;
	}
}