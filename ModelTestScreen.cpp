#include "ModelTestScreen.h"

#include "./Include/nameof.hpp"
#include "Easing.h"
#include "Engine/Input.h"
#include "SystemConfig.h"

#include "./Engine/Image.h"
#include "CubeSelectIndicator.h"
#include "./Engine/Camera.h"
#include <algorithm>

#include "OptionScreen.h"

#include "./Engine/Debug.h"
#include "DebugText.h"
#include "GroupingObject.h"

#include "Engine/Text.h"
#include "ButtonGP.h"

using KEY = SystemConfig::KEY;
using SystemConfig::GetKey;
//�R���X�g���N�^
ModelTestScreen::ModelTestScreen(GameObject* parent) :
	Screen(parent, "ModelTestScreen"),
	hImgBG(-1),
	mode(MODE_SET), prevMode(MODE_SET),
	control(CONTROL_1P), nextTurn(CONTROL_2P),
	OUTER_POINT((PIECES - 1) / 2.0f),
	//�J����
	rotSpdX(0), rotSpdY(0),		//�J������]���x
	isEnded(false),				//�Q�[���I���t���O
	CAM_DISTANCE(10),			//�Ώۂ���J�����܂ł̋���
	TH_ZEROSPEED(0.3f),			//�J�������x��0�ɂ���臒l ���̒l�������Ƒ��x���O�ɂ���
	DC_RATIO(1.2f),				//�J������������
	AT_RATIO(0.5f),				//�J�����ړ��ʂɑ΂����]�����P��
	MAX_CAM_ROTATE_X(89.9999f),	//�J����X��]�̍ō��p�x����
	MIN_CAM_ROTATE_X(-89.9999f),//�J����X��]�̍Œ�p�x����
	LIMIT_CAM_ROTATE_Y(180),	//�J����Y��]�̊p�x����(�I�[�o�[�t���[���)
	DEFAULT_CAM_SPEED(0.0f),		//�J�����̃f�t�H���g���x(0)
	camDirHN(CAM_FRONT),		//�J�����̐�������
	camDirVT(CAM_MIDDLE),		//�J�����̐�������
	//��]���[�h
	ROTATE_EASE(Easing::Ease::OUT_QUART),
	//�f�o�b�O
	debugtext(nullptr),
	testCubeParent(nullptr),
	testCubeChild(nullptr),
	//�Q�[���I������
	maxWinRotProgress(100),
	winRotProgress(0),
	enFreeLook(false),
	winPlayerMsg(nullptr),
	titleButton(nullptr),
	restartButton(nullptr),
	WIN_CAM_EASE(Easing::Ease::OUT_QUART)
{
}

//�f�X�g���N�^
ModelTestScreen::~ModelTestScreen(){}

//������
void ModelTestScreen::Initialize()
{
	//�����̈ꕔ�Őe��ύX����Ƃ��A�`��̏������ς��L���[�u���C���W�P�[�^�@����C���W�P�[�^���L���[�u�ɂȂ�
	//�������̏���������Ȃ��Ȃ��Ă����@���̂��ߓ���ݐ[���O���[�v����I�u�W�F�N�g���쐬
	//�O���[�v����I�u�W�F�N�g�𐶐�
	for (int i = 0; i < GROUP_MAX; i++) {
		groupObject[i] = Instantiate<GroupingObject>(this);
	}

	//�w�i
	hImgBG = Image::Load("Background\\bg_game.png");

	//�L���[�u�{�̂�ۑ�����vector�����T�C�Y
	cube.resize(PIECES, vector<vector<Cube*>>(PIECES, vector<Cube*>(PIECES, nullptr)));

	//�L���[�u����
	for (auto& cx : cube) {
		for (auto& cy : cx) {
			for (auto& cz : cy) {
				cz = Instantiate<Cube>(groupObject[GROUP_BACK]);
			}
		}
	}

	//�L���[�u���W�w�� PIECES�ł���������
	for (int x = 0; x < cube.size();x++) {
		for (int y = 0; y < cube[0].size();y++) {
			for (int z = 0; z < cube[0][0].size();z++) {
				//cube[x][y][z] = Instantiate<Cube>(groupObject[GROUP_BACK]);
				cube[x][y][z]->SetPosition(ConvertPts2Pos(x, y, z));
			}
		}
	}

	//�C���W�P�[�^�[�����E���W�w��
	indicator = Instantiate<CubeSelectIndicator>(groupObject[GROUP_TOP]);
	indicator->SetCubeScale(PIECES);
	indicator->SetDrawPoint(selectData.GetPos(), selectData.surface);
	indicator->SetCubeRotate(selectData.dir);
	indicator->SetRotateColumn(selectData.rotCol);
	indicator->SetDrawMode(indicator->DRAWMODE_SINGLE);

	//�f�o�b�O
	debugtext = Instantiate<DebugText>(this);
	for (int i = 0; i < 20; i++) {
		debugtext->AddStrPtr(&debugStr[i]);
	}
	/*
	for (int x = 0; x < cube.size(); x++) {
		for (int y = 0; y < cube[0].size(); y++) {
			for (int z = 0; z < cube[0][0].size(); z++) {
				if (x == 0) {
					switch (z+3*y)
					{
					case 0:	cube[x][y][z]->SetMark(SURFACE::SURFACE_LEFT, MARK::MARK_1);	break;
					case 1:	cube[x][y][z]->SetMark(SURFACE::SURFACE_LEFT, MARK::MARK_2);	break;
					case 2:	cube[x][y][z]->SetMark(SURFACE::SURFACE_LEFT, MARK::MARK_3);	break;
					case 3:	cube[x][y][z]->SetMark(SURFACE::SURFACE_LEFT, MARK::MARK_4);	break;
					case 4:	cube[x][y][z]->SetMark(SURFACE::SURFACE_LEFT, MARK::MARK_5);	break;
					case 5:	cube[x][y][z]->SetMark(SURFACE::SURFACE_LEFT, MARK::MARK_6);	break;
					case 6:	cube[x][y][z]->SetMark(SURFACE::SURFACE_LEFT, MARK::MARK_7);	break;
					case 7:	cube[x][y][z]->SetMark(SURFACE::SURFACE_LEFT, MARK::MARK_8);	break;
					case 8:	cube[x][y][z]->SetMark(SURFACE::SURFACE_LEFT, MARK::MARK_9);	break;
					}
				}
				if (!(x == y && y == z && x == z)) {}
				if (!(x == 0)) { cube[x][y][z]->Invisible(); }
					//cube[x][y][z]->Invisible();
			}
		}
	}
	*/
}

