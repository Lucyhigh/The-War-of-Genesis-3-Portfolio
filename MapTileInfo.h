#pragma once
#include "Cell.h"

class MapTileInfo
{
private:
	vector<Cell*> _vCell;

public:
	void init(void);
	void mapSetup();

	vector<Cell*>* getCell() { return &this->_vCell; }
	Cell* getCell(int x, int y) 
	{ 
        for (int i = 0; i < _vCell.size(); ++i)
        {
			if (x == _vCell[i]->getCellX() && y == _vCell[i]->getCellY())
				return _vCell[i];
        }
	}


public:
	MapTileInfo() {}
	~MapTileInfo() {}
};

