#include <stdlib.h>
#include "Direct3D.h"
#include "Text.h"
#include "Debug.h"

#include <string>

Text::Text():
	hPict_(-1),
	width_(16),
	height_(32),
	fileName_("char.png"),
	rowLength_(16),
	scale(1)
{
}

Text::~Text()
{
}

//初期化（デフォルト）
HRESULT Text::Initialize()
{
	hPict_ = Image::Load(fileName_);
	assert(hPict_ >= 0);

	if (hPict_ < 0)
		return E_FAIL;

	return S_OK;
}

//初期化（オリジナルの画像）
HRESULT Text::Initialize(const char* fileName, const unsigned int charWidth, const unsigned int charHeight, const unsigned int rowLength)
{
	strcpy_s(fileName_, fileName);
	width_ = charWidth;
	height_ = charHeight;
	rowLength_ = rowLength;

	return Initialize();
}
//初期化（オリジナルの画像）
HRESULT Text::Initialize(TEXT_MEDIA tm)
{
	std::string str;
	Load(tm, str, width_, height_, rowLength_);
	str = "Text\\" + str;
	strcpy_s(fileName_, str.c_str());

	return Initialize();
}


//描画（文字列）
void Text::Draw(int x, int y, const char* str)
{
	Draw(x, y, str, HORIZONAL_ALIGNMENT::CENTER, VERTICAL_ALIGNMENT::CENTER);
	////表示位置（左上）を計算
	////Spriteクラスは中心が(0,0)、右上が(1,1)という座標だが、ここの引数は左上を(0,0)、ドット単位で指定している
	//float px, py;

	////引数は左上原点だが、スプライトは画面中央が原点なので、画面サイズの半分ずらす
	//px = (float)(x - Direct3D::screenWidth_ / 2);
	//py = (float)(-y + Direct3D::screenHeight_ / 2);	//Y軸は+-反転

	////スプライトはPositionを1ずらすと画面サイズの半分ずれるので、ピクセル単位に変換
	//px /= (float)(Direct3D::screenWidth_ / 2.0f);
	//py /= (float)(Direct3D::screenHeight_ / 2.0f);


	////１文字ずつ表示する
	//for (int i = 0; str[i] != '\0'; i++)	//文字列の末尾まで来たら終わり
	//{
	//	//表示したい文字が、画像の何番目に書いてあるかを求める
	//	int id = str[i] - '!';		//表示したい文字のコードから「!」のコードを引くことで、!＝0、"=1、#＝2･･･という番号にする

	//	//表示したい文字が、画像のどこにあるかを求める
	//	int x = id % rowLength_;	//左から何番目
	//	int y = id / rowLength_;	//上から何番目

	//	//表示する位置
	//	Transform transform;
	//	transform.position_.x = px;
	//	transform.position_.y = py;
	//	transform.scale_ = XMFLOAT3(scale, scale, scale);
	//	Image::SetTransform(hPict_, transform);

	//	//表示する範囲
	//	Image::SetRect(hPict_, width_ * x, height_ * y, width_, height_);

	//	//表示
	//	Image::Draw(hPict_);

	//	//次の位置にずらす
	//	px += width_ / (float)(Direct3D::screenWidth_ / 2.0f);
	//}
}

//描画（整数値）
void Text::Draw(int x, int y, int value)
{
	//文字列に変換
	char str[256];
	sprintf_s(str, "%d", value);

	Draw(x, y, str);
}

void Text::Draw(int x, int y, const char* str, Text::HORIZONAL_ALIGNMENT hAlignment, Text::VERTICAL_ALIGNMENT vAlignment)
{

	//表示位置（左上）を計算
	//Spriteクラスは中心が(0,0)、右上が(1,1)という座標だが、ここの引数は左上を(0,0)、ドット単位で指定している
	float px, py;
	float strWidth = width_ *( std::strlen(str) -1);
	switch (hAlignment)
	{
	case Text::HORIZONAL_ALIGNMENT::CENTER:
		px = (float)x- strWidth/2.0f;
		break;
	case Text::HORIZONAL_ALIGNMENT::LEFT:
		//px = (float)(x - Direct3D::screenWidth_ / 2);
		px = (float)x + width_ /2.0f;
		break;
	case Text::HORIZONAL_ALIGNMENT::RIGHT:
		px = (float)(x) - strWidth - width_ / 2.0f;
		break;
	}

	switch (vAlignment)
	{
	case Text::VERTICAL_ALIGNMENT::TOP:
		py = (float)(-y) - (float)height_/ 2.0f;
		break;
	case Text::VERTICAL_ALIGNMENT::CENTER:
		py = (float)(-y);
		break;
	case Text::VERTICAL_ALIGNMENT::BOTTOM:
		py = (float)(-y) + (float)height_ / 2.0f;
		break;
	}
	std::string debugStr = "xy:" + std::to_string(px) + "," + std::to_string(py);
	//Debug::Log(debugStr, true);

	//スプライトはPositionを1ずらすと画面サイズの半分ずれるので、ピクセル単位に変換
	//px /= (float)(Direct3D::screenWidth_ / 2.0f);
	//py /= (float)(Direct3D::screenHeight_ / 2.0f);

	//１文字ずつ表示する
	for (int i = 0; str[i] != '\0'; i++)	//文字列の末尾まで来たら終わり
	{
		//表示したい文字が、画像の何番目に書いてあるかを求める
		int id = str[i] - '!';		//表示したい文字のコードから「!」のコードを引くことで、!＝0、"=1、#＝2･･･という番号にする

		//表示したい文字が、画像のどこにあるかを求める
		int x = id % rowLength_;	//左から何番目
		int y = id / rowLength_;	//上から何番目

		//表示する位置
		Transform transform;
		transform.position_.x = px;
		transform.position_.y = -py;
		transform.scale_ = XMFLOAT3(scale, scale, scale);
		Image::SetTransform(hPict_, transform);

		//表示する範囲
		Image::SetRect(hPict_, width_ * x, height_ * y, width_, height_);

		//表示
		Image::Draw(hPict_);

		//次の位置にずらす
		//px += width_ / (float)(Direct3D::screenWidth_ / 2.0f);
		px += width_;
	}
}

//解放
void Text::Release()
{
	Image::Release(hPict_);
}

void Text::SetAlpha(int val) {
	Image::SetAlpha(hPict_, val);
}