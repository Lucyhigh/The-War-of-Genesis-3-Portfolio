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

    struct sCell
    {
        bool bObstacle = false;
        bool bVisited = false;
        float fGlobalGoal;
        float fLocalGoal;
        int x;
        int y;
        vector<sCell*> vecNeighbours;
        sCell* parent;
    };

    sCell* cells = nullptr;
    int nCellX = TILESIZEX;
    int nCellY = TILESIZEY;
    sCell* cellStart = nullptr;
    sCell* cellEnd = nullptr;

protected:
    virtual bool OnUserCreate()
    {
        cells = new sCell[nCellX * nCellY];
        for (int x = 0; x < nCellX; x++)
            for (int y = 0; y < nCellY; y++)
            {
                cells[y * nCellX + x].x = x;
                cells[y * nCellX + x].y = y;
                cells[y * nCellX + x].bObstacle = false;
                cells[y * nCellX + x].parent = nullptr;
                cells[y * nCellX + x].bVisited = false;
            }

        for (int x = 0; x < nCellX; x++)
            for (int y = 0; y < nCellY; y++)
            {
                if (y > 0)
                    cells[y*nCellX + x].vecNeighbours.push_back(&cells[(y - 1) * nCellX + (x + 0)]);
                if (y < nCellY - 1)
                    cells[y*nCellX + x].vecNeighbours.push_back(&cells[(y + 1) * nCellX + (x + 0)]);
                if (x > 0)
                    cells[y*nCellX + x].vecNeighbours.push_back(&cells[(y + 0) * nCellX + (x - 1)]);
                if (x < nCellX - 1)
                    cells[y*nCellX + x].vecNeighbours.push_back(&cells[(y + 0) * nCellX + (x + 1)]);

                cellStart = &cells[(nCellY / 2) * nCellX + 1];
                cellEnd = &cells[(nCellY / 2) * nCellX + nCellX - 2];
                return true;
            }
    }

    bool Solve_AStar()
    {
        for (int x = 0; x < nCellX; x++)
            for (int y = 0; y < nCellY; y++)
            {
                cells[y*nCellX + x].bVisited = false;
                cells[y*nCellX + x].fGlobalGoal = INFINITY;
                cells[y*nCellX + x].fLocalGoal = INFINITY;
                cells[y*nCellX + x].parent = nullptr;	 
            }

        auto distance = [](sCell* start, sCell* end)  
        {
            return sqrtf((start->x - end->x)*(start->x - end->x) + (start->y - end->y)*(start->y - end->y));
        };

        auto heuristic = [distance](sCell* start, sCell* end) 
        {
            return distance(start, end);
        };
        sCell* nodeCurrent = cellStart;
        cellStart->fLocalGoal = 0.0f;
        cellStart->fGlobalGoal = heuristic(cellStart, cellEnd);

        list<sCell*> listNotTestedNodes;
        listNotTestedNodes.push_back(cellStart);

        while (!listNotTestedNodes.empty() && nodeCurrent != cellEnd)
        {
            listNotTestedNodes.sort([](const sCell* lhs, const sCell* rhs) { return lhs->fGlobalGoal < rhs->fGlobalGoal; });

            while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
                listNotTestedNodes.pop_front();

            if (listNotTestedNodes.empty())
                break;

            nodeCurrent = listNotTestedNodes.front();
            nodeCurrent->bVisited = true;  


            for (auto nodeNeighbour : nodeCurrent->vecNeighbours)
            {
                if (!nodeNeighbour->bVisited && nodeNeighbour->bObstacle == 0)
                    listNotTestedNodes.push_back(nodeNeighbour);

                float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + distance(nodeCurrent, nodeNeighbour);

                if (fPossiblyLowerGoal < nodeNeighbour->fLocalGoal)
                {
                    nodeNeighbour->parent = nodeCurrent;
                    nodeNeighbour->fLocalGoal = fPossiblyLowerGoal;

                    nodeNeighbour->fGlobalGoal = nodeNeighbour->fLocalGoal + heuristic(nodeNeighbour, cellEnd);
                }
            }
        }

        return true;
    }
    //======================================
	int _x;
	int _y;

    int _startX;
    int _startY;
    int _endX;
    int _endY;//마우스로 클릭한 좌표값

    moveUnMove _moveState;//턴넘김으로 쓸려고 했는데 다른걸로 할듯(카메라도 생각하기)
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
    moveUnMove getMoveState(){ return this->_moveState; }
	RECT getRect() { return this->_cellRc; }
public:
	Cell() {}
	~Cell() {}
};

