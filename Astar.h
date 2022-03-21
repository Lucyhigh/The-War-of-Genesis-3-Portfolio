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

//내가 클릭한 현재 타일을 저장할 구조체
struct tagTempTile
{
	int fX;
	int fY;
};

class Astar : public GameNode
{
private:

    Cell		_cell[TILESIZEX * TILESIZEY];//타일갯수
	tagTilePoint	_tilePoint;//현 캐릭터 시작점 타일
	tagTempTile		_tempTile;//클릭한 타일

	/////////////////////////////////////
	POINT			_pickingPt;

	bool			_moveUnMove;
	bool			_tempSaved;
	bool			_brushOn;
	bool			_objDelOn;
	bool			_menuInPt;
	bool			_dragMode;

	int _currentStage; // 몇 스테이지 작업중인지 (편의상 1,2,3)

	//########aStar관련 변수###########
	vector<tagAStarTile*>			_vTotalList;
	vector<tagAStarTile*>::iterator _viTotalList;

	vector<tagAStarTile*>			_vOpenList;
	vector<tagAStarTile*>::iterator _viOpenList;

	vector<tagAStarTile*>			_vCloseList;
	vector<tagAStarTile*>::iterator _viCloseList;

	int _startTile;		//시작타일의 번호
	int _endTile;			//도착타일
	int _currentTile;		//현재타일

	bool _stop; // 못찾은거
	bool _seePath;

	int _playerTile; // 플레이어 깃발이 몇타일에 있는지 로드할때 불러온다.
	int _enemyTile; // 에너미 깃발이 몇타일에 있는지 로드할때 불러온다.

	int _modifyingNum; // 몇자리수째를 수정중인지 (0=수정중x, 1천자릿수 2백자릿수 3십자리수 4일의자리수)
	int _modifyingCount; // 5초카운트

	float _dragX; float _dragY;
	bool _push;
public:
	vector<int> aStarPath(int fromTileNum, int toTileNum);

	//갈수 있는 길을 찾아내서 담아줄 함수
	vector<tagAStarTile*> addOpenList(int currentTile);
	//빠른 경로 찾을 함수
	void pathFinder(int currentTile);
};