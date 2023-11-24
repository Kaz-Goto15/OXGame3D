#include "Needle.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SphereCollider.h"    
#include "Player.h"
#include "GameData.h"
//コンストラクタ
Needle::Needle(GameObject* parent)
    :GameObject(parent, "Needle"), hModel_(-1)
{
}

//デストラクタ
Needle::~Needle()
{
}

//初期化
void Needle::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("needle.fbx");
    assert(hModel_ >= 0);

    transform_.position_.y = 5;
    transform_.position_.x = 15;

    //transform_.position_.x = (float)(rand() % 401 - 200) / 10;

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.3f);
    AddCollider(collision);
  
}

//更新
void Needle::Update()
{
    if (transform_.position_.x > -30)
    {
        transform_.position_.x -= GameData::GetSpeed() * 0.05f;
    }
    if (transform_.position_.x < -20)
    {
        KillMe();
    }

}

//描画
void Needle::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

//開放
void Needle::Release()
{
}

//何かに当たった
void Needle::OnCollision(GameObject* pTarget)
{
       //とげに当たったとき消す処理
    if (pTarget->GetObjectName() == "Player")//とげに当たったらPlayerが消える処理
    {
        if (GameData::GetGamemode() == 1) {
            int dmgs = 50 + rand() % 101;
            GameData::AddHealth(-dmgs);
            GameData::AddTempHealth(-dmgs / 3);
        }
        
        //とげに当たったPlayerが消える
        //pTarget->KillMe();
        KillMe();
        GameData::AddHits(1);

    }
}
