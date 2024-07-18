#pragma once
#include <string>
#include <vector>
#include "Engine/GameObject.h"
#include "Screen.h"
#include "Cube.h"
#include "Easing.h"

class CubeSelectIndicator;
class Screen;
class DebugText;
class GroupingObject;
class Text;
class ButtonGP;

using std::vector;

using SURFACE = Cube::SURFACE;
using ROTATE_DIR = Cube::ROTATE_DIR;
using MARK = Cube::MARK;

//�Ǘ�����N���X
class ModelTestScreen : public Screen
{
public:
	ModelTestScreen(GameObject* parent);
	~ModelTestScreen();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:
	int hImgBG;
	Screen* pScreen;	//�X�N���[���ďo�̂��߂̃|�C���^

	const int PIECES = 3;
	const float OUTER_POINT;
	vector<vector<vector<Cube*>>> cube;
	
	//���샂�[�h
	enum MODE {
		MODE_SET,       //���~��ݒu
		MODE_ROTATE,    //�L���[�u����]
		MODE_VIEW       //��]
	}mode, prevMode;

	//����Ώ�
	enum CONTROL {
		CONTROL_1P,
		CONTROL_2P
	}control, nextTurn;
	bool isIdle;
	//�I�����
	struct SelectData {
		int x, y, z;
		ROTATE_DIR dir;
		int rotCol;
		SURFACE surface;
		SelectData() {
			x = 1;
			y = 1;
			z = 0;
			surface = SURFACE::SURFACE_FRONT;
			rotCol = 1,
			dir = ROTATE_DIR::ROT_UP;
		}
		XMINT3 GetPos() { return XMINT3(x, y, z); }
	}selectData;

	enum BUTTON_ACTION {
		BACK_TO_TITLE,
		RESTART_GAME
	};
	void ButtonAct(int hAct) override;

	bool isRotating = false;

	//�O���[�v����񋓌^
	//��O���[�v�قǕ`�悪��ɂ����@AviUtl�Ǝ����悤�Ȃ���
	enum GROUP_CONTROL {
		GROUP_BACK,
		GROUP_ROTATECUBE,
		GROUP_TOP,
		GROUP_MAX
	};
	GroupingObject* groupObject[GROUP_MAX];
	int rotProgress;
	const int maxRotProgress = 100;	//��]�`�ʂɂ�����t���[����
	const int angleOfRotate = 90;
	int rotateNo;
	int rotTime = 0; 
	//�I���ꏊ�E�C���W�P�[�^�[�ړ��֘A
	CubeSelectIndicator* indicator;
	enum DIR {
		X,
		Y,
		Z
	};

	//�ړ�����
	//mode�ɂ���ăC���W�P�[�^��ω���������I�𒆂̃}�X��ς������]��ς�����ȂǁA
	//�㉺���E�L�[����͂��邱�ƂŔ������鏈�����܂Ƃ߂Ă���
	void MoveSelect(MODE mode);
	void MoveSelectParts(DIR dir, bool plus, SURFACE outSurface);
	void MoveSelectChangeDir(ROTATE_DIR changeDir);		//��]�����ύX
	void MoveSelectSlideCol(bool isPlus);				//��]��ύX

	void MoveIndicator();	//?

	void RotateModeInit();	//��]���[�h�ڍs���̏�����
	void SetModeInit();		//�ݒu���[�h�ڍs���̏�����
	bool isMoving;			//���݈ړ�����

	//============================ �J�����֘A ============================

	Transform camTra;				//�J�����ό`���
	float rotSpdX, rotSpdY;			//�J������]���x
	bool isEnded;                   //�Q�[���I���t���O
	const int CAM_DISTANCE;			//�J�������� �Œ�
	const float TH_ZEROSPEED;		//�J�������x0�ɂ���臒l
	const float DC_RATIO;            //�J������������
	const float AT_RATIO;			//�J�����ړ��ʂɑ΂����]�����P��
	const float MAX_CAM_ROTATE_X;	//�J����X��]�̍ō��p�x����
	const float MIN_CAM_ROTATE_X;	//�J����X��]�̍Œ�p�x����
	const int LIMIT_CAM_ROTATE_Y;	//�J����Y��]�̊p�x����(�I�[�o�[�t���[���)
	const float DEFAULT_CAM_SPEED;	//�J�����̃f�t�H���g���x(0
	enum CAM_DIR_HN_CARDINAL {
		CAM_FRONT,
		CAM_LEFT,
		CAM_BACK,
		CAM_RIGHT
	}camDirHN;						//�J�����̐�������
	enum CAM_DIR_VT_CARDINAL {
		CAM_TOP,
		CAM_MIDDLE,
		CAM_BOTTOM
	}camDirVT;						//�J�����̐�������

