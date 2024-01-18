#include "StageData.h"
#include <windows.h>

//void STAGE_DATA::ResizeX(int x)
//{
//	sData.resize(x, vector<vector<TILE_DATA>>(sData[0].size(), vector<TILE_DATA>(sData[0][0].size(), defaultTile)));
//}
//
//void STAGE_DATA::ResizeY(int y)
//{
//	for (size_t x = 0; x < sData.size(); x++) {
//		sData[x].resize(sData[0].size(), vector<TILE_DATA>(sData[0][0].size(), defaultTile));
//	}
//}
//
//void STAGE_DATA::ResizeZ(int z)
//{
//	for (size_t x = 0; x < sData.size(); x++) {
//		for (size_t y = 0; y < sData[0].size(); y++) {
//			sData[x][y].resize(z, defaultTile);
//		}
//	}
//}

string StageData::GetStrTileFile(TILE_TAG tag)
{
	switch (tag)
	{
	case TILE_TAG::NONE:		return "";
	case TILE_TAG::SPAWN:		return ".fbx";
	case TILE_TAG::GOAL:		return "goal.fbx";
	case TILE_TAG::TERRAIN:	return "terrain.fbx";
	case TILE_TAG::ROTATE:	return "rotatepanel.fbx";
	case TILE_TAG::WARP:		return "warppanel.fbx";
	case TILE_TAG::SWITCH:	return ".fbx";
	case TILE_TAG::BLOCK_ITEM:return ".fbx";
	case TILE_TAG::ATTACK:	return ".fbx";
	case TILE_TAG::STOP:		return ".fbx";
	case TILE_TAG::HIGHJUMP:	return ".fbx";
	}
	MessageBox(NULL, "error", "error", 0);
	return "";
}

void StageData::ResizeX(STAGE_DATA* pData, int x)
{
		pData->sData.resize(x, vector<vector<TILE_DATA>>(pData->sData[0].size(), vector<TILE_DATA>(pData->sData[0][0].size(), defaultTile)));
}

void StageData::ResizeY(STAGE_DATA* pData, int y)
{
	for (size_t x = 0; x < pData->sData.size(); x++) {
		pData->sData[x].resize(pData->sData[0].size(), vector<TILE_DATA>(pData->sData[0][0].size(), defaultTile));
	}
}

void StageData::ResizeZ(STAGE_DATA* pData, int z)
{
	for (size_t x = 0; x < pData->sData.size(); x++) {
		for (size_t y = 0; y < pData->sData[0].size(); y++) {
			pData->sData[x][y].resize(z, defaultTile);
		}
	}
}
