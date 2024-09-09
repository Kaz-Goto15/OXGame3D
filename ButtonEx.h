#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"
#include "AudioManager.h"

using std::string;
//�{�^�����Ǘ�����N���X
class ButtonEx : public GameObject
{
protected:
	enum STATE {
		IDLE,
		SELECT,
		PUSH,
		SELECTED,
		MAX
	};
	Text* buttonTextObj_;
	std::string buttonTextName_;
	Text::HORIZONAL_ALIGNMENT hAl;
	Text::VERTICAL_ALIGNMENT vAl;
	int actHandle_;
	bool nextIdle;
	STATE ActTiming;
	AudioManager::AUDIO_SOURCE sound;

	XMFLOAT2 rangeLU, rangeRB;
	
	ButtonEx *leftBtn, *upBtn, *downBtn, *rightBtn;
	bool isSelecting_;
public:
	enum MODE {
		PUSH_ONLY,          //�������A���ڍs
		PUSH_UP,            //�������痣�����Ƃ��Ɉڍs
		PUSH_ONLY_SELECT,   //�������A���ڍs �\���L�[��}�E�X�ړ��őI�����ړ�����
		PUSH_UP_SELECT      //�������痣�����Ƃ��Ɉڍs �\���L�[��}�E�X�ړ��őI�����ړ�����
	}mode_;
	STATE state;

	ButtonEx(GameObject* parent, const std::string& name = "ButtonEx");    //�R���X�g���N�^
	~ButtonEx();                     //�f�X�g���N�^
	void Initialize() override; //������
	void Update() override;     //�X�V
	void Draw() override;       //�`��
	void Release() override;    //���


	//���g(�{�^��)�Ɛe�̑I���X�e�[�g��R�Â���
	void SetAction(int hAct);

	void SetSound(AudioManager::AUDIO_SOURCE audioSource) { sound = audioSource; }
	//�e�L�X�g�ݒ�n
	void SetTextAlignment(Text::HORIZONAL_ALIGNMENT h, Text::VERTICAL_ALIGNMENT v);
	void SetFont(const char* fileName, const unsigned int charWidth, const unsigned int charHeight, const unsigned int rowLength);
	void SetFont(TEXT_SOURCE textScr);
	void SetText(std::string buttonName);

	//�{�^���摜�n
private:
	enum DIV_W {
		W_LEFT = 0,
		W_CENTER,
		W_RIGHT,
		W_MAX,
	};
	enum DIV_H {
		H_TOP = 0,
		H_CENTER,
		H_BOTTOM,
		H_MAX
	};
	const string DEFAULT_BUTTON_IMG[STATE::MAX];		//�f�t�H���g�p�X
	int hImgButton_[STATE::MAX];						//�{�^���n���h��
	int grid_;									//�{�^��3x3�����t�@�C����1x1�T�C�Y
	Transform buttonDivTra[DIV_H::H_MAX][DIV_W::W_MAX];	//3x3�����̊e�ό`���
	void CalcDivImage();								//�v�Z
public:
	void SetButtonImages(int _grid, string path_idle, string path_select = "", string path_push = "", string path_selected = "");

	//�V���h�E�n
private:
	const string DEFAULT_SHADOW_IMG;
	int hImgShadow_;
	bool isDrawShadow;
	int shadowAlpha_;
	XMINT2 shadowPos;
	float shadowScale;
public:
	void SetShadowTransform(int _x, int _y, float _scale = 1.f);
	void SetDrawShadow(bool b);
	void SetShadowImage(string path);
	



protected:
	//�������ǉ����̏���
	virtual void Init() {}
	//�摜�����N �{�^���摜��ς������ꍇ����p�����ăI�[�o�[���C�h����
	virtual std::string LinkImageFile(STATE state);
	//�{�^���A�j���[�V�����n
	virtual void DrawIdle();
	virtual void DrawSelect();
	virtual void DrawPush();
	virtual void DrawSelected();
private:
	//�eUpdate�֐�
	void UpdateIdle();
	void UpdateSelect();
	void UpdatePush();
	void UpdateSelected();
	//�{�^���̕`��͈͓��Ƀ}�E�X�J�[�\�������邩
	bool IsEntered();
	//�l���͈͓���
	bool Between(float value, float min, float max);
	//�}�E�X��1px�ł���������
	bool IsMovedMouse();
public:
	std::string GetDebugStr(int i);
};

/*
�T�C�Y�͉�ʂɑ΂���g�嗦�w��(=scale_) �f�t�H���g��1��菬�������邱�Ƃŉ����ݒ肵�Ȃ������ꍇ�Ƀ{�^���ŉ�ʂ����ߐs������邱�Ƃ�h��
*/