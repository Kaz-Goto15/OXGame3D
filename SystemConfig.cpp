#include "SystemConfig.h"
#include <assert.h>
#include <Windows.h>
#include <string>
#include "./Include/inicpp.h"
#include "./Engine/Direct3D.h"
//#include <stdlib.h>

namespace IniManager {
	ini::IniFile confIni;
	const char* directory = "Assets";
	const char* filePath = ".\\systemConf.ini";
	void Load() {
		confIni.load(filePath);									//iniロード
	}
	void Save() {

		SetCurrentDirectory(directory);
		confIni.save(filePath);
	}
}

namespace SystemConfig {
	int screenWidth = 800;
	int screenHeight = 600;
	int windowWidth = 800;
	int windowHeight = 600;
	int volBGM = 0;
	int volSE = 0;
	int FPS = 0;
	bool isFullScreen = false;
	bool debug = false;
	//ini::IniFile confIni;
	bool isResized = false;

	const char* section = "System";
	//const char* directory = "Assets";
	//const char* filePath = ".\\systemConf.ini";

	HWND windowHandle;

	void SetVolBGM(int vol) {
		volBGM = vol;
		assert(0 <=vol && vol <= 100);
		IniManager::confIni[section]["vol_bgm"] = vol;
	}
	int GetVolBGM() { return volBGM; }

	void SetVolSE(int vol) {
		volSE = vol;
		assert(0 <= vol && vol <= 100);
		IniManager::confIni[section]["vol_se"] = vol;
	}
	int GetVolSE() { return volSE; }

	void SetFPS(int fps) {
		FPS = fps;
		IniManager::confIni[section]["fps"] = fps;
	}
	int GetFPS() { return FPS; }

	void SetFullScreen(bool b) {
		isFullScreen = b;
		IniManager::confIni[section]["enFullScreen"] = b;

		Direct3D::SetFullScreen(b);
	}

	bool IsFullScreen() { return isFullScreen; }

	void SetWindowHeight(int h)
	{
		windowHeight = h;
		IniManager::confIni[section]["height"] = h;
	}

	void SetWindowWidth(int w)
	{
		windowWidth = w;
		IniManager::confIni[section]["width"] = w;
	}

	void SetWindowSize(int w, int h)
	{
		windowHeight = h;
		windowWidth = w;
		IniManager::confIni[section]["height"] = h;
		IniManager::confIni[section]["width"] = w;
		isResized = true;
	}

	//bool IsResized()
	//{
	//	if (isResized) {
	//		
	//		isResized = false;
	//		return true;
	//	}
	//	return isResized;
	//}

	void SaveConfig()
	{
		IniManager::Save();
	}

	void Initialize() {
		//※途中でモニター変えたりしてサイズ変わっても変更されない
		screenWidth = GetSystemMetrics(SM_CXSCREEN);			//スクリーン幅
		screenHeight = GetSystemMetrics(SM_CYSCREEN);			//スクリーン高さ

		using namespace IniManager;
		windowWidth = confIni[section]["width"].as<int>();		//ウィンドウ幅
		windowHeight = confIni[section]["height"].as<int>();	//ウィンドウ高さ
		volBGM = confIni[section]["vol_bgm"].as<int>();			//BGM音量
		volSE = confIni[section]["vol_se"].as<int>();			//SE音量
		FPS = confIni[section]["fps"].as<int>();				//FPS値
		//isFullScreen = confIni[section]["enFullScreen"].as<int>();
		SetFullScreen(confIni[section]["enFullScreen"].as<int>());	//フルスクリーンフラグ
		debug = confIni[section]["debug"].as<int>();			//デバッグフラグ
	}

	bool IsDebug(){	return debug;	}

	void SetWindowHandle(HWND hwnd)	{	windowHandle = hwnd;	}
	HWND GetWindowHandle()	{	return windowHandle;	}

}
namespace AspectRatio {
	int aspectRatioW;	//アス比横
	int aspectRatioH;	//アス比縦

	//初期化
	void Init() {
		const char* section = "Aspect Ratio";
		aspectRatioW = IniManager::confIni[section]["W"].as<int>();
		aspectRatioH = IniManager::confIni[section]["H"].as<int>();
	}

	//値が最小、最大の範囲内かをboolで返す
	bool Between(int val, int min, int max) {
		return (min <= val && val <= max);
	}

	/// <summary>
	/// ウィンドウサイズをアス比に矯正する
	/// </summary>
	/// <param name="w">ウィンドウサイズ横</param>
	/// <param name="h">ウィンドウサイズ縦</param>
	void ConvertWindowSize(int& w, int& h) {
		//現在のウィンドウの位置を取得
		RECT rc;
		GetWindowRect(SystemConfig::GetWindowHandle(), &rc);
		int windowX = rc.left;	//ウィンドウ左
		int windowY = rc.top;	//ウィンドウ上

		if (w > SystemConfig::screenWidth)w = SystemConfig::screenWidth;	//ウィンドウ幅の最大をスクリーン幅に
		h = w * aspectRatioH / aspectRatioW;	//幅とアス比から高さを求める
		if (h > SystemConfig::screenHeight)h = SystemConfig::screenHeight;	//ウィンドウ高さの最大をスクリーン高さに
		w = h * aspectRatioW / aspectRatioH;	//高さとアス比から幅を求める

		//ウィンドウ座標左上や右下がスクリーン外だったりしたらスクリーンサイズからウィンドウサイズ引いた値にする
		//デュアルは考慮してない
		if (!Between(windowX, 0, SystemConfig::screenWidth - windowX)) {
			windowX = SystemConfig::screenWidth - w;
		}
		if (!Between(windowY, 0, SystemConfig::screenHeight - windowY)) windowY = SystemConfig::screenHeight - h;
	}
};

namespace SystemConfig {
	void Init() {
		IniManager::Load();
		SystemConfig::Initialize();
		AspectRatio::Init();
	}

	bool IsResized()
	{
		if (isResized) {

			isResized = false;
			AspectRatio::ConvertWindowSize(SystemConfig::windowWidth, SystemConfig::windowHeight);
			return true;
		}
		return isResized;
	}

}
/*
IniManager データ読込 外部ファイルを直接的に扱う データは外部から読み込んだファイルがtmpで存在する
SystemConfig データ本体 外部クラスでの使用・変更を行う データ自体もここにある
AspectRatio:アス比関連の処理 サブの運用 アス比だけでもけっこうな量になったのでまとめた
こんなふうにしたい 可読性？知らん
*/