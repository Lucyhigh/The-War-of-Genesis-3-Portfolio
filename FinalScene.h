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
	Player* _player;
	TurnSystem* _turnSystem;
	GameUI* _gameUI;
	vector<Cell*>* _cells;
	Image* _image;
	Saladin* _saladin;
	Camera* _camera;
	AStar::Generator* _generator;

	POINT _pPlayer;
	POINT _endPoint;
	RECT _mouseRc;
	RECT _endRc;
	RECT _moveRc;
	vector<POINT> _check;

	float _lerpPercentage;
	int _mouseIndex;
	int _endPointIndex;
	int _moveIndex;
	int _count;
	bool _isMove;

	int _enemyBit;

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
	POINT lerp(POINT start, POINT end, float percentage);
public:
	FinalScene() {}
	~FinalScene() {}
};
