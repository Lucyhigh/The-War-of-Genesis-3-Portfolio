#pragma once
#include "GameNode.h"
#include "Cell.h"

struct tagAStarTile
{
	int tileNum;
	int parentNodeTileNum;
	int totalCost;          //F
	int costFromStart;      //G
	int costToGoal;         //H
	bool isOpen;
};

struct tagTilePoint
{
	float x;
	float y;
};

//���� Ŭ���� ���� Ÿ���� ������ ����ü
struct tagTempTile
{
	int fX;
	int fY;
};

class Astar : public GameNode
{
private:

    Cell		_cell[TILESIZEX * TILESIZEY];//Ÿ�ϰ���
	tagTilePoint	_tilePoint;//�� ĳ���� ������ Ÿ��
	tagTempTile		_tempTile;//Ŭ���� Ÿ��

	/////////////////////////////////////
	POINT			_pickingPt;

	bool			_moveUnMove;
	bool			_tempSaved;
	bool			_brushOn;
	bool			_objDelOn;
	bool			_menuInPt;
	bool			_dragMode;

	int _currentStage; // �� �������� �۾������� (���ǻ� 1,2,3)

	//########aStar���� ����###########
	vector<tagAStarTile*>			_vTotalList;
	vector<tagAStarTile*>::iterator _viTotalList;

	vector<tagAStarTile*>			_vOpenList;
	vector<tagAStarTile*>::iterator _viOpenList;

	vector<tagAStarTile*>			_vCloseList;
	vector<tagAStarTile*>::iterator _viCloseList;

	int _startTile;		//����Ÿ���� ��ȣ
	int _endTile;			//����Ÿ��
	int _currentTile;		//����Ÿ��

	bool _stop; // ��ã����
	bool _seePath;

	int _playerTile; // �÷��̾� ����� ��Ÿ�Ͽ� �ִ��� �ε��Ҷ� �ҷ��´�.
	int _enemyTile; // ���ʹ� ����� ��Ÿ�Ͽ� �ִ��� �ε��Ҷ� �ҷ��´�.

	int _modifyingNum; // ���ڸ���°�� ���������� (0=������x, 1õ�ڸ��� 2���ڸ��� 3���ڸ��� 4�����ڸ���)
	int _modifyingCount; // 5��ī��Ʈ

	float _dragX; float _dragY;
	bool _push;
public:
	vector<int> aStarPath(int fromTileNum, int toTileNum);

	//���� �ִ� ���� ã�Ƴ��� ����� �Լ�
	vector<tagAStarTile*> addOpenList(int currentTile);
	//���� ��� ã�� �Լ�
	void pathFinder(int currentTile);
};