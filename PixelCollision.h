#pragma once
#include "GameNode.h"

class PixelCollision : public GameNode
{
private:
	Image* _pixelTank;

	RECT _rc;
	//?ȼ? ?浹 Ž???? Y?? ????
	int _probeY;
	int _x, _y;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
public:
	PixelCollision();
	~PixelCollision();
};

