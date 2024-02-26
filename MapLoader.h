#pragma once
#include "Engine/GameObject.h"
#include <vector>
#include <string>
using std::vector;
using std::string;

namespace MapLoader
{
	vector<string> objNameList;
	enum MAP {
		M_001,
		M_002
	};
	enum OBJECT {
		NONE,
		OBJ_CUBE,
		OBJ_RTP,
		OBJ_CYLINDER,
		OBJ_WATER,
		OBJ_PLAYER,
		OBJ_HANGER,
		OBJ_BOMB,
		OBJ_MUSHROOM,
		MAX,
	};

	void Init();
	void Load(GameObject* parent, vector<GameObject*>* pGameObjectList, MAP mID);
};

