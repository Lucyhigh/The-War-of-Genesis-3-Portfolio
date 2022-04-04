#pragma once
//Ÿ���� ũ��
#define TILESIZEX 40
#define TILESIZEY 32

//Ÿ�ϰ���
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
    MOVEABLE,// �̵�����Ÿ�� 
	ATTACKABLE//�̵� �� �ߴ� 4���� Ÿ��
};

class Cell
{
protected:
	int _x;
	int _y;

    int _startX;
    int _startY;
    int _endX;
    int _endY;//���콺�� Ŭ���� ��ǥ��

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

