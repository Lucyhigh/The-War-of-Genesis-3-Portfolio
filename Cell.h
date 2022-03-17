#pragma once
enum class CELL_TYPE
{
	NORMAL,
	WALL,
	GOAL
};
class Cell
{
protected:
	int _x;
	int _y;

	CELL_TYPE _cellType;
	RECT _cellRc;
public:
	void init(int x, int y, CELL_TYPE cellType,RECT rect);
	int getCellX() { return this->_x; }
	int getCellY() { return this->_y; }

	CELL_TYPE getType() { return this->_cellType; }
	RECT getRECT() { return this->_cellRc; }
public:
	Cell() {}
	~Cell() {}
};

