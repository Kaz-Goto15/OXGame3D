#include "Screen.h"
#include "Engine/Image.h"

void Screen::DebugAction()
{
    
    LPSTR str = nullptr;
    GetWindowText(GetActiveWindow(), str, 0);
    str += *objectName_.c_str();
    SetWindowText(GetActiveWindow(),str);
}

//コンストラクタ
Screen::Screen(GameObject* parent, const std::string& name) :
    GameObject(parent, "Screen"),
    pPrevObject(nullptr)
{
    Leave();
    Invisible();
}

//デストラクタ
Screen::~Screen()
{
}

//初期化
void Screen::Initialize()
{
}

//更新
void Screen::Update()
{
}

//描画
void Screen::Draw()
{   
}

//開放
void Screen::Release()
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
