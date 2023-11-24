#include "LobbyScene.h"
#include "Engine/Image.h"

#include "CsvManager.h"
#include "Engine/Debug.h"
#include "Engine/Input.h"
//コンストラクタ
LobbyScene::LobbyScene(GameObject* parent)
	: GameObject(parent, "LobbyScene")
{
	hPict_ = -1;
	std::fill(pTextName, pTextName + 5, nullptr);
	pTextOV = nullptr;
	quantity = 0;

	pMenuSelect = Instantiate<MenuSelect>(GetParent());

	OVText = "";
	keepNo = -1;
	OVTextLen = 0;

	//デバッグ
	//debugTxt = nullptr;
	//debugTxt2 = nullptr;
	//debugTxt3 = nullptr;

	pSC = nullptr;
	pSCd = nullptr;

	//debugEf = nullptr;
}

//初期化
void LobbyScene::Initialize()
{
	//CSV読み込み
	csv.Load("select.csv");
	quantity = (int)csv.GetHeight() - 1;

	//てきすと初期化
	for (int i = 0; i < quantity; i++) {
		pTextName[i] = new Text;
		pTextName[i]->Initialize("char_re.png", 32, 64, 16);
		pTextOV = new Text;
		pTextOV->Initialize("char_gakusanmarugo_half.png", 16, 32, 16);
		if (i == 2 || i == 3) {
			pTextName[i]->SetAlpha(128);
		}
	}

	//デバッグ
	//debugTxt = new Text;
	//debugTxt->Initialize("char_gakusanmarugo_half.png", 16, 32, 16);
	//debugTxt->setAlpha(128);
	//debugTxt2 = new Text;
	//debugTxt2->Initialize("char_gakusanmarugo_half.png", 16, 32, 16);
	//debugTxt2->setAlpha(128);
	//debugTxt3 = new Text;
	//debugTxt3->Initialize("char_gakusanmarugo_half.png", 16, 32, 16);
	//debugTxt3->setAlpha(128);

	//transform_.position_.x = 0.3f;
	//transform_.position_.y = 0.3f;
	transform_.scale_.z = 1.5f;

	//画像データのロード
	hPict_ = Image::Load("lobby_bg.png");
	assert(hPict_ >= 0);

	//KeyConfig::InitKey();
	//kc.ChangeKey(KEY_ID_SELECT, DIK_LSHIFT);
	//Debug::Log(csv.GetValue(0, 0));
	//Instantiate<SceneChangeAnim>(this);
	//exit(0);
	pSC = Instantiate<SceneChange>(GetParent());
	pSC->SetFade(false);
}