	//�J�����֘A�̏���
	void RotateCamera();

	//============================ ��]���[�h�֘A ============================
	const Easing::Ease ROTATE_EASE;
	//��]��̍��W�E��]�L���[�u�̐e�I�u�W�F�N�g�ύX
	void UpdateCubeTransform();

	//�L���[�u����]
	void RotateCube(int prog, int maxProg, ROTATE_DIR dir);

	//��]�I����̏���
	void CompletedRotate();

	//�L���[�u�C���X�^���X�̓���ւ�
	void SwapCube();
	void SwapCubeModifySwapCount(int* swapCount, int row, bool isCC);	//����ւ��񐔂�ω�������֐�


	//============================ DEBUG ============================
	//�f�o�b�O�e�L�X�g
	std::string debugStr[20];
	DebugText* debugtext;
	void UpdateStr();
	Cube* testCubeParent;
	Cube* testCubeChild;
	//SURFACE testSur = SURFACE::SURFACE_TOP, testSide= SURFACE::SURFACE_TOP;
	//============================ ����֘A ============================
	//�����t���O�\����
	struct WinFlag {
		bool p1 = false;
		bool p2 = false;
		SURFACE p1WinSurface = SURFACE::SURFACE_MAX;
		SURFACE p2WinSurface = SURFACE::SURFACE_MAX;
		WinFlag() {

		}
		void Set(MARK mark, SURFACE surface) {
			switch (mark)
			{
			case MARK::MARK_O:
				p1 = true;
				p1WinSurface = surface;
				return;
			case MARK::MARK_X:
				p2 = true;
				p2WinSurface = surface;
				return;
			}
		}
	}winFlag;


	//�΂ߔ��莞�̍��W�w�莞�Ɏg���񋓌^
	//�����p���Ĕ��肷��֐��ł�0�ȏ���w�肵���Ƃ��ɌŒ�l�Ƃ݂Ȃ����߁A�����̒l��0�����ɂ���
	enum DIAG_VAR {
		DIAG_UP = -1,
		DIAG_DOWN = -2
	};

	//����̎��ɉ������T�����s��Ȃ��t�B���^
	enum FILTER {
		NONE,
		DISABLE_VERTICAL_SEARCH,
		DISABLE_HORIZONTAL_SEARCH,
		DISABLE_DEPTH_SEARCH,
	};

	//����̖{�� �Ăяo���ƈ�A�̏������s�� selectData�ƕR�Â�(�����œn���Ă��ǂ�)
	void Judge();

	//���̃^�[���ֈڍs���� �����ŏI�������������
	void TurnEnd();

	//�c�����̔���
	//�����Ă�΂��̃}�[�N���A�����ĂȂ����BLANK��Ԃ�
	//����:xyz,surface,XYZ����(����}�X�̎��ɉ���������)
	MARK CheckMarkVH(int x, int y, int z, SURFACE surface, DIR dir);
	MARK CheckMarkVH(XMINT3 xyz, SURFACE surface, DIR dir);

	//�΂ߔ���
	//XYZ��0�ȏ�͌Œ�l DIAG_VAR::UP�͏��X�ɏ㏸�ADOWN�͏��X�ɉ��~����
	//surface�͔����
	MARK CheckMarkD(int x, int y, int z, SURFACE surface);

	//�n���ꂽ�L���[�uxyz���W�z��ƖʂŁA���̍��W�̂��̖ʂ���v���Ă��邩���肷��
	//��v�����炻�̃}�[�N���A��v���Ȃ�������BLANK��Ԃ�
	MARK CheckMark(vector<XMINT3> points, SURFACE surface);

