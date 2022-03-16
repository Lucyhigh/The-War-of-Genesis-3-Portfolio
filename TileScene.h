#pragma once
#pragma once
#include "GameNode.h"
#include "Camera.h"
#include "Player.h"

#define TILESIZEX 40
#define TILESIZEY 32
enum class TILEINDEX
{
	NORMAL =0,
	START,
	END,
	WALL
};
struct tagTile
{
	int x;
	int y;
	RECT rect;
	int info;
};
class TileScene : public GameNode
{
private:
	Camera* _camera;
	Player* _player;
	Image* _image;
	RECT _mouseRc;

	int numX;
	int numY;
	int index;
	int x, y;
	//POINT pt;
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

