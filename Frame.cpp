#include "Frame.h"
#include "Engine/Image.h"

#include "SystemConfig.h"

//コンストラクタ
Frame::Frame(GameObject* parent)
    :GameObject(parent, "Frame"),
    hFrameImg_(-1)
{
}

//デストラクタ
Frame::~Frame()
{
}

//初期化
void Frame::Initialize()
{
     hFrameImg_ = Image::Load("Screen/frame256_2.png");
}

//更新
void Frame::Update()
{
}

//描画
void Frame::Draw()
{
    Image::Draw(hFrameImg_);
}

//開放
void Frame::Release()
{
}

void Frame::TransformFrame(int up, int right, int down, int left)
{
    Image::SetRect(hFrameImg_, 0, 0, edge, edge);

    using namespace SystemConfig;
    //frame構築
    for (int y = 0; y < 3; y++) {
        switch (y) {
        case 0:
            frameTra.position_.y = (float)(-screenHeight + (frameMargin.x + frameMargin.z + edge)) / 2.0f;
            frameTra.scale_.y = 1;
            break;
        case 1:
            frameTra.position_.y = 0;
            frameTra.scale_.y = (float)(screenHeight - (frameMargin.x + frameMargin.z + edge + edge)) / (float)edge;
            break;
        case 2:
            frameTra.position_.y = (float)(screenHeight - (frameMargin.x + frameMargin.z + edge)) / 2.0f;
            frameTra.scale_.y = 1;
            break;
        }
        for (int x = 0; x < 3; x++) {
            switch (x) {
            case 0:
                frameTra.position_.x = (float)(-screenWidth + (frameMargin.y + frameMargin.w + edge)) / 2.0f;
                frameTra.scale_.x = 1;
                break;
            case 1:
                frameTra.position_.x = 0;
                frameTra.scale_.x = (float)(screenWidth - (frameMargin.y + frameMargin.w + edge + edge)) / (float)edge;
                break;
            case 2:
                frameTra.position_.x = (float)(screenWidth - (frameMargin.y + frameMargin.w + edge)) / 2.0f;
                frameTra.scale_.x = 1;
                break;
            }

            Image::SetRect(hPict_[PIC_BASIC_FRAME_TEX], x * edge, y * edge, edge, edge);
            Transform tmp = frameTra;

            tmp.SetReSize(frameScale);

            Image::SetTransform(hPict_[p], tmp);
            Image::Draw(hPict_[p]);
        }
    }
}