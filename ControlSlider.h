#pragma once
#include "Engine/GameObject.h"

//スライダーを管理するクラス
class ControlSlider : public GameObject
{
private:
    int trackWidth, trackHeight;  //トラックのH,W
    const int defScrX = 1280;
    const int defScrY = 720;
    int value, minValue, maxValue; //値、最大最小
    POINT thumbPos; //可変 サム位置

    //いずれグリッド形式にもできるように
    //bool freeMove;
    //int gridNum;

    enum IMAGE {
        SLIDER_THUMB,
        SLIDER_FORE,
        SLIDER_BK,
        MAX
    };
    int hImg_[IMAGE::MAX];
    //値が範囲内か
    bool Between(float value, float min, float max);
public:
    int GetValue() { return value; }
    bool IsEntered();
    void SetImage(IMAGE img, std::string fileName);
    void SetHeight(int height);
    void SetWidth(int width);
protected:
    virtual void InitValue() = 0;   //中に最大最小と現在値を初期化するコードを書く

public:
    ControlSlider(GameObject* parent);    //コンストラクタ
    ~ControlSlider();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画
    void Release() override;    //解放
};