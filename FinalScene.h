#pragma once
#include "GameNode.h"
#include "TurnSystem.h"
#include "Player.h"

#include "MapTileInfo.h"
#include "GameUI.h"
#include "Saladin.h"
#include "Camera.h"
#include "AStar.h"


class FinalScene : public GameNode
{
private:
	MapTileInfo* _mapTileInfo;
	Animation* _animation;
	Player* _player;
	TurnSystem* _turnSystem;
	GameUI* _gameUI;
	vector<Cell*>* _cells;
	Image* _image;
	Saladin* _saladin;
	Camera* _camera;
	AStar::Generator* _generator;
    LPCWSTR _uiText[3];
	POINT _pMoveStart;
	POINT _endPoint;
	POINT _enemyPathGoal;

	RECT _mouseRc;
	RECT _endRc;
	RECT _moveRc;
	vector<POINT> _check;
	float _lerpPercentage;
	float _tileAlpha;
	int _mouseIndex;
	int _endPointIndex;
	int _moveIndex;
	int _count;
	bool _isMove;

	int _enemyBit;
    CELL_TYPE _mouseType;
    CELL_TYPE _beforeMouseType;

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
	void find4WaysTile();
	void Attack();
	POINT lerp(POINT start, POINT end, float percentage);
public:
    FinalScene() : _uiText { L"형제여!", L" 평 지 ", L"10000" } {}
	~FinalScene() {}
};
