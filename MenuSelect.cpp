#include "MenuSelect.h"
#include "Engine/Input.h"
#include "Engine/CsvReader.h"
#include "Engine/SceneManager.h"
#include "Engine/BoxCollider.h"
#include "Engine/Debug.h"
#include "Engine/Audio.h"
#include <iostream>
//コンストラクタ
MenuSelect::MenuSelect(GameObject* parent)
    :GameObject(parent, "MenuSelect")
{
    std::fill(hSound_, hSound_ + 2, -1);
    pText = nullptr;
    testring = "";
    selectNo = 0;
    lineSpace = 70;
    toLocateY = 0;
    quantity = 0;
    selectVec = { -0.86f, 0.03f, 0 }; //本来は画面サイズから指定したいなあ->selectVec
    pSelectRect = Instantiate<SelectRect>(this);
    pSelectTriangle = Instantiate<SelectTriangle>(this);
    pSC = nullptr;
}

//デストラクタ
MenuSelect::~MenuSelect()
{
}

//初期化
void MenuSelect::Initialize()
{
    CsvReader csv;
    csv.Load("select.csv");
    quantity = (int)csv.GetHeight() - 2;

    //てきすと初期化
    pText = new Text;
    pText->Initialize("char_re.png", 32, 64, 16);
    pSelectTriangle->SetPosition(selectVec);
    pSelectTriangle->SetVec(selectVec);

    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1));
    AddCollider(collision);
    pSelectTriangle->SetPosXZ(selectVec.x , selectVec.z);
    pSelectRect->SetPosition(selectVec.x + 0.26f, selectVec.y, selectVec.z);

    //サウンドのロード
    std::string audioFileName_[] = { "se_CHOOSE.wav", "se_DECISION.wav"};
    for (int i = 0; i < sizeof(audioFileName_) / sizeof(audioFileName_[0]); i++) {
        hSound_[i] = Audio::Load(audioFileName_[i], false, 5);
        assert(hSound_[i] >= 0);
    }
}

//更新
void MenuSelect::Update()
{
    pSelectRect->SetPosition(selectVec.x + 0.26f, selectVec.y, selectVec.z);
    if (1) {
        if (Input::IsKeyDown(DIK_T)) {
            selectVec.x += 0.01f;
        }
        if (Input::IsKeyDown(DIK_Y)) {
            selectVec.x -= 0.01f;
        }
        if (Input::IsKeyDown(DIK_U)) {
            selectVec.y += 0.01f;
        }
        if (Input::IsKeyDown(DIK_I)) {
            selectVec.y -= 0.01f;
        }
    }
    if (Input::IsKey(DIK_T)) {
        transform_.scale_.x += 0.3f;
        transform_.scale_.y += 0.3f;
    }
    if (Input::IsKey(DIK_G)) {
        transform_.scale_.x -= 0.3f;
        transform_.scale_.y -= 0.3f;
        Debug::Log("やってる？");
    }

}

//描画
void MenuSelect::Draw()
{
    pSelectRect->Draw();
    pSelectTriangle->Draw();
    //pText->Draw(60, 60, testring.c_str());
}

//開放
void MenuSelect::Release()
{
}

void MenuSelect::SetSelectNo(int send_) {
    if (selectNo > 0 && send_ < 0) {
        Audio::Play(hSound_[0]);
        selectNo--;
        selectVec.y += lineSpace / 360;
        pSelectTriangle->SetPosXZ(selectVec.x, selectVec.z);
        pSelectTriangle->SetVec(selectVec);
        pSelectRect->ResetLoc();
    }
    if (selectNo < quantity && send_ > 0) {
        Audio::Play(hSound_[0]);
        selectNo++;
        selectVec.y -= lineSpace / 360;
        pSelectTriangle->SetPosXZ(selectVec.x, selectVec.z);
        pSelectTriangle->SetVec(selectVec);
        pSelectRect->ResetLoc();
    }
}

//トリガー
void MenuSelect::ExeTrig() {
    if (selectNo == 0) {
        Audio::Play(hSound_[1]);
        GameData::SetGamemode(0);
        pSC = Instantiate<SceneChange>(GetParent());
        pSC->SetFade(true);
        pSC->ChangeScene(SCENE_ID_GAME);
        pSC->ModifySC(SC_LATTICE, 120);
    }
    if (selectNo == 1) {
        Audio::Play(hSound_[1]);
        GameData::SetGamemode(1);
        pSC = Instantiate<SceneChange>(GetParent());
        pSC->SetFade(true);
        pSC->ChangeScene(SCENE_ID_GAME);
        pSC->ModifySC(SC_LATTICE, 120);
    }
    if (selectNo == 4) {
        Audio::Play(hSound_[1]);
        exit(0);
    }
}

float MenuSelect::GetSelectVec(int i) {
    float returnVal = -1;
    if (i == 0) {
        returnVal = selectVec.x;
    }
    if (i == 1) {
        returnVal = selectVec.y;
    }
    if (i == 2) {
        returnVal = selectVec.z;
    }
    return returnVal;
}

std::string MenuSelect::GetInfoRect() {
    return pSelectRect->GetInfo();
}
std::string MenuSelect::GetInfoTriangle() {
    return pSelectTriangle->GetInfo();
}