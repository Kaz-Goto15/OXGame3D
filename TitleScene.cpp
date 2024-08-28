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
	progress(DEFAULT_PROGRESS), maxProgress(60),
	btnFadeEaseNo(23),
	//�����x
	ALPHA_ZERO(0), ALPHA_MAX(255),
	//�^�C�g�����S
	TITLE_PROGRESS_POINT({60,120}),
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
	AudioManager::Load(AudioManager::AUDIO_SOURCE::BGM_LOBBY);
	for (int i = 0; i < Img::PIC_MAX; i++) {
		hPict_[i] = Image::Load(TitleImgFileName(static_cast<Img>(i)));
	}

	txtPressStart = new Text();
	txtPressStart->Initialize(GAKUMARU_16px);

	InitButton(S_SEL_START,	"START",	{ (int)(-BUTTON_X_SPACE * 1.5),BUTTON_Y_FADE.y });
	InitButton(S_SEL_CREDIT,"CREDIT",	{ (int)(-BUTTON_X_SPACE *0.5)	,BUTTON_Y_FADE.x });
	InitButton(S_SEL_OPTION,"OPTION",	{ (int)(BUTTON_X_SPACE *0.5)	,BUTTON_Y_FADE.x });
	InitButton(S_SEL_EXIT,	"EXIT",		{ (int)(BUTTON_X_SPACE *1.5)	,BUTTON_Y_FADE.x });

	//debugText = Instantiate<DebugText>(this);
	//for (int i = 0; i < 20; i++) debugText->AddStrPtr(&debugStr[i]);

}
void TitleScene::Update() {
	if (state_ == S_STANDBY) {
		//����L�[�܂��͍��N���b�N
		if(Input::IsKeyDown(DIK_SPACE) || Input::IsMouseButtonDown(0)) {
			AudioManager::Play(AudioManager::AUDIO_SOURCE::BGM_LOBBY);
			//�{�^���`��(���d)
			for (int i = 0; i < S_SEL_MAX; i++) {
				btn[i]->Enter();
				btn[i]->Visible();
			}

			state_ = S_MAIN;
			progress = 0;
			Image::SetAlpha(hPict_[PIC_TITLE], ALPHA_MAX);
			Image::SetAlpha(hPict_[PIC_BACKGROUND], ALPHA_MAX);
		}
	}
}
void TitleScene::Draw() {
	switch (state_)
	{
	case TitleScene::S_STANDBY:
		//�i����
		if(progress < TITLE_PROGRESS_POINT.y)progress++;
		if (Between(progress, DEFAULT_PROGRESS, TITLE_PROGRESS_POINT.x)) {
			//������ʃN���X�ŏ�ɍ���킹������ɂ�����
			Image::SetAlpha(hPict_[PIC_TITLE],
				Easing::Calc(1, progress, TITLE_PROGRESS_POINT.x, ALPHA_ZERO, ALPHA_MAX)
			);

			Image::Draw(hPict_[PIC_TITLE]);
			txtPressStart->SetAlpha(Easing::Calc(1, progress, TITLE_PROGRESS_POINT.x, ALPHA_ZERO, ALPHA_MAX));
			txtPressStart->Draw(TEXT_POSITION.x, TEXT_POSITION.y, FIRST_TEXT_DESCR);
			break;
		}
		else if (Between(progress, TITLE_PROGRESS_POINT.x, TITLE_PROGRESS_POINT.y)) {
			//Image::SetAlpha(hPict_[PIC_BACKGROUND],
			//	Easing::Calc(1, progress, TITLE_PROGRESS_POINT[1], ALPHA_ZERO, ALPHA_MAX)
			//);
			Image::SetAlpha(hPict_[PIC_TITLE], ALPHA_MAX);
			txtPressStart->SetAlpha(ALPHA_MAX);
			//Image::Draw(hPict_[PIC_BACKGROUND]);
			Image::Draw(hPict_[PIC_TITLE]);
			txtPressStart->Draw(TEXT_POSITION.x, TEXT_POSITION.y, FIRST_TEXT_DESCR);
			break;
		}
		else {
			//state_ = S_MAIN;
			//progress = 0;
		}
		break;
	case TitleScene::S_MAIN:
		if (progress < maxProgress) {
			progress++;
			//�w�i
			Image::Draw(hPict_[PIC_BACKGROUND]);
			//�^�C�g��
			Transform tra;
			tra.position_.y = Easing::Calc(btnFadeEaseNo, progress, maxProgress, TITLE_Y_FADE.x, TITLE_Y_FADE.y);
			Image::SetTransform(hPict_[PIC_TITLE], tra);
			Image::Draw(hPict_[PIC_TITLE]);
			//�{�^���`��(���d)
			for (int i = 0; i < S_SEL_MAX; i++) {
				//�����Ƃ����v�Z���@�łł��邩��
				XMFLOAT3 pos = btn[i]->GetPosition();
				pos.y = Easing::Calc(btnFadeEaseNo, progress, maxProgress, BUTTON_Y_FADE.x, BUTTON_Y_FADE.y);
				btn[i]->SetPosition(pos);
			}
			//�� ������ʃN���X�Ŏ���������(�`�揇�̊֌W�Ń{�^������ɂ�������)
			Image::SetAlpha(hPict_[PIC_WHITE],
				Easing::Calc(1, progress, maxProgress, ALPHA_MAX, ALPHA_ZERO)
			);
			Image::Draw(hPict_[PIC_WHITE]);

			break;
		}
		Image::Draw(hPict_[PIC_BACKGROUND]);
		Image::Draw(hPict_[PIC_TITLE]);
		break;
	case TitleScene::S_SELECT:
		Image::Draw(hPict_[PIC_BACKGROUND]);
		Image::Draw(hPict_[PIC_TITLE]);
		break;
	}

	XMFLOAT3 mousePos = Input::GetMousePosition();
	//debugStr[0] = "imgSize: " + std::to_string(Image::GetWidth(hImg_)) + ", " + std::to_string(Image::GetHeight(hImg_));
	//debugStr[1] = "imgScale: " + std::to_string(nullScale_.x) + ", " + std::to_string(nullScale_.y);
	//debugStr[2] = "mousePos: " + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y);
	//debugStr[3] = btn[0]->GetDebugStr(6);

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


�{�^���Ƃ��Ēǉ����邩�H
12
34�@�Œǉ������Ƃ�

1�̂Ƃ� �㉺���E 0+2 0+1
2�̂Ƃ� �㉺���E 0+2-1 0
3�̂Ƃ� �㉺���E-2 0 0+1
4�̂Ƃ� �㉺���E-2 0-1 0

12
(3)4�@�Œǉ������Ƃ�

1�̂Ƃ� �㉺���E 0+3 0+1
2�̂Ƃ� �㉺���E 0+2-1 0
3�ɂ������̓��� --+3-3--
4�̂Ƃ� �㉺���E-2 0-3 0

1�̂Ƃ� �㉺���E 0+2 0+1
2�̂Ƃ� �㉺���E 0+2-1 0
3�ɂ������̓��� --+1-2--
4�̂Ƃ� �㉺���E-2 0-1 0

������+2 �����-2 3�ȏ�̂Ƃ������͓���Ȃ� 2�ȉ��̂Ƃ������Ȃ�
�E+1
fadein �C�[�W���O�ԍ��ɉ����ē����x�ύX�@0��100��idle SPACE:end
idle �w�莞�ԑҋ@�@�w�莞�Ԓ��߂�fadeout�� SPACE:end
fadeout �C�[�W���O�ԍ��ɉ����ē����x�ύX�@100��0��end�� SPACE:end
end �\��������̂������fadein �Ȃ���΃^�C�g���V�[����
*/