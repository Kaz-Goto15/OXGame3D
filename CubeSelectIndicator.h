#pragma once
#include "Engine/GameObject.h"
#include "Cube.h"

//キューブを管理するクラス
class CubeSelectIndicator : public GameObject
{
private:
    int hModel;
    XMFLOAT3 Surface2Rotate(Cube::SURFACE surface);
public:
    CubeSelectIndicator(GameObject* parent);    //コンストラクタ
    ~CubeSelectIndicator();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画
    void Release() override;    //解放

    /// <summary>
    /// 描画面の変更
    /// </summary>
    /// <param name="surface">面enum</param>
    void SetSurface(Cube::SURFACE surface);
};