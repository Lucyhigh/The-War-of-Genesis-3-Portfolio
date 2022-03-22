#pragma once
#include "GameNode.h"
#include "MapTileInfo.h"
#include "Player.h"
#include "Camera.h"
#include "AStar.h"

class TileScene : public GameNode
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
	vector<RECT> _check;
	int _mouseIndex;
	int _endPointIndex;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void drawMapCellInfo();
    void AstarTileInfo();
	void curAstar();
public:
	TileScene() {}
	~TileScene() {}
};

