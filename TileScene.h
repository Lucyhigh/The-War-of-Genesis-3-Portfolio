#pragma once
#pragma once
#include "GameNode.h"
#include "Camera.h"
#include "Player.h"
#include "MapTileInfo.h"

//enum class TILEINDEX
//{
//	NORMAL =0,
//	START,
//	END,
//	WALL
//};
struct tagTile
{
	int x;
	int y;
};
class TileScene : public GameNode
{
private:
	MapTileInfo* _mapTileInfo;
	Camera* _camera;
	Player* _player;
	Image* _image;
	RECT _mouseRc;

	int numX;
	int numY;
	int index;
	int x, y;
	vector<tagTile> _tile;
	vector<tagTile>::iterator _tIter;

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

