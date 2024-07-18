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
//コンストラクタ
ModelTestScreen::ModelTestScreen(GameObject* parent) :
	Screen(parent, "ModelTestScreen"),
	hImgBG(-1),
	mode(MODE_SET), prevMode(MODE_SET),
	control(CONTROL_1P), nextTurn(CONTROL_2P),
	OUTER_POINT((PIECES - 1) / 2.0f),
	//カメラ
	rotSpdX(0), rotSpdY(0),		//カメラ回転速度
	isEnded(false),				//ゲーム終了フラグ
	CAM_DISTANCE(10),			//対象からカメラまでの距離
	TH_ZEROSPEED(0.3f),			//カメラ速度を0にする閾値 この値を下回ると速度を０にする
	DC_RATIO(1.2f),				//カメラ減速割合
	AT_RATIO(0.5f),				//カメラ移動量に対する回転距離単位
	MAX_CAM_ROTATE_X(89.9999f),	//カメラX回転の最高角度制限
	MIN_CAM_ROTATE_X(-89.9999f),//カメラX回転の最低角度制限
	LIMIT_CAM_ROTATE_Y(180),	//カメラY回転の角度制限(オーバーフロー回避)
	DEFAULT_CAM_SPEED(0.0f),		//カメラのデフォルト速度(0)
	camDirHN(CAM_FRONT),		//カメラの水平方向
	camDirVT(CAM_MIDDLE),		//カメラの垂直方向
	//回転モード
	ROTATE_EASE(Easing::Ease::OUT_QUART),
	//デバッグ
	debugtext(nullptr),
	testCubeParent(nullptr),
	testCubeChild(nullptr),
	//ゲーム終了処理
	maxWinRotProgress(100),
	winRotProgress(0),
	enFreeLook(false),
	winPlayerMsg(nullptr),
	titleButton(nullptr),
	restartButton(nullptr),
	WIN_CAM_EASE(Easing::Ease::OUT_QUART)
{
}

//デストラクタ
ModelTestScreen::~ModelTestScreen(){}

