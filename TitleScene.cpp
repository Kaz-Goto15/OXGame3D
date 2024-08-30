#include "TitleScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Easing.h"
#include "Engine/Text.h"

#include "ButtonGP.h"
//#include "DebugText.h"
#include "CreditScreen.h"
#include "OptionScreen.h"

#include "AudioManager.h"

using std::to_string;
using std::string;

std::string TitleScene::State2Str(SELECT_STATE state)
{
	switch (state)
	{
	case TitleScene::S_SEL_START:	return "START";
	case TitleScene::S_SEL_CREDIT:	return "CREDIT";
	case TitleScene::S_SEL_OPTION:	return "OPTION";
	case TitleScene::S_SEL_EXIT:	return "EXIT";
	}
	return "NULL";
}

//�t�@�C�����ƕR�Â�
std::string TitleScene::TitleImgFileName(Img E_IMG)
{
	string dir = "Title\\";
	switch (E_IMG)
	{
	case Img::PIC_BACKGROUND:		return dir + "bg2.png";
	case Img::PIC_TITLE:			return dir + "titleox.png";
	case Img::PIC_WHITE:			return dir + "white.png";
	}
	return "null.png";
}

TitleScene::TitleScene(GameObject* parent) :
	GameObject(parent, "TitleScene"),
	state_(S_STANDBY),
	selectState_(S_SEL_START),
	//�t�F�[�h
	DEFAULT_PROGRESS(0),
	progress(DEFAULT_PROGRESS), MOVE_FRAMES(60),
	OBJ_FADE_EASE_NUMBER(23),
	//�����x
	ALPHA_ZERO(0), ALPHA_MAX(255),
	//�^�C�g�����S
	TITLE_PROGRESS_POINT(60),
	TITLE_Y_FADE({0,-60}),
	//�{�^��
	BUTTON_X_SPACE(270),
	BUTTON_Y_FADE({ 400,250 }),
	//�e�L�X�g
	txtPressStart(nullptr),
	TEXT_POSITION({0,240}),
	FIRST_TEXT_DESCR("Press 'Space' to continue"),

	//�J�ڌn�I�u�W�F�N�g
	pSceneManager(nullptr),
	pScreen(nullptr)
{
	std::fill(hPict_, hPict_ + PIC_MAX, -1);
	std::fill(btn, btn + S_SEL_MAX, nullptr);
}

void TitleScene::Initialize() {
	//BGM���[�h
	AudioManager::Load(AudioManager::AUDIO_SOURCE::BGM_LOBBY);

	//�摜���[�h
	for (int i = 0; i < Img::PIC_MAX; i++) {
		hPict_[i] = Image::Load(TitleImgFileName(static_cast<Img>(i)));
	}

	//�X�^���o�C���̃e�L�X�g
	txtPressStart = new Text();
	txtPressStart->Initialize(GAKUMARU_16px);

	//�{�^�����̏�����
	//��3������Y�͕ύX����邽�߂Ȃ�ł�����
	int btnX = -BUTTON_X_SPACE * Half((int)S_SEL_MAX);	//�{�^����/2�ň�ԍ��̃{�^���̍��W��ݒ�
	if (IsEven(S_SEL_MAX))btnX += Half(BUTTON_X_SPACE);	//�����̏ꍇ�Ax=0�Ƀ{�^�������Ȃ����ߗ]���̔��������炷
	for (SELECT_STATE state = static_cast<SELECT_STATE>(0); state < S_SEL_MAX; state = static_cast<SELECT_STATE>(state + 1)) {
		InitButton(state, State2Str(state), { btnX, 0 });
			btnX += BUTTON_X_SPACE;
	}
}

