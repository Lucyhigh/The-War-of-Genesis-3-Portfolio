#pragma once
#include "GameNode.h"
#include "Player.h"

class SecondScene : public GameNode
{
private:
	Image* _image;
	Player* _player;

	float _x, _y;
	int _count;
	int _indexA;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	SecondScene() {}
	~SecondScene() {}
};