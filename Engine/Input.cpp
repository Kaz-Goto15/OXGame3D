#include "Input.h"
#include "Global.h"
#include <vector>
#include <string>
#include "Debug.h"
#include "../SystemConfig.h"
namespace Input
{

	//�E�B���h�E�n���h��
	HWND	hWnd_;

	//DirectInput�I�u�W�F�N�g
	LPDIRECTINPUT8			pDInput_;

	//�L�[�{�[�h
	LPDIRECTINPUTDEVICE8	pKeyDevice_;	//�f�o�C�X�I�u�W�F�N�g
	BYTE keyState_[256];					//���݂̊e�L�[�̏��
	BYTE prevKeyState_[256];				//�O�t���[���ł̊e�L�[�̏��

	//�}�E�X
	LPDIRECTINPUTDEVICE8	pMouseDevice_;	//�f�o�C�X�I�u�W�F�N�g
	DIMOUSESTATE mouseState_;				//�}�E�X�̏��
	DIMOUSESTATE prevMouseState_;			//�O�t���[���̃}�E�X�̏��
	POINT mousePos_;							//�}�E�X�J�[�\���̈ʒu

	//�R���g���[���[
	const int MAX_PAD_NUM = 4;
	XINPUT_STATE controllerState_[MAX_PAD_NUM];
	XINPUT_STATE prevControllerState_[MAX_PAD_NUM];

	//string vector
	std::vector<std::string> keyString = {
		"Esc","1","2","3","4","5","6","7","8","9","0","-","=","BackSpace","Tab",
		"Q","W","E","R","T","Y","U","I","O","P","[","]","Enter","LCtrl",
		"A","S","D","F","G","H","J","K","L",";","'","`",
		"LShift","\\","Z","X","C","V","B","N","M",",",".","/","RShift",
		"*(Numpad)","LAlt","Space","Caps Lock",
		"F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","Num Lock","Scroll Lock",
		"7 (Numpad)","8 (Numpad)","9 (Numpad)","- (Numpad)","4 (Numpad)","5 (Numpad)","6 (Numpad)",
		"+ (Numpad)","1 (Numpad)","2 (Numpad)","3 (Numpad)","0 (Numpad)",". (Numpad)",
		"F11","F12","F13","F14","F15","kana","convert","noconvert","\\","=","^","@",":","_","Chinese Characters",
		"Stop","(JapanAX)","(J3100)","Enter (Numpad)","RCtrl",", (Numpad)","/ (Numpad)","SysRq",
		"RAlt","Pause","Home","UpArrow","PageUp","LeftArrow","RightArrow","End","DownArrow","PageDown",
		"Insert","Delete","Windows","Windows","Menu","Power","Windows"
	};
	std::vector<std::string> padString = {
		"PAD_UP","PAD_DOWN", "PAD_LEFT", "PAD_RIGHT", "PAD_START", "PAD_BACK", "PAD_L_THUMB", "PAD_R_THUMB",
		"PAD_L_SHOULDER", "PAD_R_SHOULDER", "PAD_A", "PAD_B","PAD_X","PAD_Y"
	};

	//������
	void Initialize(HWND hWnd)
	{
		//�E�B���h�E�n���h��
		hWnd_ = hWnd;

		//DirectInput�{��
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&pDInput_, nullptr);

