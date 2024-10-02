#include "GameEndImage.h"
#include "Engine/Image.h"

//�R���X�g���N�^
GameEndImage::GameEndImage(GameObject* parent)
    :GameObject(parent, "GameEndImage"),
    hImageO(-1),
    hImageX(-1),
    winner(true),
    MAX_IMG_ALPHA(255),
    WIN_IMG_ALPHA_PLUS(10),
    winImageAlpha(0)
{
}

//�f�X�g���N�^
GameEndImage::~GameEndImage()
{
}

//������
void GameEndImage::Initialize()
{
    //�摜�Ǎ�
    hImageO = Image::Load("Game\\p1win.png");
    hImageX = Image::Load("Game\\p2win.png");
}

//�X�V
void GameEndImage::Update()
{
}

//�`��
void GameEndImage::Draw()
{
    if (winImageAlpha < MAX_IMG_ALPHA) {
        winImageAlpha += WIN_IMG_ALPHA_PLUS;
        if (winImageAlpha > MAX_IMG_ALPHA)winImageAlpha = MAX_IMG_ALPHA;
    }
    if (winner) {
        Image::SetAlpha(hImageO, winImageAlpha);
        Image::Draw(hImageO);
    }
    else {
        Image::SetAlpha(hImageX, winImageAlpha);
        Image::Draw(hImageX);
    }
}

//�J��
void GameEndImage::Release()
{
}

void GameEndImage::SetWinner(bool isWinO)
{
    winner = isWinO;
    winImageAlpha = 0;
}