//�X�V
void ModelTestScreen::Update()
{

	//RotateCamera();     //�J�����̏��� MODE_VIEW�ł̕��������

	//�f�o�b�O�{�^��
	if (Input::IsKeyDown(DIK_P)) {
		Prev();
	}
	if (Input::IsKeyDown(DIK_0)) {
		if (mode == MODE_SET)mode = MODE_ROTATE;
		else if (mode == MODE_ROTATE)mode = MODE_VIEW;
		else if (mode == MODE_VIEW)mode = MODE_SET;
	}
	if (Input::IsKeyDown(DIK_9)) {
		if (control == CONTROL_1P)control = CONTROL_2P;
		else if (control == CONTROL_2P)control = CONTROL_1P;
	}

	//finish�ȂǃX�e�[�g���i�܂Ȃ����葀����󂯕t������ ����finish���ȊO�ł��邽�ߒ��ł�
	if (!finished) {
		if (Input::IsKeyDown(GetKey(KEY::KEY_ESC))) {
			pScreen = Instantiate<OptionScreen>(GetParent());
			pScreen->SetPrevScene(this);
			pScreen->Run();
		}

		RotateCamera();     //�J�����̏��� MODE_VIEW�ł̕��������
	}
	else {
		FinishCamera();     //�J�����̏��� MODE_VIEW�ł̕��������
	}

	//�����Ԃ��A�C�h���łȂ����
	if (!isIdle) {
		MoveSelect(mode);
		//���݂̃��[�h�ŏ���
		switch (mode)
		{
		case ModelTestScreen::MODE_SET:
			//�L�[�֘A�̋L�q�͓���������h�����ߎ�芸�������ׂ�elif�ŏ���
			//�}�[�N�ݒu
			if (Input::IsKeyDown(GetKey(KEY::KEY_ACT))) {
				//�I���ӏ����󔒂̂Ƃ��ɐݒu����
				if (cube[selectData.x][selectData.y][selectData.z]->GetMark(selectData.surface) == Cube::MARK_BLANK) {
					switch (control)
					{
					case ModelTestScreen::CONTROL_1P:   cube[selectData.x][selectData.y][selectData.z]->SetMark(selectData.surface, Cube::MARK::MARK_O);  break;
					case ModelTestScreen::CONTROL_2P:   cube[selectData.x][selectData.y][selectData.z]->SetMark(selectData.surface, Cube::MARK::MARK_X);  break;
					}
					//����
					Judge();
					//�^�[���G���h���� �I������������
					TurnEnd();
				}
				else {
					//�󔒂łȂ��Ƃ��̃A�j���[�V����������΂����ɏ��� �I����\�����������f�������炷�Ȃ�
					//Audio::Play("select_fail.wav");
				}
			}
			else if (Input::IsKeyDown(SystemConfig::GetKey(KEY::KEY_CHANGE))) {	//���[�h�ؑ�
				mode = MODE_ROTATE;
				indicator->SetDrawMode(indicator->DRAWMODE_CIRCLE);			//�C���W�P�[�^�̕`�惂�[�h���~�`�`���
				RotateModeInit();	//���݂̑I���ʒu���玲���w�肵���肷��
			}

			break;
		case ModelTestScreen::MODE_ROTATE:
			//��]���ؑ�
			if (Input::IsKeyDown(GetKey(KEY::KEY_CHANGE_AXIS))) {
				switch (selectData.dir)
				{
				case ROTATE_DIR::ROT_UP:
				case ROTATE_DIR::ROT_DOWN:
					selectData.dir = ROTATE_DIR::ROT_LEFT;
					break;
				case ROTATE_DIR::ROT_LEFT:
				case ROTATE_DIR::ROT_RIGHT:
					selectData.dir = ROTATE_DIR::ROT_CW;
					break;
				case ROTATE_DIR::ROT_CW:
				case ROTATE_DIR::ROT_CCW:
					selectData.dir = ROTATE_DIR::ROT_UP;
					break;
				}
				indicator->SetCubeRotate(selectData.dir);
			}
			//��]
			else if (Input::IsKeyDown(GetKey(KEY::KEY_ACT))) {
				//����̖�����
				isIdle = true;
				//�L���[�u�̈ړ���̍��W���X�V�E��]����I�u�W�F�N�g���w��
				UpdateCubeTransform();
				//��]���t���O�̗L����
				isRotating = true;

				//�ړ������E�ړ�������̃t���O�E��������E�^�[���ڍs�͕ʂ�
			}
			else if (Input::IsKeyDown(GetKey(KEY::KEY_CHANGE))) {	//���[�h�ؑ�
				mode = MODE_SET;
				indicator->SetDrawMode(indicator->DRAWMODE_SINGLE);		//�C���W�P�[�^�̕`�惂�[�h��P��`���
				SetModeInit();
			}
			break;
		case ModelTestScreen::MODE_VIEW:
			if (Input::IsKeyDown(GetKey(KEY::KEY_ACT))) {
				mode = prevMode;		//�r���[���[�h�̑O�̃��[�h�ɖ߂�
				indicator->Visible();	//�C���W�P�[�^���ĕ\��
			}
			break;
		}
	}
	else {
		if (isRotating) {
			rotProgress++;
			//�`��I�����̏��� "�ȏ�"�������̃V�X�e��������ɏ����Ȃ��̉�]���������Ă��邽�߁A
			//�ŏI�t���[���ŉ�]�����ƃV�X�e�������������ɍs����
			if (rotProgress > maxRotProgress) {
				rotProgress = 0;

				CompletedRotate();

				isRotating = false;
				Judge();
				TurnEnd();
			}

			//��]���� ���ݐi���ƍő�i���A�l��������W�ƈړ��O���W�ƈړ�����W
			RotateCube(rotProgress, maxRotProgress, selectData.dir);
		}
	}

	UpdateStr();
}

//�`��
void ModelTestScreen::Draw()
{
	Image::Draw(hImgBG);
}

//�J��
void ModelTestScreen::Release()
{
}

void ModelTestScreen::RotateModeInit()
{
	//�ݒu���[�h�����]���[�h�Ɉڍs���A���݂̃J�����p�x����I���s�Ɖ�]�����w�肷��
	//���_���������ɂȂ�悤������ ����ɂ��ŏ�����LEFT/RIGHT�͕K���w�肳��Ȃ�
	const int SET_MODE_UNIT = 90 / PIECES;
	XMFLOAT3& camRot = camTra.rotate_;
	float absCamY = abs(camRot.y);
	
	bool isDecided = false;
	//�O���SetModeInit��x�A���E��z�Ɠ����̏���
	for (int c = 0; c < PIECES; c++) {
		switch (camDirHN)
		{
		case ModelTestScreen::CAM_FRONT:
			if (camRot.y >= 45 - (c + 1) * SET_MODE_UNIT) { //�O -45~45
				selectData.rotCol = c;
				selectData.dir = ROTATE_DIR::ROT_UP;
				isDecided = true;
			}
			break;
		case ModelTestScreen::CAM_BACK:
			if (camRot.y > 0) {	//+
				if (180 - camRot.y >= 45 - (c + 1) * SET_MODE_UNIT) { //135~180��45~0�ϊ�
					selectData.rotCol = c;
					selectData.dir = ROTATE_DIR::ROT_DOWN;
					isDecided = true;
				}
			}
			else {	//-
				if (-180 - camRot.y >= 45 - (c + 1) * SET_MODE_UNIT) { //-180~-135��0~-45�ϊ�
					selectData.rotCol = c;
					selectData.dir = ROTATE_DIR::ROT_DOWN;
					isDecided = true;
				}
			}
			break;
		case ModelTestScreen::CAM_LEFT:
		case ModelTestScreen::CAM_RIGHT:
			//SetModeInit��z�Ɠ����̏���
			if (absCamY < 45 + (c + 1) * SET_MODE_UNIT) {
				selectData.rotCol = c;

				//��]�����w��
				if (camRot.y > 0) {
					selectData.dir = ROTATE_DIR::ROT_CW;
				}
				else {
					selectData.dir = ROTATE_DIR::ROT_CCW;
				}

				isDecided = true;
			}
			break;
		}
	}

	//�C���W�P�[�^�ɐݒ�
	indicator->SetCubeRotate(selectData.dir);
	indicator->SetRotateColumn(selectData.rotCol);


	debugStr[7] = "rotmodeinit:" + std::to_string(selectData.rotCol) + ","
		+ (std::string)NAMEOF_ENUM(selectData.dir);

}

void ModelTestScreen::SetModeInit()
{
	//��]���[�h����ݒu���[�h�Ɉڍs���A���݂̃J�����p�x����I���}�X���w�肷��
	const int SET_MODE_UNIT = 90 / PIECES;
	XMFLOAT3& camRot = camTra.rotate_;
	float absCamY = abs(camRot.y);

	//y�w��
	switch (camDirVT)
	{
	case ModelTestScreen::CAM_TOP:
		selectData.y = PIECES - 1;
		break;
	case ModelTestScreen::CAM_MIDDLE:
		for (int y = 0; y < PIECES; y++) {
			if (camRot.x < -45 + (y + 1) * SET_MODE_UNIT) {
				selectData.y = y;
				break;
			}
		}
		break;
	case ModelTestScreen::CAM_BOTTOM:
		selectData.y = 0;
		break;
	}

	//z�w��
	switch (camDirHN)
	{
	case ModelTestScreen::CAM_FRONT:
		selectData.z = 0;
		break;
	case ModelTestScreen::CAM_BACK:
		selectData.z = PIECES - 1;
		break;
	case ModelTestScreen::CAM_LEFT:
	case ModelTestScreen::CAM_RIGHT:
		//���݂̉�]�p�x�ɂ��Z�����̑I���ʒu�����߂� �P�[�L�𓙕��ɐ؂�悤�Ȋ���
		for (int z = 0; z < PIECES; z++) {
			if (absCamY < 45 + (z + 1) * SET_MODE_UNIT) {
				selectData.z = z;
				break;
			}
		}
		break;
	}

	//x�w��
	switch (camDirHN)
	{
	case ModelTestScreen::CAM_LEFT:
		selectData.x = 0;
		break;
	case ModelTestScreen::CAM_RIGHT:
		selectData.x = PIECES - 1;
		break;
	case ModelTestScreen::CAM_FRONT:
		for (int x = 0; x < PIECES; x++) {
			//���݂̉�]�p�x�ɂ��X�����̑I���ʒu�����߂�
			if (camRot.y > 45 - (x + 1) * SET_MODE_UNIT) { //�O -45~45
				selectData.x = x;
				break;
			}
		}
		break;
	case ModelTestScreen::CAM_BACK:
		for (int x = 0; x < PIECES; x++) {
			//���݂̉�]�p�x�ɂ��X�����̑I���ʒu�����߂�
			if (camRot.y > 0) {	//+
				if (180 - camRot.y > 45 - (x + 1) * SET_MODE_UNIT) { //135~180��45~0�ϊ�
					selectData.x = x;
					break;
				}
			}
			else {	//-
				if (-180 - camRot.y > 45 - (x + 1) * SET_MODE_UNIT) { //-180~-135��0~-45�ϊ�
					selectData.x = x;
					break;
				}
			}
		}
		break;
	}

	//�I��ʎw��
	switch (camDirVT)
	{
	case ModelTestScreen::CAM_TOP:
		selectData.surface = SURFACE::SURFACE_TOP;	//�J�������㑤�ɂ���
		break;
	case ModelTestScreen::CAM_BOTTOM:
		selectData.surface = SURFACE::SURFACE_BOTTOM;	//�J�����������ɂ���
		break;
	case ModelTestScreen::CAM_MIDDLE:
		switch (camDirHN)
		{
		case ModelTestScreen::CAM_FRONT:
			selectData.surface = SURFACE::SURFACE_FRONT;
			break;
		case ModelTestScreen::CAM_LEFT:
			selectData.surface = SURFACE::SURFACE_LEFT;
			break;
		case ModelTestScreen::CAM_BACK:
			selectData.surface = SURFACE::SURFACE_BACK;
			break;
		case ModelTestScreen::CAM_RIGHT:
			SURFACE::SURFACE_RIGHT;
			break;
		}
		break;
	}

	//�C���W�P�[�^�ɐݒ�
	indicator->SetDrawPoint(selectData.GetPos(), selectData.surface);

	debugStr[6] = "setmodeinit:" + std::to_string(selectData.x) + ","
		+ std::to_string(selectData.y) + ","
		+ std::to_string(selectData.z) + ","
		+ (std::string)NAMEOF_ENUM(selectData.surface);
}

