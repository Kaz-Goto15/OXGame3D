#pragma once
#include <string>
#include <vector>
#include "Engine/GameObject.h"
#include "Screen.h"
#include "Cube.h"
class CubeSelectIndicator;
class Screen;
class DebugText;
class GroupingObject;

using std::vector;

using SURFACE = Cube::SURFACE;
using ROTATE_DIR = Cube::ROTATE_DIR;
using MARK = Cube::MARK;

//管理するクラス
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
	Screen* pScreen;	//スクリーン呼出のためのポインタ

	const int PIECES = 3;
	const float OUTER_POINT;
	vector<vector<vector<Cube*>>> cube;
	//vector<vector<vector<Transform>>> cubePrevTra;
	//vector<vector<vector<Transform>>> cubeNextTra;
	
	//操作モード
	enum MODE {
		MODE_SET,       //○×を設置
		MODE_ROTATE,    //キューブを回転
		MODE_VIEW       //回転
	}mode, prevMode;

	//操作対象
	enum CONTROL {
		CONTROL_IDLE,
		CONTROL_1P,
		CONTROL_2P
	}control, nextTurn;

	//選択情報
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


	bool isRotating = false;

	//グループ制御列挙型
	//上グループほど描画が先にされる　AviUtlと似たようなもの
	enum GROUP_CONTROL {
		GROUP_BACK,
		GROUP_ROTATECUBE,
		GROUP_TOP,
		GROUP_MAX
	};
	GroupingObject* groupObject[GROUP_MAX];
	int rotProgress;
	const int maxRotProgress = 100;	//回転描写にかけるフレーム数
	const int angleOfRotate = 90;
	int rotateNo;
	int rotTime = 0; 
	//選択場所・インジケーター移動関連
	CubeSelectIndicator* indicator;
	enum DIR {
		X,
		Y,
		Z
	};

	//移動処理
	//modeによってインジケータを変化させたり選択中のマスを変えたり回転を変えたりなど、
	//上下左右キーを入力することで発生する処理をまとめている
	void MoveSelect(MODE mode);
	void MoveSelectParts(DIR dir, bool plus, SURFACE outSurface);
	void MoveSelectChangeDir(ROTATE_DIR changeDir);		//回転方向変更
	void MoveSelectSlideCol(bool isPlus);				//回転列変更

	void MoveIndicator();	//?

	//値が範囲内か
	template <class T>
	bool Between(T value, T min, T max) {
		return (min <= value && value <= max);
	}

	template <class T>
	bool In(T val, vector<T> search) {
		for (auto& word : search) {
			if (val == word)return true;
		}
		return false;
	}
	//複数の一致
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

	void RotateModeInit();	//回転モード移行時の初期化
	void SetModeInit();		//設置モード移行時の初期化
	bool isMoving;			//現在移動中か

	//============================ カメラ関連 ============================
	Transform camTra;				//カメラ変形情報
	float rotSpdX, rotSpdY;			//カメラ回転速度
	bool isEnded;                   //ゲーム終了フラグ
	const int CAM_DISTANCE;			//カメラ距離 固定
	//const float DC_VALUE = 0.05f;         //カメラ減速値
	const float TH_ZEROSPEED;		//カメラ速度0にする閾値
	const float DC_RATIO;            //カメラ減速割合
	const float AT_RATIO;			//カメラ移動量に対する回転距離単位
	const float MAX_CAM_ROTATE_X;	//カメラX回転の最高角度制限
	const float MIN_CAM_ROTATE_X;	//カメラX回転の最低角度制限
	const int LIMIT_CAM_ROTATE_Y;	//カメラY回転の角度制限(オーバーフロー回避)
	const int DEFAULT_CAM_SPEED;	//カメラのデフォルト速度(0)
	enum CAM_DIR_CARDINAL {
		CAM_FRONT,
		CAM_LEFT,
		CAM_BACK,
		CAM_RIGHT
	}camDir;

	//============================ DEBUG ============================
	//デバッグテキスト
	std::string debugStr[20];
	DebugText* debugtext;
	void UpdateStr();
	Cube* testCubeParent;
	Cube* testCubeChild;
	//SURFACE testSur = SURFACE::SURFACE_TOP, testSide= SURFACE::SURFACE_TOP;
	//============================ 判定関連 ============================
	//勝利フラグ構造体
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
	//斜め判定時の座標指定時に使う列挙型
	//これを用いて判定する関数では0以上を指定したときに固定値とみなすため、ここの値は0未満にする
	enum DIAG_VAR {
		DIAG_UP = -1,
		DIAG_DOWN = -2
	};

	//特定の軸に沿った探索を行わないフィルタ
	enum FILTER {
		NONE,
		DISABLE_VERTICAL_SEARCH,
		DISABLE_HORIZONTAL_SEARCH,
		DISABLE_DEPTH_SEARCH,
	};

	//判定の本体 呼び出すと一連の処理を行う selectDataと紐づく(引数で渡しても良い)
	void Judge();

	//次のターンへ移行する ここで終了処理も内包する
	void TurnEnd();

	//縦横奥の判定
	//揃ってればそのマークを、揃ってなければBLANKを返す
	//引数:xyz,surface,XYZ方向(見るマスの軸に沿った向き)
	MARK CheckMarkVH(int x, int y, int z, SURFACE surface, DIR dir);
	MARK CheckMarkVH(XMINT3 xyz, SURFACE surface, DIR dir);

	//斜め判定
	//XYZは0以上は固定値 DIAG_VAR::UPは徐々に上昇、DOWNは徐々に下降する
	//surfaceは判定面
	MARK CheckMarkD(int x, int y, int z, SURFACE surface);

	//渡されたキューブxyz座標配列と面で、その座標のその面が一致しているか判定する
	//一致したらそのマークを、一致しなかったらBLANKを返す
	MARK CheckMark(vector<XMINT3> points, SURFACE surface);

	//一キューブの判定を行う関数
	//引数：キューブ位置、判定面、格納フラグ、特定方向の探索を無効化するフィルタ
	void CheckMarkSingle(XMINT3 pos, SURFACE surface, WinFlag& flag, FILTER filter);
	void CheckMarkSingle(int x, int y, int z, SURFACE surface, WinFlag& flag, FILTER filter);
	//回転時判定
	void CheckMarkRotate(XMINT3 pos, DIR dir, WinFlag& flag);
	void CheckMarkRotate(XMINT3 pos, ROTATE_DIR dir, WinFlag& flag);

	//斜め判定
	//引数：探索座標,面,格納フラグ
	void JudgeDiag(XMINT3 pos, SURFACE surface, WinFlag& winFlag);
	//縦横奥判定
	//引数：探索座標,面,格納フラグ,フィルタ
	void JudgeVHD(XMINT3 pos, SURFACE surface, WinFlag& winFlag, FILTER filter);

	//============================ 〇〇関連 ============================
	enum WIN_STATE {	//勝利時の処理をステート管理 数値はそのステートが続くフレーム数
		WIN_DRAWSTART = 100,	//黒半透明フェード
		WIN_SHOW_WINNER = 150,	//勝利者の表示
		WIN_DRAW_BUTTON = 100,
		WIN_MAX
	};
	const int SHOW_WINNER_FADEIN_FRAMES = 30;	//勝利の画像出すときのフェードインフレーム数
	bool winProcessFlag[WIN_MAX];
	void WinProcess();
	//↑これら全部temp


	/// <summary>
	/// キューブ回転のトリガー 初期化処理とフラグ管理
	/// 
	/// </summary>
	/// <param name="dir">前から見た時の回転方向</param>
	/// <param name="no">回転する行/列 [0][0][0]を基準とし、0,1,2で指定</param>
	/// <param name="angle">何度回転させるか</param>
	void UpdateCubeNextTransform(ROTATE_DIR dir, int no, float angle = 90.0f);

	//回転後の座標・回転キューブの親オブジェクト変更
	void UpdateCubeTransform();

	//キューブ位置を座標に変換する
	XMFLOAT3 ConvertPts2Pos(int x, int y, int z);

	void RotateCube(int prog, int maxProg, ROTATE_DIR dir);
	void CompletedRotate();
	void SwapCube();
	void SwapCubeModifySwapCount(int* swapCount, int row, bool isCC);
	/// カメラ関連の処理
	void RotateCamera();
	void FinishCamera();
};

/*
SET,ROTATE
SPACE:設置
LSHIFT:切替
WASD:上下左右移動/回転方向切替
E:(ROTATEのみ)軸切替
右クリック:VIEWへ移行
VIEW
SET,ROTATEで使うキー:前回モードへ移行 Spaceでいいんじゃね
右クリック押下中にドラッグ:視点回転


*/