//初期化
void ModelTestScreen::Initialize()
{
	//処理の一部で親を変更するとき、描画の順序が変わりキューブ→インジケータ　からインジケータ→キューブになり
	//半透明の処理がされなくなっていた　そのため馴染み深いグループ制御オブジェクトを作成
	//グループ制御オブジェクトを生成
	for (int i = 0; i < GROUP_MAX; i++) {
		groupObject[i] = Instantiate<GroupingObject>(this);
	}

	//背景
	hImgBG = Image::Load("Background\\bg_game.png");

	//キューブ本体を保存するvectorをリサイズ
	cube.resize(PIECES, vector<vector<Cube*>>(PIECES, vector<Cube*>(PIECES, nullptr)));

	//キューブ生成
	for (auto& cx : cube) {
		for (auto& cy : cx) {
			for (auto& cz : cy) {
				cz = Instantiate<Cube>(groupObject[GROUP_BACK]);
			}
		}
	}

	//キューブ座標指定 PIECESでもいいかも
	for (int x = 0; x < cube.size();x++) {
		for (int y = 0; y < cube[0].size();y++) {
			for (int z = 0; z < cube[0][0].size();z++) {
				//cube[x][y][z] = Instantiate<Cube>(groupObject[GROUP_BACK]);
				cube[x][y][z]->SetPosition(ConvertPts2Pos(x, y, z));
			}
		}
	}

	//インジケーター生成・座標指定
	indicator = Instantiate<CubeSelectIndicator>(groupObject[GROUP_TOP]);
	indicator->SetCubeScale(PIECES);
	indicator->SetDrawPoint(selectData.GetPos(), selectData.surface);
	indicator->SetCubeRotate(selectData.dir);
	indicator->SetRotateColumn(selectData.rotCol);
	indicator->SetDrawMode(indicator->DRAWMODE_SINGLE);

	//デバッグ
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

//更新
void ModelTestScreen::Update()
{

	//RotateCamera();     //カメラの処理 MODE_VIEWでの分岐も内包

	//デバッグボタン
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

	//finishなどステートが進まない限り操作を受け付けるやつ 現状finish時以外できるため直打ち
	if (!finished) {
		if (Input::IsKeyDown(GetKey(KEY::KEY_ESC))) {
			pScreen = Instantiate<OptionScreen>(GetParent());
			pScreen->SetPrevScene(this);
			pScreen->Run();
		}

		RotateCamera();     //カメラの処理 MODE_VIEWでの分岐も内包
	}
	else {
		FinishCamera();     //カメラの処理 MODE_VIEWでの分岐も内包
	}

	//操作状態がアイドルでなければ
	if (!isIdle) {
		MoveSelect(mode);
		//現在のモードで処理
		switch (mode)
		{
		case ModelTestScreen::MODE_SET:
			//キー関連の記述は同時処理を防ぐため取り敢えずすべてelifで書く
			//マーク設置
			if (Input::IsKeyDown(GetKey(KEY::KEY_ACT))) {
				//選択箇所が空白のときに設置する
				if (cube[selectData.x][selectData.y][selectData.z]->GetMark(selectData.surface) == Cube::MARK_BLANK) {
					switch (control)
					{
					case ModelTestScreen::CONTROL_1P:   cube[selectData.x][selectData.y][selectData.z]->SetMark(selectData.surface, Cube::MARK::MARK_O);  break;
					case ModelTestScreen::CONTROL_2P:   cube[selectData.x][selectData.y][selectData.z]->SetMark(selectData.surface, Cube::MARK::MARK_X);  break;
					}
					//判定
					Judge();
					//ターンエンド処理 終了処理もここ
					TurnEnd();
				}
				else {
					//空白でないときのアニメーションがあればここに書く 選択を表す半透明モデルをずらすなど
					//Audio::Play("select_fail.wav");
				}
			}
			else if (Input::IsKeyDown(SystemConfig::GetKey(KEY::KEY_CHANGE))) {	//モード切替
				mode = MODE_ROTATE;
				indicator->SetDrawMode(indicator->DRAWMODE_CIRCLE);			//インジケータの描画モードを円形描画に
				RotateModeInit();	//現在の選択位置から軸を指定したりする
			}

			break;
		case ModelTestScreen::MODE_ROTATE:
			//回転軸切替
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
			//回転
			else if (Input::IsKeyDown(GetKey(KEY::KEY_ACT))) {
				//操作の無効化
				isIdle = true;
				//キューブの移動後の座標を更新・回転するオブジェクトを指定
				UpdateCubeTransform();
				//回転中フラグの有効化
				isRotating = true;

				//移動処理・移動完了後のフラグ・勝利判定・ターン移行は別で
			}
			else if (Input::IsKeyDown(GetKey(KEY::KEY_CHANGE))) {	//モード切替
				mode = MODE_SET;
				indicator->SetDrawMode(indicator->DRAWMODE_SINGLE);		//インジケータの描画モードを単一描画に
				SetModeInit();
			}
			break;
		case ModelTestScreen::MODE_VIEW:
			if (Input::IsKeyDown(GetKey(KEY::KEY_ACT))) {
				mode = prevMode;		//ビューモードの前のモードに戻す
				indicator->Visible();	//インジケータを再表示
			}
			break;
		}
	}
	else {
		if (isRotating) {
			rotProgress++;
			//描画終了時の処理 "以上"が条件のシステム処理後に条件なしの回転処理をしているため、
			//最終フレームで回転処理とシステム処理が同時に行える
			if (rotProgress > maxRotProgress) {
				rotProgress = 0;

				CompletedRotate();

				isRotating = false;
				Judge();
				TurnEnd();
			}

			//回転処理 現在進捗と最大進捗、値を入れる座標と移動前座標と移動後座標
			RotateCube(rotProgress, maxRotProgress, selectData.dir);
		}
	}

	UpdateStr();
}

//描画
void ModelTestScreen::Draw()
{
	Image::Draw(hImgBG);
}

//開放
void ModelTestScreen::Release()
{
}

void ModelTestScreen::RotateModeInit()
{
	//設置モードから回転モードに移行時、現在のカメラ角度から選択行と回転軸を指定する
	//視点から上方向になるよう初期化 それにより最初からLEFT/RIGHTは必ず指定されない
	const int SET_MODE_UNIT = 90 / PIECES;
	XMFLOAT3& camRot = camTra.rotate_;
	float absCamY = abs(camRot.y);
	
	bool isDecided = false;
	//前後はSetModeInitのx、左右はzと同等の処理
	for (int c = 0; c < PIECES; c++) {
		switch (camDirHN)
		{
		case ModelTestScreen::CAM_FRONT:
			if (camRot.y >= 45 - (c + 1) * SET_MODE_UNIT) { //前 -45~45
				selectData.rotCol = c;
				selectData.dir = ROTATE_DIR::ROT_UP;
				isDecided = true;
			}
			break;
		case ModelTestScreen::CAM_BACK:
			if (camRot.y > 0) {	//+
				if (180 - camRot.y >= 45 - (c + 1) * SET_MODE_UNIT) { //135~180→45~0変換
					selectData.rotCol = c;
					selectData.dir = ROTATE_DIR::ROT_DOWN;
					isDecided = true;
				}
			}
			else {	//-
				if (-180 - camRot.y >= 45 - (c + 1) * SET_MODE_UNIT) { //-180~-135→0~-45変換
					selectData.rotCol = c;
					selectData.dir = ROTATE_DIR::ROT_DOWN;
					isDecided = true;
				}
			}
			break;
		case ModelTestScreen::CAM_LEFT:
		case ModelTestScreen::CAM_RIGHT:
			//SetModeInitのzと同等の処理
			if (absCamY < 45 + (c + 1) * SET_MODE_UNIT) {
				selectData.rotCol = c;

				//回転方向指定
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

	//インジケータに設定
	indicator->SetCubeRotate(selectData.dir);
	indicator->SetRotateColumn(selectData.rotCol);


	debugStr[7] = "rotmodeinit:" + std::to_string(selectData.rotCol) + ","
		+ (std::string)NAMEOF_ENUM(selectData.dir);

}

void ModelTestScreen::SetModeInit()
{
	//回転モードから設置モードに移行時、現在のカメラ角度から選択マスを指定する
	const int SET_MODE_UNIT = 90 / PIECES;
	XMFLOAT3& camRot = camTra.rotate_;
	float absCamY = abs(camRot.y);

	//y指定
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

	//z指定
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
		//現在の回転角度によりZ方向の選択位置を決める ケーキを等分に切るような感じ
		for (int z = 0; z < PIECES; z++) {
			if (absCamY < 45 + (z + 1) * SET_MODE_UNIT) {
				selectData.z = z;
				break;
			}
		}
		break;
	}

	//x指定
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
			//現在の回転角度によりX方向の選択位置を決める
			if (camRot.y > 45 - (x + 1) * SET_MODE_UNIT) { //前 -45~45
				selectData.x = x;
				break;
			}
		}
		break;
	case ModelTestScreen::CAM_BACK:
		for (int x = 0; x < PIECES; x++) {
			//現在の回転角度によりX方向の選択位置を決める
			if (camRot.y > 0) {	//+
				if (180 - camRot.y > 45 - (x + 1) * SET_MODE_UNIT) { //135~180→45~0変換
					selectData.x = x;
					break;
				}
			}
			else {	//-
				if (-180 - camRot.y > 45 - (x + 1) * SET_MODE_UNIT) { //-180~-135→0~-45変換
					selectData.x = x;
					break;
				}
			}
		}
		break;
	}

	//選択面指定
	switch (camDirVT)
	{
	case ModelTestScreen::CAM_TOP:
		selectData.surface = SURFACE::SURFACE_TOP;	//カメラが上側にある
		break;
	case ModelTestScreen::CAM_BOTTOM:
		selectData.surface = SURFACE::SURFACE_BOTTOM;	//カメラが下側にある
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

	//インジケータに設定
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
				//WASDをASDWに
				tmp = keys.front();
				keys.erase(keys.begin());
				keys.push_back(tmp);
				break;
			case ModelTestScreen::CAM_RIGHT:
				//WASDをDWASに
				tmp = keys.back();
				keys.pop_back();
				keys.insert(keys.begin(), tmp);
				break;
			case ModelTestScreen::CAM_BACK:
				//WASDをSDWAに
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
				//WASDをDWASに
				tmp = keys.back();
				keys.pop_back();
				keys.insert(keys.begin(), tmp);
				break;
			case ModelTestScreen::CAM_RIGHT:
				//WASDをASDWに
				tmp = keys.front();
				keys.erase(keys.begin());
				keys.push_back(tmp);
				break;
			case ModelTestScreen::CAM_BACK:
				//WASDをSDWAに
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
		//回転モード中のキー移動時の処理
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
				//前、上
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
				else {	//前、下
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
				//前、上
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
				else {	//前、下
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
		//回転モード中のキー移動時の処理
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

//============================ カメラ関連 ============================

//カメラ関連の処理
void ModelTestScreen::RotateCamera() {
	bool moveFlag = false;

	//左クリック中にドラッグで移動する
	if (Input::IsMouseButton(0)) {
		rotSpdY = Input::GetMouseMove().x * AT_RATIO;   //マウスx移動量でy軸回転
		rotSpdX = Input::GetMouseMove().y * AT_RATIO;   //マウスy移動量でx軸回転
		moveFlag = true;
	}
	if (mode != MODE_VIEW) {
		if (rotSpdX != 0 || rotSpdY != 0) {
			prevMode = mode;
			mode = MODE_VIEW;
		}
	}
	//カメラ移動しなかったら速度減少
	if (!moveFlag) {
		//各速度が0でない場合割合減少 一定以下で0にする
		if (rotSpdX != DEFAULT_CAM_SPEED) {
			rotSpdX /= DC_RATIO;
			if (std::abs(rotSpdX) < TH_ZEROSPEED)rotSpdX = DEFAULT_CAM_SPEED;
		}
		if (rotSpdY != DEFAULT_CAM_SPEED) {
			rotSpdY /= DC_RATIO;
			if (std::abs(rotSpdY) < TH_ZEROSPEED)rotSpdY = DEFAULT_CAM_SPEED;
		}
	}

	//回転情報に加算
	camTra.rotate_.y += rotSpdY;
	camTra.rotate_.x += rotSpdX;

	//範囲内処理(直接代入にすると一瞬固まるため加減することで回避)
	camTra.rotate_.x = std::clamp(camTra.rotate_.x, MIN_CAM_ROTATE_X, MAX_CAM_ROTATE_X);
	if (camTra.rotate_.y > LIMIT_CAM_ROTATE_Y) {
		camTra.rotate_.y -= Twice(LIMIT_CAM_ROTATE_Y);
	}
	if (camTra.rotate_.y < -LIMIT_CAM_ROTATE_Y) {
		camTra.rotate_.y += Twice(LIMIT_CAM_ROTATE_Y);
	}

	XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(camTra.rotate_.y));   //Y軸でY回転量分回転させる行列
	XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(camTra.rotate_.x));   //X軸でX回転量分回転させる行列

	//カメラ設定 位置->対象の後方
	XMVECTOR vCam = { 0,0,-CAM_DISTANCE,0 };                  //距離指定
	vCam = XMVector3TransformCoord(vCam, mRotX * mRotY);    //変形:回転
	Camera::SetPosition(vCam);            //セット

	//カメラの回転情報から移動などで判定に使う方位を登録する
	if (Between(camTra.rotate_.y, -45.0f, 45.0f))camDirHN = CAM_FRONT;
	else if (Between(camTra.rotate_.y, 45.0f, 135.0f))camDirHN = CAM_LEFT;
	else if (Between(camTra.rotate_.y, -135.0f, -45.0f))camDirHN = CAM_RIGHT;
	else camDirHN = CAM_BACK;

	if (Between(camTra.rotate_.x, 45.0f, MAX_CAM_ROTATE_X))camDirVT = CAM_TOP;
	else if (Between(camTra.rotate_.x, MIN_CAM_ROTATE_X, -45.0f))camDirVT = CAM_BOTTOM;
	else camDirVT = CAM_MIDDLE;

	/*
	・移動系の処理は対象が0, 0, 0で固定なので書かなくていい
	・対象との距離も今回は変える必要がまったくないので定数化
	*/
}

//============================ 回転モード関連 ============================

void ModelTestScreen::UpdateCubeTransform()
{
	//前回座標、次回座標、回転するキューブの親を中心に指定する
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
	//キューブの親連結を解除
	//キューブ情報の入れ替え
	//キューブインスタンス自体を入れ替え
	//キューブ座標を指定
	// 
	// 改善前まではTransformをキューブの個数分用意して都度座標を指定するものだったが、
	// インスタンスの入れ替え後に再度座標を初期化するほうが容量を食わないのでそちらを採用
	// （多分回転方向によって範囲指定したほうが効率はいい これはキューブサイズが増えるほど効果がある）

	switch (selectData.dir)
	{
	case ROTATE_DIR::ROT_UP:
	case ROTATE_DIR::ROT_DOWN:
		for (int y = 0; y < PIECES; y++) {
			for (int z = 0; z < PIECES; z++) {
				//親を元に戻す
				cube[selectData.rotCol][y][z]->SetParent(groupObject[GROUP_BACK]);

				//キューブデータ入替
				cube[selectData.rotCol][y][z]->SwapData(selectData.dir);

			}
		}
		break;
	case ROTATE_DIR::ROT_LEFT:
	case ROTATE_DIR::ROT_RIGHT:
		for (int x = 0; x < PIECES; x++) {
			for (int z = 0; z < PIECES; z++) {
				//親を元に戻す
				cube[x][selectData.rotCol][z]->SetParent(groupObject[GROUP_BACK]);

				//データ入替
				cube[x][selectData.rotCol][z]->SwapData(selectData.dir);
			}
		}
		break;
	case ROTATE_DIR::ROT_CW:
	case ROTATE_DIR::ROT_CCW:
		for (int x = 0; x < PIECES; x++) {
			for (int y = 0; y < PIECES; y++) {
				//親を元に戻す
				cube[x][y][selectData.rotCol]->SetParent(groupObject[GROUP_BACK]);

				//データ入替
				cube[x][y][selectData.rotCol]->SwapData(selectData.dir);
			}
		}
		break;
	}


	//キューブ配列入替
	SwapCube();

	//キューブ座標指定
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


	bool isCC = In(selectData.dir, { ROTATE_DIR::ROT_DOWN, ROTATE_DIR::ROT_LEFT, ROTATE_DIR::ROT_CW });	//回転軸に対して時計回りかどうか

	//配列入替
	if (isCC) {
		for (int row = PIECES - 1; row >= 0; row--) {
			//入れ替え回数の更新
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
			//入れ替え回数の更新
			SwapCubeModifySwapCount(&swapCount, row, isCC);
		}
	}
}
void ModelTestScreen::SwapCubeModifySwapCount(int* swapCount, int row, bool isCC)
{
	if (!isCC) {									//回転軸に対し反時計の場合
		if (row != Half(PIECES)) {					//一辺の半分(端数切捨)と同等でなければ
			if (row > Half(PIECES))	(*swapCount)++;	//半分より大きければ増加
			else					(*swapCount)--;	//半分より小さければ減少
		}
		else if (IsEven(PIECES))	(*swapCount)++;	//半分と同等で偶数であれば増加
	}
	else {											//回転軸に対し時計の場合
		if (row != Half(PIECES)) {					//一辺の半分(端数切捨)と同等でなければ
			if (row > Half(PIECES))	(*swapCount)--;	//半分より大きければ減少
			else					(*swapCount)++;	//半分より小さければ増加
		}
		else if (IsEven(PIECES))  (*swapCount)--;	//半分と同等で偶数であれば減少
	}
}


//単一キューブ判定
void ModelTestScreen::CheckMarkSingle(XMINT3 pos, SURFACE surface, WinFlag& flag, FILTER filter = NONE)
{
	//斜め判定
	JudgeDiag(pos, surface, flag);
	//縦横奥判定
	JudgeVHD(pos, surface, flag, filter);
}
void ModelTestScreen::CheckMarkSingle(int x, int y, int z, SURFACE surface, WinFlag& flag, FILTER filter = NONE)
{
	CheckMarkSingle(XMINT3(x, y, z), surface, flag, filter);
}

//回転時の判定
void ModelTestScreen::CheckMarkRotate(XMINT3 pos, DIR dir, WinFlag& flag)
{
	/*
	0,0,0をX軸で上下方向に移動した場合
	X位置が固定
	000front 010front 020front
	020top 021top 022top
	002back 012back 022back
	000bottom 001bottom 002bottom
	0,0,0をY軸で左右方向に移動した場合
	Y位置が固定
	000front 100front 200front
	000left 001left 002left
	002back 102back 202back
	200right 201right 202right
	0,0,0をZ軸で時計反時計方向に移動した場合
	Z位置が固定
	000left 010left 020left
	020top 120top 220top
	200right 210right 220right
	000bottom 100bottom 200bottom
	*/
	//それぞれのマスの判定 回転時に移動する12面 同軸は関係性が変わらないため見ない
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

//斜め判定
void ModelTestScreen::JudgeDiag(XMINT3 pos, Cube::SURFACE surface, WinFlag& flag){
//□　　　　上
//□□□□　前右後左
//□　　　　下　　　
	switch (surface)
	{
	case Cube::SURFACE_TOP:     //左下が0,-,0
		//探索座標2軸一致 右上
		if (pos.x == pos.z) {
			flag.Set(CheckMarkD(DIAG_VAR::DIAG_UP, PIECES - 1, DIAG_VAR::DIAG_UP, surface), surface);
		}
		//探索座標2軸交差 右下
		if (PIECES - 1 - pos.x == pos.z) {
			flag.Set(CheckMarkD(DIAG_VAR::DIAG_UP, PIECES - 1, DIAG_VAR::DIAG_DOWN, surface), surface);
		}
		break;
	case Cube::SURFACE_BOTTOM:  //左上が0,-,0
		//探索座標2軸一致 右下
		if (pos.x == pos.z) {
			flag.Set(CheckMarkD(DIAG_VAR::DIAG_UP, 0, DIAG_VAR::DIAG_UP, surface), surface);
		}
		if (PIECES - 1 - pos.x == pos.z) {  //交差条件 右上
			flag.Set(CheckMarkD(DIAG_VAR::DIAG_UP, 0, DIAG_VAR::DIAG_DOWN, surface), surface);
		}
		break;
	case Cube::SURFACE_LEFT:    //右下が-,0,0
		if (pos.y == pos.z) {   //同座標一致条件 右下
			flag.Set(CheckMarkD(0, DIAG_VAR::DIAG_DOWN, DIAG_VAR::DIAG_DOWN, surface), surface);
		}
		if (PIECES - 1 - pos.y == pos.z) {  //交差条件 右上
			flag.Set(CheckMarkD(0, DIAG_VAR::DIAG_UP, DIAG_VAR::DIAG_DOWN, surface), surface);
		}
		break;
	case Cube::SURFACE_RIGHT:   //左下が-,0,0
		if (pos.y == pos.z) {   //同座標一致条件 右上
			flag.Set(CheckMarkD(PIECES - 1, DIAG_VAR::DIAG_UP, DIAG_VAR::DIAG_UP, surface), surface);
		}
		if (PIECES - 1 - pos.y == pos.z) {  //交差条件 右下
			flag.Set(CheckMarkD(PIECES - 1, DIAG_VAR::DIAG_DOWN, DIAG_VAR::DIAG_UP, surface), surface);
		}
		break;
	case Cube::SURFACE_FRONT:   //左下が0,0,-
		if (pos.x == pos.y) {   //同座標一致条件 右上
			flag.Set(CheckMarkD(DIAG_VAR::DIAG_UP, DIAG_VAR::DIAG_UP, 0, surface), surface);
		}
		if (PIECES - 1 - pos.x == pos.y) {  //交差条件 右下
			flag.Set(CheckMarkD(DIAG_VAR::DIAG_UP, DIAG_VAR::DIAG_DOWN, 0, surface), surface);
		}
		break;
	case Cube::SURFACE_BACK:    //右下が0,0,-
		if (pos.x == pos.y) {   //同座標一致条件 右下
			flag.Set(CheckMarkD(DIAG_VAR::DIAG_DOWN, DIAG_VAR::DIAG_DOWN, PIECES - 1, surface), surface);
		}
		if (PIECES - 1 - pos.x == pos.y) {  //交差条件 右上
			flag.Set(CheckMarkD(DIAG_VAR::DIAG_DOWN, DIAG_VAR::DIAG_UP, PIECES - 1, surface), surface);
		}
		break;
	}
}
//縦横奥判定
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
		Debug::Log("2Pのターン", true);
	}
	if (control == CONTROL_2P) {
		nextTurn = CONTROL_1P;

		Debug::Log("1Pのターン", true);
	}
	isIdle = false;
	
	control = nextTurn; //ここで次のターンにする
}

void ModelTestScreen::Judge()
{
	switch (mode)
	{
	case ModelTestScreen::MODE_SET:
		CheckMarkSingle(selectData.GetPos(), selectData.surface, winFlag);	//自身の選択マスのみ判定
		break;
	case ModelTestScreen::MODE_ROTATE:
		CheckMarkRotate(selectData.GetPos(), selectData.dir, winFlag);				//回転した全てのマスを判定
		break;
	}

	//勝利判定
	//両方揃ってたら相手の勝利
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

	Debug::Log("縦横判定", true);
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
		Debug::Log("斜め判定", true);
		checkMarks.push_back(check);
	}
	return CheckMark(checkMarks, surface);
}

Cube::MARK ModelTestScreen::CheckMark(vector<XMINT3> points, SURFACE surface)
{
	/*
	揃ったとき、そのマークを返す
	揃わなければ空白を返す
	※空白で揃っても空白を返す
	*/

	Cube::MARK mark = cube[points[0].x][points[0].y][points[0].z]->GetMark(surface);   //揃ったときに返すマーク
	assert(points.size() > 0);  //手違いで空の配列が来た時にassert

	Debug::Log("判定：["+ std::to_string(points[0].x) + std::to_string(points[0].y) + std::to_string(points[0].z) +"]:" + 
		((std::string)NAMEOF_ENUM(mark)).substr(5) + ", ", false);

	for (int i = 1; i < points.size(); i++) { 

		Debug::Log("[" + std::to_string(points[i].x) + std::to_string(points[i].y) + std::to_string(points[i].z) + "]:" + 
			((std::string)NAMEOF_ENUM(cube[points[i].x][points[i].y][points[i].z]->GetMark(surface))).substr(5) + ", ", false);

		if (cube[points[i].x][points[i].y][points[i].z]->GetMark(surface) != mark) {

			Debug::Log(((std::string)NAMEOF_ENUM(mark)).substr(5) + "はそろわなかった", true);

			return Cube::MARK_BLANK;    //揃わなかったら空白
		}
	}
	Debug::Log(((std::string)NAMEOF_ENUM(mark)).substr(5) + "がそろった", true);
	return mark;
}

//============================ ゲーム終了処理関連 ============================

void ModelTestScreen::WinProcess(CONTROL winner) {

	finished = true;
	//カメラ系初期化
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

	//ボタン初期化
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

	//左クリックで回転させられた場合、フリールックを有効化
	if (Input::IsMouseButton(0)) {
		rotSpdY = Input::GetMouseMove().x * AT_RATIO;   //マウスx移動量でy軸回転
		rotSpdX = Input::GetMouseMove().y * AT_RATIO;   //マウスy移動量でx軸回転
		enFreeLook = true;
		movingCamera = true;
	}

	if (enFreeLook) {
		//カメラ移動しなかったら速度減少
		if (!movingCamera) {
			//各速度が0でない場合割合減少 一定以下で0にする
			if (rotSpdX != DEFAULT_CAM_SPEED) {
				rotSpdX /= DC_RATIO;
				if (std::abs(rotSpdX) < TH_ZEROSPEED)rotSpdX = DEFAULT_CAM_SPEED;
			}
			if (rotSpdY != DEFAULT_CAM_SPEED) {
				rotSpdY /= DC_RATIO;
				if (std::abs(rotSpdY) < TH_ZEROSPEED)rotSpdY = DEFAULT_CAM_SPEED;
			}
		}

		//回転情報に加算
		camTra.rotate_.y += rotSpdY;
		camTra.rotate_.x += rotSpdX;

		//範囲内処理(直接代入にすると一瞬固まるため加減することで回避)
		camTra.rotate_.x = std::clamp(camTra.rotate_.x, MIN_CAM_ROTATE_X, MAX_CAM_ROTATE_X);
		if (camTra.rotate_.y > LIMIT_CAM_ROTATE_Y) {
			camTra.rotate_.y -= Twice(LIMIT_CAM_ROTATE_Y);
		}
		if (camTra.rotate_.y < -LIMIT_CAM_ROTATE_Y) {
			camTra.rotate_.y += Twice(LIMIT_CAM_ROTATE_Y);
		}
	}
	else {
		//0~100 後置
		if (winRotProgress > maxWinRotProgress) {
			enFreeLook = true;
			return;
		}
		camTra.rotate_.x = Easing::Calc(WIN_CAM_EASE, winRotProgress, maxWinRotProgress, winPrevRot.x, winNextRot.x);
		camTra.rotate_.y = Easing::Calc(WIN_CAM_EASE, winRotProgress, maxWinRotProgress, winPrevRot.y, winNextRot.y);
		camTra.rotate_.z = Easing::Calc(WIN_CAM_EASE, winRotProgress, maxWinRotProgress, winPrevRot.z, winNextRot.z);
		winRotProgress++;
	}

	//カメラにセットする
	XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(camTra.rotate_.y));   //Y軸でY回転量分回転させる行列
	XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(camTra.rotate_.x));   //X軸でX回転量分回転させる行列

	//カメラ設定 位置->対象の後方
	XMVECTOR vCam = { 0,0,-CAM_DISTANCE,0 };                  //距離指定
	vCam = XMVector3TransformCoord(vCam, mRotX * mRotY);    //変形:回転
	Camera::SetPosition(vCam);            //セット

}

