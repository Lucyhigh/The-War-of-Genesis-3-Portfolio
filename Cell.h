#pragma once
#define TILESIZEX 40
#define TILESIZEY 32

enum class CELL_TYPE
{
	NORMAL,
	WALL,
	START,
	GOAL,
    MOVEABLE
};

enum class moveUnMove
{
    MOVE, UNMOVE
};

enum class menuNum
{
    ONE = 1, TWO, THREE
};


class Cell
{
private:
    bool _bObstacle = false;
    bool _bVisited = false;
    float _fGlobalGoal;
    float _fLocalGoal;
    int _x;
    int _y;

    int _startX;
    int _startY;
    int _endX;
    int _endY;//마우스로 클릭한 좌표값

    vector<Cell*> _vCell;
    vector<Cell*> vecNeighbours;
    Cell* parent;
    moveUnMove moveState;//턴넘김으로 쓸려고 했는데 다른걸로 할듯(카메라도 생각하기)
    CELL_TYPE cellType;
    RECT cellRc;

public:

	void init(int x, int y, CELL_TYPE cellType,RECT rect);
	int getCellX() { return this->_x; }
	int getCellY() { return this->_y; }

    int getStartCellX() { return this->_startX; }
    int getStartCellY() { return this->_startY; }

    int getEndCellX() { return this->_endX; }
    int getEndCellY() { return this->_endY; }

    void setEndCellX(int endX) { this->_endX = endX; }
    void setEndCellY(int endY) { this->_endY = endY; }

	CELL_TYPE getType() { return this->cellType; }
	void setType(CELL_TYPE cellType) { this->cellType = cellType; }
    moveUnMove getMoveState(){ return this->moveState; }
	RECT getRect() { return this->cellRc; }
public:
	Cell() {}
	~Cell() {}
};

