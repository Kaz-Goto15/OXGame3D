#pragma once
#include "Engine/GameObject.h"

class GameEndImage : public GameObject
{
    int hImageO, hImageX;
    bool winner;                    //true=O false=X
    int MAX_IMG_ALPHA;				//�摜�A���t�@�l�ő�
    int WIN_IMG_ALPHA_PLUS;				//�摜�A���t�@�l���Z�l
    int winImageAlpha;				//�摜�A���t�@�l�i�[
public:
    GameEndImage(GameObject* parent);    //�R���X�g���N�^
    ~GameEndImage();                     //�f�X�g���N�^
    void Initialize() override; //������
    void Update() override;     //�X�V
    void Draw() override;       //�`��
    void Release() override;    //���

    /// <summary>
    /// ���҂��w�肷��
    /// </summary>
    /// <param name="isWinO">O���������Ȃ�true X���������Ȃ�false</param>
    void SetWinner(bool isWinO);
};