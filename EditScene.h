#pragma once
#include <vector>
#include "Engine/GameObject.h"

using std::vector;

//class StageView;
//class StageTheme;
//class StageEditGUI;

class EditScene : public GameObject
{
public:
	EditScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:
	static const int LOGO_COUNT = 2;
	static const int DRAW_TIME = 1000;
	int hLogo_[LOGO_COUNT];
	bool isDisplaying = false;
	int queue_, drawTime_;
	XMINT3 mapSize;
	vector<vector<vector<int>>> mapData_;
	//StageView pView;
	//StageTheme pTheme;
	//StageEditGUI pEditGUI;
	enum STATE {
		S_Edit_START,
		S_Edit_MAIN,
		S_Edit_END,
		S_STAGETEST,
	}state_ = S_Edit_START;

	void EditStart();
	void EditMain();
	void EditEnd();
	void NextScene();
	enum TILE_TAG {
		NONE,
		SPAWN,
		GOAL,
		TERRAIN,
		ROTATE,
		WARP,
		SWITCH,
		BLOCK_ITEM,
		ATTACK,
		STOP,
		HIGHJUMP,
	};
	struct TILE_DATA {
		TILE_TAG tag;
		vector<int> property;
	};

	void LoadStageData();
};