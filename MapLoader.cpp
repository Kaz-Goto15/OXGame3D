#include "MapLoader.h"

#include <fstream>
#include <string>
#include "Include/json.hpp"
#include "Include/nameof.hpp"

#include "GameSceneObject.h"
#define GAMEOBJECT GameObject;

using json = nlohmann::json;
using namespace nameof;


void MapLoader::Init()
{
	GameObject* maploadRoot = Instantiate<GAMEOBJECT>(nullptr);
	vector<GameObject*> objectList;

	//オブジェクトの種類追加するたびに追加
	//objectList.push_back(Instantiate<GameSceneObject>(maploadRoot));

	for (auto& it : objectList) {
		objNameList.push_back(it->GetObjectName());
	}
	maploadRoot->ReleaseSub();
	objectList.clear();
}


void MapLoader::Load(GameObject* parent, std::vector<GameObject*>* pGameObjectList, MAP mID)
{
	std::ifstream f;
	switch (mID)
	{
	case MapLoader::M_001:	f.open("map1.json");	break;
	case MapLoader::M_002:	f.open("map2.json");	break;
	}
	json data = json::parse(f);

	for (int i = 0; i < data["mapData"].size(); i + ) {
		GameObject* gso = nullptr;
	}
	GameObject* gso = nullptr;
	switch (objectName)
	{
	case MapLoader::M_001:
		gso = Instantiate<GameObject>(parent);
		break;
	default:
		break;
	}
	//fileName = data["mapData"]["objName"];

	gso->SetPosition(0, 0, 0);
	gso->SetRotate(0, 0, 0);
	gso->SetScale(1, 1, 1);
	pGameObjectList->push_back(gso);
	//多分Load後に消え失せる？
}