void ModelTestScreen::Restart()
{
	//各種再初期化
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
回転トリガー時、回転方向と回転列を指定し、回転フラグを有効化
回転フラグが有効化されたら、回転方向と回転列に従い、回転
回転終了後、回転フラグを無効化し、Cubeオブジェクトを入れ替える
*/

/*
ひとえに横判定といっても左右だとz、他はxで判定することになる
縦判定だと前後左右がy、上下がz
斜めだとさらに面倒で、前後はxy、左右はyz、上下はxzである

選択場所によって斜めの判定を入れるかが問題となるが、
上下だとx=0,2かつz=0,2
左右だとy=0,2かつz=0,2
前後だとx=0,2かつy=0,2
で斜めが入る
さらに、右上に上がるか右下に下がるかを求める必要もあり、
上はx,z=0,0 2,2で右上 x,z=0,2 2,0で右下
https://cpprefjp.github.io/lang/cpp11/variadic_templates.html

移動問題
カメラにかかわらない移動
前後左右のWSはY-+、範囲外で上下へSURFACE転換で良い
前のADはX-+、範囲外で左右
右のADはZ-+、範囲外で前後
左のADはZ+-、範囲外で後前
後のADはX+-、範囲外で右左
カメラにかかわる移動
Y軸で変わる移動
上
WSがZ+-、ADがX-+

座標系がなんと
 +
- +
 -
*/