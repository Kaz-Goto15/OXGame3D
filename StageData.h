#pragma once
#include <vector>
#include <string>

using std::vector;
using std::string;

//タイル属性
enum class TILE_TAG {
	NONE,
	SPAWN,
	GOAL,
	TERRAIN,
	ROTATE,
	WARP,
	SWITCH,
	BLOCK_ITEM,
	ATTACK,
	STOP,
	HIGHJUMP,
	MAX
};
enum class ROTATE {
	NORTH = 0,
	WEST,
	SORTH,
	EAST
};
//タイルデータ
struct TILE_DATA {
	TILE_TAG tag;
	ROTATE rot;
	vector<int> property;
};
struct int3 {
	int x;
	int y;
	int z;
};
//ステージデータ
struct STAGE_DATA {
	vector<vector<vector<TILE_DATA>>> sData;
	int3 stageRange;
	//void ResizeX(int x);
	//void ResizeY(int y);
	//void ResizeZ(int z);

	void Init();
};

class StageData
{
public:
	string GetStrTileFile(TILE_TAG tag);
	//※xyを横縦、zを高さとしている

private:
	void ResizeX(STAGE_DATA* pData, int x);
	void ResizeY(STAGE_DATA* pData, int y);
	void ResizeZ(STAGE_DATA* pData, int z);
	TILE_DATA defaultTile = { TILE_TAG::NONE, ROTATE::NORTH, vector<int>(1,0) };
};

