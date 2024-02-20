#include "TextLoader.h"

#include <fstream>
#include <string>
#include "Include/json.hpp"
#include "Include/nameof.hpp"
using json = nlohmann::json;
using namespace nameof;

void TextLoader::Load(TEXT_MEDIA tm, std::string &fileName, unsigned int &charWidth, unsigned int &charHeight, unsigned int &rowLength)
{
	std::ifstream f("charTextSource.json");
	json data = json::parse(f);

	fileName = data[NAMEOF_ENUM(tm)]["fileName"];
	charWidth = data[NAMEOF_ENUM(tm)]["charWidth"];
	charHeight = data[NAMEOF_ENUM(tm)]["charHeight"];
	rowLength = data[NAMEOF_ENUM(tm)]["rowLength"];
}
