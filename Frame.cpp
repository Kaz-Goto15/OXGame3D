#include "Frame.h"
#include "Engine/Image.h"

#include "SystemConfig.h"

//コンストラクタ
Frame::Frame(GameObject* parent):
    GameObject(parent, "Frame"),
    hFrameImg_(-1),
    fileName("Screen/frame256_2.png"),
    grid(64)
{
}

//デストラクタ
Frame::~Frame()
{
}

//初期化
void Frame::Initialize()
{
     hFrameImg_ = Image::Load(fileName);
}

//更新
void Frame::Update()
{Instantiate
}

//描画
void Frame::Draw()
{
    for (int h = FRAME_H::H_TOP; h < FRAME_H::H_MAX; h++) {
        for (int w = FRAME_W::W_LEFT; w < FRAME_W::W_MAX; w++) {
            Image::SetRect(hFrameImg_, w * edge, h * edge, edge, edge);
            Image::SetTransform(hFrameImg_, tra[h][w]);
            Image::Draw(hFrameImg_);
        }
    }
}

//開放
void Frame::Release()
{
}

void Frame::ChangeTheme(std::string _filePath, int _grid)
{
    filePath = _filePath;
    grid = _grid;
    hImgFrame = Image::Load(filePath);
}

void Frame::ChangeMode(MODE _mode, int value1, int value2, int value3, int value4)
{
    switch (_mode)
    {
    case Frame::AUTO_ASPECT:
        ChangeMode(_mode, value1, value2);
        break;
    case Frame::CONST_MARGIN:
    case Frame::CONST_SIZE:
        uptop
        break;
    default:
        break;
    }
}

void Frame::TransformFrame(int up, int right, int down, int left)
{
    //Image::SetRect(hFrameImg_, 0, 0, edge, edge);
    const int DEFAULT_SCALE = 1;
    const int DEFAULT_POSITION_X = 0;
    const int DEFAULT_POSITION_Y = 0;
    using namespace SystemConfig;
    //frame構築
    for (int y = FRAME_H::H_TOP; y < FRAME_H::H_MAX; y++) {
        for (int x = FRAME_W::W_LEFT; x < FRAME_W::W_MAX; x++) {
            switch (y) {
            case FRAME_H::H_TOP:
                tra[y][x].position_.y = Half(-windowHeight + (up + down + edge));
                tra[y][x].scale_.y = DEFAULT_SCALE;
                break;
            case FRAME_H::H_CENTER:
                tra[y][x].position_.y = DEFAULT_POSITION_Y;
                tra[y][x].scale_.y = (float)(windowHeight - (up + down + edge + edge)) / (float)edge;
                break;
            case FRAME_H::H_BOTTOM:
                tra[y][x].position_.y = Half(windowHeight - (up + down + edge));
                tra[y][x].scale_.y = DEFAULT_SCALE;
                break;
            }

            switch (x) {
            case FRAME_W::W_LEFT:
                tra[y][x].position_.x = Half(-windowWidth + (right + left + edge));
                tra[y][x].scale_.x = DEFAULT_SCALE;
                break;
            case FRAME_W::W_CENTER:
                tra[y][x].position_.x = DEFAULT_POSITION_X;
                tra[y][x].scale_.x = (float)(windowWidth - (right + left + edge + edge)) / (float)edge;
                break;
            case FRAME_W::W_RIGHT:
                tra[y][x].position_.x = Half(windowWidth - (right + left + edge));
                tra[y][x].scale_.x = DEFAULT_SCALE;
                break;
            }

            //Image::SetRect(hFrameImg_, x * edge, y * edge, edge, edge);

            tra[y][x].SetReSize(transform_.scale_);
        }
    }
}