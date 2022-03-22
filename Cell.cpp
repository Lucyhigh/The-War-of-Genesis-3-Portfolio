#include "Stdafx.h"
#include "Cell.h"

void Cell::init(int _x, int _y, CELL_TYPE cellType, RECT rect)
{
	this->x = _x;
	this->y = _y;
	this->cellType = cellType;
	this->cellRc = rect;
}