//更新
void LobbyScene::Update()
{
	if (Input::IsKeyDown(KeyConfig::GetKey(KEY_ID_UP_JUMP))){
		pMenuSelect->SetSelectNo(-1);
	}
	if (Input::IsKeyDown(KeyConfig::GetKey(KEY_ID_DOWN))) {
		pMenuSelect->SetSelectNo(1);
	}
	if (Input::IsKeyDown(KeyConfig::GetKey(KEY_ID_SELECT))) {
		pMenuSelect->ExeTrig();
	}
	//texts
	if (keepNo != pMenuSelect->GetSelectNo()) {
		keepNo = pMenuSelect->GetSelectNo();
		OVTextLen = 0;
		OVText = "";
	}
	if (OVTextLen < csv.GetString(2, keepNo + 1).length()) {
		OVText += csv.GetString(2, keepNo + 1)[OVTextLen];
		OVTextLen++;
	}

	//if(Input::IsKey(DIK_SPACE))
	//if (1) {
	//	if (Input::IsKey(DIK_T)) {
	//		transform_.rotate_.x += 1.0f;
	//		Debug::Log(transform_.rotate_.x);
	//	}
	//	if (Input::IsKey(DIK_G)) {
	//		transform_.rotate_.x -= 1.0f;
	//		Debug::Log(transform_.rotate_.x);
	//	}
	//	if (Input::IsKey(DIK_F)) {
	//		transform_.rotate_.y += 1.0f;
	//		Debug::Log(transform_.rotate_.y);
	//	}
	//	if (Input::IsKey(DIK_H)) {
	//		transform_.rotate_.y -= 1.0f;
	//		Debug::Log(transform_.rotate_.y);
	//	}
	//	if (Input::IsKey(DIK_R)) {
	//		transform_.rotate_.z += 1.0f;
	//		Debug::Log(transform_.rotate_.z);
	//	}
	//	if (Input::IsKey(DIK_Y)) {
	//		transform_.rotate_.z -= 1.0f;
	//		Debug::Log(transform_.rotate_.z);
	//	}
	//}
	/*
	if (1) {
		if (Input::IsKey(DIK_T)) {
			transform_.scale_.x += 1.0f;
			Debug::Log(transform_.scale_.x);
		}
		if (Input::IsKey(DIK_G)) {
			transform_.scale_.x -= 1.0f;
			Debug::Log(transform_.scale_.x);
		}
		if (Input::IsKey(DIK_F)) {
			transform_.scale_.y += 1.0f;
			Debug::Log(transform_.scale_.y);
		}
		if (Input::IsKey(DIK_H)) {
			transform_.scale_.y -= 1.0f;
			Debug::Log(transform_.scale_.y);
		}
		if (Input::IsKey(DIK_R)) {
			transform_.scale_.z += 1.0f;
			Debug::Log(transform_.scale_.z);
		}
		if (Input::IsKey(DIK_Y)) {
			transform_.scale_.z -= 1.0f;
			Debug::Log(transform_.scale_.z);
		}
	}
	*/
	//effect debug
	/*
	if (Input::IsKeyDown(DIK_P)) {
		debugEf = Instantiate<Effect>(this);
		debugEf->SetEffect(EFFECT_GO);
	}
	if (Input::IsKeyDown(DIK_O)) {
		debugEf = Instantiate<Effect>(this);
		debugEf->SetEffect(EFFECT_GAME_END);
	}
	if (Input::IsKeyDown(DIK_I)) {
		debugEf = Instantiate<Effect>(this);
		debugEf->SetEffect(EFFECT_TIME_UP);
	}
	if (Input::IsKeyDown(DIK_J)) {
		pSC = Instantiate<SceneChange>(GetParent());
		pSC->ModifySC(SC_BLACK);
		pSC->SetFade(false);
	}
	if (Input::IsKeyDown(DIK_K)) {
		pSC = Instantiate<SceneChange>(GetParent());
		pSC->ModifySC(SC_WHITE);
		pSC->SetFade(false);
	}
	if (Input::IsKeyDown(DIK_L)) {
		pSC = Instantiate<SceneChange>(GetParent());
		pSC->ModifySC(SC_BLACK);
		pSC->SetFade(true);
		pSC->ChangeScene(SCENE_ID_RESULT);
	}
	*/
}

//描画
void LobbyScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
	pMenuSelect->Draw();
	//文字関連表示
	for (int i = 0; i < quantity; i++) {
		pTextName[i]->Draw(150, 350 + (int)(i * pMenuSelect->GetLineSpace()), csv.GetString(1, i + 1).c_str());
	}
	pTextOV->Draw(450, 600, OVText.c_str());
	
	////デバッグ
	//std::string debuga = "keepNo: " + std::to_string(keepNo) + " selectNo: " + std::to_string(pMenuSelect->getSelectNo()) + " OVTextLen: " + std::to_string(OVTextLen);
	//debugTxt->Draw(50, 10, debuga.c_str());
	//std::string debuga2 = "selectVec: ( " +
	//	std::to_string(pMenuSelect->getSelectVec(0)) + " , " +
	//	std::to_string(pMenuSelect->getSelectVec(1)) + " , " +
	//	std::to_string(pMenuSelect->getSelectVec(2)) + " )";
	//debugTxt->Draw(50, 40, debuga2.c_str());
	//debugTxt->Draw(50, 70, pMenuSelect->getInfoRect().c_str());
	//debugTxt->Draw(50, 100, pMenuSelect->getInfoTriangle().c_str());
}

//開放
void LobbyScene::Release()
{
}