#pragma once
#include "Engine/GameObject.h"
#include <vector>

using std::vector;

class Text;
class Field;
class Entity;

class PlayScene : public GameObject
{
	int hBackground_;
	Field* pField_;
	vector<GameObject*> pActiveFieldList_;
	vector<GameObject*> pEntityList_;

	int temp;
	int count;
	const int MAX_COUNT = 300;

public:
	PlayScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};