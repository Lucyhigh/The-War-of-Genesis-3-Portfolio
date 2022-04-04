#pragma once
#include "GameNode.h"
#include "TurnSystem.h"
#include "Player.h"
#include "ProgressBar.h"
#include "MapTileInfo.h"
#include "GameUI.h"
#include "Saladin.h"
#include "Camera.h"
#include "AStar.h"

struct tagQMoveTile
{
	RECT _clickTileRect;
	int _cellX;
	int _cellY;
};
class FinalScene : public GameNode
{
private:
	MapTileInfo* _mapTileInfo;
	Animation* _aniCursor;
	Animation* _tileClick;
	Animation* _turnMark;
	ProgressBar* _hpBar;
	Player* _player;
	TurnSystem* _turnSystem;
	GameUI* _gameUI;
	vector<Cell*>* _cells;
	Image* _image;
	Saladin* _saladin;
	Camera* _camera;
	AStar::Generator* _generator;
    LPCWSTR _uiText[4];
	Cell* _cMoveStart;
	POINT _endPoint;
	POINT _enemyPathGoal;
	POINT _playerPathGoal;
    CELL_TYPE _mouseType;
    CELL_TYPE _beforeMouseType;

	RECT _mouseRc;
	RECT _endRc;
	RECT _moveRc;
	vector<POINT> _check;
	queue<pair<int,Cell*>> _qMoveTile;//
    vector<Cell*> _vMoveableTile;//
	//float _x, _y; //체력바 위치
	float _currentHp;
	float _maxHp;
	float _lerpPercentage;
	float _tileAlpha;
	int _mouseIndex;
	int _endPointIndex;
	int _moveIndex;
	int _count;
	int _enemyBit;

	bool _isMoveTileOn;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void drawMapCellInfo();
	void AstarTileInfo();
	void rectMoveToPath();
	void curAstar();
    void changeImage();
	//void showClickTile();
	void find4WaysTile();
	void Attack();
    //타일 4개를 여기에 넣을거임
    void computeShowMoveableTile(int range,Cell* cell,bool isMoveable);
    //여기안에 큐에 쌓여야함;;타일 정보를 큐에 쌓을거임
    void startShowMoveableTile(int range,Cell* cell,bool isMoveable);

	POINT lerp(POINT start, POINT end, float percentage);
public:
    FinalScene() : _uiText { L"형제여!", L" 평 지 ", L"99999",L"eld" }{}
	~FinalScene() {}
};
