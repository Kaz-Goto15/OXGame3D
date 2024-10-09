#pragma once
#include <string>
#include <windows.h>
//-----------------------------------------------------------
//�T�E���h���Ǘ�����iXAudio�g�p�j
//-----------------------------------------------------------
namespace Audio
{

	const int NULL_HANDLE = -1;

	enum ATTRIBUTE {
		BGM,
		SE,
		OTHER
	};
	//������
	void Initialize();

	//�T�E���h�t�@�C��(.wav�j�����[�h
	//���łɓ������O�̃t�@�C�������[�h�ς݂̏ꍇ�́A�����̃f�[�^�̔ԍ���Ԃ�
	//�����FfileName	�t�@�C����
	//�����FisLoop		���[�v�Đ����������Ȃ�true
	//�����FsvNum�@		�����ɖ炷�ő吔�i�ȗ��j
	//�ߒl�F���̃f�[�^�Ɋ��蓖�Ă�ꂽ�ԍ�
	int Load(std::string fileName, bool isLoop = false, int svNum = 1, ATTRIBUTE at = OTHER);

	//�Đ�
	//�����Fhandle	�炵�����T�E���h�̔ԍ�
	void Play(int ID);

	//��~
	//�����Fhandle	�~�߂����T�E���h�̔ԍ�
	void Stop(int ID);

	//�V�[�����Ƃ̉���i���[�h�����T�E���h������j
	void Release();

	//�{�̂����
	void AllRelease();

	//�s�b�`�X�V
	void SetPitch(int ID,float pitch);

	bool Confirm(bool* prevSucc, BOOL b, std::string msg);
	bool Confirm(bool prevSucc, BOOL b, std::string msg);
	bool IsPlaying(int ID);
};

