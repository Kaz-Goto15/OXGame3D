#include "RivalObject.h"
#include "Engine/Model.h"
#include "Ground.h"
#include "GameData.h"
#include "ceiling.h"
#include "Engine/Debug.h"
#include <sstream>
//戻すときに針を消す
//timeフレーム毎に針を3個設置
//アイテムも
//コンストラクタ
RivalObject::RivalObject(GameObject* parent)
	: GameObject(parent, "RivalObject"), hModel_(-1)
{
}

//初期化
void RivalObject::Initialize()
{
	Instantiate<Ground>(this);
	Instantiate<ceiling>(this);
	std::fill(pNeedle, pNeedle + 30, nullptr);
}

//更新
void RivalObject::Update()
{
	if (nowPlaying) {

		//床と針の移動とループ30行ったら戻る
		if (transform_.position_.x > -30)
		{
			transform_.position_.x -= GameData::GetSpeed() * 0.05f;
		}
		else
		{
			transform_.position_.x = -30 * -1;
		}
	}
}

//描画
void RivalObject::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void RivalObject::Release()
{
}

void RivalObject::SpawnNeedle() {

	//ただしいトゲのつくりかた
	int bornNeedleCnt = 3 + (GameData::GetMeters() / 1000);
	if (bornNeedleCnt > 7)bornNeedleCnt = 7;
	Debug::Log("Meter = ");
	Debug::Log(std::to_string(GameData::GetMeters()));
	Debug::Log("トゲ生成 生成数: "); Debug::Log(bornNeedleCnt, true);

	int tmp = rand() % 10; //0-9の乱数生成
	for (int i = 0; i < 10; i++) {
		int tmp2 = i - tmp;
		if (tmp2 < 0)tmp2 += 10;
		if (tmp2 >= 0 && tmp2 < bornNeedleCnt) {
				pNeedle[setNeedlePtr] = Instantiate<Needle>(GetParent());
				pNeedle[setNeedlePtr]->SetPositionY((float)(i+1));
				setNeedlePtr++;
				if (setNeedlePtr == LOOP_NEEDLE_ARRAY)setNeedlePtr = 0;
		}
	}
}

void RivalObject::SpawnItem() {
	//被らない乱数 基本3+1000m毎に+1生成 親はGameScene
	Debug::Log("Meter = ");
	Debug::Log(std::to_string(GameData::GetMeters()));
	Debug::Log("速度上昇を生成 ", true);
	pItem = Instantiate<Item>(GetParent());
	pItem->SetPositionY((float)(rand() % 10 + 1));
}