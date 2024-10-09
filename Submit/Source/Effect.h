#pragma once
#include "Engine/GameObject.h"
#include "Engine/Image.h"

enum EFFECT_ID {
    EFFECT_GO = 0,
    EFFECT_GAME_END,
    EFFECT_TIME_UP,
    EFFECT_EOF,
};
//�V�[���ؑւ����܂Ȃ��\�����Ǘ�����N���X
class Effect : public GameObject
{
    int hPict_[8];
    int effectID = 0;
    int nowFrame;
    Transform ImgTrans_[8];
    float sinx;
    float scaleVal;
    int clipping;
public:
    //�R���X�g���N�^
    Effect(GameObject* parent);

    //�f�X�g���N�^
    ~Effect();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //effect set
    void SetEffect(EFFECT_ID efid);

    //effect imageload
    void LoadImg(int hpict, std::string imgFile);
    //effect Init
    void Init();
};
