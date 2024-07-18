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
	
	//操作モード
	enum MODE {
		MODE_SET,       //○×を設置
		MODE_ROTATE,    //キューブを回転
		MODE_VIEW       //回転
	}mode, prevMode;

	//操作対象
	enum CONTROL {
		CONTROL_1P,
		CONTROL_2P
	}control, nextTurn;
	bool isIdle;
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

	enum BUTTON_ACTION {
		BACK_TO_TITLE,
		RESTART_GAME
	};
	void ButtonAct(int hAct) override;

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

	void RotateModeInit();	//回転モード移行時の初期化
	void SetModeInit();		//設置モード移行時の初期化
	bool isMoving;			//現在移動中か

	//============================ カメラ関連 ============================

	Transform camTra;				//カメラ変形情報
	float rotSpdX, rotSpdY;			//カメラ回転速度
	bool isEnded;                   //ゲーム終了フラグ
	const int CAM_DISTANCE;			//カメラ距離 固定
	const float TH_ZEROSPEED;		//カメラ速度0にする閾値
	const float DC_RATIO;            //カメラ減速割合
	const float AT_RATIO;			//カメラ移動量に対する回転距離単位
	const float MAX_CAM_ROTATE_X;	//カメラX回転の最高角度制限
	const float MIN_CAM_ROTATE_X;	//カメラX回転の最低角度制限
	const int LIMIT_CAM_ROTATE_Y;	//カメラY回転の角度制限(オーバーフロー回避)
	const float DEFAULT_CAM_SPEED;	//カメラのデフォルト速度(0
	enum CAM_DIR_HN_CARDINAL {
		CAM_FRONT,
		CAM_LEFT,
		CAM_BACK,
		CAM_RIGHT
	}camDirHN;						//カメラの水平方向
	enum CAM_DIR_VT_CARDINAL {
		CAM_TOP,
		CAM_MIDDLE,
		CAM_BOTTOM
	}camDirVT;						//カメラの垂直方向

	//カメラ関連の処理
	void RotateCamera();

	//============================ 回転モード関連 ============================
	const Easing::Ease ROTATE_EASE;
	//回転後の座標・回転キューブの親オブジェクト変更
	void UpdateCubeTransform();

	//キューブを回転
	void RotateCube(int prog, int maxProg, ROTATE_DIR dir);

	//回転終了後の処理
	void CompletedRotate();

	//キューブインスタンスの入れ替え
	void SwapCube();
	void SwapCubeModifySwapCount(int* swapCount, int row, bool isCC);	//入れ替え回数を変化させる関数


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

	//============================ ゲーム終了処理関連 ============================
	bool finished;					//ゲーム終了フラグ
	XMFLOAT3 winPrevRot, winNextRot;//勝利時のカメラ回転率と移動後のカメラ回転率を格納する変数
	const int maxWinRotProgress;	//終了時に揃った列にカメラを移動させるときのフレーム数
	int winRotProgress;				//現在カメラ移動フレーム数
	bool enFreeLook;				//ゲーム終了後にカメラを動かした場合に有効化 trueにすると揃った面に移動するカメラが途中でも停止する
	Text* winPlayerMsg;
	ButtonGP* titleButton;			//タイトルへ戻るボタン
	ButtonGP* restartButton;		//再戦ボタン
	Easing::Ease WIN_CAM_EASE;
	void WinProcess(CONTROL winner);//勝利確定時の処理
	void FinishCamera();			//ゲーム終了時のカメラ処理

	//これらはButtonActから呼び出されるやつ
	void Restart();					//再戦
	void BackToTitle();				//タイトルへ戻る

	//XMFLOAT3 Surface2CamRot(SURFACE surface, XMFLOAT3* camRot);	//その面に垂直に向くようなカメラ回転率を返す

	//============================ 〇〇関連 ============================



	//============================ 汎用関数・変換関数 ============================
	//値が範囲内か
	template <class T>
	bool Between(T value, T min, T max) {
		return (min <= value && value <= max);
	}

	//SQLのIn句と同じ
	template <class T>
	bool In(T val, vector<T> search) {
		for (auto& word : search) {
			if (val == word)return true;
		}
		return false;
	}

	//半分にする 型をそのまんま返すためintなどは自動切り捨て
	template <class T>
	T Half(T value) {
		return (value / 2.0f);
	}

	//2倍にする
	template <class T>
	T Twice(T value) {
		return (value * 2.0f);
	}

	//偶数かを見る
	bool IsEven(int value) {
		return (value % 2 == 0);
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
	// 
	//キューブ位置を座標に変換する
	XMFLOAT3 ConvertPts2Pos(int x, int y, int z);

	//その面に垂直に向くようなカメラ回転率を返す 上下はrotXさえ垂直であればいいので現在のrotYをそのまま使う
	XMFLOAT3 Surface2CamRot(SURFACE surface, XMFLOAT3* camRot);
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

/*
回転モードの変数まとめきれてないのとそれ以降の関数整列してないよ

*/