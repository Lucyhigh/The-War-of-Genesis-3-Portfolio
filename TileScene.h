#pragma once
#pragma once
#include "GameNode.h"

class TileScene : public GameNode
{
private:
	int numX;
	int numY;
	int index;
	int x, y;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
public:
	TileScene() {}
	~TileScene() {}
};

