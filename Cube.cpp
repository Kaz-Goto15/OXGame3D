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
    hModel_col = ModelLoader::Load(ModelLoader::MODEL::COLOR_YELLOW);
}

//更新
void Cube::Update()
{
}

//描画
void Cube::Draw()
{
    //Model::SetTransform(hModel_, transform_);
    //Model::Draw(hModel_);
    Model::SetTransform(hModel_col, transform_);
    Model::Draw(hModel_col);
}

//開放
void Cube::Release()
{
}