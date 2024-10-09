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
		confIni.load(filePath);									//ini���[�h
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
		//���r���Ń��j�^�[�ς����肵�ăT�C�Y�ς���Ă��ύX����Ȃ�
		screenWidth = GetSystemMetrics(SM_CXSCREEN);			//�X�N���[����
		screenHeight = GetSystemMetrics(SM_CYSCREEN);			//�X�N���[������

		using namespace IniManager;
		windowWidth = confIni[section]["width"].as<int>();		//�E�B���h�E��
		windowHeight = confIni[section]["height"].as<int>();	//�E�B���h�E����
		volBGM = confIni[section]["vol_bgm"].as<int>();			//BGM����
		volSE = confIni[section]["vol_se"].as<int>();			//SE����
		FPS = confIni[section]["fps"].as<int>();				//FPS�l
		//isFullScreen = confIni[section]["enFullScreen"].as<int>();
		SetFullScreen(confIni[section]["enFullScreen"].as<int>());	//�t���X�N���[���t���O
		debug = confIni[section]["debug"].as<int>();			//�f�o�b�O�t���O
	}

	bool IsDebug(){	return debug;	}

	void SetWindowHandle(HWND hwnd)	{	windowHandle = hwnd;	}
	HWND GetWindowHandle()	{	return windowHandle;	}

	int GetKey(KEY key)
	{
		return key;
	}

}
namespace AspectRatio {
	int aspectRatioW;	//�A�X�䉡
	int aspectRatioH;	//�A�X��c

	//������
	void Init() {
		const char* section = "Aspect Ratio";
		aspectRatioW = IniManager::confIni[section]["W"].as<int>();
		aspectRatioH = IniManager::confIni[section]["H"].as<int>();
	}

	//�l���ŏ��A�ő�͈͓̔�����bool�ŕԂ�
	bool Between(int val, int min, int max) {
		return (min <= val && val <= max);
	}

	/// <summary>
	/// �E�B���h�E�T�C�Y���A�X��ɋ�������
	/// </summary>
	/// <param name="w">�E�B���h�E�T�C�Y��</param>
	/// <param name="h">�E�B���h�E�T�C�Y�c</param>
	void ConvertWindowSize(int& w, int& h, int prevW, int prevH) {
		//���݂̃E�B���h�E�̈ʒu���擾
		RECT rc;
		GetWindowRect(SystemConfig::GetWindowHandle(), &rc);
		RECT windowSize;
		GetClientRect(SystemConfig::GetWindowHandle(), &windowSize);
		int windowX = rc.left;	//�E�B���h�E��
		int windowY = rc.top;	//�E�B���h�E��
		int tmpW = -1, tmpH = -1;
		bool modX = false, modY = false;
		if (windowSize.right != SystemConfig::windowWidth) {
			if (w > SystemConfig::screenWidth)w = SystemConfig::screenWidth;	//�E�B���h�E���̍ő���X�N���[������
			tmpH = w * aspectRatioH / aspectRatioW;	//���ƃA�X�䂩�獂�������߂�
			modX = true;

		}
		if (windowSize.bottom != SystemConfig::windowHeight) {
			if (h > SystemConfig::screenHeight)h = SystemConfig::screenHeight;	//�E�B���h�E�����̍ő���X�N���[��������
			tmpW = h * aspectRatioW / aspectRatioH;	//�����ƃA�X�䂩�畝�����߂�
			modY = true;
		}
		if (modX && !modY) {
			h = tmpH;
		}
		if (!modX && modY) {
			w = tmpW;
		}
		if (modX && modY) {
			if (w > tmpW)h = tmpH;
			else w = tmpW;
		}

		//�E�B���h�E���W���オ�X�N���[���O�������肵����X�N���[���T�C�Y����E�B���h�E�T�C�Y�������l�ɂ���
		//�f���A���͍l�����ĂȂ�
		if (!Between(windowX, 0, SystemConfig::screenWidth - windowX)) {
			windowX = SystemConfig::screenWidth - w;
		}
		if (!Between(windowY, 0, SystemConfig::screenHeight - windowY)) windowY = SystemConfig::screenHeight - h;
	}
};

namespace SystemConfig {
	bool initFlag = false;
	void Init() {
		IniManager::Load();
		SystemConfig::Initialize();
		AspectRatio::Init();
		initFlag = true;
	}

	bool IsResized()
	{
		if (isResized) {

			isResized = false;
			/*AspectRatio::ConvertWindowSize(SystemConfig::windowWidth, SystemConfig::windowHeight);*/
			return true;
		}
		return isResized;
	}
	void SetWindowSize(int w, int h)
	{
		if (initFlag) {
			AspectRatio::ConvertWindowSize(w, h, SystemConfig::windowWidth, SystemConfig::windowHeight);
			windowHeight = h;
			windowWidth = w;
			IniManager::confIni[section]["height"] = h;
			IniManager::confIni[section]["width"] = w;


			isResized = true;
		}
	}

}
/*
IniManager �f�[�^�Ǎ� �O���t�@�C���𒼐ړI�Ɉ��� �f�[�^�͊O������ǂݍ��񂾃t�@�C����tmp�ő��݂���
SystemConfig �f�[�^�{�� �O���N���X�ł̎g�p�E�ύX���s�� �f�[�^���̂������ɂ���
AspectRatio:�A�X��֘A�̏��� �T�u�̉^�p �A�X�䂾���ł����������ȗʂɂȂ����̂ł܂Ƃ߂�
����Ȃӂ��ɂ����� �ǐ��H�m���

*/