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
	std::ifstream f("Data\\modelSource.json");
	data = json::parse(f);
}

int ModelLoader::Load(MODEL model)
{
	handle[model] = Model::Load(data["Source"][NAMEOF_ENUM(model)]);
	return handle[model];
}

void ModelLoader::ChangeAnim(MODEL model, string animName, float speed){
	Model::SetAnimFrame(
		handle[model],
		data["Source"][NAMEOF_ENUM(model)]["anim"][animName]["start"],
		data["Source"][NAMEOF_ENUM(model)]["anim"][animName]["end"],
		speed
	);
}