void ModelTestScreen::UpdateStr()
{
	using std::to_string;
	debugStr[0] = "control:" + (std::string)NAMEOF_ENUM(control) + "(Press '9' to change)";
	debugStr[1] = "scrH:" + to_string(SystemConfig::windowHeight) + "scrW:" + to_string(SystemConfig::windowWidth);
	debugStr[2] = "mode:" + (std::string)NAMEOF_ENUM(mode) + "(Press '0' to change)";
	debugStr[3] = "select:(" +
		std::to_string(selectData.x) + "," +
		std::to_string(selectData.y) + "," +
		std::to_string(selectData.z) + ") SUR:" +
		(std::string)NAMEOF_ENUM(selectData.surface) + " col:" +
		std::to_string(selectData.rotCol) + " dir:" +
		(std::string)NAMEOF_ENUM(selectData.dir);
		

	debugStr[4] = "camTra:" + std::to_string(camTra.rotate_.x) + ", " + std::to_string(camTra.rotate_.y);
}


void ModelTestScreen::ButtonAct(int hAct)
{
	switch (hAct)
	{
	case BUTTON_ACTION::BACK_TO_TITLE:
		BackToTitle();
		break;
	case BUTTON_ACTION::RESTART_GAME:
		Restart();
		break;
	}
}

