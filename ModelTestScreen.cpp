#include "ModelTestScreen.h"
#include "Engine/Input.h"

#include "SystemConfig.h"
#include "DebugText.h"
#include "./Engine/Camera.h"
#include "Easing.h"
#include "./Engine/Image.h"
#include <algorithm>
#include "CubeSelectIndicator.h"

#include "./Include/nameof.hpp"
#include "./Engine/Debug.h"

//コンストラクタ
ModelTestScreen::ModelTestScreen(GameObject* parent) :
	Screen(parent, "ModelTestScreen"),
	hImgBG(-1),
	mode(MODE_SET),prevMode(MODE_SET),
	control(CONTROL_1P),nextTurn(CONTROL_2P),
	rotSpdX(0),rotSpdY(0),isEnded(false),	//カメラ
	debugtext(nullptr)
{
}

//デストラクタ
ModelTestScreen::~ModelTestScreen(){}

//初期化
void ModelTestScreen::Initialize()
{
	//背景
	hImgBG = Image::Load("Background\\bg_game.png");

	//キューブ本体、キューブ変形情報などを保存するvectorをリサイズ
	cube.resize(PIECES, vector<vector<Cube*>>(PIECES, vector<Cube*>(PIECES, nullptr)));
	cubeNextTra.resize(PIECES, vector<vector<Transform>>(PIECES, vector<Transform>(PIECES)));
	cubePrevTra.resize(PIECES, vector<vector<Transform>>(PIECES, vector<Transform>(PIECES)));

	//キューブ生成
	for (auto& cx : cube) {
		for (auto& cy : cx) {
			for (auto& cz : cy) {
				cz = Instantiate<Cube>(this);
			}
		}
	}

	//キューブ座標指定
	for (int x = 0; x < cube.size();x++) {
		for (int y = 0; y < cube[0].size();y++) {
			for (int z = 0; z < cube[0][0].size();z++) {
				cube[x][y][z]->SetPosition(x - 1, y - 1, z - 1);
				cubeNextTra[x][y][z] = cube[x][y][z]->GetTransform(); //次の場所の初期化
			}
		}
	}

	//インジケーター生成・座標指定
	indicator = Instantiate<CubeSelectIndicator>(this);
	indicator->SetPosition(selectData.x - 1, selectData.y - 1, selectData.z - 1);
	indicator->SetSurface(selectData.surface);

	//デバッグ
	debugtext = Instantiate<DebugText>(this);
	for (int i = 0; i < 20; i++) {
		debugtext->AddStrPtr(&debugStr[i]);
	}
}

