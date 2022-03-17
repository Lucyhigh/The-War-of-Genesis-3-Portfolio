#include "Stdafx.h"
#include "Cell.h"

void Cell::init(int x, int y, CELL_TYPE cellType, RECT rect)
{
	_x = x;
	_y = y;
	_cellType = cellType;
}
