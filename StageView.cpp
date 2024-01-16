#include "StageView.h"
#include "Engine/Model.h"
//コンストラクタ
StageView::StageView(GameObject* parent) :
    GameObject(parent, "StageView"),
    pStageData_(nullptr)
{
}

//デストラクタ
StageView::~StageView()
{
}

//初期化
void StageView::Initialize()
{

}

//更新
void StageView::Update()
{
}

//描画
void StageView::Draw()
{
    Transform stagetrans;
    for (int z = 0; z < pStageData_->stageRange.z; z++) {
        stagetrans.position_.y = z;
        for (int x = 0; x < pStageData_->stageRange.x; x++) {
            stagetrans.position_.x = x;
            for (int y = 0; y < pStageData_->stageRange.y; y++) {
                stagetrans.position_.z = y;
                stagetrans.rotate_.x = (int)(pStageData_->sData[x][y][z].rot) * 90;
                Model::SetTransform(hModel[(int)(pStageData_->sData[x][y][z].tag)], stagetrans);
                Model::Draw(hModel[(int)(pStageData_->sData[x][y][z].tag)]);
                
            }
        }
    }
}

//開放
void StageView::Release()
{
}