void ModelTestScreen::MoveSelect(MODE mode)
{
	using SURFACE = Cube::SURFACE;
	vector<int> keys = { GetKey(KEY::KEY_UP),GetKey(KEY::KEY_LEFT),GetKey(KEY::KEY_DOWN),GetKey(KEY::KEY_RIGHT) };

	switch (mode)
	{
	case ModelTestScreen::MODE_SET:
		int tmp;
		switch (selectData.surface)
		{
		case SURFACE::SURFACE_TOP:
			switch (camDirHN)
			{
			case ModelTestScreen::CAM_FRONT:
				break;
			case ModelTestScreen::CAM_LEFT:
				//WASD��ASDW��
				tmp = keys.front();
				keys.erase(keys.begin());
				keys.push_back(tmp);
				break;
			case ModelTestScreen::CAM_RIGHT:
				//WASD��DWAS��
				tmp = keys.back();
				keys.pop_back();
				keys.insert(keys.begin(), tmp);
				break;
			case ModelTestScreen::CAM_BACK:
				//WASD��SDWA��
				for (int i = 0; i < 2; i++) {
					tmp = keys.back();
					keys.pop_back();
					keys.insert(keys.begin(), tmp);
				}
				break;
			}

			if (Input::IsKeyDown(keys[0]))  MoveSelectParts(Z, true, SURFACE::SURFACE_BACK);
			if (Input::IsKeyDown(keys[1]))  MoveSelectParts(X, false, SURFACE::SURFACE_LEFT);
			if (Input::IsKeyDown(keys[2]))  MoveSelectParts(Z, false, SURFACE::SURFACE_FRONT);
			if (Input::IsKeyDown(keys[3]))  MoveSelectParts(X, true, SURFACE::SURFACE_RIGHT);
			break;

		case SURFACE::SURFACE_BOTTOM:
			switch (camDirHN)
			{
			case ModelTestScreen::CAM_FRONT:
				break;
			case ModelTestScreen::CAM_LEFT:
				//WASD��DWAS��
				tmp = keys.back();
				keys.pop_back();
				keys.insert(keys.begin(), tmp);
				break;
			case ModelTestScreen::CAM_RIGHT:
				//WASD��ASDW��
				tmp = keys.front();
				keys.erase(keys.begin());
				keys.push_back(tmp);
				break;
			case ModelTestScreen::CAM_BACK:
				//WASD��SDWA��
				for (int i = 0; i < 2; i++) {
					tmp = keys.back();
					keys.pop_back();
					keys.insert(keys.begin(), tmp);
				}
				break;
			}

			if (Input::IsKeyDown(keys[0]))  MoveSelectParts(Z, false, SURFACE::SURFACE_FRONT);
			if (Input::IsKeyDown(keys[1]))  MoveSelectParts(X, false, SURFACE::SURFACE_LEFT);
			if (Input::IsKeyDown(keys[2]))  MoveSelectParts(Z, true, SURFACE::SURFACE_BACK);
			if (Input::IsKeyDown(keys[3]))  MoveSelectParts(X, true, SURFACE::SURFACE_RIGHT);
			break;
		case SURFACE::SURFACE_LEFT:
			if (Input::IsKeyDown(DIK_A))    MoveSelectParts(Z, true, SURFACE::SURFACE_BACK);
			if (Input::IsKeyDown(DIK_D))    MoveSelectParts(Z, false, SURFACE::SURFACE_FRONT);
			if (Input::IsKeyDown(DIK_W))    MoveSelectParts(Y, true, SURFACE::SURFACE_TOP);
			if (Input::IsKeyDown(DIK_S))    MoveSelectParts(Y, false, SURFACE::SURFACE_BOTTOM);
			break;
		case SURFACE::SURFACE_RIGHT:
			if (Input::IsKeyDown(DIK_A))    MoveSelectParts(Z, false, SURFACE::SURFACE_FRONT);
			if (Input::IsKeyDown(DIK_D))    MoveSelectParts(Z, true, SURFACE::SURFACE_BACK);
			if (Input::IsKeyDown(DIK_W))    MoveSelectParts(Y, true, SURFACE::SURFACE_TOP);
			if (Input::IsKeyDown(DIK_S))    MoveSelectParts(Y, false, SURFACE::SURFACE_BOTTOM);
			break;
		case SURFACE::SURFACE_FRONT:
			if (Input::IsKeyDown(DIK_A))    MoveSelectParts(X, false, SURFACE::SURFACE_LEFT);
			if (Input::IsKeyDown(DIK_D))    MoveSelectParts(X, true, SURFACE::SURFACE_RIGHT);
			if (Input::IsKeyDown(DIK_W))    MoveSelectParts(Y, true, SURFACE::SURFACE_TOP);
			if (Input::IsKeyDown(DIK_S))    MoveSelectParts(Y, false, SURFACE::SURFACE_BOTTOM);
			break;
		case SURFACE::SURFACE_BACK:
			if (Input::IsKeyDown(DIK_A))    MoveSelectParts(X, true, SURFACE::SURFACE_RIGHT);
			if (Input::IsKeyDown(DIK_D))    MoveSelectParts(X, false, SURFACE::SURFACE_LEFT);
			if (Input::IsKeyDown(DIK_W))    MoveSelectParts(Y, true, SURFACE::SURFACE_TOP);
			if (Input::IsKeyDown(DIK_S))    MoveSelectParts(Y, false, SURFACE::SURFACE_BOTTOM);
			break;
		}
		break;
	case ModelTestScreen::MODE_ROTATE:
		//��]���[�h���̃L�[�ړ����̏���
		switch (selectData.dir)
		{
		case ROTATE_DIR::ROT_UP:
		case ROTATE_DIR::ROT_DOWN:
			switch (camDirHN)
			{
			case ModelTestScreen::CAM_FRONT:
				if (Input::IsKeyDown(GetKey(KEY::KEY_UP))) {
					MoveSelectChangeDir(ROTATE_DIR::ROT_UP);
				}
				else if (Input::IsKeyDown(GetKey(KEY::KEY_LEFT))) {
					MoveSelectSlideCol(false);
				}
				else if (Input::IsKeyDown(GetKey(KEY::KEY_DOWN))) {
					MoveSelectChangeDir(ROTATE_DIR::ROT_DOWN);
				}
				else if (Input::IsKeyDown(GetKey(KEY::KEY_RIGHT))) {
					MoveSelectSlideCol(true);
				}
				break;
			case ModelTestScreen::CAM_LEFT:
				if (Input::IsKeyDown(GetKey(KEY::KEY_UP))) {
					MoveSelectSlideCol(true);
				}
				else if (Input::IsKeyDown(GetKey(KEY::KEY_LEFT))) {
					MoveSelectChangeDir(ROTATE_DIR::ROT_UP);
				}
				else if (Input::IsKeyDown(GetKey(KEY::KEY_DOWN))) {
					MoveSelectSlideCol(false);
				}
				else if (Input::IsKeyDown(GetKey(KEY::KEY_RIGHT))) {
					MoveSelectChangeDir(ROTATE_DIR::ROT_DOWN);
				}
				break;
			case ModelTestScreen::CAM_BACK:
				if (Input::IsKeyDown(GetKey(KEY::KEY_UP))) {
					MoveSelectChangeDir(ROTATE_DIR::ROT_DOWN);
				}
				else if (Input::IsKeyDown(GetKey(KEY::KEY_LEFT))) {
					MoveSelectSlideCol(true);
				}
				else if (Input::IsKeyDown(GetKey(KEY::KEY_DOWN))) {
					MoveSelectChangeDir(ROTATE_DIR::ROT_UP);
				}
				else if (Input::IsKeyDown(GetKey(KEY::KEY_RIGHT))) {
					MoveSelectSlideCol(false);
				}
				break;
			case ModelTestScreen::CAM_RIGHT:
				if (Input::IsKeyDown(GetKey(KEY::KEY_UP))) {
					MoveSelectSlideCol(false);
				}
				else if (Input::IsKeyDown(GetKey(KEY::KEY_LEFT))) {
					MoveSelectChangeDir(ROTATE_DIR::ROT_DOWN);
				}
				else if (Input::IsKeyDown(GetKey(KEY::KEY_DOWN))) {
					MoveSelectSlideCol(true);
				}
				else if (Input::IsKeyDown(GetKey(KEY::KEY_RIGHT))) {
					MoveSelectChangeDir(ROTATE_DIR::ROT_UP);
				}
				break;
			}
			break;
		case ROTATE_DIR::ROT_LEFT:
		case ROTATE_DIR::ROT_RIGHT:
			if (Input::IsKeyDown(GetKey(KEY::KEY_UP))) {
				MoveSelectSlideCol(true);
			}
			else if (Input::IsKeyDown(GetKey(KEY::KEY_LEFT))) {
				MoveSelectChangeDir(ROTATE_DIR::ROT_LEFT);
			}
			else if (Input::IsKeyDown(GetKey(KEY::KEY_DOWN))) {
				MoveSelectSlideCol(false);
			}
			else if (Input::IsKeyDown(GetKey(KEY::KEY_RIGHT))) {
				MoveSelectChangeDir(ROTATE_DIR::ROT_RIGHT);
			}
			break;
		case ROTATE_DIR::ROT_CW:
		case ROTATE_DIR::ROT_CCW:
			switch (camDirHN)
			{
			case ModelTestScreen::CAM_FRONT:
				//�O�A��
				if (camTra.rotate_.x > 0) {
					if (Input::IsKeyDown(GetKey(KEY::KEY_UP))) {
						MoveSelectSlideCol(true);
					}
					else if (Input::IsKeyDown(GetKey(KEY::KEY_LEFT))) {
						MoveSelectChangeDir(ROTATE_DIR::ROT_CCW);
					}
					else if (Input::IsKeyDown(GetKey(KEY::KEY_DOWN))) {
						MoveSelectSlideCol(false);
					}
					else if (Input::IsKeyDown(GetKey(KEY::KEY_RIGHT))) {
						MoveSelectChangeDir(ROTATE_DIR::ROT_CW);
					}
				}
				else {	//�O�A��
					if (Input::IsKeyDown(GetKey(KEY::KEY_UP))) {
						MoveSelectSlideCol(false);
					}
					else if (Input::IsKeyDown(GetKey(KEY::KEY_LEFT))) {
						MoveSelectChangeDir(ROTATE_DIR::ROT_CW);
					}
					else if (Input::IsKeyDown(GetKey(KEY::KEY_DOWN))) {
						MoveSelectSlideCol(true);
					}
					else if (Input::IsKeyDown(GetKey(KEY::KEY_RIGHT))) {
						MoveSelectChangeDir(ROTATE_DIR::ROT_CCW);
					}
				}
				break;
			case ModelTestScreen::CAM_LEFT:
				if (Input::IsKeyDown(GetKey(KEY::KEY_UP))) {
					MoveSelectChangeDir(ROTATE_DIR::ROT_CW);
				}
				else if (Input::IsKeyDown(GetKey(KEY::KEY_LEFT))) {
					MoveSelectSlideCol(true);
				}
				else if (Input::IsKeyDown(GetKey(KEY::KEY_DOWN))) {
					MoveSelectChangeDir(ROTATE_DIR::ROT_CCW);
				}
				else if (Input::IsKeyDown(GetKey(KEY::KEY_RIGHT))) {
					MoveSelectSlideCol(false);

				}
				break;
			case ModelTestScreen::CAM_BACK:
				//�O�A��
				if (camTra.rotate_.x > 0) {
					if (Input::IsKeyDown(GetKey(KEY::KEY_UP))) {
						MoveSelectSlideCol(false);
					}
					else if (Input::IsKeyDown(GetKey(KEY::KEY_LEFT))) {
						MoveSelectChangeDir(ROTATE_DIR::ROT_CW);
					}
					else if (Input::IsKeyDown(GetKey(KEY::KEY_DOWN))) {
						MoveSelectSlideCol(true);
					}
					else if (Input::IsKeyDown(GetKey(KEY::KEY_RIGHT))) {
						MoveSelectChangeDir(ROTATE_DIR::ROT_CCW);
					}
				}
				else {	//�O�A��
					if (Input::IsKeyDown(GetKey(KEY::KEY_UP))) {
						MoveSelectSlideCol(true);
					}
					else if (Input::IsKeyDown(GetKey(KEY::KEY_LEFT))) {
						MoveSelectChangeDir(ROTATE_DIR::ROT_CCW);
					}
					else if (Input::IsKeyDown(GetKey(KEY::KEY_DOWN))) {
						MoveSelectSlideCol(false);
					}
					else if (Input::IsKeyDown(GetKey(KEY::KEY_RIGHT))) {
						MoveSelectChangeDir(ROTATE_DIR::ROT_CW);
					}
				}
				break;
			case ModelTestScreen::CAM_RIGHT:
				if (Input::IsKeyDown(GetKey(KEY::KEY_UP))) {
					MoveSelectChangeDir(ROTATE_DIR::ROT_CCW);
				}
				else if (Input::IsKeyDown(GetKey(KEY::KEY_LEFT))) {
					MoveSelectSlideCol(false);
				}
				else if (Input::IsKeyDown(GetKey(KEY::KEY_DOWN))) {
					MoveSelectChangeDir(ROTATE_DIR::ROT_CW);
				}
				else if (Input::IsKeyDown(GetKey(KEY::KEY_RIGHT))) {
					MoveSelectSlideCol(true);

				}
				break;
			}
		}
		//��]���[�h���̃L�[�ړ����̏���
		break;
	}

}

void ModelTestScreen::MoveSelectParts(DIR dir, bool plus, Cube::SURFACE outSurface) {

	int* target = nullptr;
	switch (dir)
	{
	case ModelTestScreen::X:target = &selectData.x; break;
	case ModelTestScreen::Y:target = &selectData.y; break;
	case ModelTestScreen::Z:target = &selectData.z; break;
	}
	if (target != nullptr) {
		if (plus) {
			*target += 1;
			if (*target >= PIECES) {
				*target = PIECES - 1;
				selectData.surface = outSurface;
			}
		}
		else {
			*target -= 1;
			if (*target < 0) {
				*target = 0;
				selectData.surface = outSurface;
			}
		}
	}
	indicator->SetDrawPoint(selectData.GetPos(), selectData.surface);
}