		//�L�[�{�[�h
		pDInput_->CreateDevice(GUID_SysKeyboard, &pKeyDevice_, nullptr);
		pKeyDevice_->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice_->SetCooperativeLevel(NULL, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

		//�}�E�X
		pDInput_->CreateDevice(GUID_SysMouse, &pMouseDevice_, nullptr);
		pMouseDevice_->SetDataFormat(&c_dfDIMouse);
		pMouseDevice_->SetCooperativeLevel(hWnd_, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}


	//�X�V
	void Update()
	{
		//�L�[�{�[�h
		pKeyDevice_->Acquire();
		memcpy(prevKeyState_, keyState_, sizeof(keyState_));
		pKeyDevice_->GetDeviceState(sizeof(keyState_), &keyState_);

		//�}�E�X
		pMouseDevice_->Acquire();
		memcpy(&prevMouseState_, &mouseState_, sizeof(mouseState_));
		pMouseDevice_->GetDeviceState(sizeof(mouseState_), &mouseState_);

		//�R���g���[���[
		for (int i = 0; i < MAX_PAD_NUM; i++)
		{
			memcpy(&prevControllerState_[i], &controllerState_[i], sizeof(controllerState_[i]));
			XInputGetState(i, &controllerState_[i]);
		}

	}



	//�J��
	void Release()
	{
		SAFE_RELEASE(pMouseDevice_);
		SAFE_RELEASE(pKeyDevice_);
		SAFE_RELEASE(pDInput_);
	}



	/////////////////////////////�@�L�[�{�[�h���擾�@//////////////////////////////////

	//�L�[��������Ă��邩���ׂ�
	bool IsKey(int keyCode)
	{
		//�����Ă�
		if (keyState_[keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}


	//�L�[���������������ׂ�i�������ςȂ��͖����j
	bool IsKeyDown(int keyCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if (IsKey(keyCode) && !(prevKeyState_[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}


	//�L�[���������������ׂ�
	bool IsKeyUp(int keyCode)
	{
		//�������ĂȂ��āA�O��͉����Ă�
		if (!IsKey(keyCode) && prevKeyState_[keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	//�������L�[�𒲂ׂ�i�������ςȂ��͖����j
	//�ߒl�F�����Ă�L�[�̐��l(�R�[�h���������A�P�L�[�̂�) �Ȃ��ꍇ-1
	int AnyKeyDown() {
		int returnVal = -1;
		for (int i = 0; i < 223;i++) {
			if (!IsKey(i) && prevKeyState_[i] & 0x80) {
				returnVal = i;
				break;
			}
		}
		return returnVal;
	}

	std::string KeyInt2String(int keyCode) {
		return keyString.at(keyCode - 1);
	}

	/////////////////////////////�@�}�E�X���擾�@//////////////////////////////////

	//�}�E�X�̃{�^����������Ă��邩���ׂ�
	bool IsMouseButton(int buttonCode)
	{
		//�����Ă�
		if (mouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	//�}�E�X�̃{�^�����������������ׂ�i�������ςȂ��͖����j
	bool IsMouseButtonDown(int buttonCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if (IsMouseButton(buttonCode) && !(prevMouseState_.rgbButtons[buttonCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	//�}�E�X�̃{�^�����������������ׂ�
	bool IsMouseButtonUp(int buttonCode)
	{
		//�������ĂȂ��āA�O��͉����Ă�
		if (!IsMouseButton(buttonCode) && prevMouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	//�}�E�X�J�[�\���̈ʒu���擾
	XMFLOAT3 GetMousePosition(bool stdScreenCenter)
	{
		XMFLOAT3 result = XMFLOAT3((float)mousePos_.x, (float)mousePos_.y, 0);
		if (stdScreenCenter) {
			result.x -= SystemConfig::windowWidth / 2.0f;
			result.y -= SystemConfig::windowHeight / 2.0f;
		}
		return result;
	}

	//�}�E�X�J�[�\���̈ʒu���Z�b�g
	void SetMousePosition(int x, int y)
	{
		mousePos_.x = x;
		mousePos_.y = y;
	}

	//���̃t���[���ł̃}�E�X�̈ړ��ʂ��擾
	XMFLOAT3 GetMouseMove()
	{
		XMFLOAT3 result = XMFLOAT3((float)mouseState_.lX, (float)mouseState_.lY, (float)mouseState_.lZ);
		//Debug::Log("x:" + std::to_string(result.x) + "y:" + std::to_string(result.y), true);
		return result;
	}

	/////////////////////////////�@�R���g���[���[���擾�@//////////////////////////////////

	//�R���g���[���[�̃{�^����������Ă��邩���ׂ�
	bool IsPadButton(int buttonCode, int padID)
	{
		if (controllerState_[padID].Gamepad.wButtons & buttonCode)
		{
			return true; //�����Ă�
		}
		return false; //�����ĂȂ�
	}

	//�R���g���[���[�̃{�^�����������������ׂ�i�������ςȂ��͖����j
	bool IsPadButtonDown(int buttonCode, int padID)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if (IsPadButton(buttonCode, padID) && !(prevControllerState_[padID].Gamepad.wButtons & buttonCode))
		{
			return true;
		}
		return false;
	}

	//�R���g���[���[�̃{�^�����������������ׂ�
	bool IsPadButtonUp(int buttonCode, int padID)
	{
		//�������ĂȂ��āA�O��͉����Ă�
		if (!IsPadButton(buttonCode, padID) && prevControllerState_[padID].Gamepad.wButtons & buttonCode)
		{
			return true;
		}
		return false;
	}

	//�������{�^���𒲂ׂ�
	//�ߒl�F�����Ă�{�^���̐��l (�R�[�h���������A�P�{�^���̂�) �Ȃ��ꍇ-1
	int AnyPadButtonDown(int padID) {
		int returnVal = -1;
		for (int i = 0; i < 32769; i = i * 2) {
			if (!IsPadButton(i, padID) && prevControllerState_[padID].Gamepad.wButtons & 0x80) {
				returnVal = i;
				break;
			}
		}
		return returnVal;
	}

	float GetAnalogValue(int raw, int max, int deadZone)
	{
		float result = (float)raw;

		if (result > 0)
		{
			//�f�b�h�]�[��
			if (result < deadZone)
			{
				result = 0;
			}
			else
			{
				result = (result - deadZone) / (max - deadZone);
			}
		}

		else
		{
			//�f�b�h�]�[��
			if (result > -deadZone)
			{
				result = 0;
			}
			else
			{
				result = (result + deadZone) / (max - deadZone);
			}
		}

		return result;
	}


	//���X�e�B�b�N�̌X�����擾
	XMFLOAT3 GetPadStickL(int padID)
	{
		float x = GetAnalogValue(controllerState_[padID].Gamepad.sThumbLX, 32767, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		float y = GetAnalogValue(controllerState_[padID].Gamepad.sThumbLY, 32767, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		return XMFLOAT3(x, y, 0);
	}

	//�E�X�e�B�b�N�̌X�����擾
	XMFLOAT3 GetPadStickR(int padID)
	{
		float x = GetAnalogValue(controllerState_[padID].Gamepad.sThumbRX, 32767, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		float y = GetAnalogValue(controllerState_[padID].Gamepad.sThumbRY, 32767, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		return XMFLOAT3(x, y, 0);
	}

	//���g���K�[�̉������݋���擾
	float GetPadTrrigerL(int padID)
	{
		return GetAnalogValue(controllerState_[padID].Gamepad.bLeftTrigger, 255, XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
	}

	//�E�g���K�[�̉������݋���擾
	float GetPadTrrigerR(int padID)
	{
		return GetAnalogValue(controllerState_[padID].Gamepad.bRightTrigger, 255, XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
	}

	//�U��������
	void SetPadVibration(int l, int r, int padID)
	{
		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		vibration.wLeftMotorSpeed = l; // �����[�^�[�̋���
		vibration.wRightMotorSpeed = r;// �E���[�^�[�̋���
		XInputSetState(padID, &vibration);
	}

}