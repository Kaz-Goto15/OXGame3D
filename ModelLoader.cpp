#include "ModelLoader.h"

#include <fstream>
#include <string>
#include "Include/nameof.hpp"
#include "Include/json.hpp"

#include "Engine/Model.h"
using json = nlohmann::json;
using namespace nameof;
namespace ModelLoader {
	int handle[MODEL::MAX];
	json data;
}
void ModelLoader::Init()
{
	std::fill_n(handle, MODEL::MAX, -1);
	std::ifstream f("Data\\modelSource.json");
	data = json::parse(f);
}

int ModelLoader::Load(MODEL model)
{
	for (auto& j : data["Source"]) {
		if (j["name"] == (std::string)NAMEOF_ENUM(model)) {
			handle[model] = Model::Load(j["file"]);
			return handle[model];
		}
	}
	return -1;
	//handle[model] = Model::Load(data["Source"][NAMEOF_ENUM(model)]["file"]);
	//return handle[model];
}

void ModelLoader::ChangeAnim(int handle, string animName, float speed){
	std::string name = Model::GetModelName(handle);	//モデル名取得

	//モデル名のキーと合致したら
	for (auto& src : data["Source"]) {
		if (src["file"] == name) {
			for (auto& anm : src["anim"]) {
				if (anm["name"] == animName) {
					Model::SetAnimFrame(
						handle,
						anm["start"],
						anm["end"],
						speed
					);
					break;
				}
			}
		}
	}
	//for (int i = 0; i < data["Source"].size(); i++) {
	//	if (data["Source"][i]["file"] == name) {

	//		//そのキー内のanim/nameを検索
	//		for (int j = 0; j < data["Source"][i]["anim"].size(); j++) {
	//			if (data["Source"][i]["anim"][j]["name"] == animName) {
	//				Model::SetAnimFrame(
	//					handle,
	//					data["Source"][i]["anim"][j]["start"],
	//					data["Source"][i]["anim"][j]["end"],
	//					speed
	//				);
	//				break;
	//			}
	//		}
	//	}
	//}
}

/*
	"DEFAULT": "Cube.fbx",
	"Cube": "Cube.fbx",
	"Cylinder": "Cylinder.fbx",
	"Hanger": "Hanger.fbx",
	
	
	*/