void ModelTestScreen::MoveSelectChangeDir(ROTATE_DIR changeDir)
{
	selectData.dir = changeDir;
	indicator->SetCubeRotate(selectData.dir);
}

void ModelTestScreen::MoveSelectSlideCol(bool isPlus)
{
	if (isPlus) {
		if (selectData.rotCol < PIECES - 1) {
			selectData.rotCol++;
			indicator->SetRotateColumn(selectData.rotCol);
		}
	}
	else {
		if (selectData.rotCol > 0) {
			selectData.rotCol--;
			indicator->SetRotateColumn(selectData.rotCol);
		}
	}
}

void ModelTestScreen::MoveIndicator()
{
}

//============================ �J�����֘A ============================

//�J�����֘A�̏���
void ModelTestScreen::RotateCamera() {
	bool moveFlag = false;

	//���N���b�N���Ƀh���b�O�ňړ�����
	if (Input::IsMouseButton(0)) {
		rotSpdY = Input::GetMouseMove().x * AT_RATIO;   //�}�E�Xx�ړ��ʂ�y����]
		rotSpdX = Input::GetMouseMove().y * AT_RATIO;   //�}�E�Xy�ړ��ʂ�x����]
		moveFlag = true;
	}
	if (mode != MODE_VIEW) {
		if (rotSpdX != 0 || rotSpdY != 0) {
			prevMode = mode;
			mode = MODE_VIEW;
		}
	}
	//�J�����ړ����Ȃ������瑬�x����
	if (!moveFlag) {
		//�e���x��0�łȂ��ꍇ�������� ���ȉ���0�ɂ���
		if (rotSpdX != DEFAULT_CAM_SPEED) {
			rotSpdX /= DC_RATIO;
			if (std::abs(rotSpdX) < TH_ZEROSPEED)rotSpdX = DEFAULT_CAM_SPEED;
		}
		if (rotSpdY != DEFAULT_CAM_SPEED) {
			rotSpdY /= DC_RATIO;
			if (std::abs(rotSpdY) < TH_ZEROSPEED)rotSpdY = DEFAULT_CAM_SPEED;
		}
	}

	//��]���ɉ��Z
	camTra.rotate_.y += rotSpdY;
	camTra.rotate_.x += rotSpdX;

	//�͈͓�����(���ڑ���ɂ���ƈ�u�ł܂邽�߉������邱�Ƃŉ��)
	camTra.rotate_.x = std::clamp(camTra.rotate_.x, MIN_CAM_ROTATE_X, MAX_CAM_ROTATE_X);
	if (camTra.rotate_.y > LIMIT_CAM_ROTATE_Y) {
		camTra.rotate_.y -= Twice(LIMIT_CAM_ROTATE_Y);
	}
	if (camTra.rotate_.y < -LIMIT_CAM_ROTATE_Y) {
		camTra.rotate_.y += Twice(LIMIT_CAM_ROTATE_Y);
	}

	XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(camTra.rotate_.y));   //Y����Y��]�ʕ���]������s��
	XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(camTra.rotate_.x));   //X����X��]�ʕ���]������s��

	//�J�����ݒ� �ʒu->�Ώۂ̌��
	XMVECTOR vCam = { 0,0,-CAM_DISTANCE,0 };                  //�����w��
	vCam = XMVector3TransformCoord(vCam, mRotX * mRotY);    //�ό`:��]
	Camera::SetPosition(vCam);            //�Z�b�g

	//�J�����̉�]��񂩂�ړ��ȂǂŔ���Ɏg�����ʂ�o�^����
	if (Between(camTra.rotate_.y, -45.0f, 45.0f))camDirHN = CAM_FRONT;
	else if (Between(camTra.rotate_.y, 45.0f, 135.0f))camDirHN = CAM_LEFT;
	else if (Between(camTra.rotate_.y, -135.0f, -45.0f))camDirHN = CAM_RIGHT;
	else camDirHN = CAM_BACK;

	if (Between(camTra.rotate_.x, 45.0f, MAX_CAM_ROTATE_X))camDirVT = CAM_TOP;
	else if (Between(camTra.rotate_.x, MIN_CAM_ROTATE_X, -45.0f))camDirVT = CAM_BOTTOM;
	else camDirVT = CAM_MIDDLE;

	/*
	�E�ړ��n�̏����͑Ώۂ�0, 0, 0�ŌŒ�Ȃ̂ŏ����Ȃ��Ă���
	�E�ΏۂƂ̋���������͕ς���K�v���܂������Ȃ��̂Œ萔��
	*/
}

//============================ ��]���[�h�֘A ============================

void ModelTestScreen::UpdateCubeTransform()
{
	//�O����W�A������W�A��]����L���[�u�̐e�𒆐S�Ɏw�肷��
	switch (selectData.dir)
	{
	case ROTATE_DIR::ROT_UP:
	case ROTATE_DIR::ROT_DOWN:
		for (int y = 0; y < PIECES; y++) {
			for (int z = 0; z < PIECES; z++) {
				cube[selectData.rotCol][y][z]->SetParent(groupObject[GROUP_ROTATECUBE]);
			}
		}
		break;
	case ROTATE_DIR::ROT_LEFT:
	case ROTATE_DIR::ROT_RIGHT:
		for (int x = 0; x < PIECES; x++) {
			for (int z = 0; z < PIECES; z++) {
				cube[x][selectData.rotCol][z]->SetParent(groupObject[GROUP_ROTATECUBE]);
			}
		}
		break;
	case ROTATE_DIR::ROT_CW:
	case ROTATE_DIR::ROT_CCW:
		for (int x = 0; x < PIECES; x++) {
			for (int y = 0; y < PIECES; y++) {
				cube[x][y][selectData.rotCol]->SetParent(groupObject[GROUP_ROTATECUBE]);
			}
		}
		break;
	}
}


void ModelTestScreen::RotateCube(int prog, int maxProg, ROTATE_DIR dir) {
	switch (dir)
	{
	case ROTATE_DIR::ROT_UP:	groupObject[GROUP_ROTATECUBE]->SetRotateX(Easing::Calc(11, (float)prog, (float)maxProg, 0.0f, 90.0f));	break;
	case ROTATE_DIR::ROT_DOWN:	groupObject[GROUP_ROTATECUBE]->SetRotateX(Easing::Calc(11, (float)prog, (float)maxProg, 0.0f, -90.0f));	break;
	case ROTATE_DIR::ROT_LEFT:	groupObject[GROUP_ROTATECUBE]->SetRotateY(Easing::Calc(11, (float)prog, (float)maxProg, 0.0f, 90.0f));	break;
	case ROTATE_DIR::ROT_RIGHT:	groupObject[GROUP_ROTATECUBE]->SetRotateY(Easing::Calc(11, (float)prog, (float)maxProg, 0.0f, -90.0f));	break;
	case ROTATE_DIR::ROT_CW:	groupObject[GROUP_ROTATECUBE]->SetRotateZ(Easing::Calc(11, (float)prog, (float)maxProg, 0.0f, -90.0f));	break;
	case ROTATE_DIR::ROT_CCW:	groupObject[GROUP_ROTATECUBE]->SetRotateZ(Easing::Calc(11, (float)prog, (float)maxProg, 0.0f, 90.0f));	break;
	}
}

void ModelTestScreen::CompletedRotate()
{
	//�L���[�u�̐e�A��������
	//�L���[�u���̓���ւ�
	//�L���[�u�C���X�^���X���̂����ւ�
	//�L���[�u���W���w��
	// 
	// ���P�O�܂ł�Transform���L���[�u�̌����p�ӂ��ēs�x���W���w�肷����̂��������A
	// �C���X�^���X�̓���ւ���ɍēx���W������������ق����e�ʂ�H��Ȃ��̂ł�������̗p
	// �i������]�����ɂ���Ĕ͈͎w�肵���ق��������͂��� ����̓L���[�u�T�C�Y��������قǌ��ʂ�����j

	switch (selectData.dir)
	{
	case ROTATE_DIR::ROT_UP:
	case ROTATE_DIR::ROT_DOWN:
		for (int y = 0; y < PIECES; y++) {
			for (int z = 0; z < PIECES; z++) {
				//�e�����ɖ߂�
				cube[selectData.rotCol][y][z]->SetParent(groupObject[GROUP_BACK]);

				//�L���[�u�f�[�^����
				cube[selectData.rotCol][y][z]->SwapData(selectData.dir);

			}
		}
		break;
	case ROTATE_DIR::ROT_LEFT:
	case ROTATE_DIR::ROT_RIGHT:
		for (int x = 0; x < PIECES; x++) {
			for (int z = 0; z < PIECES; z++) {
				//�e�����ɖ߂�
				cube[x][selectData.rotCol][z]->SetParent(groupObject[GROUP_BACK]);

				//�f�[�^����
				cube[x][selectData.rotCol][z]->SwapData(selectData.dir);
			}
		}
		break;
	case ROTATE_DIR::ROT_CW:
	case ROTATE_DIR::ROT_CCW:
		for (int x = 0; x < PIECES; x++) {
			for (int y = 0; y < PIECES; y++) {
				//�e�����ɖ߂�
				cube[x][y][selectData.rotCol]->SetParent(groupObject[GROUP_BACK]);

				//�f�[�^����
				cube[x][y][selectData.rotCol]->SwapData(selectData.dir);
			}
		}
		break;
	}


	//�L���[�u�z�����
	SwapCube();

	//�L���[�u���W�w��
	for (int x = 0; x < PIECES; x++) {
		for (int y = 0; y < PIECES; y++) {
			for (int z = 0; z < PIECES; z++) {
				cube[x][y][z]->SetPosition(ConvertPts2Pos(x, y, z));
			}
		}
	}

}

