#include "ModelLoader.h"

#include <fstream>
#include <string>
#include "Include/nameof.hpp"
#include "Include/json.hpp"

#include "Engine/Model.h"
using json = nlohmann::json;
using namespace nameof;
namespace ModelLoader {
	json data;
}
void ModelLoader::Init()
{
	std::ifstream f("modelSource.json");
	data = json::parse(f);
}

int ModelLoader::Load(MODEL model)
{
	return Model::Load(data["Source"][NAMEOF_ENUM(model)]);
}
