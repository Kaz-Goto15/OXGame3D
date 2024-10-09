#pragma once
#include <Windows.h>
#include "Engine/Input.h"
namespace SystemConfig {
	extern int windowHeight;
	extern int windowWidth;
	/// BGM音量設定 0-100
	/// <param name="vol">音量(%)</param>
	void SetVolBGM(int vol);

	/// BGM音量取得
	/// <returns>音量(%)</returns>
	int GetVolBGM();

	/// SE音量設定
	/// <param name="vol">音量(%)</param>
	void SetVolSE(int vol);

	/// SE音量取得
	/// <returns>音量(%)</returns>
	int GetVolSE();

	/// フレームレート指定
	/// <param name="fps">FPS</param>
	void SetFPS(int fps);

	/// フレームレート取得
	/// <returns>FPS</returns>
	int GetFPS();

	/// フルスクリーンを有効にするか
	/// <param name="b">true=有効 false=無効</param>
	void SetFullScreen(bool b);

	/// フルスクリーンが有効かどうか
	/// <returns>有効であればtrue</returns>
	bool IsFullScreen();

	/// ウィンドウ高さ変更
	/// <param name="h">新規高さ</param>
	void SetWindowHeight(int h);

	/// ウィンドウ幅変更
	/// <param name="w">新規幅</param>
	void SetWindowWidth(int w);

	/// ウィンドウサイズ変更
	/// <param name="w">Width</param>
	/// <param name="h">Height</param>
	void SetWindowSize(int w, int h);

	bool IsResized();
	/// 設定保存
	void SaveConfig();

	/// 初期化
	void Init();

	bool IsDebug();

	void SetWindowHandle(HWND hwnd);
	HWND GetWindowHandle();

	//まとめるためだけに実装した超簡潔キーコン 修正必至
	enum KEY {
		KEY_UP = DIK_W,
		KEY_DOWN = DIK_S,
		KEY_LEFT = DIK_A,
		KEY_RIGHT = DIK_D,
		KEY_ESC = DIK_ESCAPE,
		KEY_ACT = DIK_SPACE,
		KEY_CHANGE = DIK_LSHIFT,
		KEY_CHANGE_AXIS = DIK_E
	};

	//キーバインド実装などで役立つため一応ゲッターは用意しておく
	int GetKey(KEY key);
}