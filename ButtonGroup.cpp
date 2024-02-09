#include "ButtonGroup.h"

//コンストラクタ
ButtonGroup::ButtonGroup(GameObject* parent)
    :GameObject(parent, "ButtonGroup")
{
}

//デストラクタ
ButtonGroup::~ButtonGroup()
{
}

//初期化
void ButtonGroup::Initialize()
{
}

//更新
void ButtonGroup::Update()
{
}

//描画
void ButtonGroup::Draw()
{
}

//開放
void ButtonGroup::Release()
{
}

void ButtonGroup::AddButton(int handle, Button* btn)
{
	//btn[ss] = Instantiate <TitleButton>(this);
	//btn[ss]->SetText(text);
	//btn[ss]->SetAction(ss);
	//btn[ss]->SetPosition(pos.x, pos.y, 0.0f);
}
