#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"
#include "AudioManager.h"

//�{�^�����Ǘ�����N���X
class ButtonOld : public GameObject
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
    int hImg_[MAX];
    Text::HORIZONAL_ALIGNMENT hAl;
    Text::VERTICAL_ALIGNMENT vAl;
    int actHandle_;
    //XMINT4 clip = { 0,0,128,128 };
    bool nextIdle;
    STATE ActTiming;
    AudioManager::AUDIO_SOURCE sound;

    XMFLOAT2 rangeLU, rangeRB;
public:
    STATE state;

    ButtonOld(GameObject* parent, const std::string& name= "ButtonOld");    //�R���X�g���N�^
    ~ButtonOld();                     //�f�X�g���N�^
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