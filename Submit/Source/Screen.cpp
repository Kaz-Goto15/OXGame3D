#include "Screen.h"
#include "Engine/Image.h"
#include <string>
void Screen::DebugAction()
{
    char str[8];
    GetWindowTextA(GetForegroundWindow(), str, 8);
    std::string out = str;
    out += "   " + objectName_ ;
    SetWindowText(GetActiveWindow(),out.c_str());
}

//�R���X�g���N�^
Screen::Screen(GameObject* parent, const std::string& name) :
    GameObject(parent, name),
    pPrevObject(nullptr)
{
    Leave();
    Invisible();
}

//�f�X�g���N�^
Screen::~Screen()
{
}

void Screen::SetPrevScene(GameObject* prevScene)
{
    pPrevObject = prevScene;
}

void Screen::Prev()
{
    pPrevObject->Enter();
    KillMe();   //��������A�j���[�V�����͖���
}

void Screen::Run()
{
    Enter();
    Visible();
    pPrevObject->Leave();
}