void TitleScene::Update() {

	//�X�^���o�C���̂ݍX�V ����ȊO�̓{�^�������ŏ���
	if (In(state_, { S_STANDBY,S_STANDBY_WAIT })) {
		//����L�[�܂��͍��N���b�N
		if(Input::IsKeyDown(DIK_SPACE) || Input::IsMouseButtonDown(0)) {
			//BGM�Đ�
			AudioManager::Play(AudioManager::AUDIO_SOURCE::BGM_LOBBY);
			//�{�^���̍X�V�J�n�A�`��J�n
			for (int i = 0; i < S_SEL_MAX; i++) {
				btn[i]->Enter();
				btn[i]->Visible();
			}

			state_ = S_MAIN;				//�X�e�[�g��MAIN�ɂ���
			progress = DEFAULT_PROGRESS;	//�i����0�ɂ��ǂ�

			//�^�C�g���Ɣw�i�����S�\��
			Image::SetAlpha(hPict_[PIC_TITLE], ALPHA_MAX);
			Image::SetAlpha(hPict_[PIC_BACKGROUND], ALPHA_MAX);
		}
	}
}
void TitleScene::Draw() {
	switch (state_)
	{
	case TitleScene::S_STANDBY:
		//�i�����^�C�g���L�[2�ڂ�菭�Ȃ�������1plus
		if(progress < TITLE_PROGRESS_POINT)progress++;
		//�^�C�g���\���܂�
		if (Between(progress, DEFAULT_PROGRESS, TITLE_PROGRESS_POINT)) {
			//�����x�����X�ɂ�����(�s���ߗ����グ��)
			int alpha = Easing::Calc(1, progress, TITLE_PROGRESS_POINT, ALPHA_ZERO, ALPHA_MAX);

			Image::SetAlpha(hPict_[PIC_TITLE],alpha);
			txtPressStart->SetAlpha(alpha);
		}
		//�s���߂ɂȂ�����WAIT�X�e�[�g�Ɉڍs���ăA�N�V������ҋ@����
		else {
			state_ = S_STANDBY_WAIT;
			//�^�C�g���ƕ�����255(�����x0%)��z�肵�Ă��邪�����ꉽ���̔��q��254(�����x0.39%)�ɂȂ��Ă���߂����̂ŔO�̂��ߕs���߂ɂ���
			Image::SetAlpha(hPict_[PIC_TITLE], ALPHA_MAX);
			txtPressStart->SetAlpha(ALPHA_MAX);
		}
		//�`�揈����STANDBY��WAIT�͓����Ȃ̂�break�������̂܂܎󂯗���
		[[fallthrough]];
	case TitleScene::S_STANDBY_WAIT:

		//�`��
		Image::Draw(hPict_[PIC_TITLE]);
		txtPressStart->Draw(TEXT_POSITION.x, TEXT_POSITION.y, FIRST_TEXT_DESCR);
		break;

	case TitleScene::S_MAIN:
		if (progress < MOVE_FRAMES) {
			progress++;
			//�w�i
			Image::Draw(hPict_[PIC_BACKGROUND]);

			//�^�C�g���ړ�
			Transform tra;
			tra.position_.y = Easing::Calc(OBJ_FADE_EASE_NUMBER, progress, MOVE_FRAMES, TITLE_Y_FADE.x, TITLE_Y_FADE.y);
			Image::SetTransform(hPict_[PIC_TITLE], tra);
			Image::Draw(hPict_[PIC_TITLE]);

			//�{�^���ړ�
			for (int i = 0; i < S_SEL_MAX; i++) {
				//�����Ƃ����v�Z���@�łł��邩��
				XMFLOAT3 pos = btn[i]->GetPosition();
				pos.y = Easing::Calc(OBJ_FADE_EASE_NUMBER, progress, MOVE_FRAMES, BUTTON_Y_FADE.x, BUTTON_Y_FADE.y);
				btn[i]->SetPosition(pos);
			}

			//��
			Image::SetAlpha(hPict_[PIC_WHITE],
				Easing::Calc(1, progress, MOVE_FRAMES, ALPHA_MAX, ALPHA_ZERO)
			);
			Image::Draw(hPict_[PIC_WHITE]);

			break;
		}
		Image::Draw(hPict_[PIC_BACKGROUND]);
		Image::Draw(hPict_[PIC_TITLE]);
		break;
	}

	XMFLOAT3 mousePos = Input::GetMousePosition();
}
void TitleScene::Release() {}

