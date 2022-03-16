#pragma once
#include "GameNode.h"
#define TILE_MAX 10

struct  tagTile
{
	Image* img;
	RECT rc; // nXn의 n번째 렉트
	bool onTile;
	float x, y;

};

class TileMap : public GameNode
{
private:

	vector<tagTile> _vTileMap;
	vector<tagTile>::iterator _viTileMap;

	int tileNum;

	RECT rc; // 전체 타일이 나올 렉트. ptInrect를 통해 움직일 수 있다. 
	// 벡터를 이용해서 마름모 

public:
	TileMap() {};
	~TileMap() {};

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};


// 100*100 최대 100개 타일을 가질 수 있는 큰 rc를
// 사용자의 입력에 맞춰 나눈다. 
// 
