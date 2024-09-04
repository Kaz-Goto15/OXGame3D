#include "Frame.h"
#include "Engine/Image.h"

#include "SystemConfig.h"
#include "DebugText.h"
#include "Engine/Input.h"

//コンストラクタ
Frame::Frame(GameObject* parent):
    GameObject(parent, "Frame"),
    mode_(AUTO_ASPECT),
    filePath_("Screen/frame256_2.png"),grid_(64),
    hImgFrame_(-1),
    mUp(0),mRight(0),mDown(0),mLeft(0),
    sWidth(0),sHeight(0)
{
}

//デストラクタ
Frame::~Frame()
{
}

//初期化
void Frame::Initialize()
{
    Init();
    debugText = Instantiate<DebugText>(this);
    debugText->AddStrPtr(&debStr);
    debugText->AddStrPtr(&debStr2);
    debugText->AddStrPtr(&debStr3);
    debugText->AddStrPtr(&debStr4);
    hPt = Image::Load("circle.png");
}

//更新
void Frame::Update()
{
    if (Input::IsKey(DIK_W))transform_.position_.y--;
    if (Input::IsKey(DIK_S))transform_.position_.y++;
    if (Input::IsKey(DIK_A))transform_.position_.x--;
    if (Input::IsKey(DIK_D))transform_.position_.x++;

    if (SystemConfig::IsResized()) {
        //UpdateDrawData();
    }

}

//描画
void Frame::Draw()
{
    debStr = "(" + std::to_string((int)transform_.position_.x) + "," + std::to_string((int)transform_.position_.y) + ")";
    debStr2 = "(" + std::to_string(SystemConfig::windowWidth) +","+ std::to_string(SystemConfig::windowHeight) + ")";
    debStr3 = "mLeft(" + std::to_string(mLeft) +
        ") + Half(-windowWidth" + std::to_string(SystemConfig::windowWidth) +
        " + grid_(" + std::to_string(grid_) +
        ")(" + std::to_string(Half(-SystemConfig::windowWidth + grid_)) + ") = " + std::to_string(mLeft + Half(-SystemConfig::windowWidth + grid_));
    debStr4 = "mousePos:(" + std::to_string((int)Input::GetMousePosition(true).x) + ", " + std::to_string((int)Input::GetMousePosition(true).y) + ")";
    Image::SetTransform(hPt, transform_);
    Image::Draw(hPt);
    //描画
    for (int h = FRAME_H::H_TOP; h < FRAME_H::H_MAX; h++) {
        for (int w = FRAME_W::W_LEFT; w < FRAME_W::W_MAX; w++) {
            Image::SetRect(hImgFrame_, w * grid_, h * grid_, grid_, grid_);
            Image::SetTransform(hImgFrame_, tra[h][w]);
            Image::Draw(hImgFrame_);
        }
    }
}

//開放
void Frame::Release()
{
}

void Frame::ChangeTheme(std::string _filePath, int _grid)
{
    filePath_ = _filePath;
    grid_ = _grid;
    Init();
}

void Frame::ChangeMode(MODE _mode, int value1, int value2, int value3, int value4)
{
    mode_ = _mode;

    switch (_mode)
    {
    case Frame::AUTO_ASPECT:
        ChangeMode(_mode, (float)value1, (float)value2);
        return;

    case Frame::CONST_MARGIN:
        mUp = value1;
        mRight = value2;
        mDown = value3;
        mLeft = value4;
        break;

    case Frame::CONST_SIZE:
        sWidth = value1;
        sHeight = value2;
        break;
    }

    UpdateDrawData();
}

void Frame::ChangeMode(MODE _mode, float xRatio, float yRatio)
{
    mode_ = _mode;

    switch (_mode)
    {
    case Frame::AUTO_ASPECT:
        transform_.scale_.x = xRatio;
        transform_.scale_.y = yRatio;
        break;

    case Frame::CONST_MARGIN:
    case Frame::CONST_SIZE:
        ChangeMode(_mode, (int)xRatio, (int)yRatio);
        return;
    }

    UpdateDrawData();
}

void Frame::Init()
{
    hImgFrame_ = Image::Load(filePath_);
    UpdateDrawData();
}

void Frame::UpdateDrawData()
{
    const int DEFAULT_SCALE = 1;
    const int DEFAULT_POSITION_X = 0;
    const int DEFAULT_POSITION_Y = 0;

    switch (mode_)
    {
    case Frame::AUTO_ASPECT:
        break;
    case Frame::CONST_MARGIN:
        //Image::SetRect(hFrameImg_, 0, 0, edge, edge);
        using namespace SystemConfig;

        //frame構築
        for (int y = FRAME_H::H_TOP; y < FRAME_H::H_MAX; y++) {

            for (int x = FRAME_W::W_LEFT; x < FRAME_W::W_MAX; x++) {
                switch (y) {
                case FRAME_H::H_TOP:
                    tra[y][x].position_.y = Half(-windowHeight + (mUp + grid_));
                    tra[y][x].scale_.y = DEFAULT_SCALE;
                    break;
                case FRAME_H::H_CENTER:
                    tra[y][x].position_.y = DEFAULT_POSITION_Y;
                    tra[y][x].scale_.y = (float)(windowHeight - (mUp + mDown + grid_ + grid_)) / (float)grid_;
                    break;
                case FRAME_H::H_BOTTOM:
                    tra[y][x].position_.y = Half(windowHeight - (mDown + grid_));
                    tra[y][x].scale_.y = DEFAULT_SCALE;
                    break;
                }

                switch (x) {
                case FRAME_W::W_LEFT:
                    tra[y][x].position_.x = mLeft + Half(-windowWidth + grid_);
                    tra[y][x].scale_.x = DEFAULT_SCALE;
                    break;
                case FRAME_W::W_CENTER:
                    tra[y][x].position_.x = Half(mLeft + mRight);
                    tra[y][x].scale_.x = (float)(windowWidth - (mRight + mLeft + grid_ + grid_)) / (float)grid_;
                    break;
                case FRAME_W::W_RIGHT:
                    tra[y][x].position_.x = -mRight + Half(windowWidth - grid_);
                    tra[y][x].scale_.x = DEFAULT_SCALE;
                    break;
                }
                //Image::SetRect(hFrameImg_, x * edge, y * edge, edge, edge);

                tra[y][x].SetReSize(transform_.scale_);
            }
        }
        break;
        /*
        左右X=1 上下Y=1
        左：-640+30+32画面横幅/2-左右余白
        
        positionの挙動がキモい サイズ変更しても1280(/2)x720(/2)の範囲内でしか画面に写らない

        マウスポインタやただの変数、はどちらかといえば画面サイズに依存しない挙動をする
        ボタンクラスの範囲判定はマウス座標をコンバートして実現している
        Transformクラスほかメディアオブジェクトは画面サイズ変更により自動で変形する ただし元の変形情報は全く変化しない

        的確に表すなら1280pで編集してたやつをフレームバッファでn倍しているような感じ 画質変わらないんだからキモ
        大体のエンジンが設計上の仕様として割り切ってる部分だけども 映像出身者には引き延ばしする仕様は嫌われますよ...
width/2=640
+mLeft + 64/2

1280x720
grid=64
mL=50
配置=640-64-25=551

640x360
AviUtl等での本来の配置座標=320-64-25=231
このままでは1280x720上での231を参照するため、割合参照する必要がある
単純に640x360では2倍かかるので つまり？知らん
        */

    case Frame::CONST_SIZE:

        break;
    default:
        break;
    }
}
