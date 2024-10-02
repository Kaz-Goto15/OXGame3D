#pragma once
#include "Engine/GameObject.h"

class GameEndImage : public GameObject
{
    int hImageO, hImageX;
    bool winner;                    //true=O false=X
    int MAX_IMG_ALPHA;				//画像アルファ値最大
    int WIN_IMG_ALPHA_PLUS;				//画像アルファ値加算値
    int winImageAlpha;				//画像アルファ値格納
public:
    GameEndImage(GameObject* parent);    //コンストラクタ
    ~GameEndImage();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画
    void Release() override;    //解放

    /// <summary>
    /// 勝者を指定する
    /// </summary>
    /// <param name="isWinO">Oが勝ったならtrue Xが勝ったならfalse</param>
    void SetWinner(bool isWinO);
};