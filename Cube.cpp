#include "Cube.h"
#include "./ModelLoader.h"
#include "Engine/Model.h"

//コンストラクタ
Cube::Cube(GameObject* parent)
    :GameObject(parent, "Cube")
{
}

//デストラクタ
Cube::~Cube()
{
}

//初期化
void Cube::Initialize()
{
    hModel_ = ModelLoader::Load(ModelLoader::MODEL::Cube);
}

//更新
void Cube::Update()
{
}

//描画
void Cube::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Cube::Release()
{
}