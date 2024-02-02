#include "DebugText.h"
#include "Engine/Text.h"

//コンストラクタ
DebugText::DebugText(GameObject* parent)
    :GameObject(parent, "DebugText"),
    txt(nullptr),
    pos({-640,-360}),
    lineHeight(35)
{
}

//デストラクタ
DebugText::~DebugText()
{
}

//初期化
void DebugText::Initialize()
{
    txt = new Text();
    txt->Initialize("char_gakusanmarugo_half.png", 16, 32, 16);
}

//更新
void DebugText::Update()
{
}

//描画
void DebugText::Draw()
{
    for (int i = 0; i < pStrList_.size(); i++) {
        txt->Draw(pos.x, pos.y + lineHeight * i, pStrList_[i]->c_str(), Text::HORIZONAL_ALIGNMENT::LEFT, Text::VERTICAL_ALIGNMENT::TOP);
    }
}

//開放
void DebugText::Release()
{
}

void DebugText::AddStrPtr(string* pStr)
{
    pStrList_.push_back(pStr);
}