	//��L���[�u�̔�����s���֐�
	//�����F�L���[�u�ʒu�A����ʁA�i�[�t���O�A��������̒T���𖳌�������t�B���^
	void CheckMarkSingle(XMINT3 pos, SURFACE surface, WinFlag& flag, FILTER filter);
	void CheckMarkSingle(int x, int y, int z, SURFACE surface, WinFlag& flag, FILTER filter);
	//��]������
	void CheckMarkRotate(XMINT3 pos, DIR dir, WinFlag& flag);
	void CheckMarkRotate(XMINT3 pos, ROTATE_DIR dir, WinFlag& flag);

	//�΂ߔ���
	//�����F�T�����W,��,�i�[�t���O
	void JudgeDiag(XMINT3 pos, SURFACE surface, WinFlag& winFlag);
	//�c��������
	//�����F�T�����W,��,�i�[�t���O,�t�B���^
	void JudgeVHD(XMINT3 pos, SURFACE surface, WinFlag& winFlag, FILTER filter);

	//============================ �Q�[���I�������֘A ============================
	bool finished;					//�Q�[���I���t���O
	XMFLOAT3 winPrevRot, winNextRot;//�������̃J������]���ƈړ���̃J������]�����i�[����ϐ�
	const int maxWinRotProgress;	//�I�����ɑ�������ɃJ�������ړ�������Ƃ��̃t���[����
	int winRotProgress;				//���݃J�����ړ��t���[����
	bool enFreeLook;				//�Q�[���I����ɃJ�����𓮂������ꍇ�ɗL���� true�ɂ���Ƒ������ʂɈړ�����J�������r���ł���~����
	Text* winPlayerMsg;
	ButtonGP* titleButton;			//�^�C�g���֖߂�{�^��
	ButtonGP* restartButton;		//�Đ�{�^��
	Easing::Ease WIN_CAM_EASE;
	void WinProcess(CONTROL winner);//�����m�莞�̏���
	void FinishCamera();			//�Q�[���I�����̃J��������

	//������ButtonAct����Ăяo�������
	void Restart();					//�Đ�
	void BackToTitle();				//�^�C�g���֖߂�

	//XMFLOAT3 Surface2CamRot(SURFACE surface, XMFLOAT3* camRot);	//���̖ʂɐ����Ɍ����悤�ȃJ������]����Ԃ�

	//============================ �Z�Z�֘A ============================



	//============================ �ėp�֐��E�ϊ��֐� ============================
	//�l���͈͓���
	template <class T>
	bool Between(T value, T min, T max) {
		return (min <= value && value <= max);
	}

	//SQL��In��Ɠ���
	template <class T>
	bool In(T val, vector<T> search) {
		for (auto& word : search) {
			if (val == word)return true;
		}
		return false;
	}

	//�����ɂ��� �^�����̂܂�ܕԂ�����int�Ȃǂ͎����؂�̂�
	template <class T>
	T Half(T value) {
		return (value / 2.0f);
	}

	//2�{�ɂ���
	template <class T>
	T Twice(T value) {
		return (value * 2.0f);
	}

	//������������
	bool IsEven(int value) {
		return (value % 2 == 0);
	}

	//�����̈�v
	//template<class T, typename... Args>
	//bool MultiEquals(T val1, T val2, Args... values) {
	//	if (MultiEquals(val2, values)) {
	//		return true;
	//	}
	//	return false;
	//}

	//template <class T>
	//bool MultiEquals(T val1, T val2) {
	//	return (val1 == val2);
	//}
	// 
	//�L���[�u�ʒu�����W�ɕϊ�����
	XMFLOAT3 ConvertPts2Pos(int x, int y, int z);

	//���̖ʂɐ����Ɍ����悤�ȃJ������]����Ԃ� �㉺��rotX���������ł���΂����̂Ō��݂�rotY�����̂܂܎g��
	XMFLOAT3 Surface2CamRot(SURFACE surface, XMFLOAT3* camRot);
};

/*
SET,ROTATE
SPACE:�ݒu
LSHIFT:�ؑ�
WASD:�㉺���E�ړ�/��]�����ؑ�
E:(ROTATE�̂�)���ؑ�
�E�N���b�N:VIEW�ֈڍs
VIEW
SET,ROTATE�Ŏg���L�[:�O�񃂁[�h�ֈڍs Space�ł����񂶂��
�E�N���b�N�������Ƀh���b�O:���_��]


*/

/*
��]���[�h�̕ϐ��܂Ƃ߂���ĂȂ��̂Ƃ���ȍ~�̊֐����񂵂ĂȂ���

*/