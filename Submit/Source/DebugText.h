#pragma once
#include "Engine/GameObject.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class Text;

//�f�o�b�O�e�L�X�g���Ǘ�����N���X
class DebugText : public GameObject
{
    Text* txt;
    vector<string*> pStrList_;
    POINT pos;
    int lineHeight;
public:
    DebugText(GameObject* parent);    //�R���X�g���N�^
    ~DebugText();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���

    void AddStrPtr(string* pStr);
};