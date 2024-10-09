#pragma once
#include <string>
#include <sstream>
#include "Engine/Input.h"
#include "Engine/CsvManager.h"
#include "GameData.h"

//�Q�[���Ŏg�p����L�[
enum KEY_ID
{
	KEY_ID_SELECT = 0,
	KEY_ID_CANSEL,
	KEY_ID_UP_JUMP,
	KEY_ID_DOWN,
	KEY_ID_LEFT,
	KEY_ID_RIGHT,
};

namespace KeyConfig
{

	//�L�[�u��
	//�����FreplaseID	�u���L�[ID
	//�����FkeyNum	�u���L�[���l
	void ChangeKey(KEY_ID replaseID, int keyNum);

	//�L�[�R���t�B�O������ ���f�o�b�O�p�@���s������S�L�[�ύX�������������
	//�����߂�l����
	void InitKey();

	//�L�[�Ǎ��@�K���Ăяo�����̏������ɏ���
	void Init(std::string csvName);

	//�L�[�擾 ������Ă��邩�̔��莞�Ɏg�p
	//���� KEY_ID�@�L�[ID
	//�ߒl int�@�@�Ή����鐔�l��Ԃ�(dInput)
	int GetKey(KEY_ID keyid);
};