void ModelTestScreen::SwapCube() {

	int swapCount = PIECES;


	bool isCC = In(selectData.dir, { ROTATE_DIR::ROT_DOWN, ROTATE_DIR::ROT_LEFT, ROTATE_DIR::ROT_CW });	//��]���ɑ΂��Ď��v��肩�ǂ���

	//�z�����
	if (isCC) {
		for (int row = PIECES - 1; row >= 0; row--) {
			//����ւ��񐔂̍X�V
			SwapCubeModifySwapCount(&swapCount, row, isCC);
			for (int col = PIECES - 1; col >= PIECES - swapCount; col--) {

				switch (selectData.dir)
				{
				case ROTATE_DIR::ROT_UP:
				case ROTATE_DIR::ROT_DOWN:
					std::swap(cube[selectData.rotCol][row][col], cube[selectData.rotCol][col][PIECES - 1 - row]);
					break;
				case ROTATE_DIR::ROT_LEFT:
				case ROTATE_DIR::ROT_RIGHT:
					std::swap(cube[row][selectData.rotCol][col], cube[col][selectData.rotCol][PIECES - 1 - row]);
					break;
				case ROTATE_DIR::ROT_CW:
				case ROTATE_DIR::ROT_CCW:
					std::swap(cube[row][col][selectData.rotCol], cube[col][PIECES - 1 - row][selectData.rotCol]);
					break;
				}

			}
		}
	}
	else {
		for (int row = 0; row < PIECES; row++) {
			for (int col = PIECES - swapCount; col < PIECES; col++) {
				switch (selectData.dir)
				{
				case ROTATE_DIR::ROT_UP:
				case ROTATE_DIR::ROT_DOWN:
					std::swap(cube[selectData.rotCol][row][col], cube[selectData.rotCol][col][PIECES - 1 - row]);
					break;
				case ROTATE_DIR::ROT_LEFT:
				case ROTATE_DIR::ROT_RIGHT:
					std::swap(cube[row][selectData.rotCol][col], cube[col][selectData.rotCol][PIECES - 1 - row]);
					break;
				case ROTATE_DIR::ROT_CW:
				case ROTATE_DIR::ROT_CCW:
					std::swap(cube[row][col][selectData.rotCol], cube[col][PIECES - 1 - row][selectData.rotCol]);
					break;
				}
			}
			//����ւ��񐔂̍X�V
			SwapCubeModifySwapCount(&swapCount, row, isCC);
		}
	}
}
void ModelTestScreen::SwapCubeModifySwapCount(int* swapCount, int row, bool isCC)
{
	if (!isCC) {									//��]���ɑ΂������v�̏ꍇ
		if (row != Half(PIECES)) {					//��ӂ̔���(�[���؎�)�Ɠ����łȂ����
			if (row > Half(PIECES))	(*swapCount)++;	//�������傫����Α���
			else					(*swapCount)--;	//������菬������Ό���
		}
		else if (IsEven(PIECES))	(*swapCount)++;	//�����Ɠ����ŋ����ł���Α���
	}
	else {											//��]���ɑ΂����v�̏ꍇ
		if (row != Half(PIECES)) {					//��ӂ̔���(�[���؎�)�Ɠ����łȂ����
			if (row > Half(PIECES))	(*swapCount)--;	//�������傫����Ό���
			else					(*swapCount)++;	//������菬������Α���
		}
		else if (IsEven(PIECES))  (*swapCount)--;	//�����Ɠ����ŋ����ł���Ό���
	}
}


//�P��L���[�u����
void ModelTestScreen::CheckMarkSingle(XMINT3 pos, SURFACE surface, WinFlag& flag, FILTER filter = NONE)
{
	//�΂ߔ���
	JudgeDiag(pos, surface, flag);
	//�c��������
	JudgeVHD(pos, surface, flag, filter);
}
void ModelTestScreen::CheckMarkSingle(int x, int y, int z, SURFACE surface, WinFlag& flag, FILTER filter = NONE)
{
	CheckMarkSingle(XMINT3(x, y, z), surface, flag, filter);
}

//��]���̔���
void ModelTestScreen::CheckMarkRotate(XMINT3 pos, DIR dir, WinFlag& flag)
{
	/*
	0,0,0��X���ŏ㉺�����Ɉړ������ꍇ
	X�ʒu���Œ�
	000front 010front 020front
	020top 021top 022top
	002back 012back 022back
	000bottom 001bottom 002bottom
	0,0,0��Y���ō��E�����Ɉړ������ꍇ
	Y�ʒu���Œ�
	000front 100front 200front
	000left 001left 002left
	002back 102back 202back
	200right 201right 202right
	0,0,0��Z���Ŏ��v�����v�����Ɉړ������ꍇ
	Z�ʒu���Œ�
	000left 010left 020left
	020top 120top 220top
	200right 210right 220right
	000bottom 100bottom 200bottom
	*/
	//���ꂼ��̃}�X�̔��� ��]���Ɉړ�����12�� �����͊֌W�����ς��Ȃ����ߌ��Ȃ�
	switch (dir)
	{
	case ModelTestScreen::X:
		for (int i = 0; i < PIECES; i++) {
			CheckMarkSingle(pos.x, i, 0, SURFACE::SURFACE_FRONT, winFlag, DISABLE_HORIZONTAL_SEARCH);
			CheckMarkSingle(pos.x, PIECES - 1, i, SURFACE::SURFACE_TOP, winFlag, DISABLE_DEPTH_SEARCH);
			CheckMarkSingle(pos.x, i, PIECES - 1, SURFACE::SURFACE_BACK, winFlag, DISABLE_HORIZONTAL_SEARCH);
			CheckMarkSingle(pos.x, 0, i, SURFACE::SURFACE_BOTTOM, winFlag, DISABLE_DEPTH_SEARCH);
		}
		break;
	case ModelTestScreen::Y:
		for (int i = 0; i < PIECES; i++) {
			CheckMarkSingle(i, pos.y, 0, SURFACE::SURFACE_FRONT, winFlag, DISABLE_VERTICAL_SEARCH);
			CheckMarkSingle(0, pos.y, i, SURFACE::SURFACE_LEFT, winFlag, DISABLE_DEPTH_SEARCH);
			CheckMarkSingle(i, pos.y, PIECES - 1, SURFACE::SURFACE_BACK, winFlag, DISABLE_VERTICAL_SEARCH);
			CheckMarkSingle(PIECES - 1, pos.y, i, SURFACE::SURFACE_RIGHT, winFlag, DISABLE_DEPTH_SEARCH);
		}
		break;
	case ModelTestScreen::Z:
		for (int i = 0; i < PIECES; i++) {
			CheckMarkSingle(0, i, pos.z, SURFACE::SURFACE_LEFT, winFlag, DISABLE_HORIZONTAL_SEARCH);
			CheckMarkSingle(i, PIECES - 1, pos.z, SURFACE::SURFACE_TOP, winFlag, DISABLE_DEPTH_SEARCH);
			CheckMarkSingle(PIECES - 1, i, pos.z, SURFACE::SURFACE_RIGHT, winFlag, DISABLE_HORIZONTAL_SEARCH);
			CheckMarkSingle(i, 0, pos.z, SURFACE::SURFACE_BOTTOM, winFlag, DISABLE_DEPTH_SEARCH);
		}
		break;
	}
}
void ModelTestScreen::CheckMarkRotate(XMINT3 pos, ROTATE_DIR dir, WinFlag& flag)
{
	switch (dir)
	{
	case ROTATE_DIR::ROT_UP:
	case ROTATE_DIR::ROT_DOWN:
		CheckMarkRotate(pos, DIR::X, flag);
		break;
	case ROTATE_DIR::ROT_LEFT:
	case ROTATE_DIR::ROT_RIGHT:
		CheckMarkRotate(pos, DIR::Y, flag);
		break;
	case ROTATE_DIR::ROT_CW:
	case ROTATE_DIR::ROT_CCW:
		CheckMarkRotate(pos, DIR::Z, flag);
		break;
	}
}

