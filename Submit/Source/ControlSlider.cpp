#include "ControlSlider.h"
#include "./Engine/Input.h"
#include "./Engine/Image.h"
#include "SystemConfig.h"

//�R���X�g���N�^
ControlSlider::ControlSlider(GameObject* parent)
    :GameObject(parent, "ControlSlider"),
	trackWidth(420),
	trackHeight(50),
	thumbSize(75)
{
}

//�f�X�g���N�^
ControlSlider::~ControlSlider()
{
}

//������
void ControlSlider::Initialize()
{
	//�摜�Ǎ�
	hImg_[SLIDER_THUMB] = Image::Load("Slider\\sliderThumb.png");
	hImg_[SLIDER_FORE] = Image::Load("Slider\\sliderFore.png");
	hImg_[SLIDER_BK] = Image::Load("Slider\\sliderBk.png");

	//�g���b�N�̕�
	//float trackWRatio = defScrX / trackWidth;
	//float trackHRatio = defScrY / trackHeight;
	//float trackThumbRatio = defScrX / thumbSize;
	trackWRatio = (float)(trackWidth)/( float)(defScrX);
	trackHRatio = (float)(trackHeight) / (float)(defScrY);
	float trackThumbWRatio = (float)(thumbSize) / (float)(defScrX);
	float trackThumbHRatio = (float)(thumbSize) / (float)(defScrY);
	//XMFLOAT3 imgSize[IMAGE::MAX];	//�摜�T�C�Y
	imgSize[SLIDER_THUMB] = Image::GetSize(hImg_[SLIDER_THUMB]);
	imgSize[SLIDER_FORE] = Image::GetSize(hImg_[SLIDER_FORE]);
	imgSize[SLIDER_BK] = Image::GetSize(hImg_[SLIDER_BK]);
	//int imgBackW = Image::GetWidth(hImg_[SLIDER_BK]);
	//int imgBackH = Image::GetHeight(hImg_[SLIDER_BK]);
	//Transform traImage[IMAGE::MAX];	//�e�ό`���
	for (int i = 0; i < IMAGE::MAX; i++){
		float a;
		//FORE��BK��
		//�E�B���h�E�T�C�Y*�g���b�N�g�嗦(�f�t�H���g�X�N���[���T�C�Y/�g���b�N�T�C�Y) / �摜�T�C�Y
		switch (i) {
		case IMAGE::SLIDER_FORE:
			//fore,bk�̉����̔������}�C�i�X��center�ɂ���
			a = (float)SystemConfig::windowWidth * (float)trackWRatio / 2.0f;
			bool b;
			traImage[i].SetCenter(0, 0, 0);
			traImage[i].position_.x = a;

			traImage[i].IsCalcCenterPoint(true);
			traImage[i].SetReSize((float)SystemConfig::windowWidth * trackWRatio / (float)imgSize[i].x,
				(float)SystemConfig::windowHeight * trackHRatio / (float)imgSize[i].x,1
				);
			break;
		case IMAGE::SLIDER_BK:
			traImage[i].scale_.x = (float)SystemConfig::windowWidth * trackWRatio / (float)imgSize[i].x;
			traImage[i].scale_.y = (float)SystemConfig::windowHeight * trackHRatio / (float)imgSize[i].x;
			break;
		case IMAGE::SLIDER_THUMB:
			traImage[i].scale_.x = (float)SystemConfig::windowWidth * trackThumbWRatio / (float)imgSize[i].x;
			traImage[i].scale_.y = (float)SystemConfig::windowHeight * trackThumbHRatio / (float)imgSize[i].x;
			break;
		}
		
		Image::SetTransform(hImg_[i], traImage[i]);
	}
	
	//traImageBack.scale_.x = (float)SystemConfig::windowWidth * trackWRatio / (float)imgBackW;
	//traImageBack.scale_.y = (float)SystemConfig::windowHeight * trackHRatio / (float)imgBackH;
	
	/*
	FORE��BK�͓����T�C�Y����Ȃ��Ƃ����Ȃ��H�Ⴄ�T�C�Y�̏ꍇ���T�C�Y���邩�������~�߂�K�v������
	*/
}

