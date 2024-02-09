#pragma once

namespace SystemConfig {
	extern int screenHeight;
	extern int screenWidth;
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
	void EnableFullScreen(bool b);

	/// フルスクリーンが有効かどうか
	/// <returns>有効であればtrue</returns>
	bool IsFullScreen();

	/// 初期化
	void Init();
}