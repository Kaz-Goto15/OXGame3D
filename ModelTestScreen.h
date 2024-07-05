#pragma once
#include <string>
#include <vector>
#include "Engine/GameObject.h"
#include "Screen.h"
#include "Cube.h"
class CubeSelectIndicator;
class Screen;
class DebugText;

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
	vector<vector<vector<Cube*>>> cube;
	vector<vector<vector<Transform>>> cubePrevTra;
	vector<vector<vector<Transform>>> cubeNextTra;
	
	//���샂�[�h
	enum MODE {
		MODE_SET,       //���~��ݒu
		MODE_ROTATE,    //�L���[�u����]
		MODE_VIEW       //��]
	}mode, prevMode;

	//����Ώ�
	enum CONTROL {
		CONTROL_IDLE,
		CONTROL_1P,
		CONTROL_2P
	}control, nextTurn;

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

	void CalcCubeTrans();

	bool isRotating = false;
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
	void MoveSelect(MODE mode);
	void MoveSelectParts(DIR dir, bool plus, SURFACE outSurface);
	void MoveSelectChangeDir(ROTATE_DIR changeDir);
	void MoveSelectSlideCol(bool isPlus);

	void MoveIndicator();

	//�l���͈͓���
	template <class T>
	bool Between(T value, T min, T max) {
		return (min <= value && value <= max);
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

	void RotateModeInit();
	void SetModeInit();
	bool isMoving;
	//============================ �J�����֘A ============================
	Transform camTra;                       //�J�����ό`���
	float rotSpdX, rotSpdY;                 //�J������]���x
	bool isEnded;                           //�Q�[���I���t���O
	const int CAM_DISTANCE = 10;            //�J�������� �Œ�
	//const float DC_VALUE = 0.05f;         //�J���������l
	const float TH_ZEROSPEED = 0.3f;        //�J�������x0�ɂ���臒l
	const float DC_RATIO = 1.2f;            //�J������������
	const float AT_RATIO = 0.5f;        //�J�����ړ��ʂɑ΂����]�����P��
	const float MAX_CAM_ROTATE_X = 89.9999f;    //�J����X��]�̍ō��p�x����
	const float MIN_CAM_ROTATE_X = -89.9999f;   //�J����X��]�̍Œ�p�x����
	const int LIMIT_CAM_ROTATE_Y = 180;         //�J����Y��]�̊p�x����(�I�[�o�[�t���[���)
	const int DEFAULT_SPEED = 0;                //�J�����̃f�t�H���g���x(0)
	enum CAM_DIR_CARDINAL {
		CAM_FRONT,
		CAM_LEFT,
		CAM_BACK,
		CAM_RIGHT
	}camDir;
	//============================ DEBUG ============================
	//�f�o�b�O�e�L�X�g
	std::string debugStr[20];
	DebugText* debugtext;
	void UpdateStr();
	//============================ ����֘A ============================
	//�����t���O�\����
	struct WinFlag {
		bool p1 = false;
		bool p2 = false;
		WinFlag() {

		}
		void Set(MARK mark) {
			switch (mark)
			{
			case MARK::MARK_O:  p1 = true;  return;
			case MARK::MARK_X:  p2 = true;  return;
			}
		}
	}winFlag;

	bool finished;
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

	//============================ �Z�Z�֘A ============================
	enum WIN_STATE {	//�������̏������X�e�[�g�Ǘ� ���l�͂��̃X�e�[�g�������t���[����
		WIN_DRAWSTART = 100,	//���������t�F�[�h
		WIN_SHOW_WINNER = 150,	//�����҂̕\��
		WIN_DRAW_BUTTON = 100,
		WIN_MAX
	};
	const int SHOW_WINNER_FADEIN_FRAMES = 30;	//�����̉摜�o���Ƃ��̃t�F�[�h�C���t���[����
	bool winProcessFlag[WIN_MAX];
	void WinProcess();
	//�������S��temp


	/// <summary>
	/// �L���[�u��]�̃g���K�[ �����������ƃt���O�Ǘ�
	/// 
	/// </summary>
	/// <param name="dir">��]���� �O�ォ�猩�đO(��)��(��))���E���v�����v</param>
	/// <param name="no">��]����s/�� [0][0][0]����Ƃ��A0,1,2�Ŏw��</param>
	/// <param name="angle">���x��]�����邩</param>
	void UpdateCubeNextTransform(ROTATE_DIR dir, int no, float angle = 90.0f);

	/// �J�����֘A�̏���
	void RotateCamera();
	void FinishCamera();
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