#pragma once
#include "Engine/GameObject.h"

//�O���[�v����N���X �Ƃ͖��΂��� ���̎��Ԃ�GameObject�N���X�̌p���N���X�ɉ����L�q���Ȃ����P���p���N���X
class GroupingObject : public GameObject
{

public:
    GroupingObject(GameObject* parent);    //�R���X�g���N�^
    ~GroupingObject();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���
};