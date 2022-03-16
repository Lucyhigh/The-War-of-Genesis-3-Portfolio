#pragma once
#include "GameNode.h"
#define TILE_MAX 10

struct  tagTile
{
	Image* img;
	RECT rc; // nXn�� n��° ��Ʈ
	bool onTile;
	float x, y;

};

class TileMap : public GameNode
{
private:

	vector<tagTile> _vTileMap;
	vector<tagTile>::iterator _viTileMap;

	int tileNum;

	RECT rc; // ��ü Ÿ���� ���� ��Ʈ. ptInrect�� ���� ������ �� �ִ�. 
	// ���͸� �̿��ؼ� ������ 

public:
	TileMap() {};
	~TileMap() {};

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};


// 100*100 �ִ� 100�� Ÿ���� ���� �� �ִ� ū rc��
// ������� �Է¿� ���� ������. 
// 
