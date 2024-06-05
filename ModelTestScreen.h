#pragma once
#include <string>
#include <vector>
#include "Engine/GameObject.h"
#include "Screen.h"
class Cube;
class DebugText;

using std::vector;
//ä«óùÇ∑ÇÈÉNÉâÉX
class ModelTestScreen : public Screen
{
    int hModel;

    DebugText* debugtext;
    std::string debugStr[20];
    vector<vector<vector<Cube*>>> cube;
    void UpdateStr();

    enum ROTATE {
        FRONT,
        BACK,
        LEFT,
        RIGHT,
        CW,
        CCW
    };

    void CubeRotate(ROTATE rot, int col, float value);
public:
    ModelTestScreen(GameObject* parent);
    ~ModelTestScreen();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};