//更新
void ModelTestScreen::Update()
{

	RotateCamera();     //カメラの処理 MODE_VIEWでの分岐も内包

	//もどる(デバッグ)
	if (Input::IsKeyDown(DIK_P)) {
		Prev();
	}
	if (Input::IsKeyDown(DIK_0)) {
		if (mode == MODE_SET)mode = MODE_ROTATE;
		else if (mode == MODE_ROTATE)mode = MODE_VIEW;
		else if (mode == MODE_VIEW)mode = MODE_SET;
	}
	if (Input::IsKeyDown(DIK_9)) {
		if (control == CONTROL_IDLE)control = CONTROL_1P;
		else if (control == CONTROL_1P)control = CONTROL_2P;
		else if (control == CONTROL_2P)control = CONTROL_IDLE;
	}
	//操作状態がアイドルでなければ
	if (control != CONTROL_IDLE) {
		//現在のモードで処理
		switch (mode)
		{
		case ModelTestScreen::MODE_SET:
			MoveSelect();
			//キー関連の記述は同時処理を防ぐため取り敢えずすべてelifで書く
			//マーク設置
			if (Input::IsKeyDown(DIK_SPACE)) {
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
			else if (Input::IsKeyDown(DIK_LSHIFT)) {
				mode = MODE_ROTATE;
			}

			break;
		case ModelTestScreen::MODE_ROTATE:
			//回転
			if (Input::IsKeyDown(DIK_SPACE)) {
				//情報を回転する関数
				//RotateCube();?
				Judge();
			}
			else if (Input::IsKeyDown(DIK_LSHIFT)) {	//モード切替
				mode = MODE_SET;
			}
			break;
		case ModelTestScreen::MODE_VIEW:
			if (Input::IsKeyDown(DIK_SPACE)) {
				mode = prevMode;
			}
			break;
		default:
			break;
		}
	}

	//if (!isMoving) {
	//    if (Input::IsKeyDown(DIK_R)) {
	//        transform_.rotate_.z++;
	//    }
	//    //kaiten
	//    int column = 0;
	//    if (Input::IsKeyDown(DIK_LSHIFT)) {
	//        if (Input::IsKey(DIK_LALT))column = 2;
	//        else column = 1;
	//    }
	//    if (Input::IsKeyDown(DIK_Q)) {
	//        RotateCube(CCW, column, 45);
	//    }
	//    if (Input::IsKeyDown(DIK_E)) {
	//        RotateCube(CW, column, 45);
	//    }
	//    if (Input::IsKeyDown(DIK_W)) {
	//        RotateCube(BACK, column, 45);
	//    }
	//    if (Input::IsKeyDown(DIK_S)) {
	//        RotateCube(FRONT, column, 45);
	//    }
	//    if (Input::IsKeyDown(DIK_A)) {
	//        RotateCube(LEFT, column, 45);
	//    }
	//    if (Input::IsKeyDown(DIK_D)) {
	//        RotateCube(RIGHT, column, 45);
	//    }
	//}
	//else {
	//    ModelTestScreen::CalcCubeTrans();
	//}
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

void ModelTestScreen::UpdateStr()
{
	using std::to_string;
	debugStr[0] = "control:" + (std::string)NAMEOF_ENUM(control) + "(Press '9' to change)";
	debugStr[1] = "scrH:" + to_string(SystemConfig::windowHeight) + "scrW:" + to_string(SystemConfig::windowWidth);
	debugStr[2] = "mode:" + (std::string)NAMEOF_ENUM(mode) + "(Press '0' to change)";
	debugStr[3] = "select:" + std::to_string(selectData.x) + "," + std::to_string(selectData.y) + "," + std::to_string(selectData.z) + "," + (std::string)NAMEOF_ENUM(selectData.surface);
	debugStr[4] = "camTra:" + std::to_string(camTra.rotate_.x) + ", " + std::to_string(camTra.rotate_.y);
}

void ModelTestScreen::CalcCubeTrans()
{
	rotTime++;
	if (rotTime >= angleOfRotate) {
		rotTime = 90;
		isMoving = false;
	}
	switch (dir)
	{
	case ModelTestScreen::FRONT:
		for (int y = 0; y < 3; y++) {
			for (int z = 0; z < 3; z++) {
				//座標はそのまま変える
				cube[rotateNo][y][z]->SetPosition(
					Easing::Calc(7, rotTime, angleOfRotate, cubePrevTra[rotateNo][y][z].position_.x, cubeNextTra[rotateNo][y][z].position_.x),
					Easing::Calc(7, rotTime, angleOfRotate, cubePrevTra[rotateNo][y][z].position_.y, cubeNextTra[rotateNo][y][z].position_.y),
					Easing::Calc(7, rotTime, angleOfRotate, cubePrevTra[rotateNo][y][z].position_.z, cubeNextTra[rotateNo][y][z].position_.z)
				);
				cube[rotateNo][y][z]->SetRotate(
					Easing::Calc(1, rotTime, angleOfRotate, cubePrevTra[rotateNo][y][z].rotate_.x, cubeNextTra[rotateNo][y][z].rotate_.x),
					Easing::Calc(1, rotTime, angleOfRotate, cubePrevTra[rotateNo][y][z].rotate_.y, cubeNextTra[rotateNo][y][z].rotate_.y),
					Easing::Calc(1, rotTime, angleOfRotate, cubePrevTra[rotateNo][y][z].rotate_.z, cubeNextTra[rotateNo][y][z].rotate_.z)
				);
			}
		}
	case ModelTestScreen::BACK:
		break;
	case ModelTestScreen::LEFT:
		break;
	case ModelTestScreen::RIGHT:
		break;
	case ModelTestScreen::CW:
		break;
	case ModelTestScreen::CCW:
		break;
	default:
		break;
	}
	if (isMoving == false) {
		rotTime = 0;

		switch (dir)
		{
		case ModelTestScreen::FRONT:
			//配列の入れ替えを行い、タイルの方向も変える
			//rotateは0に戻す
			//positionも入れ替え後の座標にする これは最後に座標がその位置へ向かうため配列番号の移動のみで済む
			//→rotateを0にしてから、配列を入れ替える
			//std::rotateM
			break;
		case ModelTestScreen::BACK:
			break;
		case ModelTestScreen::LEFT:
			break;
		case ModelTestScreen::RIGHT:
			break;
		case ModelTestScreen::CW:
			break;
		case ModelTestScreen::CCW:
			break;
		default:
			break;
		}
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
	indicator->SetPosition(selectData.x - 1, selectData.y - 1, selectData.z - 1);
	indicator->SetSurface(selectData.surface);
}
void ModelTestScreen::MoveSelect()
{
	using SURFACE = Cube::SURFACE;
	vector<int> keys = { DIK_W,DIK_A,DIK_S,DIK_D };

	switch (selectData.surface)
	{
	case SURFACE::SURFACE_TOP:
		if (Between(camTra.rotate_.y, -45.0f, 45.0f)) {}
		else if (Between(camTra.rotate_.y, 45.0f, 135.0f)) {
			//WASDをASDWに
			int tmp = keys.front();
			keys.erase(keys.begin());
			keys.push_back(tmp);
		}
		else if (Between(camTra.rotate_.y, -135.0f, -45.0f)) {
			//WASDをDWASに
			int tmp = keys.back();
			keys.pop_back();
			keys.insert(keys.begin(), tmp);
		}
		else {
			//WASDをSDWAに
			for (int i = 0; i < 2; i++) {
				int tmp = keys.back();
				keys.pop_back();
				keys.insert(keys.begin(), tmp);
			}
		}
		if (Input::IsKeyDown(keys[0]))  MoveSelectParts(Z, true, SURFACE::SURFACE_BACK);
		if (Input::IsKeyDown(keys[1]))  MoveSelectParts(X, false, SURFACE::SURFACE_LEFT);
		if (Input::IsKeyDown(keys[2]))  MoveSelectParts(Z, false, SURFACE::SURFACE_FRONT);
		if (Input::IsKeyDown(keys[3]))  MoveSelectParts(X, true, SURFACE::SURFACE_RIGHT);
		break;
	case SURFACE::SURFACE_BOTTOM:
		if (Between(camTra.rotate_.y, -45.0f, 45.0f)) {}
		else if (Between(camTra.rotate_.y, 45.0f, 135.0f)) {
			//WASDをDWASに
			int tmp = keys.back();
			keys.pop_back();
			keys.insert(keys.begin(), tmp);
		}
		else if (Between(camTra.rotate_.y, -135.0f, -45.0f)) {
			//WASDをASDWに
			int tmp = keys.front();
			keys.erase(keys.begin());
			keys.push_back(tmp);
		}
		else {
			//WASDをSDWAに
			for (int i = 0; i < 2; i++) {
				int tmp = keys.back();
				keys.pop_back();
				keys.insert(keys.begin(), tmp);
			}
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

}

void ModelTestScreen::MoveIndicator()
{
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
	case ModelTestScreen::FRONT:
	case ModelTestScreen::BACK:
		CheckMarkRotate(pos, DIR::X, flag);
	case ModelTestScreen::LEFT:
	case ModelTestScreen::RIGHT:
		CheckMarkRotate(pos, DIR::Y, flag);
	case ModelTestScreen::CW:
	case ModelTestScreen::CCW:
		CheckMarkRotate(pos, DIR::Z, flag);
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
			flag.Set(CheckMarkD(DIAG_VAR::UP, PIECES - 1, DIAG_VAR::UP, surface));
		}
		//探索座標2軸交差 右下
		if (PIECES - 1 - pos.x == pos.z) {
			flag.Set(CheckMarkD(DIAG_VAR::UP, PIECES - 1, DIAG_VAR::DOWN, surface));
		}
		break;
	case Cube::SURFACE_BOTTOM:  //左上が0,-,0
		//探索座標2軸一致 右下
		if (pos.x == pos.z) {
			flag.Set(CheckMarkD(DIAG_VAR::UP, 0, DIAG_VAR::UP, surface));
		}
		if (PIECES - 1 - pos.x == pos.z) {  //交差条件 右上
			flag.Set(CheckMarkD(DIAG_VAR::UP, 0, DIAG_VAR::DOWN, surface));
		}
		break;
	case Cube::SURFACE_LEFT:    //右下が-,0,0
		if (pos.y == pos.z) {   //同座標一致条件 右下
			flag.Set(CheckMarkD(0, DIAG_VAR::DOWN, DIAG_VAR::DOWN, surface));
		}
		if (PIECES - 1 - pos.y == pos.z) {  //交差条件 右上
			flag.Set(CheckMarkD(0, DIAG_VAR::UP, DIAG_VAR::DOWN, surface));
		}
		break;
	case Cube::SURFACE_RIGHT:   //左下が-,0,0
		if (pos.y == pos.z) {   //同座標一致条件 右上
			flag.Set(CheckMarkD(PIECES - 1, DIAG_VAR::UP, DIAG_VAR::UP, surface));
		}
		if (PIECES - 1 - pos.y == pos.z) {  //交差条件 右下
			flag.Set(CheckMarkD(PIECES - 1, DIAG_VAR::DOWN, DIAG_VAR::UP, surface));
		}
		break;
	case Cube::SURFACE_FRONT:   //左下が0,0,-
		if (pos.x == pos.y) {   //同座標一致条件 右上
			flag.Set(CheckMarkD(DIAG_VAR::UP, DIAG_VAR::UP, 0, surface));
		}
		if (PIECES - 1 - pos.x == pos.y) {  //交差条件 右下
			flag.Set(CheckMarkD(DIAG_VAR::UP, DIAG_VAR::DOWN, 0, surface));
		}
		break;
	case Cube::SURFACE_BACK:    //右下が0,0,-
		if (pos.x == pos.y) {   //同座標一致条件 右下
			flag.Set(CheckMarkD(DIAG_VAR::DOWN, DIAG_VAR::DOWN, PIECES - 1, surface));
		}
		if (PIECES - 1 - pos.x == pos.y) {  //交差条件 右上
			flag.Set(CheckMarkD(DIAG_VAR::DOWN, DIAG_VAR::UP, PIECES - 1, surface));
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
		if (filter != DISABLE_VERTICAL_SEARCH)  flag.Set(CheckMarkVH(pos, surface, X));
		if (filter != DISABLE_HORIZONTAL_SEARCH)flag.Set(CheckMarkVH(pos, surface, Y));
	case Cube::SURFACE::SURFACE_LEFT:
	case Cube::SURFACE::SURFACE_RIGHT:
		if (filter != DISABLE_HORIZONTAL_SEARCH)flag.Set(CheckMarkVH(pos, surface, Y));
		if (filter != DISABLE_DEPTH_SEARCH)     flag.Set(CheckMarkVH(pos, surface, Z));
		break;
	case Cube::SURFACE::SURFACE_TOP:
	case Cube::SURFACE::SURFACE_BOTTOM:
		if (filter != DISABLE_VERTICAL_SEARCH)  flag.Set(CheckMarkVH(pos, surface, X));
		if (filter != DISABLE_DEPTH_SEARCH)     flag.Set(CheckMarkVH(pos, surface, Z));
		break;
	}
}


void ModelTestScreen::RotateCube(ROTATE_DIR rot, int col, float value)
{
	rotateNo = col;
	dir = rot;
	//フラグ管理
	isMoving = true;    //移動中フラグ

	//次の座標指定 回転は一時的なのでしない、移動後にキューブ情報を更新する=変形後のタイル情報 これもここで指定していいかも(とりあえず未実装)
	switch (rot)
	{
	case ModelTestScreen::FRONT:
		for (int y = 0; y < 3; y++) {
			for (int z = 0; z < 3; z++) {
				cubePrevTra[col][y][z].position_ = cube[col][y][z]->GetPosition();
				//cubePrevTra[col][y][z].position_ = cubeNextTra[col][y][z].position_;    //こっちのほうが都合がいいかも？
				cubeNextTra[col][y][z].position_ = { (float)col - 1,(float)-(z - 1),(float)y - 1 };
				cube[col][y][z]->SetPosition({ (float)col-1,(float)-(z - 1),(float)y - 1 });
				cube[col][y][z]->SetRotate({ value,0,0 });
				
			}
		}
		//cube[col][1][1]->SetRotate(value, 0, 0);
		break;
	case ModelTestScreen::BACK:
		break;
	case ModelTestScreen::LEFT:
		break;
	case ModelTestScreen::RIGHT:
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				if (x == 1 && y == 1)break;
				cube[x][y][0]->SetParent(cube[1][1][col]);
				//cube[col][y][z]->SetParent(cube[col][1][1]);
			}
		}
		cube[1][1][col]->SetRotate(0, 0, value);

		break;
	case ModelTestScreen::CW:
		break;
	case ModelTestScreen::CCW:
		break;
	default:
		break;
	}
}

void ModelTestScreen::TurnEnd()
{
	if (control == CONTROL_1P) {
		nextTurn = CONTROL_2P;
	}
	if (control == CONTROL_2P) {
		nextTurn = CONTROL_1P;
	}
	control = CONTROL_IDLE;
	
	control = nextTurn; //今はアニメーションやディレイが無いのでここで次のターンにする
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

	auto win = [=](CONTROL control) {
		switch (control)
		{
		case ModelTestScreen::CONTROL_1P:
			debugStr[5] = "1p syouri";
			break;
		case ModelTestScreen::CONTROL_2P:
			debugStr[5] = "2p syouri";
			break;
		default:
			break;
		}
	};

	//勝利判定
	//両方揃ってたら相手の勝利
	if (control == CONTROL_1P) {
		if (winFlag.p2) {
			win(CONTROL_2P);
		}
		else if (winFlag.p1) {
			win(CONTROL_1P);
		}
	}
	if (control == CONTROL_2P) {
		if (winFlag.p1) {
			win(CONTROL_1P);
		}
		else if (winFlag.p2) {
			win(CONTROL_2P);
		}
	}
}

void ModelTestScreen::RotateCamera() {
	//カメラ(後々実装：デバッグ)

	bool moveFlag = false;
	//ビューモードの場合、移動を許可
	if (mode == MODE_VIEW) {
		//左クリック中にドラッグで移動する(仮)
		if (Input::IsMouseButton(0)) {
			rotSpdY = Input::GetMouseMove().x * AT_RATIO;   //マウスx移動量でy軸回転
			rotSpdX = Input::GetMouseMove().y * AT_RATIO;   //マウスy移動量でx軸回転
			moveFlag = true;
		}
	}

	//カメラ移動しなかったら速度減少
	if (!moveFlag) {
		//各速度が0でない場合割合減少 一定以下で0にする
		if (rotSpdX != DEFAULT_SPEED) {
			rotSpdX /= DC_RATIO;
			if (std::abs(rotSpdX) < TH_ZEROSPEED)rotSpdX = DEFAULT_SPEED;
		}
		if (rotSpdY != DEFAULT_SPEED) {
			rotSpdY /= DC_RATIO;
			if (std::abs(rotSpdY) < TH_ZEROSPEED)rotSpdY = DEFAULT_SPEED;
		}
	}
	//固定値減少 過去のカメラの対象の滑らかな移動をするコードから流用したがカメラ回転だと思った挙動にならないため没
	//if (rotSpdX > 0) {
	//    rotSpdX -= decSpd;
	//    if (rotSpdX < 0)rotSpdX = 0;
	//}
	//else if (rotSpdX < 0) {
	//    rotSpdX += decSpd;
	//    if (rotSpdX > 0)rotSpdX = 0;
	//}
	//if (rotSpdY > 0) {
	//    rotSpdY -= decSpd;
	//    if (rotSpdY < 0)rotSpdY = 0;
	//}
	//else if (rotSpdY < 0) {
	//    rotSpdY += decSpd;
	//    if (rotSpdY > 0)rotSpdY = 0;
	//}

	//回転情報に加算
	camTra.rotate_.y += rotSpdY;
	camTra.rotate_.x += rotSpdX;

	//範囲内処理(直接代入にすると一瞬固まるため加減する)
	camTra.rotate_.x = std::clamp(camTra.rotate_.x, MIN_CAM_ROTATE_X, MAX_CAM_ROTATE_X);
	if (camTra.rotate_.y > LIMIT_CAM_ROTATE_Y) {
		camTra.rotate_.y -= 2 * LIMIT_CAM_ROTATE_Y;
	}
	if (camTra.rotate_.y < -LIMIT_CAM_ROTATE_Y) {
		camTra.rotate_.y += 2 * LIMIT_CAM_ROTATE_Y;
	}

	XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(camTra.rotate_.y));   //Y軸でY回転量分回転させる行列
	XMMATRIX mRotX = XMMatrixRotationX(XMConvertToRadians(camTra.rotate_.x));   //X軸でX回転量分回転させる行列

	//カメラ設定 位置->対象の後方
	XMVECTOR vCam = { 0,0,-CAM_DISTANCE,0 };                  //距離指定
	vCam = XMVector3TransformCoord(vCam, mRotX * mRotY);    //変形:回転
	Camera::SetPosition(vCam);            //セット

	/*
	・移動系は対象が0, 0, 0で固定なので書かなくていい
	・対象との距離も今回は変える必要がまったくないので実装しない
	*/
}

void ModelTestScreen::FinishCamera()
{
	//doonce作ってカメラ回転さしたいね
	Transform toTra;
	//toTra.rotate_.x 
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
			if (x == DIAG_VAR::UP)check.x = i;
			if (x == DIAG_VAR::DOWN)check.x = PIECES - 1 - i;
		}
		else {
			check.x = x;
		}
		if (y < 0) {
			if (y == DIAG_VAR::UP)check.y = i;
			if (y == DIAG_VAR::DOWN)check.y = PIECES - 1 - i;
		}
		else {
			check.y = y;
		}
		if (z < 0) {
			if (z == DIAG_VAR::UP)check.z = i;
			if (z == DIAG_VAR::DOWN)check.z = PIECES - 1 - i;
		}
		else {
			check.z = z;
		}
		checkMarks.push_back(check);
	}
	return CheckMark(checkMarks, surface);
}

