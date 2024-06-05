#include "ModelTestScreen.h"
#include "Engine/Input.h"
#include "./ModelLoader.h"

#include "SystemConfig.h"
#include "DebugText.h"
#include "ButtonGP.h"
#include "ControlSlider.h"

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
    hModel = ModelLoader::Load(ModelLoader::MODEL::Cube);

    debugtext = Instantiate<DebugText>(this);
    for (int i = 0; i < 20; i++) {
        debugtext->AddStrPtr(&debugStr[i]);
    }
}

//更新
void ModelTestScreen::Update()
{
    //もどる
    if (Input::IsKeyDown(DIK_P)) {
        Prev();
    }

    //kaiten
    if (Input::IsKey(DIK_6)) {
         -= 0.01f;
    }
    if (Input::IsKey(DIK_7)) {
        frameScale += 0.01f;
    }
    if (Input::IsKey(DIK_8)) {
        framePos.y -= 1.0f;
    }
    if (Input::IsKey(DIK_9)) {
        framePos.y += 1.0f;
    }
    UpdateStr();
}

void ModelTestScreen::UpdateStr()
{
    using std::to_string;
    debugStr[0] = "scrH:" + to_string(SystemConfig::windowHeight) + "scrW:" + to_string(SystemConfig::windowWidth);
    debugStr[1] = "mousePos:(" + to_string(Input::GetMousePosition(true).x) + ", " + to_string(Input::GetMousePosition(true).y) + ")";
    debugStr[2] = "scale(ModelTestscreen):" + to_string(transform_.scale_.x);
    debugStr[3] = "scale(ModelTestscreen):" + to_string(transform_.scale_.x);
    debugStr[4] = "monitorX:" + to_string(GetSystemMetrics(SM_CXSCREEN));
    debugStr[5] = "monitorY:" + to_string(GetSystemMetrics(SM_CYSCREEN));
    RECT r;
    //GetWindowRect(SystemConfig::GetWindowHandle(), &r);
    GetClientRect(SystemConfig::GetWindowHandle(), &r);
    //AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);
    debugStr[6] = "windowX:" + to_string(r.left);
    debugStr[7] = "windowY:" + to_string(r.top);
    debugStr[8] = "windowR:" + to_string(r.right);
    debugStr[9] = "windowB:" + to_string(r.bottom);
    debugStr[10] = pSlider->GetDebugStr(1);
    debugStr[11] = pSlider->GetDebugStr(2);
    debugStr[12] = pSlider->GetDebugStr(3);
    debugStr[16] = testBtn[6]->GetDebugStr(7);
    debugStr[19] = backBtn->GetDebugStr(7);
}

//描画
void ModelTestScreen::Draw()
{
    for (int i = 0; i < PIC_MAX; i++) {
        if (i == PIC_BASIC_FRAME_TEX) {
            Transform frameTra;
            frameTra.SetCenter(framePos);   //中心点を移動して座標決めてるので注意 具体的には符号逆転する(中心点を動かすと必然的に逆側に移動するため)
            frameTra.IsCalcCenterPoint(true);
            int edge = 64;
            Image::SetRect(hPict_[PIC_BASIC_FRAME_TEX], 0, 0, edge, edge);

            using namespace SystemConfig;
            //frame構築
            for (int y = 0; y < 3; y++) {
                switch (y) {
                case 0:
                    //frameTra.position_.y = -270;
                    frameTra.position_.y = (float)(-windowHeight + (frameMargin.x + frameMargin.z + edge)) / 2.0f;
                    frameTra.scale_.y = 1;
                    break;
                case 1:
                    frameTra.position_.y = 0;
                    frameTra.scale_.y = (float)(windowHeight - (frameMargin.x + frameMargin.z + edge + edge)) / (float)edge;
                    break;
                case 2:
                    frameTra.position_.y = (float)(windowHeight - (frameMargin.x + frameMargin.z + edge)) / 2.0f;
                    frameTra.scale_.y = 1;
                    break;
                }
                for (int x = 0; x < 3; x++) {
                    switch (x) {
                    case 0:
                        frameTra.position_.x = (float)(-windowWidth + (frameMargin.y + frameMargin.w + edge)) / 2.0f;
                        frameTra.scale_.x = 1;
                        break;
                    case 1:
                        frameTra.position_.x = 0;
                        frameTra.scale_.x = (float)(windowWidth - (frameMargin.y + frameMargin.w + edge + edge)) / (float)edge;
                        break;
                    case 2:
                        frameTra.position_.x = (float)(windowWidth - (frameMargin.y + frameMargin.w + edge)) / 2.0f;
                        frameTra.scale_.x = 1;
                        break;
                    }

                    Image::SetRect(hPict_[PIC_BASIC_FRAME_TEX], x * edge, y * edge, edge, edge);
                    Transform tmp = frameTra;

                    tmp.SetReSize(frameScale);

                    Image::SetTransform(hPict_[i], tmp);
                    Image::Draw(hPict_[i]);

                    //                XMFLOAT3 tmpPos = {
                    //(tmp.position_.x - tmp.center_.x) * (tmp.scale_.x * tmp.reSize_.x),// + center_.x,
                    //(tmp.position_.y - tmp.center_.y) * (tmp.scale_.y * tmp.reSize_.y),// + center_.y,
                    //(tmp.position_.z - tmp.center_.z) * (tmp.scale_.z * tmp.reSize_.z),// + center_.z
                    //                };
                    //                debugStr[y * 3 + x] =
                    //                    "frame" + std::to_string(y * 3 + x) + ": " + std::to_string(x) + ", " + std::to_string(y) +
                    //                    " tra: pos(" + std::to_string((int)tmp.position_.x) + "," + std::to_string((int)tmp.position_.y) +
                    //                    ") scl(" + std::to_string(tmp.scale_.x) + "," + std::to_string(tmp.scale_.y) + ")" +
                    //                    "cv(" + std::to_string(tmpPos.x) + "," + std::to_string(tmpPos.y)
                    //                    ;

                }
                //debugStr[9] = "scr:" + std::to_string(windowWidth) + "," + std::to_string(windowHeight);
                //debugStr[10] = "mousePos: " + std::to_string(Input::GetMousePosition().x - 640) + ", " + std::to_string(Input::GetMousePosition().y - 360);
                //debugStr[11] = "center:" + std::to_string(framePos.x) + "," + std::to_string(framePos.y);
                //debugStr[12] = "resize:" + std::to_string(frameScale);
            }
        }
        else {
            Image::SetTransform(hPict_[i], transform_);
            Image::Draw(hPict_[i]);
        }

    }

}

//開放
void ModelTestScreen::Release()
{
}

void ModelTestScreen::ButtonAct(int hAct)
{
    if (hAct == 0) {
        Prev();
    }

    //test
    switch (hAct) {
    case 1: SystemConfig::SetWindowSize(640, 360); break;
    case 2: SystemConfig::SetWindowSize(1280, 720); break;
    case 3: SystemConfig::SetWindowSize(1600, 900); break;
    case 4: SystemConfig::SetWindowSize(1920, 1080); break;
    case 5: SystemConfig::SetFullScreen(true);  break;
    case 6: SystemConfig::SetFullScreen(false); break;
    case 7: SystemConfig::SaveConfig(); break;
    }
}
