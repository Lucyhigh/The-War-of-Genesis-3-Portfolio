#pragma once
#include "GameNode.h"
// 이니셜 라이즈에는 여기에 인클루드 하지 않는다.

#define FLAME_COUNT 4.0f

class Flame : public GameNode
{
private:
	Image* _img;
	int _count, _index;
	bool _start;

	// 0207 추가
	RECT _rc;
	float *_x;
	float *_y;
	float _flameTick;

public:

	Flame();
	~Flame();

	//HRESULT init(void);
	//0207 추가
	HRESULT init(const char*fileName, float* x, float* y);
	
	void release(void);
	void update(void);
	void render(void);

	void setStart(bool state) { _start = state;}
	void setXY(float x, float y) 
	{
		_img->setX(x);
		_img->setY(y);
	}
};

