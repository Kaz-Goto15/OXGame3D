#include "TextLoader.h"

#include <fstream>
#include <string>
#include "Include/json.hpp"
#include "Include/nameof.hpp"
using json = nlohmann::json;
using namespace nameof;

void TextLoader::Load(TEXT_SOURCE source, std::string &fileName, unsigned int &charWidth, unsigned int &charHeight, unsigned int &rowLength)
{
	std::ifstream f("Data\\charTextSource.json");
	json data = json::parse(f);

	fileName = data[NAMEOF_ENUM(source)]["fileName"];
	charWidth = data[NAMEOF_ENUM(source)]["charWidth"];
	charHeight = data[NAMEOF_ENUM(source)]["charHeight"];
	rowLength = data[NAMEOF_ENUM(source)]["rowLength"];
}
