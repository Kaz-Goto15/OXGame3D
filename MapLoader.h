#pragma once
#include "Include/json.hpp"
#include <vector>
#include <string>

#include "Engine/GameObject.h"
#include "Field.h"
#include "Entity.h"

using std::vector;
using std::string;

namespace MapLoader
{
	//
	enum MAP {
		M_001,
		M_002
	};
	enum OBJECT {
		NONE,
		OBJ_F_CUBE,
		OBJ_F_RTP,
		OBJ_F_CYLINDER,
		OBJ_F_WATER,
		OBJ_E_PLAYER,
		OBJ_E_HANGER,
		OBJ_E_BOMB,
		OBJ_E_MUSHROOM,
		MAX,
	};
	NLOHMANN_JSON_SERIALIZE_ENUM(OBJECT,
		{
			{ NONE, nullptr },
			{ OBJ_F_CUBE, "Cube" },
			{ OBJ_F_RTP, "RTP" },
			{ OBJ_F_CYLINDER, "Cylinder" },
			{ OBJ_F_WATER, "Water" },
			{ OBJ_E_PLAYER, "Player" },
			{ OBJ_E_HANGER, "Hanger" },
			{ OBJ_E_BOMB, "Bomb" },
			{OBJ_E_MUSHROOM,"Mushroom" }
		});
	void Init();
	void Load(GameObject* pParent, vector<Field::FIELD_DATA>* pFieldData, vector<GameObject*>* pActiveFieldList, vector<GameObject*>* pEntityList, MAP mID);
	
	template<typename BasicJsonType>
	inline void to_json(BasicJsonType& j, const OBJECT& e);
	template<typename BasicJsonType>
	inline void from_json(const BasicJsonType& j, OBJECT& e);
};

