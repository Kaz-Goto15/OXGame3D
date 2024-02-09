#include "CreditScreen.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

#include "DebugText.h"

//コンストラクタ
CreditScreen::CreditScreen(GameObject* parent):
    Screen(parent, "CreditScreen"),
    margin({ 100,100,100,100 })
{
}

//デストラクタ
CreditScreen::~CreditScreen()
{
}

//初期化
void CreditScreen::Initialize()
{
    hPict_[PIC_BACKGROUND] = Image::Load("black.png");
    hPict_[PIC_BASIC_FRAME_TEX] = Image::Load("frame.png");
    hPict_[PIC_DESCRIPTION] = Image::Load("descr.png");
    Image::SetAlpha(hPict_[PIC_BACKGROUND], 128);
    //keyHelp.push_back(KEY_CANCEL, "戻る");
    
    debugtext = Instantiate<DebugText>(this);
    for (int i = 0; i < 20; i++) {
        debugtext->AddStrPtr(&debugStr[i]);
    }
}

//更新
void CreditScreen::Update()
{
    if (Input::IsKeyDown(DIK_P)) {
        Prev();
    }
}

//描画
void CreditScreen::Draw()
{
    for (int i = 0; i < PIC_MAX; i++) {
        Image::SetTransform(hPict_[i], transform_);
        Image::Draw(hPict_[i]);
    }
    
    Transform frameTra;
    int edge = 64;
    Image::SetRect(hPict_[PIC_BASIC_FRAME_TEX], 0, 0, edge, edge);
    
    //frame構築
    for (int y = 0; y < 3; y++) {
        switch (y){
        case 0: 
            frameTra.position_.y = -(scrH / 2.0f) + margin.x + edge/2.0f; 
            frameTra.scale_.y = 1;
            break;
        case 1:
            frameTra.position_.y = 0;
            frameTra.scale_.y = (scrH - edge*2 - margin.x - margin.z)/ edge;
            break;
        case 2:
            frameTra.position_.y = (scrH / 2.0f) - margin.z - edge / 2.0f;
            frameTra.scale_.y = 1;
            break;
        }
        for (int x = 0; x < 3; x++) {
            switch (x) {
            case 0:
                frameTra.position_.x = -(scrW / 2.0f) + margin.y + edge / 2.0f;
                frameTra.scale_.x = 1;
                break;
            case 1:
                frameTra.position_.x = 0;
                frameTra.scale_.x = (scrW - edge * 2 - margin.y - margin.w) / edge;
                break;
            case 2:
                frameTra.position_.x = (scrW / 2.0f) - margin.w - edge / 2.0f;
                frameTra.scale_.x = 1;
                break;
            }

            Image::SetRect(hPict_[PIC_BASIC_FRAME_TEX], x*edge, y*edge, edge, edge);
            Transform tmp = frameTra;
            //tmp.SetScale(0.5, 0, 0, 0);
            Image::SetTransform(hPict_[PIC_BASIC_FRAME_TEX], tmp);
            Image::Draw(hPict_[PIC_BASIC_FRAME_TEX]);
            debugStr[y * 3 + x] =
                "frame:" + std::to_string(x) + "," + std::to_string(y) +
                " tra: pos(" + std::to_string((int)tmp.position_.x) + "," + std::to_string((int)tmp.position_.y) +
                ") scl(" + std::to_string((int)tmp.scale_.x) + "," + std::to_string((int)tmp.scale_.y);
        }
    }
    debugStr[9] = "scr:" + std::to_string(scrW) + "," + std::to_string(scrH);
}

//開放
void CreditScreen::Release()
{
}