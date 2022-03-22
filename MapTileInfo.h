#pragma once
#include "Cell.h"

class MapTileInfo
{
private:
	
    Cell* cells = nullptr;
    Cell* cellStart = nullptr;
    Cell* cellEnd = nullptr;

    vector<Cell*> _vCell;

    int nCellX = TILESIZEX;
    int nCellY = TILESIZEY;

protected:
    virtual bool OnUserCreate()
    {
        Cell* cells = new Cell[nCellX * nCellY];
        for (int x = 0; x < nCellX; x++)
            for (int y = 0; y < nCellY; y++)
            {
                cells[y * nCellX + x]->_x = x;
                cells[y * nCellX + x]->_y = y;
                cells[y * nCellX + x]->_bObstacle = false;
                cells[y * nCellX + x]->_bVisited = false;
                cells[y * nCellX + x]->_parent = nullptr;
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

