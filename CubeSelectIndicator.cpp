#include "CubeSelectIndicator.h"
#include "./ModelLoader.h"
#include "Engine/Model.h"

XMFLOAT3 CubeSelectIndicator::Surface2Rotate(Cube::SURFACE surface)
{
    //モデルで上方向(0,1,0)に配置する
    switch (surface)
    {
    case Cube::SURFACE_TOP: return { 0,0,0 };
    case Cube::SURFACE_BOTTOM:return { 180,0,0 };
    case Cube::SURFACE_LEFT:    return { 0,0,90 };
    case Cube::SURFACE_RIGHT:   return { 0,0,-90 };
    case Cube::SURFACE_FRONT:   return { 90,0,0 };
    case Cube::SURFACE_BACK:    return { -90,0,0 };
    }
}

//コンストラクタ
CubeSelectIndicator::CubeSelectIndicator(GameObject* parent)
    :GameObject(parent, "CubeSelectIndicator")
{
    hModel = -1;
}

//デストラクタ
CubeSelectIndicator::~CubeSelectIndicator()
{
}

//初期化
void CubeSelectIndicator::Initialize()
{
    hModel = ModelLoader::Load(ModelLoader::CubeSelectIndicator);
    ModelLoader::ChangeAnim(hModel, "green");
}

//更新
void CubeSelectIndicator::Update()
{
}

//描画
void CubeSelectIndicator::Draw()
{
    Model::SetTransform(hModel, transform_);
    Model::Draw(hModel);
}

//開放
void CubeSelectIndicator::Release()
{
}

void CubeSelectIndicator::SetSurface(Cube::SURFACE surface)
{
}