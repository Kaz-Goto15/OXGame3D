#pragma once
#include "Engine/GameObject.h"

//スライダーを管理するクラス
class ControlSlider : public GameObject
{
private:
    int trackWidth, trackHeight;  //トラックのH,W
    int thumbSize;  //ボタンサイズ
    const int defScrX = 1280;
    const int defScrY = 720;
    int value, minValue, maxValue; //値、最大最小
    POINT thumbPos; //可変 サム位置
    float rc = 0;
    //いずれグリッド形式にもできるように
    //bool freeMove;
    //int gridNum;

    enum IMAGE {
        SLIDER_BK,
        SLIDER_FORE,
        SLIDER_THUMB,
        MAX
    };
    int hImg_[IMAGE::MAX];
    XMFLOAT3 imgSize[IMAGE::MAX];	//画像サイズ
    Transform traImage[IMAGE::MAX];	//各変形情報
    XMFLOAT2 sliderRangeLU, sliderRangeRB;
    float trackWRatio= 0, trackHRatio = 0;

    //1/2
    template <class T>
    T Half(T pValue) {
        return pValue /= 2.0f;
    }
    //値が範囲内か
    template <class T>
    bool Between(T value, T min, T max) {
        return (min <= value && value <= max);
    }
public:
    int GetValue() { return value; }
    bool IsEntered();   //マウス範囲内かを判定
    void SetImage(IMAGE img, std::string fileName);
    void SetHeight(int height);
    void SetWidth(int width);
protected:
    //virtual void InitValue() = 0;   //中に最大最小と現在値を初期化するコードを書く

public:
    ControlSlider(GameObject* parent);    //コンストラクタ
    ~ControlSlider();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画
    void Release() override;    //解放
    std::string GetDebugStr(int debugNum);
};

/*
デフォルトのウィンドウサイズとトラック幅、トラック高さを指定
ウィンドウサイズとトラック幅、ウィンドウサイズとトラック高さからそれぞれ割合を計算
scale,posを求め座標指定

・指定座標を中心にする関数、左中右揃え void SetCenterPos(float x, float y, hAlignment);
・長さと基準幅を指定して幅指定する関数 void SetLength(int len, int stdWidth = SysCon::windowWidth);
・範囲内かを返す関数 IsEntered(); owari
*/