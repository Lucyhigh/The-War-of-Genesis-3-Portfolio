#pragma once
#pragma once
#include "GameNode.h"
#define TILESIZE 50
struct tagTile
{
	int x;
	int y;
	//int info;
	int sizeX;
	int sizeY;
	RECT rect;
};
class TileScene : public GameNode
{
private:
	int numX;
	int numY;
	int index;
	int x, y;
	POINT pt;
	vector<tagTile> _tile;
	vector<tagTile>::iterator _tIter;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
public:
	TileScene() {}
	~TileScene() {}
};