//�΂ߔ���
void ModelTestScreen::JudgeDiag(XMINT3 pos, Cube::SURFACE surface, WinFlag& flag){
//���@�@�@�@��
//���������@�O�E�㍶
//���@�@�@�@���@�@�@
	switch (surface)
	{
	case Cube::SURFACE_TOP:     //������0,-,0
		//�T�����W2����v �E��
		if (pos.x == pos.z) {
			flag.Set(CheckMarkD(DIAG_VAR::DIAG_UP, PIECES - 1, DIAG_VAR::DIAG_UP, surface), surface);
		}
		//�T�����W2������ �E��
		if (PIECES - 1 - pos.x == pos.z) {
			flag.Set(CheckMarkD(DIAG_VAR::DIAG_UP, PIECES - 1, DIAG_VAR::DIAG_DOWN, surface), surface);
		}
		break;
	case Cube::SURFACE_BOTTOM:  //���オ0,-,0
		//�T�����W2����v �E��
		if (pos.x == pos.z) {
			flag.Set(CheckMarkD(DIAG_VAR::DIAG_UP, 0, DIAG_VAR::DIAG_UP, surface), surface);
		}
		if (PIECES - 1 - pos.x == pos.z) {  //�������� �E��
			flag.Set(CheckMarkD(DIAG_VAR::DIAG_UP, 0, DIAG_VAR::DIAG_DOWN, surface), surface);
		}
		break;
	case Cube::SURFACE_LEFT:    //�E����-,0,0
		if (pos.y == pos.z) {   //�����W��v���� �E��
			flag.Set(CheckMarkD(0, DIAG_VAR::DIAG_DOWN, DIAG_VAR::DIAG_DOWN, surface), surface);
		}
		if (PIECES - 1 - pos.y == pos.z) {  //�������� �E��
			flag.Set(CheckMarkD(0, DIAG_VAR::DIAG_UP, DIAG_VAR::DIAG_DOWN, surface), surface);
		}
		break;
	case Cube::SURFACE_RIGHT:   //������-,0,0
		if (pos.y == pos.z) {   //�����W��v���� �E��
			flag.Set(CheckMarkD(PIECES - 1, DIAG_VAR::DIAG_UP, DIAG_VAR::DIAG_UP, surface), surface);
		}
		if (PIECES - 1 - pos.y == pos.z) {  //�������� �E��
			flag.Set(CheckMarkD(PIECES - 1, DIAG_VAR::DIAG_DOWN, DIAG_VAR::DIAG_UP, surface), surface);
		}
		break;
	case Cube::SURFACE_FRONT:   //������0,0,-
		if (pos.x == pos.y) {   //�����W��v���� �E��
			flag.Set(CheckMarkD(DIAG_VAR::DIAG_UP, DIAG_VAR::DIAG_UP, 0, surface), surface);
		}
		if (PIECES - 1 - pos.x == pos.y) {  //�������� �E��
			flag.Set(CheckMarkD(DIAG_VAR::DIAG_UP, DIAG_VAR::DIAG_DOWN, 0, surface), surface);
		}
		break;
	case Cube::SURFACE_BACK:    //�E����0,0,-
		if (pos.x == pos.y) {   //�����W��v���� �E��
			flag.Set(CheckMarkD(DIAG_VAR::DIAG_DOWN, DIAG_VAR::DIAG_DOWN, PIECES - 1, surface), surface);
		}
		if (PIECES - 1 - pos.x == pos.y) {  //�������� �E��
			flag.Set(CheckMarkD(DIAG_VAR::DIAG_DOWN, DIAG_VAR::DIAG_UP, PIECES - 1, surface), surface);
		}
		break;
	}
}
//�c��������
void ModelTestScreen::JudgeVHD(XMINT3 pos, Cube::SURFACE surface, WinFlag& flag, FILTER filter)
{
	switch (surface) {
	case Cube::SURFACE::SURFACE_FRONT:
	case Cube::SURFACE::SURFACE_BACK:
		if (filter != DISABLE_VERTICAL_SEARCH)  flag.Set(CheckMarkVH(pos, surface, X), surface);
		if (filter != DISABLE_HORIZONTAL_SEARCH)flag.Set(CheckMarkVH(pos, surface, Y), surface);
		break;
	case Cube::SURFACE::SURFACE_LEFT:
	case Cube::SURFACE::SURFACE_RIGHT:
		if (filter != DISABLE_HORIZONTAL_SEARCH)flag.Set(CheckMarkVH(pos, surface, Y), surface);
		if (filter != DISABLE_DEPTH_SEARCH)     flag.Set(CheckMarkVH(pos, surface, Z), surface);
		break;
	case Cube::SURFACE::SURFACE_TOP:
	case Cube::SURFACE::SURFACE_BOTTOM:
		if (filter != DISABLE_VERTICAL_SEARCH)  flag.Set(CheckMarkVH(pos, surface, X), surface);
		if (filter != DISABLE_DEPTH_SEARCH)     flag.Set(CheckMarkVH(pos, surface, Z), surface);
		break;
	}
}

void ModelTestScreen::TurnEnd()
{
	if (control == CONTROL_1P) {
		nextTurn = CONTROL_2P;
		Debug::Log("2P�̃^�[��", true);
	}
	if (control == CONTROL_2P) {
		nextTurn = CONTROL_1P;

		Debug::Log("1P�̃^�[��", true);
	}
	isIdle = false;
	
	control = nextTurn; //�����Ŏ��̃^�[���ɂ���
}

void ModelTestScreen::Judge()
{
	switch (mode)
	{
	case ModelTestScreen::MODE_SET:
		CheckMarkSingle(selectData.GetPos(), selectData.surface, winFlag);	//���g�̑I���}�X�̂ݔ���
		break;
	case ModelTestScreen::MODE_ROTATE:
		CheckMarkRotate(selectData.GetPos(), selectData.dir, winFlag);				//��]�����S�Ẵ}�X�𔻒�
		break;
	}

	//��������
	//���������Ă��瑊��̏���
	if (control == CONTROL_1P) {
		if (winFlag.p2) {
			WinProcess(CONTROL_2P);
		}
		else if (winFlag.p1) {
			WinProcess(CONTROL_1P);
		}
	}
	if (control == CONTROL_2P) {
		if (winFlag.p1) {
			WinProcess(CONTROL_1P);
		}
		else if (winFlag.p2) {
			WinProcess(CONTROL_2P);
		}
	}
}

Cube::MARK ModelTestScreen::CheckMarkVH(int x, int y, int z, SURFACE surface, DIR dir)
{
	vector<XMINT3> checkMarks;
	for (int i = 0; i < PIECES; i++) {
		switch (dir)
		{
		case ModelTestScreen::X:
			checkMarks.push_back({ i,y,z });
			break;
		case ModelTestScreen::Y:
			checkMarks.push_back({ x,i,z });
			break;
		case ModelTestScreen::Z:
			checkMarks.push_back({ x,y,i });
			break;
		}
	}

	Debug::Log("�c������", true);
	return CheckMark(checkMarks, surface);
}

Cube::MARK ModelTestScreen::CheckMarkVH(XMINT3 xyz, SURFACE surface, DIR dir)
{
	return CheckMarkVH(xyz.x, xyz.y, xyz.z, surface, dir);
}

Cube::MARK ModelTestScreen::CheckMarkD(int x, int y, int z, SURFACE surface) {

	vector<XMINT3> checkMarks;
	for (int i = 0; i < PIECES; i++) {
		XMINT3 check;
		if (x < 0) {
			if (x == DIAG_VAR::DIAG_UP)check.x = i;
			if (x == DIAG_VAR::DIAG_DOWN)check.x = PIECES - 1 - i;
		}
		else {
			check.x = x;
		}
		if (y < 0) {
			if (y == DIAG_VAR::DIAG_UP)check.y = i;
			if (y == DIAG_VAR::DIAG_DOWN)check.y = PIECES - 1 - i;
		}
		else {
			check.y = y;
		}
		if (z < 0) {
			if (z == DIAG_VAR::DIAG_UP)check.z = i;
			if (z == DIAG_VAR::DIAG_DOWN)check.z = PIECES - 1 - i;
		}
		else {
			check.z = z;
		}
		Debug::Log("�΂ߔ���", true);
		checkMarks.push_back(check);
	}
	return CheckMark(checkMarks, surface);
}

