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
//コンストラクタ
ModelTestScreen::ModelTestScreen(GameObject* parent) :
    Screen(parent, "ModelTestScreen"),
    hModel(-1),
    debugtext(nullptr)
{
}

//デストラクタ
ModelTestScreen::~ModelTestScreen()
{
}

//初期化
void ModelTestScreen::Initialize()
{
    hImgBG = Image::Load("Background\\bg_game.png");
    cube.resize(3, vector<vector<Cube*>>(3, vector<Cube*>(3, nullptr)));
    cubeNextTra.resize(3, vector<vector<Transform>>(3, vector<Transform>(3)));
    cubePrevTra.resize(3, vector<vector<Transform>>(3, vector<Transform>(3)));

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
    mode = MODE_VIEW;   //debug

    RotateCamera();     //カメラの処理 MODE_VIEWでの分岐も内包
    MoveSelect();

    //もどる(デバッグ)
    if (Input::IsKeyDown(DIK_P)) {
        Prev();
    }
    //操作状態がアイドルでなければ
    if (control != CONTROL_IDLE) {
        //現在のモードで処理
        switch (mode)
        {
        case ModelTestScreen::MODE_SET:
            //キー関連の記述は同時処理を防ぐため取り敢えずすべてelifで書く
            //マーク設置
            if (Input::IsKeyDown(DIK_SPACE)) {
                //選択箇所が空白のときに設置する
                if (cube[selectData.x][selectData.y][selectData.x]->GetMark(selectData.surface) == Cube::MARK_BLANK) {
                    Cube::MARK mark;

                    if (control == CONTROL_1P) {
                        mark = Cube::MARK::MARK_O;
                    }
                    else {
                        mark = Cube::MARK::MARK_X;
                    }

                    cube[selectData.x][selectData.y][selectData.x]->SetMark(selectData.surface, mark);
                    TurnEnd();
                }
                else {
                    //空白でないときのアニメーションがあればここに書く 選択を表す半透明モデルをずらすなど
                }
            }
            else if (Input::IsKeyDown(DIK_LSHIFT)) {
                mode = MODE_ROTATE;
            }
            else if (Input::IsKeyDown(DIK_W)) {
                using SURFACE = Cube::SURFACE;

                selectData.y--;
                if (selectData.y == -1) {

                }
                //全てy-1になるときである
                //前で上に行くとき：上に
                //上で上に行くとき：後に
                //後で上に行くとき：下に
                //下で上に行くとき：前に
                //左で上に行くとき：上に
                //右で上に行くとき：上に
            }
            break;
        case ModelTestScreen::MODE_ROTATE:
            break;
        case ModelTestScreen::MODE_VIEW:
            break;
        default:
            break;
        }
    }

    if (!isMoving) {
        if (Input::IsKeyDown(DIK_R)) {
            transform_.rotate_.z++;
        }
        //kaiten
        int column = 0;
        if (Input::IsKeyDown(DIK_LSHIFT)) {
            if (Input::IsKey(DIK_LALT))column = 2;
            else column = 1;
        }
        if (Input::IsKeyDown(DIK_Q)) {
            RotateCube(CCW, column, 45);
        }
        if (Input::IsKeyDown(DIK_E)) {
            RotateCube(CW, column, 45);
        }
        if (Input::IsKeyDown(DIK_W)) {
            RotateCube(BACK, column, 45);
        }
        if (Input::IsKeyDown(DIK_S)) {
            RotateCube(FRONT, column, 45);
        }
        if (Input::IsKeyDown(DIK_A)) {
            RotateCube(LEFT, column, 45);
        }
        if (Input::IsKeyDown(DIK_D)) {
            RotateCube(RIGHT, column, 45);
        }
    }
    else {
        ModelTestScreen::CalcCubeTrans();
    }
    UpdateStr();
}

