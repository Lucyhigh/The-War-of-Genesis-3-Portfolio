#pragma once
#include "GameNode.h"
#include "MapTileInfo.h"
#include "Player.h"
#include "Camera.h"

class TileScene : public GameNode
{
private:
	MapTileInfo* _mapTileInfo;
	vector<Cell*>* _cells;
	Image* _image;
	Player* _player;
	Camera* _camera;
	RECT _mouseRc;
	int _mouseIndex;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void drawMapCellInfo();
	void curMap();
public:
	TileScene() {}
	~TileScene() {}
};