Cube::MARK ModelTestScreen::CheckMark(vector<XMINT3> points, SURFACE surface)
{
	/*
	�������Ƃ��A���̃}�[�N��Ԃ�
	����Ȃ���΋󔒂�Ԃ�
	���󔒂ő����Ă��󔒂�Ԃ�
	*/

	Cube::MARK mark = cube[points[0].x][points[0].y][points[0].z]->GetMark(surface);   //�������Ƃ��ɕԂ��}�[�N
	assert(points.size() > 0);  //��Ⴂ�ŋ�̔z�񂪗�������assert

	Debug::Log("����F["+ std::to_string(points[0].x) + std::to_string(points[0].y) + std::to_string(points[0].z) +"]:" + 
		((std::string)NAMEOF_ENUM(mark)).substr(5) + ", ", false);

	for (int i = 1; i < points.size(); i++) { 

		Debug::Log("[" + std::to_string(points[i].x) + std::to_string(points[i].y) + std::to_string(points[i].z) + "]:" + 
			((std::string)NAMEOF_ENUM(cube[points[i].x][points[i].y][points[i].z]->GetMark(surface))).substr(5) + ", ", false);

		if (cube[points[i].x][points[i].y][points[i].z]->GetMark(surface) != mark) {

			Debug::Log(((std::string)NAMEOF_ENUM(mark)).substr(5) + "�͂����Ȃ�����", true);

			return Cube::MARK_BLANK;    //����Ȃ��������
		}
	}
	Debug::Log(((std::string)NAMEOF_ENUM(mark)).substr(5) + "���������", true);
	return mark;
}

//============================ �Q�[���I�������֘A ============================

void ModelTestScreen::WinProcess(CONTROL winner) {

	finished = true;
	//�J�����n������
	winRotProgress = 0;
	enFreeLook = false;
	winPrevRot = camTra.rotate_;
	switch (winner)
	{
	case ModelTestScreen::CONTROL_1P:
		winNextRot = Surface2CamRot(winFlag.p1WinSurface, &winPrevRot);
		debugStr[5] = "1p syouri";
		break;
	case ModelTestScreen::CONTROL_2P:
		winNextRot = Surface2CamRot(winFlag.p2WinSurface, &winPrevRot);
		debugStr[5] = "2p syouri";
		break;
	}

	//�{�^��������
	titleButton = Instantiate<ButtonGP>(this);
	titleButton->SetText("Back to Title");
	titleButton->SetPosition({ -200,200,0 });
	titleButton->SetScale(0.5f);
	//titleButton->
	titleButton->SetAction(BUTTON_ACTION::BACK_TO_TITLE);

}

void ModelTestScreen::FinishCamera()
{
	bool movingCamera = false;

	//���N���b�N�ŉ�]������ꂽ�ꍇ�A�t���[���b�N��L����
	if (Input::IsMouseButton(0)) {
		rotSpdY = Input::GetMouseMove().x * AT_RATIO;   //�}�E�Xx�ړ��ʂ�y����]
		rotSpdX = Input::GetMouseMove().y * AT_RATIO;   //�}�E�Xy�ړ��ʂ�x����]
		enFreeLook = true;
		movingCamera = true;
	}

	if (enFreeLook) {
		//�J�����ړ����Ȃ������瑬�x����
		if (!movingCamera) {
			//�e���x��0�łȂ��ꍇ�������� ���ȉ���0�ɂ���
			if (rotSpdX != DEFAULT_CAM_SPEED) {
				rotSpdX /= DC_RATIO;
				if (std::abs(rotSpdX) < TH_ZEROSPEED)rotSpdX = DEFAULT_CAM_SPEED;
			}
			if (rotSpdY != DEFAULT_CAM_SPEED) {
				rotSpdY /= DC_RATIO;
				if (std::abs(rotSpdY) < TH_ZEROSPEED)rotSpdY = DEFAULT_CAM_SPEED;
			}
		}

		//��]���ɉ��Z
		camTra.rotate_.y += rotSpdY;
		camTra.rotate_.x += rotSpdX;

		//�͈͓�����(���ڑ���ɂ���ƈ�u�ł܂邽�߉������邱�Ƃŉ��)
		camTra.rotate_.x = std::clamp(camTra.rotate_.x, MIN_CAM_ROTATE_X, MAX_CAM_ROTATE_X);
		if (camTra.rotate_.y > LIMIT_CAM_ROTATE_Y) {
			camTra.rotate_.y -= Twice(LIMIT_CAM_ROTATE_Y);
		}
		if (camTra.rotate_.y < -LIMIT_CAM_ROTATE_Y) {
			camTra.rotate_.y += Twice(LIMIT_CAM_ROTATE_Y);
		}
	}
	else {
		//0~100 ��u
		if (winRotProgress > maxWinRotProgress) {
			enFreeLook = true;
			return;
		}
		camTra.rotate_.x = Easing::Calc(WIN_CAM_EASE, winRotProgress, maxWinRotProgress, winPrevRot.x, winNextRot.x);
		camTra.rotate_.y = Easing::Calc(WIN_CAM_EASE, winRotProgress, maxWinRotProgress, winPrevRot.y, winNextRot.y);
		camTra.rotate_.z = Easing::Calc(WIN_CAM_EASE, winRotProgress, maxWinRotProgress, winPrevRot.z, winNextRot.z);
		winRotProgress++;
	}

	//�J�����ɃZ�b�g����
	XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(camTra.rotate_.y));   //Y����Y��]�ʕ���]������s��
	XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(camTra.rotate_.x));   //X����X��]�ʕ���]������s��

	//�J�����ݒ� �ʒu->�Ώۂ̌��
	XMVECTOR vCam = { 0,0,-CAM_DISTANCE,0 };                  //�����w��
	vCam = XMVector3TransformCoord(vCam, mRotX * mRotY);    //�ό`:��]
	Camera::SetPosition(vCam);            //�Z�b�g

}

void ModelTestScreen::Restart()
{
	//�e��ď�����
}

void ModelTestScreen::BackToTitle()
{
	
}


XMFLOAT3 ModelTestScreen::ConvertPts2Pos(int x, int y, int z) {
	return { (float)x - OUTER_POINT, (float)y - OUTER_POINT, (float)z - OUTER_POINT };
}

XMFLOAT3 ModelTestScreen::Surface2CamRot(SURFACE surface, XMFLOAT3* camRot)
{
	switch (surface)
	{
	case Cube::SURFACE::SURFACE_FRONT:	return { 0, 0, 0 };
	case Cube::SURFACE::SURFACE_BACK:
		if (camRot->y > 0)	return { 0, 180, 0 };
		return { 0, -180, 0 };
	case Cube::SURFACE::SURFACE_LEFT:
		return { 0, 90, 0 };
	case Cube::SURFACE::SURFACE_RIGHT:
		return { 0, -90, 0 };
	case Cube::SURFACE::SURFACE_TOP:
		return { MAX_CAM_ROTATE_X, camRot->y, 0 };
	case Cube::SURFACE::SURFACE_BOTTOM:
		return { MIN_CAM_ROTATE_X, camRot->y, 0 };
	}

	return { 0,0,0 };
}

/*
��]�g���K�[���A��]�����Ɖ�]����w�肵�A��]�t���O��L����
��]�t���O���L�������ꂽ��A��]�����Ɖ�]��ɏ]���A��]
��]�I����A��]�t���O�𖳌������ACube�I�u�W�F�N�g�����ւ���
*/

/*
�ЂƂ��ɉ�����Ƃ����Ă����E����z�A����x�Ŕ��肷�邱�ƂɂȂ�
�c���肾�ƑO�㍶�E��y�A�㉺��z
�΂߂��Ƃ���ɖʓ|�ŁA�O���xy�A���E��yz�A�㉺��xz�ł���

�I���ꏊ�ɂ���Ď΂߂̔�������邩�����ƂȂ邪�A
�㉺����x=0,2����z=0,2
���E����y=0,2����z=0,2
�O�ゾ��x=0,2����y=0,2
�Ŏ΂߂�����
����ɁA�E��ɏオ�邩�E���ɉ����邩�����߂�K�v������A
���x,z=0,0 2,2�ŉE�� x,z=0,2 2,0�ŉE��
https://cpprefjp.github.io/lang/cpp11/variadic_templates.html

�ړ����
�J�����ɂ������Ȃ��ړ�
�O�㍶�E��WS��Y-+�A�͈͊O�ŏ㉺��SURFACE�]���ŗǂ�
�O��AD��X-+�A�͈͊O�ō��E
�E��AD��Z-+�A�͈͊O�őO��
����AD��Z+-�A�͈͊O�Ō�O
���AD��X+-�A�͈͊O�ŉE��
�J�����ɂ������ړ�
Y���ŕς��ړ�
��
WS��Z+-�AAD��X-+

���W�n���Ȃ��
 +
- +
 -
*/