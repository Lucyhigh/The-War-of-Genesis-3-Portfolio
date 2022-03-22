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
    int _endY;//���콺�� Ŭ���� ��ǥ��

    vector<Cell*> _vCell;
    vector<Cell*> vecNeighbours;
    Cell* parent;
    moveUnMove moveState;//�ϳѱ����� ������ �ߴµ� �ٸ��ɷ� �ҵ�(ī�޶� �����ϱ�)
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

