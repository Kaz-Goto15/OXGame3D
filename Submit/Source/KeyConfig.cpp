#include "KeyConfig.h"
#include "Engine/Debug.h"
#include "Engine/Input.h"
#include <vector>

namespace KeyConfig {

	static CsvManager csv;
	static std::string csvFileName;
	//�L�[�u��
	//�����FreplaseID	�u���L�[ID
	//�����FkeyNum	�u���L�[���l
	void KeyConfig::ChangeKey(KEY_ID replaseID, int keyNum)
	{
		//�����{�^�������邩�m�F���� ���������������ւ���
		for (int i = 1; i < csv.GetHeight(); i++) {
			if (csv.GetValue(2, i) == keyNum) {
				csv.Write(csvFileName, 2, i, std::to_string(csv.GetValue(2, replaseID + 1)));
				Debug::Log("����");
			}
		}
		//�u��
		csv.Write(csvFileName, 2, replaseID + 1, std::to_string(keyNum));
	}

	//�L�[�R���t�B�O������ ���f�o�b�O�p�@���s������S�L�[�ύX�������������
	//�����߂�l����
	void KeyConfig::InitKey()
	{


		std::vector<int> keyInit = {
			DIK_SPACE,
			DIK_LSHIFT,
			DIK_W,
			DIK_S,
			DIK_A,
			DIK_D
		};
		for (int i = 1; i < csv.GetHeight(); i++) {
			csv.Write(csvFileName,
				2,
				i,
				std::to_string(keyInit[i - 1]));
		}
	}

	//�L�[�Ǎ��@�K���Ăяo�����̏������ɏ���
	//���� csvName �t�@�C����
	void KeyConfig::Init(std::string csvName)
	{
		csv.Load(csvName);
		csvFileName = csvName;
	}

	//�L�[�擾 ������Ă��邩�̔��莞�Ɏg�p
	//���� KEY_ID�@�L�[ID
	//�ߒl int�@�@�Ή����鐔�l��Ԃ�(dInput)
	int KeyConfig::GetKey(KEY_ID keyid)
	{
		int returnint = csv.GetValue(2, keyid + 1);
		return returnint;
	}
}