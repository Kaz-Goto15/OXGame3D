#pragma once
#include "Engine/GameObject.h"
#include <vector>

using std::vector;
class Text;
class ButtonEx;
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
		S_STANDBY_WAIT,
		S_MAIN
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
	const int MOVE_FRAMES;			//各オブジェクトの移動、白背景エフェクトにかけるフレーム数
	const int OBJ_FADE_EASE_NUMBER;			//イージング番号をいれる

	const int ALPHA_ZERO, ALPHA_MAX;	//透明度処理に使う定数

	//タイトル
	const int TITLE_PROGRESS_POINT;	//黒背景→タイトル表示までのフレーム数/ボタン押下後のボタン表示までかかるフレーム数
	const XMINT2 TITLE_Y_FADE;	//タイトル縦フェード 初期座標(スプラッシュ後に表示されるY座標)/移動後座標 基準は1280x720

	//ボタン
	std::string State2Str(SELECT_STATE state);	//選択ステート(ボタン)を文字列に ボタンの名前表示に使用
	ButtonEx* btn[S_SEL_MAX];	//各ボタンオブジェクト
	const int BUTTON_X_SPACE;	//ボタン横間隔
	const XMINT2 BUTTON_Y_FADE;	//ボタン縦フェード 初期座標/移動後座標 基準は1280x720

	//テキスト
	Text* txtPressStart;			//テキストオブジェクト
	const XMINT2 TEXT_POSITION;		//テキスト表示座標 基準は1280x720
	const char* FIRST_TEXT_DESCR;	//最初に表示するテキストの内容

	std::string TitleImgFileName(Img E_IMG);

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

	//SQLのIn句と同じ
	template <class T>
	bool In(T val, vector<T> search) {
		for (auto& word : search) {
			if (val == word)return true;
		}
		return false;
	}

public:
	TitleScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void ButtonAct(int hAct);
};