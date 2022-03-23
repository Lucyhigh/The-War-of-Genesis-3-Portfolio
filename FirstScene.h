#pragma once
#include "GameNode.h"
#include "MapTileInfo.h"
#include "Player.h"
#include "Camera.h"
#include "AStar.h"

class FirstScene : public GameNode
{
private:
	MapTileInfo* _mapTileInfo;
	vector<Cell*>* _cells;
	Image* _image;
	Player* _player;
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

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void drawMapCellInfo();
    void AstarTileInfo();
    void rectMoveToPath();
	void curAstar();
	POINT lerp(POINT start, POINT end, float percentage);
public:
	FirstScene() {}
	~FirstScene() {}
};

