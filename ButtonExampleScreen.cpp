#include "ButtonExampleScreen.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

#include "SystemConfig.h"
#include "ButtonEx.h"
#include "Frame.h"

//�R���X�g���N�^
ButtonExampleScreen::ButtonExampleScreen(GameObject* parent) :
	Screen(parent, "ButtonExampleScreen"),
	pFrame(nullptr),
	framePosY(-55),
	backBtn(nullptr),
	unselected(true)
{
	std::fill_n(hPict_, PIC_MAX, -1);
}

//�f�X�g���N�^
ButtonExampleScreen::~ButtonExampleScreen()
{
}

//������
void ButtonExampleScreen::Initialize()
{
	//�摜
	hPict_[PIC_BACKGROUND] = Image::Load("Screen/black.png");
	hPict_[PIC_DESCRIPTION] = Image::Load("Screen/descr2.png");
	Image::SetAlpha(hPict_[PIC_BACKGROUND], 128);

	//���ǂ�{�^��
	backBtn = Instantiate<ButtonEx>(this);
	backBtn->SetButtonImages(32, "btnDefIdle32.png", "btnDefSelect32.png", "btnDefPush32.png", "btnDefSelected32.png");
	backBtn->SetShadowImage("btnDefShadow32.png");
	backBtn->SetText("BACK");
	backBtn->SetPosition(0, 280);
	backBtn->EnDrawShadow(true);
	backBtn->SetActionHandle(0);
	backBtn->SetSize(0.2f, 0.15f);
	backBtn->SetSelectedAudio(AudioManager::SE_CANCEL);
	backBtn->EnDecideKey(true);

	//�t���[��
	pFrame = Instantiate<Frame>(this);
	pFrame->ChangeMode(Frame::MODE::AUTO_ASPECT, 0.8f, 0.75f, 0.0f, framePosY);

}

//�X�V
void ButtonExampleScreen::Update()
{
	//Esc�ł��߂�
	if (Input::IsKeyDown(SystemConfig::GetKey(SystemConfig::KEY_ESC))) {
		ButtonAct(0);

	}

	//�S�Ė��I���̂Ƃ��̏���
	if (!unselected && backBtn->GetState() != ButtonEx::STATE::IDLE) {
		unselected = false;
	}
	if (unselected) {
		if (
			Input::IsKeyDown(SystemConfig::GetKey(SystemConfig::KEY::KEY_LEFT)) ||
			Input::IsKeyDown(SystemConfig::GetKey(SystemConfig::KEY::KEY_UP)) ||
			Input::IsKeyDown(SystemConfig::GetKey(SystemConfig::KEY::KEY_RIGHT)) ||
			Input::IsKeyDown(SystemConfig::GetKey(SystemConfig::KEY::KEY_DOWN))
			) {
			backBtn->ChangeState(ButtonEx::STATE::SELECT);
		}
	}
}

//�`��
void ButtonExampleScreen::Draw()
{
	Transform creditTra;
	creditTra.position_.y = framePosY;
	Transform frameTra;

	for (PIC p = static_cast<PIC>(0); p < PIC_MAX; p = static_cast<PIC>(p + 1)) {
		switch (p)
		{
		case ButtonExampleScreen::PIC_BACKGROUND:
			Image::SetTransform(hPict_[p], transform_);
			Image::Draw(hPict_[p]);

			//�t���[���`��
			pFrame->DrawFrame();
			break;
		case ButtonExampleScreen::PIC_DESCRIPTION:
			Image::SetTransform(hPict_[p], creditTra);
			Image::Draw(hPict_[p]);
			break;
		}
	}
}

//�J��
void ButtonExampleScreen::Release()
{
}

void ButtonExampleScreen::ButtonAct(int hAct)
{
	if (hAct == 0) {
		Prev();
	}
}
