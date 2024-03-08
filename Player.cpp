#include "Player.h"
#include "ModelLoader.h"
#include "AudioManager.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Ground.h"
#include "Needle.h"
#include "KeyConfig.h"
#include "Engine/Debug.h"
#include "GameData.h"

//コンストラクタ
Player::Player(GameObject* parent):
    GameObject(parent, "Player"),
    state_(S_IDLE),
    hModel_(-1)
{
    std::fill(hSound_, hSound_ + 3, -1);
    nowFly = false;

    knockback = 0;
    hasHealth = true;
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{
    //モデルデータのロード
    hModel_ = ModelLoader::Load(ModelLoader::MODEL::Player);
    assert(hModel_ >= 0);

    maxVel = -0.15f; //自然落下の最高速

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 1.05f, 0), 0.35f);
    AddCollider(collision);
    BoxCollider* collision1 = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0));
    AddCollider(collision1);
  
    //サウンドのロード
    using AudioManager::AUDIO_SOURCE;
    AudioManager::Load(AUDIO_SOURCE::SE_DAMAGED, AUDIO_SOURCE::SE_THROW);
    //std::string audioFileName_[] = { "se_JUMP.wav", "se_LAND.wav", "se_HIT.wav" };
    //for (int i = 0; i < sizeof(audioFileName_) / sizeof(audioFileName_[0]); i++) {
    //    using AudioManager::AUDIO_SOURCE;
    //    AudioManager::Load(AUDIO_SOURCE::SE_DAMAGED);

    //    assert(hSound_[i] >= 0);
    //}

}

//更新
void Player::Update()
{
    if (GameData::GetHealth() <= 0) {
        AUDIO_ASSET
    }
    else {
        hasHealth = true;
    }
    if (hasHealth) {
        //左右の移動と移動範囲
        if (Input::IsKey(KeyConfig::GetKey(KEY_ID_RIGHT))) {
            transform_.position_.x += 0.1f;
            if (transform_.position_.x > -3)transform_.position_.x = -3;
        }
        if (Input::IsKey(KeyConfig::GetKey(KEY_ID_LEFT))) {
            transform_.position_.x -= 0.1f;
            if (transform_.position_.x < -9)transform_.position_.x = -9;
        }

        //ジャンプ
        if (Input::IsKeyDown(KeyConfig::GetKey(KEY_ID_UP_JUMP))) {
            nowFly = true;
            Debug::Log("FLY", true);
            Audio::Play(hSound_[0]);
            velY = 0.6f;
        }
    }
    //最高高度
    if (transform_.position_.y > 10) {
        transform_.position_.y = 10;
        velY = 0;
    }

    //knockback
    if (knockback > 0) {
        transform_.position_.x -= knockback;
        if (transform_.position_.x < -9)transform_.position_.x = -9;
        knockback -= 0.05f;
    }

    //重力降下
    velY -= 0.05f;
    
    //自然落下の最高速を上回るとき上書きする
    if (maxVel > velY)velY = maxVel;
    //下の高速落下(上書)
    if (Input::IsKey(KeyConfig::GetKey(KEY_ID_DOWN)))velY = -0.55f;

    transform_.position_.y += velY;

    Debug::Log(transform_.position_.y, true);

    Ground* pGround = (Ground*)FindObject("Ground");
    int hGroundModel = pGround->GetModelHandle();
    RayCastData rayData;
    rayData.start = transform_.position_;   //レイの発射位置
    rayData.start.y = 0;
    rayData.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hGroundModel, &rayData); //レイを発射
    
    //着地処理
    if (rayData.hit){
        if (transform_.position_.y < 0.01) {
            if (nowFly) {
                nowFly = false;
                Debug::Log("LAND", true);
                Audio::Play(hSound_[1]);
            }
            transform_.position_.y = -rayData.dist;
        }
    }

}

//描画
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

}

//開放
void Player::Release()
{
}

//当たった時の処理
void Player::OnCollision(GameObject* pTarget){
        //当たったときの処理
    if (pTarget->ExistTag("Enemy", "Neutral")) {    //タグがあるオブジェクトに当たった時の処理
        ChangeState(S_DAMAGED);
    }
    if(pTarget->ExistTag("item"))
        if (pTarget->GetObjectName() == "Needle")//Bulletに当たったら敵が消える処理
        {
            Audio::Play(hSound_[2]);
            knockback = 0.4f;
        }

        //当たったときの処理

}

float Player::GetPositionY()
{
    return transform_.position_.y;
}

void Player::UpdateAct(STATE state)
{
    bool doOnce
    switch (state)
    {
    case Player::STATE::S_IDLE:
        ModelLoader::ChangeAnim(hModel_, "idle");
        
        break;
    case Player::STATE::S_MOVE:
        break;
    case Player::STATE::S_JUMP:
        break;
    case Player::STATE::S_FALL:
        break;
    case Player::STATE::S_DAMAGED:
        break;
    case Player::STATE::S_THROW:
        break;
    case Player::STATE::S_DOWN:
        break;
    default:
        break;
    }
}

void Player::ChangeState(STATE state)
{
    state_ = state;

    //各stateのdoonce的処理を行う
    switch (state)
    {
    case Player::S_IDLE:
        ModelLoader::ChangeAnim(hModel_, "idle");
        break;
    case Player::S_MOVE:
        break;
    case Player::S_JUMP:
        break;
    case Player::S_FALL:
        break;
    case Player::S_DAMAGED:
        break;
    case Player::S_THROW:
        break;
    case Player::S_DOWN:
        break;
    default:
        break;
    }
}
