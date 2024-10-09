#include "DebugText.h"
#include "Engine/Text.h"
#include "SystemConfig.h"
//�R���X�g���N�^
DebugText::DebugText(GameObject* parent)
    :GameObject(parent, "DebugText"),
    txt(nullptr),
    pos({-640,-360}),
    lineHeight(35)
{
}

//�f�X�g���N�^
DebugText::~DebugText()
{
}

//������
void DebugText::Initialize()
{
    txt = new Text();
    txt->Initialize(GAKUMARU_16px);
}

//�X�V
void DebugText::Update()
{
}

//�`��
void DebugText::Draw()
{
    if (SystemConfig::IsDebug()) {
        for (int i = 0; i < pStrList_.size(); i++) {
            txt->Draw(pos.x, pos.y + lineHeight * i, pStrList_[i]->c_str(), Text::HORIZONAL_ALIGNMENT::LEFT, Text::VERTICAL_ALIGNMENT::TOP);
        }
    }
}

//�J��
void DebugText::Release()
{
}

void DebugText::AddStrPtr(string* pStr)
{
    pStrList_.push_back(pStr);
}
