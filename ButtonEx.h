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

public:
	enum DIR {
		DIR_DOWN,
		DIR_UP,
		DIR_LEFT,
		DIR_RIGHT,
		DIR_MAX,
	};
private:
	ButtonEx* nextBtn[DIR::DIR_MAX];
public:
	void SetNextKey(DIR dir, ButtonEx* _pBtn);
	
	bool isSelecting_;
public:
	enum MODE {
		PUSH_ONLY,          //�������A���ڍs 
		PUSH_UP,            //�������痣�����Ƃ��Ɉڍs
		PUSH_ONLY_SELECT,   //�������A���ڍs �\���L�[��}�E�X�ړ��őI�����ړ����� ���ŏ����炢��Ă������� �ǂ���nullptr�Ȃ�쓮���Ȃ���
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
	void DrawDivImage(STATE _state);
public:
	void SetButtonImages(int _grid, string path_idle, string path_select = "", string path_push = "", string path_selected = "");
private:
	void SetScale(XMFLOAT3 scale) { }
	void SetScale(float x, float y, float z = 1.0f) { }
	void SetScale(float all) {}
	void SetScale(float all, float oX, float oY, float oZ) {}
public:
	void SetSize(float x, float y);

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
	void EnDrawShadow(bool b);
	void SetShadowImage(string path);
	void DrawDivShadow();
	



protected:
	//�������ǉ����̏���
	virtual void Init() {}
	//�{�^���A�j���[�V�����n���g������ۂɏ㏑������
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

	//�}�E�X��1px�ł���������
	bool IsMovedMouse();
public:
	std::string GetDebugStr(int i);
};

/*
�T�C�Y�͉�ʂɑ΂���g�嗦�w��(=scale_) �f�t�H���g��1��菬�������邱�Ƃŉ����ݒ肵�Ȃ������ꍇ�Ƀ{�^���ŉ�ʂ����ߐs������邱�Ƃ�h��
�{�^����Assets\Image\Button\���Q�Ƃ��܂�
*/