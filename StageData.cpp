#include "StageData.h"
#include <windows.h>

void STAGE_DATA::ResizeX(int x)
{
	sData.resize(x, vector<vector<TILE_DATA>>(sData[0].size(), vector<TILE_DATA>(sData[0][0].size(), defaultTile)));
}

void STAGE_DATA::ResizeY(int y)
{
	for (size_t x = 0; x < sData.size(); x++) {
		sData[x].resize(sData[0].size(), vector<TILE_DATA>(sData[0][0].size(), defaultTile));
	}
}

void STAGE_DATA::ResizeZ(int z)
{
	for (size_t x = 0; x < sData.size(); x++) {
		for (size_t y = 0; y < sData[0].size(); y++) {
			sData[x][y].resize(z, defaultTile);
		}
	}
}

string StageData::GetStrTileFile(TILE_TAG tag)
{
	switch (tag)
	{
	case NONE:		return "";
	case SPAWN:		return ".fbx";
	case GOAL:		return "goal.fbx";
	case TERRAIN:	return "terrain.fbx";
	case ROTATE:	return "rotatepanel.fbx";
	case WARP:		return "warppanel.fbx";
	case SWITCH:	return ".fbx";
	case BLOCK_ITEM:return ".fbx";
	case ATTACK:	return ".fbx";
	case STOP:		return ".fbx";
	case HIGHJUMP:	return ".fbx";
	case MAX:		return ".fbx";
	default:		return ".fbx";
	}
	MessageBox(NULL, "error", "error", 0);
	return "";
}
