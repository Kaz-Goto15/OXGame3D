#include "ModelLoader.h"

#include <fstream>
#include <string>
#include "Include/nameof.hpp"
#include "Include/json.hpp"

#include "Engine/Model.h"

using json = nlohmann::json;
using namespace nameof;
using Model::NULL_HANDLE;

namespace ModelLoader {
	int handle[MODEL::MAX];
	json data;
	const char dataFile[] = "Data\\modelSource.json";
}

void ModelLoader::Init()
{
	std::fill_n(handle, MODEL::MAX, NULL_HANDLE);
	std::ifstream f(dataFile);
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

	return NULL_HANDLE;
}

void ModelLoader::ChangeAnim(int handle, string animName, float speed){

	std::string name = Model::GetModelName(handle);	//モデル名取得

	//モデル名・アニメーション名が合致したらアニメーションをする
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
}

/*
	"DEFAULT": "Cube.fbx",
	"Cube": "Cube.fbx",
	"Cylinder": "Cylinder.fbx",
	"Hanger": "Hanger.fbx",
*/