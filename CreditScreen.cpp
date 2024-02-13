#include "CreditScreen.h"
#include "Engine/Input.h"
#include "Engine/Image.h"

#include "SystemConfig.h"
#include "DebugText.h"

//コンストラクタ
CreditScreen::CreditScreen(GameObject* parent):
    Screen(parent, "CreditScreen")
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
    hPict_[PIC_BASIC_FRAME_TEX] = Image::Load("frame256.png");
    hPict_[PIC_DESCRIPTION] = Image::Load("descr.png");
    Image::SetAlpha(hPict_[PIC_BACKGROUND], 128);
    //keyHelp.push_back(KEY_CANCEL, "戻る");
    
    debugtext = Instantiate<DebugText>(this);
    for (int i = 0; i < 20; i++) {
        debugtext->AddStrPtr(&debugStr[i]);
    }
    margin = { 50,50,200,50 };   //コンストラクタでやるとxが-1になる 原因不明のためこっちで
    debugStr[16] = std::to_string(margin.x);
}

//更新
void CreditScreen::Update()
{
    if (Input::IsKeyDown(DIK_P)) {
        Prev();
    }

    if (Input::IsKeyDown(DIK_6)) {
        resize = (0.25f);
    }
    if (Input::IsKeyDown(DIK_7)) {
        resize = (1.0f);
    }
    if (Input::IsKey(DIK_4)) {
        scaleMag -= 0.01f;
    }
    if (Input::IsKey(DIK_5)) {
        scaleMag += 0.01f;
    }
    if (Input::IsKey(DIK_2)) {
        b = false;
    }
    if (Input::IsKey(DIK_3)) {
        b = true;
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
    frameTra.IsCalcCenterPoint(b);
    int edge = 64;
    Image::SetRect(hPict_[PIC_BASIC_FRAME_TEX], 0, 0, edge, edge);
    
    using namespace SystemConfig;
    //frame構築
    for (int y = 0; y < 3; y++) {
        switch (y){
        case 0: 
            frameTra.position_.y = -(screenHeight / 2.0f) + (float)(margin.x + margin.z + edge) / 2.0f;
            //debugStr[11] = "-(screenHeight / 2.0f) + margin.x + edge/2.0f:" + std::to_string(-(screenHeight / 2.0f) + margin.x + edge / 2.0f);
            //debugStr[12] = "-(screenHeight / 2.0f):" + std::to_string(-(screenHeight / 2.0f));
            //debugStr[13] = "margin.x:" + std::to_string(margin.x);
            //debugStr[14] = "edge/2.0f:" + std::to_string(edge / 2.0f);
            frameTra.scale_.y = 1;
            break;
        case 1:
            frameTra.position_.y = 0;
            frameTra.scale_.y = (float)(screenHeight - edge * 2 - margin.x - margin.z) / (float)edge;
            break;
        case 2:
            frameTra.position_.y = ((float)screenHeight / 2.0f) - (float)(margin.x + margin.z + edge) / 2.0f;
            frameTra.scale_.y = 1;
            break;
        }
        for (int x = 0; x < 3; x++) {
            switch (x) {
            case 0:
                frameTra.position_.x = -(screenWidth / 2.0f) + margin.y + edge / 2.0f;
                frameTra.scale_.x = 1;
                break;
            case 1:
                frameTra.position_.x = 0;
                frameTra.scale_.x = (float)(screenWidth - edge * 2 - margin.y - margin.w) / (float)edge;
                break;
            case 2:
                frameTra.position_.x = (screenWidth / 2.0f) - margin.w - edge / 2.0f;
                frameTra.scale_.x = 1;
                break;
            }

            Image::SetRect(hPict_[PIC_BASIC_FRAME_TEX], x*edge, y*edge, edge, edge);
            Transform tmp = frameTra;
            tmp.SetReSize(resize);
            tmp.scale_.x *= scaleMag;
            tmp.scale_.y *= scaleMag;
            tmp.scale_.z *= scaleMag;
            Image::SetTransform(hPict_[PIC_BASIC_FRAME_TEX], tmp);
            Image::Draw(hPict_[PIC_BASIC_FRAME_TEX]);
            debugStr[y * 3 + x] =
                "frame" + std::to_string(y*3+x) + ": " + std::to_string(x) + ", " + std::to_string(y) +
                " tra: pos(" + std::to_string((int)tmp.position_.x) + "," + std::to_string((int)tmp.position_.y) +
                ") scl(" + std::to_string(tmp.scale_.x) + "," + std::to_string(tmp.scale_.y) + ")";
        }
    }
    debugStr[9] = "scr:" + std::to_string(screenWidth) + "," + std::to_string(screenHeight);
    debugStr[10] = "mousePos: " + std::to_string(Input::GetMousePosition().x-640) + ", " + std::to_string(Input::GetMousePosition().y-360);
}

//開放
void CreditScreen::Release()
{
}