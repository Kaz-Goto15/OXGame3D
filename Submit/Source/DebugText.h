#pragma once
#include "Engine/GameObject.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class Text;

//デバッグテキストを管理するクラス
class DebugText : public GameObject
{
    Text* txt;
    vector<string*> pStrList_;
    POINT pos;
    int lineHeight;
public:
    DebugText(GameObject* parent);    //コンストラクタ
    ~DebugText();                     //デストラクタ
    void Initialize() override; //初期化
    void Update() override;     //更新
    void Draw() override;       //描画
    void Release() override;    //解放

    void AddStrPtr(string* pStr);
};