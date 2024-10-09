#include <Windows.h>
#include "CsvManager.h"
#include "Debug.h"

//�R���X�g���N�^
CsvManager::CsvManager()
{
	data_.clear();
}

//�f�X�g���N�^
CsvManager::~CsvManager()
{
	//�S�f�[�^���J��
	for (int y = 0; y < data_.size(); y++)
	{
		for (int x = 0; x < data_[y].size(); x++)
		{
			data_[y][x].clear();
		}
	}
}

//CSV�t�@�C���̃��[�h
bool CsvManager::Load(std::string fileName)
{
	//�t�@�C�����J��
	HANDLE hFile;
	hFile = CreateFile(fileName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	//�J���Ȃ�����
	if (hFile == INVALID_HANDLE_VALUE)
	{
		std::string message = "�u" + fileName + "�v���J���܂���B\n�J���Ă���ꍇ�͕��Ă��������B";
		MessageBox(NULL, message.c_str(), "BaseProjDx9�G���[", MB_OK);

		return false;
	}

	//�t�@�C���̃T�C�Y�i�������j�𒲂ׂ�
	DWORD fileSize = GetFileSize(hFile, NULL);

	//���ׂĂ̕�����������z���p��
	char* temp;
	temp = new char[fileSize];

	//�t�@�C���̒��g��z��ɓǂݍ���
	DWORD dwBytes = 0;
	ReadFile(hFile, temp, fileSize, &dwBytes, NULL);

	//�J�����t�@�C�������
	CloseHandle(hFile);
	//1�s�̃f�[�^������z��
	std::vector<std::string>	line;

	//���ׂ镶���̈ʒu
	DWORD index = 0;

	//�Ō�̕����܂ŌJ��Ԃ�
	while (index < fileSize)
	{
		//index�����ڂ���u,�v���u���s�v�܂ł̕�������擾
		std::string val;
		GetToComma(&val, temp, &index);

		//��������0�������Ƃ������Ƃ͍s��
		if (val.length() - 1 == 0)
		{
			//_data��1�s���ǉ�
			data_.push_back(line);

			//1�s�f�[�^���N���A
			line.clear();

			//index++;
			continue;
		}

		//1�s���̃f�[�^�ɒǉ�
		line.push_back(val);
	}

	//�ǂݍ��񂾃f�[�^�͊J������
	delete[] temp;

	//����
	return true;
}

//�u,�v���u���s�v�܂ł̕�������擾
void CsvManager::GetToComma(std::string* result, std::string data, DWORD* index)
{
	//�u,�v�܂ňꕶ������result�ɓ����
	while (data[*index] != ',' && data[*index] != '\n' && data[*index] != '\r')
	{
		*result += data[*index];
		(*index)++;
	}

	//�Ō�Ɂu\0�v��t����
	*result += '\0';
	(*index)++;
}

//�w�肵���ʒu�̃f�[�^�𕶎���Ŏ擾
std::string CsvManager::GetString(DWORD x, DWORD y)
{
	if (x < 0 || x >= GetWidth() || y < 0 || y >= GetHeight())
		return "";

	return data_[y][x];
}

//�w�肵���ʒu�̃f�[�^�𐮐��Ŏ擾
int CsvManager::GetValue(DWORD x, DWORD y)
{
	return atoi(GetString(x, y).c_str());
}

//�t�@�C���̗񐔂��擾
size_t CsvManager::GetWidth()
{
	return data_[0].size();
}

//�t�@�C���̍s�����擾
size_t CsvManager::GetHeight()
{
	return data_.size();
}

bool CsvManager::Write(std::string fileName, DWORD x, DWORD y, std::string repData)
{
	//�t�@�C�����J��
	HANDLE hFile2;
	hFile2 = CreateFile(fileName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	//�J���Ȃ�����
	if (hFile2 == INVALID_HANDLE_VALUE)
	{
		std::string message = "�u" + fileName + "�v���J���܂���B\n�J���Ă���ꍇ�͕��Ă��������B";
		MessageBox(NULL, message.c_str(), "BaseProjDx9�G���[", MB_OK);

		return false;
	}

	////�t�@�C���̃T�C�Y�i�������j�𒲂ׂ�
	//DWORD fileSize = GetFileSize(hFile, NULL);
	//
	////���ׂĂ̕�����������z���p��
	//char* temp;
	//temp = new char[fileSize];
	//
	////�t�@�C���̒��g��z��ɓǂݍ���
	DWORD dwBytes = 0;
	//ReadFile(hFile, temp, fileSize, &dwBytes, NULL);
	//
	if (x < 0 || x >= GetWidth() || y < 0 || y >= GetHeight())return false;
	//38232 
	data_[y][x] = repData;
	data_[y][x] += " ";
	//Debug::Log(data_[y][x]);


	//temp�̒l���ǂ��ɂ����ĕς���@data_������temp2�ɏ����Ă����΂����̂ł́H

	std::string writedata;

	for (int i = 0; i < GetHeight(); i++) {
		for (int j = 0; j < GetWidth(); j++) {
			writedata += data_[i][j];
			writedata.pop_back();
			if (static_cast<unsigned long long>(j) + 1 != GetWidth())writedata += ",";
		}

		//if (static_cast<unsigned long long>(i) + 1 != GetHeight())
		writedata += "\r\n";
	}
	writedata += "\0";
	Debug::Log(writedata,true);
	Debug::Log("�݂Ă邩?");
	//�t�@�C���̒��g��z��ɓǂݍ���
	////dwBytes = 0;
	WriteFile(hFile2, writedata.c_str(), writedata.size(), &dwBytes, NULL);

	//�J�����t�@�C�������
	CloseHandle(hFile2);
	//�ǂݍ��񂾃f�[�^�͊J������
	//delete[] temp;
	//����
	return true;

}
