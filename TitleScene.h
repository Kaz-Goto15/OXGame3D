#pragma once
#include "Engine/GameObject.h"

class Text;
class ButtonGP;
class DebugText;
class SceneManager;
class Screen;

class TitleScene : public GameObject
{
	enum Img {
		PIC_BACKGROUND,
		PIC_TITLE,
		PIC_WHITE,
		//SEL_CHOOSE,
		PIC_MAX
	};
	int hPict_[Img::PIC_MAX];	//ハンドル格納配列

	enum STATE {
		S_STANDBY,
		S_MAIN,
		S_SELECT,
	}state_;

	enum SELECT_STATE {
		S_SEL_START,
		S_SEL_CREDIT,
		S_SEL_OPTION,
		S_SEL_EXIT,
		S_SEL_MAX
	}selectState_;

	//ボタンが画面外からやってくる描画に使う
	const int DEFAULT_PROGRESS;	//再度動かす際にprogressに設定される値
	int progress;				//進捗
	int maxProgress;			//最大進捗数 フレーム指定
	int btnFadeEaseNo;			//イージング番号をいれる

	const int ALPHA_ZERO, ALPHA_MAX;	//透明度処理に使う定数

	//タイトル
	const XMINT2 TITLE_PROGRESS_POINT;	//黒背景→タイトルのみ表示までのフレーム数/ボタン押下後のボタン表示までかかるフレーム数 加算式、アニメーションで指定フレームにキーを打ち込む感覚で
	const XMINT2 TITLE_Y_FADE;	//タイトル縦フェード 初期座標(スプラッシュ後に表示されるY座標)/移動後座標 基準は1280x720

	//ボタン
	std::string State2Str(SELECT_STATE state);	//選択ステート(ボタン)を文字列に ボタンの名前表示に使用
	ButtonGP* btn[S_SEL_MAX];	//各ボタンオブジェクト
	const int BUTTON_X_SPACE;	//ボタン横間隔
	const XMINT2 BUTTON_Y_FADE;	//ボタン縦フェード 初期座標/移動後座標 基準は1280x720

	//テキスト
	Text* txtPressStart;			//テキストオブジェクト
	const XMINT2 TEXT_POSITION;		//テキスト表示座標 基準は1280x720
	const char* FIRST_TEXT_DESCR;	//最初に表示するテキストの内容

	std::string TitleImgFileName(Img E_IMG);
	//void Run(SELECT_STATE& ss);

	//DebugText* debugText;
	//std::string debugStr[20];
	void InitButton(SELECT_STATE ss, std::string text, XMINT2 pos);

	//int hSound_;	//音

	SceneManager* pSceneManager;
	Screen* pScreen;

	//1/2
	template <class T>
	T Half(T pValue) {
		return pValue /= 2.0f;
	}
	//範囲内か
	template <class T>
	bool Between(T value, T min, T max) {
		return (min <= value && value <= max);
	}
	//偶数かを見る
	bool IsEven(int value) {
		return (value % 2 == 0);
	}

public:
	TitleScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void ButtonAct(int hAct);
};