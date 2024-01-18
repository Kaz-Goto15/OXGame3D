#include "EditScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include <string>
using std::string;
EditScene::EditScene(GameObject* parent)
	: GameObject(parent, "EditScene"),
	queue_(-1),
	mapSize({5,5,5})
{}
void EditScene::Initialize() {
	//pView = new StageView();
	//pTheme = new StageTheme();
	//pView->SetTheme(pTheme);
	//pEditGUI = new StageEditGUI();
	//pEditGUI->SetTheme(pTheme);
	mapData_.resize(mapSize.x);
	for (size_t x = 0; x < mapSize.x; x++) {
		mapData_[x].resize(mapSize.y);
		for (size_t y = 0; y < mapSize.y; y++) {
			mapData_[x][y].resize(mapSize.z, 0);
		}
	}
}
void EditScene::Update() {
}
void EditScene::Draw() {

}
void EditScene::Release() {}

void EditScene::EditStart()
{
	//drawTime_ = 0;
	//queue_++;
	//isDisplaying = true;
	//state_ = S_Edit;
}

void EditScene::EditMain()
{
	
	//drawTime_++;

	//if (isDisplaying) {

	//}
	//else {
	//	queue_++;
	//	isDisplaying = true;
	//	if (!(queue_ < LOGO_COUNT)) {
	//		state_ = S_NEXT_SCENE;
	//	}
	//}

}

void EditScene::EditEnd()
{
	//if(que)
}

void EditScene::NextScene()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_TEST);
}

bool EditScene::LoadStageData()
{
	string ext = "hnsg";
	char fileName[MAX_PATH] = "無題.hnsg";  //ファイル名を入れる変数

	//「ファイルを開く」ダイアログの設定
	OPENFILENAME ofn;                         	//名前をつけて保存ダイアログの設定用構造体
	ZeroMemory(&ofn, sizeof(ofn));            	//構造体初期化
	ofn.lStructSize = sizeof(OPENFILENAME);   	//構造体のサイズ
	string categoryStr = "ステージデータ(*." + ext + ")\0 * ." + ext + "\0";

	ofn.lpstrFilter = TEXT(categoryStr.c_str())			//─┬ファイルの種類
		,TEXT("すべてのファイル(*.*)\0*.*\0\0");                     //─┘
	ofn.lpstrFile = fileName;               	//ファイル名
	ofn.nMaxFile = MAX_PATH;               	//パスの最大文字数
	ofn.Flags = OFN_OVERWRITEPROMPT;   		//フラグ（同名ファイルが存在したら上書き確認）
	ofn.lpstrDefExt = "hnsg";                  	//デフォルト拡張子

	//「ファイルを開く」ダイアログ
	BOOL selFile;
	selFile = GetOpenFileName(&ofn);

	//キャンセルしたら中断
	if (selFile == FALSE) return false;

	//if (!ConfirmDestruct())return false;
	HANDLE hFile;
	//ファイルを開く
	hFile = CreateFile(
		fileName,  //ファイル名
		GENERIC_READ,              //アクセスモード（書き込み用）
		0,                          //共有（なし）
		NULL,                       //セキュリティ属性（継承しない）
		OPEN_EXISTING,              //作成方法
		FILE_ATTRIBUTE_NORMAL,      //属性とフラグ（設定なし）
		NULL);                      //拡張属性（なし）

	if (hFile == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, ("CANNOT OPEN FILE: " + (string)fileName).c_str(), "Error", MB_OK);
		return false;
	}

	//ファイルサイズ取得
	DWORD fileSize = GetFileSize(hFile, NULL);

	//ファイルのサイズ分メモリを確保
	char* data = new char[fileSize];

	DWORD dwBytes = 0; //読み込み位置
	BOOL res = ReadFile(
		hFile,     //ファイルハンドル
		data,      //データを入れる変数
		fileSize,  //読み込むサイズ
		&dwBytes,  //読み込んだサイズ
		NULL);     //オーバーラップド構造体（今回は使わない）

	if (res == FALSE) {
		MessageBox(NULL, ("FAILED TO READ: " + (string)fileName).c_str(), "Error", MB_OK);
		return false;
	}

	CloseHandle(hFile);

	//ここに持ってきたデータ読み込むコード
	//読込データ入れる配列
	std::vector<std::vector<std::string>> data_;

	//LoadData(fileSize, data, &data_);

	//読み込んだデータを開放
	delete[] data;

	//データを現在のプロジェクトファイルに読込
	//for (int l = 0; l < data_.size(); l++) {
	//	table_[atoi(data_[l][0].c_str())][atoi(data_[l][1].c_str())].height = atoi(data_[l][2].c_str());
	//	table_[atoi(data_[l][0].c_str())][atoi(data_[l][1].c_str())].bType = (BLOCKTYPE)atoi(data_[l][3].c_str());
	//}

	//全データ開放
	for (int y = 0; y < data_.size(); y++)
		for (int x = 0; x < data_[y].size(); x++)
			data_[y][x].clear();

	//isEdited_ = false;
}