Cube::MARK ModelTestScreen::CheckMark(vector<XMINT3> points, SURFACE surface)
{
	/*
	揃ったとき、そのマークを返す
	揃わなければ空白を返す
	空白で揃っても空白を返す
	*/

	Cube::MARK mark = cube[points[0].x][points[0].y][points[0].z]->GetMark(surface);   //揃ったときに返すマーク
	assert(points.size() > 0);  //手違いで空の配列が来た時にassert
	Debug::Log("判定：["+ std::to_string(points[0].x) + std::to_string(points[0].y) + std::to_string(points[0].z) +"]:" + (std::string)NAMEOF_ENUM(mark) +", ", false);
	for (int i = 1; i < points.size(); i++) { 
		Debug::Log("[" + std::to_string(points[i].x) + std::to_string(points[i].y) + std::to_string(points[i].z) + "]:" + (std::string)NAMEOF_ENUM(cube[points[i].x][points[i].y][points[i].z]->GetMark(surface)) + ", ", false);
		if (cube[points[i].x][points[i].y][points[i].z]->GetMark(surface) != mark) {
			Debug::Log((std::string)NAMEOF_ENUM(mark) + "はそろわなかった", true);
			return Cube::MARK_BLANK;    //揃わなかったら空白
		}
	}
	Debug::Log((std::string)NAMEOF_ENUM(mark) + "がそろった", true);
	return mark;
}

/*
回転トリガー時、回転方向と回転列を指定し、回転フラグを有効化
回転フラグが有効化されたら、回転方向と回転列に従い、回転　　      ※回転には回転前変形情報と回転後変形情報を用いる
回転終了後、回転フラグを無効化し、Cubeオブジェクトを入れ替える
*/

/*
3x3の2→0方向への回転(前(下)、右、反時計)
	vector<vector<int>> arr;
	arr.resize(3, vector<int>(3));

	for (int i = 0; i < 3; i++) {
		swap(arr[2-i][0], arr[0][i]);
	}

	for (int i = 1; i < 3; i++) {
		swap(arr[0][i], arr[3-1][i]);
	}

	swap(arr[0][1], arr[1][2]);

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