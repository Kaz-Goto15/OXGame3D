#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"
#include "AudioManager.h"

using std::string;
//ボタンを管理するクラス
class ButtonEx : public GameObject
{
protected:
	enum STATE {
		IDLE,
		SELECT,
		PUSH,
		SELECTED,
		MAX
	};
	Text* buttonTextObj_;
	std::string buttonTextName_;
	Text::HORIZONAL_ALIGNMENT hAl;
	Text::VERTICAL_ALIGNMENT vAl;
	int actHandle_;
	bool nextIdle;
	STATE ActTiming;
	AudioManager::AUDIO_SOURCE sound;

	XMFLOAT2 rangeLU, rangeRB;
	
	ButtonEx *leftBtn, *upBtn, *downBtn, *rightBtn;
	bool isSelecting_;
public:
	enum MODE {
		PUSH_ONLY,          //押下時、即移行
		PUSH_UP,            //押下から離したときに移行
		PUSH_ONLY_SELECT,   //押下時、即移行 十字キーやマウス移動で選択が移動する
		PUSH_UP_SELECT      //押下から離したときに移行 十字キーやマウス移動で選択が移動する
	}mode_;
	STATE state;

	ButtonEx(GameObject* parent, const std::string& name = "ButtonEx");    //コンストラクタ
	~ButtonEx();                     //デストラクタ
	void Initialize() override; //初期化
	void Update() override;     //更新
	void Draw() override;       //描画
	void Release() override;    //解放


	//自身(ボタン)と親の選択ステートを紐づける
	void SetAction(int hAct);

	void SetSound(AudioManager::AUDIO_SOURCE audioSource) { sound = audioSource; }
	//テキスト設定系
	void SetTextAlignment(Text::HORIZONAL_ALIGNMENT h, Text::VERTICAL_ALIGNMENT v);
	void SetFont(const char* fileName, const unsigned int charWidth, const unsigned int charHeight, const unsigned int rowLength);
	void SetFont(TEXT_SOURCE textScr);
	void SetText(std::string buttonName);

	//ボタン画像系
private:
	enum DIV_W {
		W_LEFT = 0,
		W_CENTER,
		W_RIGHT,
		W_MAX,
	};
	enum DIV_H {
		H_TOP = 0,
		H_CENTER,
		H_BOTTOM,
		H_MAX
	};
	const string DEFAULT_BUTTON_IMG[STATE::MAX];		//デフォルトパス
	int hImgButton_[STATE::MAX];						//ボタンハンドル
	int grid_;									//ボタン3x3分割ファイルの1x1サイズ
	Transform buttonDivTra[DIV_H::H_MAX][DIV_W::W_MAX];	//3x3分割の各変形情報
	void CalcDivImage();								//計算
public:
	void SetButtonImages(int _grid, string path_idle, string path_select = "", string path_push = "", string path_selected = "");

	//シャドウ系
private:
	const string DEFAULT_SHADOW_IMG;
	int hImgShadow_;
	bool isDrawShadow;
	int shadowAlpha_;
	XMINT2 shadowPos;
	float shadowScale;
public:
	void SetShadowTransform(int _x, int _y, float _scale = 1.f);
	void SetDrawShadow(bool b);
	void SetShadowImage(string path);
	



protected:
	//初期化追加時の処理
	virtual void Init() {}
	//画像リンク ボタン画像を変えたい場合これ継承してオーバーライドする
	virtual std::string LinkImageFile(STATE state);
	//ボタンアニメーション系
	virtual void DrawIdle();
	virtual void DrawSelect();
	virtual void DrawPush();
	virtual void DrawSelected();
private:
	//各Update関数
	void UpdateIdle();
	void UpdateSelect();
	void UpdatePush();
	void UpdateSelected();
	//ボタンの描画範囲内にマウスカーソルがあるか
	bool IsEntered();
	//値が範囲内か
	bool Between(float value, float min, float max);
	//マウスが1pxでも動いたか
	bool IsMovedMouse();
public:
	std::string GetDebugStr(int i);
};

/*
サイズは画面に対する拡大率指定(=scale_) デフォルトを1より小さくすることで何も設定しなかった場合にボタンで画面が埋め尽くされることを防ぐ
*/