//�X�V
void ControlSlider::Update()
{
	if (IsEntered()) {
		//�}�E�X�݂̂ɂ��܂���?�͂�
		//������Ă�Ƃ���
		if (Input::IsMouseButtonDown(0)) {

		}
	}

	if (Input::IsKey(DIK_1)) {
		traImage[SLIDER_FORE].position_.x++;
	}
	if (Input::IsKey(DIK_2)) {
		traImage[SLIDER_FORE].position_.x--;
	}
	if (Input::IsKey(DIK_3)) {
		traImage[SLIDER_FORE].position_.y++;
	}
	if (Input::IsKey(DIK_4)) {
		traImage[SLIDER_FORE].position_.y--;
	}
	if (Input::IsKey(DIK_5)) {
		traImage[SLIDER_FORE].scale_.x++;
	}
	if (Input::IsKey(DIK_6)) {
		traImage[SLIDER_FORE].scale_.x--;
	}
	if (Input::IsKey(DIK_7)) {
		rc += 0.5f;
		Image::SetRect(hImg_[SLIDER_FORE], 0, 0, rc, 20);
		traImage[SLIDER_BK].scale_.y++;
	}
	if (Input::IsKey(DIK_8)) {
		rc -= 0.5f;
		Image::SetRect(hImg_[SLIDER_FORE], 0, 0, rc, 20);
		traImage[SLIDER_BK].scale_.y--;
	}
}

//�`��
void ControlSlider::Draw()
{
Image::SetTransform(hImg_[SLIDER_FORE], traImage[SLIDER_FORE]);
	//float trackWRatio = (float)(trackWidth) / (float)(defScrX);
	//float trackHRatio = (float)(trackHeight) / (float)(defScrY);
	//Transform frameTra;
	//frameTra.SetCenter((float)SystemConfig::windowWidth * (float)trackWRatio / 2.0f,0,0);   //���S�_���ړ����č��W���߂Ă�̂Œ��� ��̓I�ɂ͕����t�]����(���S�_�𓮂����ƕK�R�I�ɋt���Ɉړ����邽��)
	//frameTra.IsCalcCenterPoint(true);
	////int edge = 64;

	//using namespace SystemConfig;
	////frame�\�z
	//frameTra.position_.y = 0;
	//frameTra.scale_.y = (float)(windowHeight - (imgSize[SLIDER_FORE].y + imgSize[SLIDER_FORE].y)) / (float)imgSize[SLIDER_FORE].y;
	//frameTra.position_.x = (float)(-windowWidth + (imgSize[SLIDER_FORE].x)) / 2.0f;
	//frameTra.scale_.x = 1;
	//Transform tmp = frameTra;
	//tmp.SetReSize((float)SystemConfig::windowWidth * trackWRatio / (float)imgSize[SLIDER_FORE].x, (float)SystemConfig::windowHeight * trackHRatio / (float)imgSize[SLIDER_FORE].x,1);
	////Image::SetTransform(hImg_[SLIDER_FORE], tmp);
	//Image::Draw(hImg_[SLIDER_FORE]);


	//for (int& img : hImg_) {
	//	Image::Draw(img);
	//}
	Image::Draw(hImg_[SLIDER_BK]);
	Image::Draw(hImg_[SLIDER_FORE]);
	Image::Draw(hImg_[SLIDER_THUMB]);
}

//�J��
void ControlSlider::Release()
{
}

std::string ControlSlider::GetDebugStr(int debugNum)
{
	switch (debugNum)
	{
	case 1: return "SLIDER_LU:" + std::to_string(sliderRangeLU.x) + "," + std::to_string(sliderRangeLU.y);
	case 2: return "SLIDER_RB:" + std::to_string(sliderRangeRB.x) + "," + std::to_string(sliderRangeRB.y);
	case 3: if (IsEntered())return "MOUSE ENTERED"; else return "MOUSE NOT ENTERED";
	}
	return "";
}

//���ꗬ�p���ăX�N���[���T�C�Y�ς�������̃o�O�𒼂����I
bool ControlSlider::IsEntered()
{

	sliderRangeLU = {
		-(Half(SystemConfig::windowWidth * trackWRatio)),
		-(Half(SystemConfig::windowHeight * trackHRatio)),
	};
	sliderRangeRB = {
		(Half(SystemConfig::windowWidth * (float)trackWRatio)),
		(Half(SystemConfig::windowHeight * trackHRatio)),
	};
	if (Between(Input::GetMousePosition(true).x, sliderRangeLU.x, sliderRangeRB.x) && Between(Input::GetMousePosition(true).y, sliderRangeLU.y, sliderRangeRB.y)) {
		return true;
	}
	return false;
}