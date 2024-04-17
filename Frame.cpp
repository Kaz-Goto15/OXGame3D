#include "Frame.h"
#include "Engine/Image.h"

#include "SystemConfig.h"

//コンストラクタ
Frame::Frame(GameObject* parent):
    GameObject(parent, "Frame"),
    hFrameImg_(-1),
    fileName("Screen/frame256_2.png"),
    edge(64)
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
{
}

//描画
void Frame::Draw()
{
    for (int h = FRAME_H::TOP; h < FRAME_H::MAX; h++) {
        for (int w = FRAME_W::LEFT; w < FRAME_W::MAX; w++) {
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

void Frame::TransformFrame(int up, int right, int down, int left)
{
    //Image::SetRect(hFrameImg_, 0, 0, edge, edge);
    const int DEFAULT_SCALE = 1;
    const int DEFAULT_POSITION_X = 0;
    const int DEFAULT_POSITION_Y = 0;
    using namespace SystemConfig;
    //frame構築
    for (int y = FRAME_H::TOP; y < FRAME_H::MAX; y++) {
        for (int x = FRAME_W::LEFT; x < FRAME_W::MAX; x++) {
            switch (y) {
            case FRAME_H::TOP:
                tra[y][x].position_.y = Half(-screenHeight + (up + down + edge));
                tra[y][x].scale_.y = DEFAULT_SCALE;
                break;
            case FRAME_H::CENTER:
                tra[y][x].position_.y = DEFAULT_POSITION_Y;
                tra[y][x].scale_.y = (float)(screenHeight - (up + down + edge + edge)) / (float)edge;
                break;
            case FRAME_H::BOTTOM:
                tra[y][x].position_.y = Half(screenHeight - (up + down + edge));
                tra[y][x].scale_.y = DEFAULT_SCALE;
                break;
            }

            switch (x) {
            case FRAME_W::LEFT:
                tra[y][x].position_.x = Half(-screenWidth + (right + left + edge));
                tra[y][x].scale_.x = DEFAULT_SCALE;
                break;
            case FRAME_W::CENTER:
                tra[y][x].position_.x = DEFAULT_POSITION_X;
                tra[y][x].scale_.x = (float)(screenWidth - (right + left + edge + edge)) / (float)edge;
                break;
            case FRAME_W::RIGHT:
                tra[y][x].position_.x = Half(screenWidth - (right + left + edge));
                tra[y][x].scale_.x = DEFAULT_SCALE;
                break;
            }

            //Image::SetRect(hFrameImg_, x * edge, y * edge, edge, edge);

            tra[y][x].SetReSize(transform_.scale_);
        }
    }
}