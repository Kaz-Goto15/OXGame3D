#pragma once
#include <vector>
#include <string>

//-----------------------------------------------------------
//CSV�t�@�C���������N���X
//-----------------------------------------------------------
class CsvManager
{
	//�ǂݍ��񂾃f�[�^�����Ă���2�����z��
	std::vector<std::vector<std::string>> data_;

	//�u,�v���u���s�v�܂ł̕�������擾
	//�����Freuult	���ʂ�����A�h���X
	//�����Fdata	���Ƃ̕�����f�[�^
	//�����Findex	�������ڂ��璲�ׂ邩
	//�ߒl�F�Ȃ�
	void GetToComma(std::string* result, std::string data, DWORD* index);

public:
	//�R���X�g���N�^
	CsvManager();

	//�f�X�g���N�^
	~CsvManager();

	//CSV�t�@�C���̃��[�h
	//�����FfileName�@�t�@�C����
	//�ߒl�F������true�@���s��false
	bool Load(std::string fileName);


	//�w�肵���ʒu�̃f�[�^�𕶎���Ŏ擾
	//�����Fx,y�@�擾�������ʒu
	//�ߒl�F�擾����������
	std::string GetString(DWORD x, DWORD y);

	//�w�肵���ʒu�̃f�[�^�𐮐��Ŏ擾
	//�����Fx,y�@�擾�������ʒu
	//�ߒl�F�擾�����l
	int GetValue(DWORD x, DWORD y);

	//�t�@�C���̗񐔂��擾
	//�����F�Ȃ�
	//�ߒl�F��
	size_t GetWidth();

	//�t�@�C���̍s�����擾
	//�����F�Ȃ�
	//�ߒl�F�s��
	size_t GetHeight();

	//�t�@�C���ɏ�������
	//�����FfileName�@�t�@�C�����@x,y�@�u���������ʒu�@repData�@�u���f�[�^ 
	//�ߒl�F������true�@���s��false
	bool Write(std::string fileName, DWORD x, DWORD y, std::string repData);

};

