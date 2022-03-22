#pragma once
#include "Stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class OneLoneCoder_PathFinding
{

private:

    struct sNode
    {
        bool bObstacle = false;			// Is the node an obstruction?
        bool bVisited = false;			// Have we searched this node before?
        float fGlobalGoal;				// Distance to goal so far
        float fLocalGoal;				// Distance to goal if we took the alternative route
        int x;							// Nodes position in 2D space
        int y;
        vector<sNode*> vecNeighbours;	// Connections to neighbours
        sNode* parent;					// Node connecting to this node that offers shortest parent
    };

    sNode *nodes = nullptr;
    int nMapWidth = 16;
    int nMapHeight = 16;

    sNode *nodeStart = nullptr;
    sNode *nodeEnd = nullptr;


protected:
    virtual bool OnUserCreate()
    {
        // Create a 2D array of nodes - this is for convenience of rendering and construction
        // and is not required for the algorithm to work - the nodes could be placed anywhere
        // in any space, in multiple dimensions...
        nodes = new sNode[nMapWidth * nMapHeight];
        for (int x = 0; x < nMapWidth; x++)
            for (int y = 0; y < nMapHeight; y++)
            {
                nodes[y * nMapWidth + x].x = x; // ...because we give each node its own coordinates
                nodes[y * nMapWidth + x].y = y;
                nodes[y * nMapWidth + x].bObstacle = false;
                nodes[y * nMapWidth + x].parent = nullptr;
                nodes[y * nMapWidth + x].bVisited = false;
            }

        // Create connections - in this case nodes are on a regular grid
        for (int x = 0; x < nMapWidth; x++)
            for (int y = 0; y < nMapHeight; y++)
            {
                if (y > 0)
                    nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x + 0)]);
                if (y < nMapHeight - 1)
                    nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x + 0)]);
                if (x > 0)
                    nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * nMapWidth + (x - 1)]);
                if (x < nMapWidth - 1)
                    nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * nMapWidth + (x + 1)]);

                // We can also connect diagonally
                /*if (y>0 && x>0)
                    nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x - 1)]);
                if (y<nMapHeight-1 && x>0)
                    nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x - 1)]);
                if (y>0 && x<nMapWidth-1)
                    nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x + 1)]);
                if (y<nMapHeight - 1 && x<nMapWidth-1)
                    nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x + 1)]);
                */
            }

        // Manually positio the start and end markers so they are not nullptr
        nodeStart = &nodes[(nMapHeight / 2) * nMapWidth + 1];
        nodeEnd = &nodes[(nMapHeight / 2) * nMapWidth + nMapWidth - 2];
        return true;
    }

    bool Solve_AStar()
    {
        // Reset Navigation Graph - default all node states
        for (int x = 0; x < nMapWidth; x++)
            for (int y = 0; y < nMapHeight; y++)
            {
                nodes[y*nMapWidth + x].bVisited = false;
                nodes[y*nMapWidth + x].fGlobalGoal = INFINITY;
                nodes[y*nMapWidth + x].fLocalGoal = INFINITY;
                nodes[y*nMapWidth + x].parent = nullptr;	// No parents
            }

        auto distance = [](sNode* a, sNode* b) // For convenience
        {
            return sqrtf((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
        };

        auto heuristic = [distance](sNode* a, sNode* b) // So we can experiment with heuristic
        {
            return distance(a, b);
        };

        // Setup starting conditions
        sNode *nodeCurrent = nodeStart;
        nodeStart->fLocalGoal = 0.0f;
        nodeStart->fGlobalGoal = heuristic(nodeStart, nodeEnd);

        // Add start node to not tested list - this will ensure it gets tested.
        // As the algorithm progresses, newly discovered nodes get added to this
        // list, and will themselves be tested later
        list<sNode*> listNotTestedNodes;
        listNotTestedNodes.push_back(nodeStart);

        // if the not tested list contains nodes, there may be better paths
        // which have not yet been explored. However, we will also stop 
        // searching when we reach the target - there may well be better
        // paths but this one will do - it wont be the longest.
        while (!listNotTestedNodes.empty() && nodeCurrent != nodeEnd)// Find absolutely shortest path // && nodeCurrent != nodeEnd)
        {
            // Sort Untested nodes by global goal, so lowest is first
            listNotTestedNodes.sort([](const sNode* lhs, const sNode* rhs) { return lhs->fGlobalGoal < rhs->fGlobalGoal; });

            // Front of listNotTestedNodes is potentially the lowest distance node. Our
            // list may also contain nodes that have been visited, so ditch these...
            while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
                listNotTestedNodes.pop_front();

            // ...or abort because there are no valid nodes left to test
            if (listNotTestedNodes.empty())
                break;

            nodeCurrent = listNotTestedNodes.front();
            nodeCurrent->bVisited = true; // We only explore a node once


            // Check each of this node's neighbours...
            for (auto nodeNeighbour : nodeCurrent->vecNeighbours)
            {
                // ... and only if the neighbour is not visited and is 
                // not an obstacle, add it to NotTested List
                if (!nodeNeighbour->bVisited && nodeNeighbour->bObstacle == 0)
                    listNotTestedNodes.push_back(nodeNeighbour);

                // Calculate the neighbours potential lowest parent distance
                float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + distance(nodeCurrent, nodeNeighbour);

                // If choosing to path through this node is a lower distance than what 
                // the neighbour currently has set, update the neighbour to use this node
                // as the path source, and set its distance scores as necessary
                if (fPossiblyLowerGoal < nodeNeighbour->fLocalGoal)
                {
                    nodeNeighbour->parent = nodeCurrent;
                    nodeNeighbour->fLocalGoal = fPossiblyLowerGoal;

                    // The best path length to the neighbour being tested has changed, so
                    // update the neighbour's score. The heuristic is used to globally bias
                    // the path algorithm, so it knows if its getting better or worse. At some
                    // point the algo will realise this path is worse and abandon it, and then go
                    // and search along the next best path.
                    nodeNeighbour->fGlobalGoal = nodeNeighbour->fLocalGoal + heuristic(nodeNeighbour, nodeEnd);
                }
            }
        }

        return true;
    }

    virtual bool OnUserUpdate(float fElapsedTime)
    {
        int nNodeSize = 9;
        int nNodeBorder = 2;

        // Use integer division to nicely get cursor position in node space
        int nSelectedNodeX = m_mousePosX / nNodeSize;
        int nSelectedNodeY = m_mousePosY / nNodeSize;

        if (m_mouse[0].bReleased) // Use mouse to draw maze, shift and ctrl to place start and end
        {
            if (nSelectedNodeX >= 0 && nSelectedNodeX < nMapWidth)
                if (nSelectedNodeY >= 0 && nSelectedNodeY < nMapHeight)
                {
                    if (m_keys[VK_SHIFT].bHeld)
                        nodeStart = &nodes[nSelectedNodeY * nMapWidth + nSelectedNodeX];
                    else if (m_keys[VK_CONTROL].bHeld)
                        nodeEnd = &nodes[nSelectedNodeY * nMapWidth + nSelectedNodeX];
                    else
                        nodes[nSelectedNodeY * nMapWidth + nSelectedNodeX].bObstacle = !nodes[nSelectedNodeY * nMapWidth + nSelectedNodeX].bObstacle;

                    Solve_AStar(); // Solve in "real-time" gives a nice effect
                }
        }

        // Draw Connections First - lines from this nodes position to its
        // connected neighbour node positions
        Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');
        for (int x = 0; x < nMapWidth; x++)
            for (int y = 0; y < nMapHeight; y++)
            {
                for (auto n : nodes[y*nMapWidth + x].vecNeighbours)
                {
                    DrawLine(x*nNodeSize + nNodeSize / 2, y*nNodeSize + nNodeSize / 2,
                        n->x*nNodeSize + nNodeSize / 2, n->y*nNodeSize + nNodeSize / 2, PIXEL_SOLID, FG_DARK_BLUE);
                }
            }

        // Draw Nodes on top
        for (int x = 0; x < nMapWidth; x++)
            for (int y = 0; y < nMapHeight; y++)
            {

                Fill(x*nNodeSize + nNodeBorder, y*nNodeSize + nNodeBorder,
                    (x + 1)*nNodeSize - nNodeBorder, (y + 1)*nNodeSize - nNodeBorder,
                    PIXEL_HALF, nodes[y * nMapWidth + x].bObstacle ? FG_WHITE : FG_BLUE);

                if (nodes[y * nMapWidth + x].bVisited)
                    Fill(x*nNodeSize + nNodeBorder, y*nNodeSize + nNodeBorder, (x + 1)*nNodeSize - nNodeBorder, (y + 1)*nNodeSize - nNodeBorder, PIXEL_SOLID, FG_BLUE);

                if (&nodes[y * nMapWidth + x] == nodeStart)
                    Fill(x*nNodeSize + nNodeBorder, y*nNodeSize + nNodeBorder, (x + 1)*nNodeSize - nNodeBorder, (y + 1)*nNodeSize - nNodeBorder, PIXEL_SOLID, FG_GREEN);

                if (&nodes[y * nMapWidth + x] == nodeEnd)
                    Fill(x*nNodeSize + nNodeBorder, y*nNodeSize + nNodeBorder, (x + 1)*nNodeSize - nNodeBorder, (y + 1)*nNodeSize - nNodeBorder, PIXEL_SOLID, FG_RED);

            }


        // Draw Path by starting ath the end, and following the parent node trail
        // back to the start - the start node will not have a parent path to follow
        if (nodeEnd != nullptr)
        {
            sNode *p = nodeEnd;
            while (p->parent != nullptr)
            {
                DrawLine(p->x*nNodeSize + nNodeSize / 2, p->y*nNodeSize + nNodeSize / 2,
                    p->parent->x*nNodeSize + nNodeSize / 2, p->parent->y*nNodeSize + nNodeSize / 2, PIXEL_SOLID, FG_YELLOW);

                // Set next node to this node's parent
                p = p->parent;
            }
        }

        return true;
    }

};

int main()
{
    OneLoneCoder_PathFinding game;
    game.ConstructConsole(160, 160, 6, 6);
    game.Start();
    return 0;
}

//#include "Cell.h"
//
//
///* Astar Class Infor
//
//// 클래스의 생성.
//Astar::Coordinate SP(0,0);
//Astar::Coordinate DP(0,4);
//Astar astar(SP, DP); // 텍스트 맵을 불러와 초기화, 출발지와 목적지 설정 및 길 찾기 함수까지 실행.
//
//// 출력
//astar.PrintPath(); // 경로의 좌표를 순차적으로 출력. ex) 00 01 02 12 ...
//astar.PrintMap(); // astar에 저장되어 있는 맵을 출력
//astar.PrintNavi(); // 맵을 출력하되 astar 경로를 숫자 7로 표시
//
//// 경로를 가져오기
/// 좌표 가져오기(GetPos(순서))
//astar.GetPos(1); // 1번째 경로의 좌표를 가져옴
//ex) cout << astar.GetPos(1).x << astar.GetPos(1).y << endl;
//
/// 경로 전체를 리스트로 가져오기(GetPath()) - 큐
//list<Astar::Coordinate*> path = astar.GetPath();
//list<Astar::Coordinate*>::iterator iter = path.begin();
//
//// 길 찾기
//astar.FindPath(); // 길 찾기를 다시 실행(맵이 수정되었을 경우 실행해야 함)
//
//*/
//
//class Astar
//{
//public:
//	class Coordinate
//	{
//	public:
//		int x;
//		int y;
//        
//		void Set(int _x = 0, int _y = 0)
//		{
//			x = _x; y = _y;
//		}
//	public:
//		Coordinate() {}
//		Coordinate(int _x, int _y) : x(_x), y(_y) {}
//	};
//
//	class Node
//	{
//	public:
//		Coordinate point;
//		Coordinate end;
//		int F, G, H;     // F = 비용, G = 지난 거리, H = 남은 거리
//
//		Node* pParent;
//
//	public:
//		Node(int _x, int _y, Node* _pParent, Coordinate _EndPoint);
//		Node() {}
//		~Node() {}
//	};
//
//	class Map
//	{
//    private:
//        vector<Cell*> _vCell;
//
//    public:
//        void init(void);
//        void mapSetup();
//
//        vector<Cell*>* getCell() { return &this->_vCell; }
//        Cell* getCell(int x, int y)
//        {
//            for (int i = 0; i < _vCell.size(); ++i)
//            {
//                if (x == _vCell[i]->getCellX() && y == _vCell[i]->getCellY())
//                    return _vCell[i];
//            }
//        }
//
//	public:
//		int sizeX, sizeY;
//		int** nMap;
//	public:
//		void Copy(Map* _map);
//		void PrintMap();
//	public:
//		Map();
//		~Map();
//	};
//
//
//
//private: // 내부 함수
//	list<Coordinate*> FindPath(Map* Navi, Coordinate StartPoint, Coordinate EndPoint);
//	list<Node*>::iterator FindNextNode(list<Node*>* pOpenNode); // 오픈노드 중 F값이 제일 작은 노드 찾아서 반환
//	list<Node*>::iterator FindCoordNode(int x, int y, list<Node*>* NodeList); // 노드리스트에서 x,y 좌표의 노드를 찾아서 주소를 반환. 없으면 end()반환.
//	void ExploreNode(Map* Navi, Node* SNode, list<Node*>* OpenNode, list<Node*>* CloseNode, Coordinate EndPoint); // 8방향 노드를 탐색하고 열린 노드에 추가 및 부모 변경을 실행함
//
//public:
//	void FindPath();
//	Coordinate GetPos(int order); // order번째 경로의 좌표를 받아옴
//	list<Coordinate*> GetPath() { return path; } // 경로를 Coordinate* 리스트로 통째로 받아옴
//
//    void PrintMoveAbleTile();
//	void PrintPath();
//	void PrintMap();
//	void PrintNavi();
//	void SetFree(int _x, int _y);
//	void SetObstacle(int _x, int _y);
//private:
//	Map Navi; // 맵 생성
//	Map printNavi; // 출력용 맵 생성(경로까지 출력)
//
//private:
//	Coordinate StartPoint; // 출발지점
//	Coordinate EndPoint; // 목표지점
//	list<Coordinate*> path; // 경로
//	list<Coordinate*>::iterator iter; // 경로 iterator
//
//public:
//	Astar(Coordinate _StartPoint, Coordinate _EndPoint)
//	{
//		StartPoint.x = _StartPoint.x; StartPoint.y = _StartPoint.y;
//		EndPoint.x = _EndPoint.x; EndPoint.y = _EndPoint.y;
//		FindPath();
//	}
//	~Astar()
//	{ // path 동적할당 해제
//		iter = path.begin();
//		for (; iter != path.end(); iter++)
//		{
//			delete *iter;
//		}
//	}
//};
