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

//コンストラクタ
Screen::Screen(GameObject* parent, const std::string& name) :
    GameObject(parent, name),
    pPrevObject(nullptr)
{
    Leave();
    Invisible();
}

//デストラクタ
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
    KillMe();   //いったんアニメーションは無し
}

void Screen::Run()
{
    Enter();
    Visible();
    pPrevObject->Leave();
}
