#include "Stdafx.h"
#include "MapTileInfo.h"

void MapTileInfo::init(void)
{
	mapSetup();
}

void MapTileInfo::mapSetup()
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("map.json");

	auto map = root["map"];
	for (int y = 0; y < map.size(); ++y)
	{
		for (int x = 0; x < map[y].size(); ++x)
		{
			Cell* cell = new Cell;
			cell->init(x, y, (CELL_TYPE)map[y][x].asInt(), 
					   RectMake(x*TILESIZEX, y*TILESIZEY, TILESIZEX, TILESIZEY));
			_vCell.push_back(cell);
		}
	}
}
