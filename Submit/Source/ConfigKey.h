#pragma once
#include "Engine/GameObject.h"
#include "Engine/CsvManager.h"
#include <vector>
//�L�[�R���̎��\�����Ǘ�����N���X
class ConfigKey : public GameObject
{
    std::vector<std::vector <std::string>> textStrings;
public:
    //�R���X�g���N�^
    ConfigKey(GameObject* parent);

    //�f�X�g���N�^
    ~ConfigKey();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};