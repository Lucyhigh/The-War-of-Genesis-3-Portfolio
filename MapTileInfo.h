#pragma once
#include "Cell.h"
#define TILESIZEX 40
#define TILESIZEY 32
class MapTileInfo
{
private:
	vector<Cell*> _vCell;
public:
	void init(void);
	void mapSetup(Cell* pMap = nullptr);

	vector<Cell*>* getCell() { return &this->_vCell; }

public:
	MapTileInfo() {}
	~MapTileInfo() {}
};

