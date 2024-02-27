#pragma once
#include "Engine/GameObject.h"
#include <vector>

using std::vector;

class Text;
class Field;
class Entity;

class PlayScene : public GameObject
{
	Field* pField_;
	vector<GameObject*> pActiveFieldList_;
	vector<Entity*> pEntityList_;
public:
	PlayScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};