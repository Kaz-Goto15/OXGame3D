#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"
#include "AudioManager.h"

using std::string;
//�{�^�����Ǘ�����N���X
class ButtonEx : public GameObject
{
protected:
	int actHandle_;
	bool nextIdle;	//�X�N���[���`��ȂǂőI���ϕ`��𑱂��邽�߂̃t���O

	XMFLOAT2 rangeLU, rangeRB;
//����n�H
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
	
public:
	enum MODE {
		PUSH_ONLY,          //�������A���ڍs 
		PUSH_UP,            //�������痣�����Ƃ��Ɉڍs
		PUSH_ONLY_SELECT,   //�������A���ڍs �\���L�[��}�E�X�ړ��őI�����ړ����� ���ŏ����炢��Ă������� �ǂ���nullptr�Ȃ�쓮���Ȃ���
		PUSH_UP_SELECT      //�������痣�����Ƃ��Ɉڍs �\���L�[��}�E�X�ړ��őI�����ړ�����
	}mode_;
	

	ButtonEx(GameObject* parent, const std::string& name = "ButtonEx");    //�R���X�g���N�^
	~ButtonEx();                     //�f�X�g���N�^
	void Initialize() override; //������
	void Update() override;     //�X�V
	void Draw() override;       //�`��
	void Release() override;    //���


	//���g(�{�^��)�Ɛe�̑I���X�e�[�g��R�Â���
	void SetAction(int hAct);

	//void SetSound(AudioManager::AUDIO_SOURCE audioSource) { sound = audioSource; }

//�e�L�X�g�ݒ�n
private:
	Text* textObj_;					//�e�L�X�g�I�u�W�F�N�g
	std::string text_;				//�e�L�X�g���e
	Text::HORIZONAL_ALIGNMENT hAl;	//���������̔z�u
	Text::VERTICAL_ALIGNMENT vAl;	//���������̔z�u
public:
	/// <summary>
	/// �{�^�����e�L�X�g�̔z�u�ύX
	/// </summary>
	/// <param name="h">���������̔z�u</param>
	/// <param name="v">���������̔z�u</param>
	void SetTextAlignment(Text::HORIZONAL_ALIGNMENT h, Text::VERTICAL_ALIGNMENT v);

	/// <summary>
	/// �t�H���g�ݒ�
	/// </summary>
	/// <param name="fileName">�t�@�C���p�X Fonts�t�H���_���J�����g�f�B���N�g��</param>
	/// <param name="charWidth">1������</param>
	/// <param name="charHeight">�P��������</param>
	/// <param name="rowLength">���ɉ��������邩</param>
	void SetFont(const char* filePath, const unsigned int charWidth, const unsigned int charHeight, const unsigned int rowLength);

	/// <summary>
	/// �t�H���g�ݒ�
	/// </summary>
	/// <param name="textScr">�t�H���g</param>
	void SetFont(TEXT_SOURCE textScr);

	/// <summary>
	/// �e�L�X�g�̓��e��ύX
	/// </summary>
	/// <param name="_text">���e</param>
	void SetText(std::string _text);
	


//�X�e�[�g�n
private:
	enum STATE {
		IDLE,
		SELECT,
		PUSH,
		SELECTED,
		MAX
	};
	STATE state;
	bool isChangeState;
	STATE nextState;

private:
	/// <summary>
	/// ����X�V���A�X�V���s������ɏ�Ԃ�ω������܂��B
	/// </summary>
	/// <param name="state">����X�e�[�g</param>
	void ChangeState(STATE state);


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
	const string DEFAULT_DIRECTORY;
	const string DEFAULT_BUTTON_IMG[STATE::MAX];		//�f�t�H���g�p�X
	int hImgButton_[STATE::MAX];						//�{�^���n���h��
	int grid_;									//�{�^��3x3�����t�@�C����1x1�T�C�Y
	Transform buttonDivTra[DIV_H::H_MAX][DIV_W::W_MAX];	//3x3�����̊e�ό`���
	void CalcDivImage();								//�v�Z
	void DrawDivImage(STATE _state);					//�������ꂽ�摜��`�悷��
public:
	/// <summary>
	/// �{�^���Ɏg���摜��ݒ�
	/// �V���h�E���܂߂ē����T�C�Y�łȂ���΂Ȃ�Ȃ�
	/// </summary>
	/// <param name="_grid">3x3������1x1�̐����`�̒���</param>
	/// <param name="path_idle">�A�C�h�����̉摜�p�X</param>
	/// <param name="path_select">�I�����̉摜�p�X</param>
	/// <param name="path_push">�������̉摜�p�X</param>
	/// <param name="path_selected">�I���ςݎ��̉摜�p�X</param>
	void SetButtonImages(int _grid, string path_idle, string path_select = "", string path_push = "", string path_selected = "");

	/// <summary>
	/// �{�^���̃T�C�Y���w��
	/// ��ʑS�̂�1�Ƃ����Ƃ��̃{�^���̃T�C�Y�������Ŏw��
	/// </summary>
	/// <param name="x">x����</param>
	/// <param name="y">y����</param>
	void SetSize(float x, float y);

	void SetPosition(int x, int y);
	//SetScale�𕕈�
	void SetPosition(XMFLOAT3 position) = delete;
	void SetPosition(float x, float y, float z) = delete;
	void SetPosition(int x, int y, int z) = delete;
	void SetScale(XMFLOAT3 scale) = delete;
	void SetScale(float x, float y, float z = 1.0f) = delete;
	void SetScale(float all) = delete;
	void SetScale(float all, float oX, float oY, float oZ) = delete;

//�V���h�E�n
private:
	const string DEFAULT_SHADOW_IMG;
	int hImgShadow_;
	bool isDrawShadow;
	int shadowAlpha_;
	XMINT2 shadowPos;
	float shadowScale;
public:
	void SetShadowTransform(int _x, int _y, float _scale = 1.f, int _alpha = 255);
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