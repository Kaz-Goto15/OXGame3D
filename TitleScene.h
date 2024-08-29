#pragma once
#include "Engine/GameObject.h"

class Text;
class ButtonGP;
class DebugText;
class SceneManager;
class Screen;

class TitleScene : public GameObject
{
	enum Img {
		PIC_BACKGROUND,
		PIC_TITLE,
		PIC_WHITE,
		//SEL_CHOOSE,
		PIC_MAX
	};
	int hPict_[Img::PIC_MAX];	//�n���h���i�[�z��

	enum STATE {
		S_STANDBY,
		S_MAIN,
		S_SELECT,
	}state_;

	enum SELECT_STATE {
		S_SEL_START,
		S_SEL_CREDIT,
		S_SEL_OPTION,
		S_SEL_EXIT,
		S_SEL_MAX
	}selectState_;

	//�{�^������ʊO�������Ă���`��Ɏg��
	const int DEFAULT_PROGRESS;	//�ēx�������ۂ�progress�ɐݒ肳���l
	int progress;				//�i��
	int maxProgress;			//�ő�i���� �t���[���w��
	int btnFadeEaseNo;			//�C�[�W���O�ԍ��������

	const int ALPHA_ZERO, ALPHA_MAX;	//�����x�����Ɏg���萔

	//�^�C�g��
	const XMINT2 TITLE_PROGRESS_POINT;	//���w�i���^�C�g���̂ݕ\���܂ł̃t���[����/�{�^��������̃{�^���\���܂ł�����t���[���� ���Z���A�A�j���[�V�����Ŏw��t���[���ɃL�[��ł����ފ��o��
	const XMINT2 TITLE_Y_FADE;	//�^�C�g���c�t�F�[�h �������W(�X�v���b�V����ɕ\�������Y���W)/�ړ�����W ���1280x720

	//�{�^��
	std::string State2Str(SELECT_STATE state);	//�I���X�e�[�g(�{�^��)�𕶎���� �{�^���̖��O�\���Ɏg�p
	ButtonGP* btn[S_SEL_MAX];	//�e�{�^���I�u�W�F�N�g
	const int BUTTON_X_SPACE;	//�{�^�����Ԋu
	const XMINT2 BUTTON_Y_FADE;	//�{�^���c�t�F�[�h �������W/�ړ�����W ���1280x720

	//�e�L�X�g
	Text* txtPressStart;			//�e�L�X�g�I�u�W�F�N�g
	const XMINT2 TEXT_POSITION;		//�e�L�X�g�\�����W ���1280x720
	const char* FIRST_TEXT_DESCR;	//�ŏ��ɕ\������e�L�X�g�̓��e

	std::string TitleImgFileName(Img E_IMG);
	//void Run(SELECT_STATE& ss);

	//DebugText* debugText;
	//std::string debugStr[20];
	void InitButton(SELECT_STATE ss, std::string text, XMINT2 pos);

	//int hSound_;	//��

	SceneManager* pSceneManager;
	Screen* pScreen;

	//1/2
	template <class T>
	T Half(T pValue) {
		return pValue /= 2.0f;
	}
	//�͈͓���
	template <class T>
	bool Between(T value, T min, T max) {
		return (min <= value && value <= max);
	}
	//������������
	bool IsEven(int value) {
		return (value % 2 == 0);
	}

public:
	TitleScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void ButtonAct(int hAct);
};