#pragma once
#include <Windows.h>
#include "Engine/Input.h"
namespace SystemConfig {
	extern int windowHeight;
	extern int windowWidth;
	/// BGM���ʐݒ� 0-100
	/// <param name="vol">����(%)</param>
	void SetVolBGM(int vol);

	/// BGM���ʎ擾
	/// <returns>����(%)</returns>
	int GetVolBGM();

	/// SE���ʐݒ�
	/// <param name="vol">����(%)</param>
	void SetVolSE(int vol);

	/// SE���ʎ擾
	/// <returns>����(%)</returns>
	int GetVolSE();

	/// �t���[�����[�g�w��
	/// <param name="fps">FPS</param>
	void SetFPS(int fps);

	/// �t���[�����[�g�擾
	/// <returns>FPS</returns>
	int GetFPS();

	/// �t���X�N���[����L���ɂ��邩
	/// <param name="b">true=�L�� false=����</param>
	void SetFullScreen(bool b);

	/// �t���X�N���[�����L�����ǂ���
	/// <returns>�L���ł����true</returns>
	bool IsFullScreen();

	/// �E�B���h�E�����ύX
	/// <param name="h">�V�K����</param>
	void SetWindowHeight(int h);

	/// �E�B���h�E���ύX
	/// <param name="w">�V�K��</param>
	void SetWindowWidth(int w);

	/// �E�B���h�E�T�C�Y�ύX
	/// <param name="w">Width</param>
	/// <param name="h">Height</param>
	void SetWindowSize(int w, int h);

	bool IsResized();
	/// �ݒ�ۑ�
	void SaveConfig();

	/// ������
	void Init();

	bool IsDebug();

	void SetWindowHandle(HWND hwnd);
	HWND GetWindowHandle();

	//�܂Ƃ߂邽�߂����Ɏ����������Ȍ��L�[�R�� �C���K��
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

	//�L�[�o�C���h�����ȂǂŖ𗧂��߈ꉞ�Q�b�^�[�͗p�ӂ��Ă���
	int GetKey(KEY key);
}