void ModelTestScreen::UpdateStr()
{
    using std::to_string;
    debugStr[0] = "scrH:" + to_string(SystemConfig::windowHeight) + "scrW:" + to_string(SystemConfig::windowWidth);
    debugStr[1] = "mode:" + (std::string)NAMEOF_ENUM(mode);
    debugStr[2] = "select:" + std::to_string(selectData.x) + "," + std::to_string(selectData.y) + "," + std::to_string(selectData.z) + "," + (std::string)NAMEOF_ENUM(selectData.surface);
    debugStr[3] = "camTra:" + std::to_string(camTra.rotate_.x) + ", " + std::to_string(camTra.rotate_.y);
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

    if (plus) {
        *target+= 1;
        if (*target >= PIECES) {
            *target = PIECES - 1;
            selectData.surface = outSurface;
        }
    }
    else {
        *target-= 1;
        if (*target < 0) {
            *target = 0;
            selectData.surface = outSurface;
        }
    }
    indicator->SetPosition(selectData.x - 1, selectData.y - 1, selectData.z - 1);
    indicator->SetSurface(selectData.surface);
}
void ModelTestScreen::MoveSelect()
{
    using SURFACE = Cube::SURFACE;
    vector<int> keys = {DIK_W,DIK_A,DIK_S,DIK_D};

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
        if (Input::IsKeyDown(DIK_A))    MoveSelectParts(Z, true,  SURFACE::SURFACE_BACK);
        if (Input::IsKeyDown(DIK_D))    MoveSelectParts(Z, false, SURFACE::SURFACE_FRONT);
        if (Input::IsKeyDown(DIK_W))    MoveSelectParts(Y, true,  SURFACE::SURFACE_TOP);
        if (Input::IsKeyDown(DIK_S))    MoveSelectParts(Y, false,  SURFACE::SURFACE_BOTTOM);
        break;
    case SURFACE::SURFACE_RIGHT:
        if (Input::IsKeyDown(DIK_A))    MoveSelectParts(Z, false, SURFACE::SURFACE_FRONT);
        if (Input::IsKeyDown(DIK_D))    MoveSelectParts(Z, true,  SURFACE::SURFACE_BACK);
        if (Input::IsKeyDown(DIK_W))    MoveSelectParts(Y, true,  SURFACE::SURFACE_TOP);
        if (Input::IsKeyDown(DIK_S))    MoveSelectParts(Y, false,  SURFACE::SURFACE_BOTTOM);
        break;
    case SURFACE::SURFACE_FRONT:
        if (Input::IsKeyDown(DIK_A))    MoveSelectParts(X, false, SURFACE::SURFACE_LEFT);
        if (Input::IsKeyDown(DIK_D))    MoveSelectParts(X, true,  SURFACE::SURFACE_RIGHT);
        if (Input::IsKeyDown(DIK_W))    MoveSelectParts(Y, true,  SURFACE::SURFACE_TOP);
        if (Input::IsKeyDown(DIK_S))    MoveSelectParts(Y, false, SURFACE::SURFACE_BOTTOM);
        break;
    case SURFACE::SURFACE_BACK:
        if (Input::IsKeyDown(DIK_A))    MoveSelectParts(X, true,  SURFACE::SURFACE_RIGHT);
        if (Input::IsKeyDown(DIK_D))    MoveSelectParts(X, false, SURFACE::SURFACE_LEFT);
        if (Input::IsKeyDown(DIK_W))    MoveSelectParts(Y, true,  SURFACE::SURFACE_TOP);
        if (Input::IsKeyDown(DIK_S))    MoveSelectParts(Y, false, SURFACE::SURFACE_BOTTOM);
        break;
    }

}

void ModelTestScreen::MoveIndicator()
{
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
    if (mode == MODE_SET) {
        switch (selectData.surface)
        {
        case Cube::SURFACE::SURFACE_TOP:
            //cube[selectData.x]
        default:
            break;
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

    //範囲内処理(y軸は制限ないが∞に回転されて値あふれても困るのでコンバート 直接代入にすると一瞬固まるため加減する)
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
//bool Yoko() {
//    if()
//    return true;
//}
//bool Tate();
//bool Naname() { return true; }
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