#pragma once
//타일의 크기
#define TILESIZEX 40
#define TILESIZEY 32

//타일갯수
#define STAGE1TILEX 53
#define STAGE1TILEY 49

#define STAGE2TILEX 53
#define STAGE2TILEY 49

#define STAGE3TILEX 39
#define STAGE3TILEY 34

enum class CELL_TYPE
{
	NORMAL,
	WALL,
	START,
	GOAL,
    MOVEPATH,
    MOVEABLE,// 이동가능타일 
	ATTACKABLE//이동 후 뜨는 4방향 타일
};

class Cell
{
protected:
	int _x;
	int _y;

    int _startX;
    int _startY;
    int _endX;
    int _endY;//마우스로 클릭한 좌표값

	CELL_TYPE _cellType;
	RECT _cellRc;
public:
	void init(int x, int y, CELL_TYPE cellType,RECT rect);
	int getCellX() { return this->_x; }
	int getCellY() { return this->_y; }

    int getStartCellX() { return this->_startX; }
    int getStartCellY() { return this->_startY; }

    int getEndCellX() { return this->_endX; }
    int getEndCellY() { return this->_endY; }

    void setEndCellX(int endX) { _endX = endX; }
    void setEndCellY(int endY) { _endY = endY; }

	CELL_TYPE getType() { return this->_cellType; }
	void setType(CELL_TYPE cellType) { _cellType = cellType; }
	RECT getRect() { return this->_cellRc; }
public:
	Cell() {}
	~Cell() {}
};