void TitleScene::ButtonAct(int hAct)
{
	SELECT_STATE ss = static_cast<SELECT_STATE>(hAct);
	switch (ss)
	{
	case TitleScene::S_SEL_START:
		pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
		break;
	case TitleScene::S_SEL_CREDIT:
		pScreen = Instantiate<CreditScreen>(GetParent());
		pScreen->SetPrevScene(this);
		pScreen->Run();
		break;
	case TitleScene::S_SEL_OPTION:

		pScreen = Instantiate<OptionScreen>(GetParent());
		pScreen->SetPrevScene(this);
		pScreen->Run();

		break;
	case TitleScene::S_SEL_EXIT:
		exit(0);
	default:
		break;
	}
}

void TitleScene::InitButton(SELECT_STATE ss, std::string text, XMINT2 pos)
{
	btn[ss] = Instantiate <ButtonGP>(this);
	btn[ss]->SetText(text);
	btn[ss]->SetAction(ss);
	btn[ss]->SetPosition(pos.x, pos.y, 0);
	btn[ss]->Leave();
	btn[ss]->Invisible();
}

/*
BUTTON STATE
IDLE:
 �I���O�̃A�j���[�V����
 �J�[�\������������SELECT�Ɉړ�

 �{�^���őI�΂ꂽ�Ƃ�SELECT�Ɉړ�

SELECT:
 �I�𒆂̃A�j���[�V����
 �}�E�X�{�^���������ꂽ��PUSH�Ɉړ�
 �J�[�\�����O�ꂽ��IDLE�Ɉړ�
 �{�^���������ꂽ��SELECTED�Ɉړ�(keydown up�ł͂Ȃ�)
 �{�^�������ɍs�����Ƃ�IDLE�Ɉړ�

PUSH:
 �������A�j���[�V����

 �J�[�\�����O�ꂽ��IDLE�Ɉړ�
 �}�E�X�{�^���������ꂽ�Ƃ��ASELECTED�Ɉړ�

SELECTED:
 �I�����ꂽ�A�j���[�V����
 �������s��
 �������I�������IDLE�Ɉړ�

 �}�E�X�͎����ŏ����ł���
 �{�^����������



�J�[�\�����ڂ����ɗ������̏����Fbtn_select
�{�^����ŉ����A���������Ă��鎞�̏����Fbtn_push
�{�^����ŉ����A�������Ƃ��̏����Fbtn_selected
�����ꂽ�Ƃ��E�{�^����ɖ������̏����Fbtn_idle


�I�𒆂�BTN_ENUM

��in�Ń{�^���t�F�[�h�C�� �I���\
 �{�^���F�I���O/�I��/�I�𒆂�������Ă���/�I����̏�����
 �����ꂽ�Ƃ��̏������l����
 �{�^����o�^����Ƃ���Generate(cmd);
 �\���͐e�̂ق���TitleBtn.count()����for��Draw
 �{�^���������ꂽ��e��Run(COMMAND cmd);���Ă�
main
background
select: logo (���t�F�[�h)
start/option/edit/exit
start��screen�ŐV���ɋL�q
option��screen
edit���u���b�N�A�E�g����editscene
exit�����̂܂��exit(0)�ł���

fadein �C�[�W���O�ԍ��ɉ����ē����x�ύX�@0��100��idle SPACE:end
idle �w�莞�ԑҋ@�@�w�莞�Ԓ��߂�fadeout�� SPACE:end
fadeout �C�[�W���O�ԍ��ɉ����ē����x�ύX�@100��0��end�� SPACE:end
end �\��������̂������fadein �Ȃ���΃^�C�g���V�[����
*/