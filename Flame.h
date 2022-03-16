#pragma once
#include "GameNode.h"
// �̴ϼ� ������� ���⿡ ��Ŭ��� ���� �ʴ´�.

#define FLAME_COUNT 4.0f

class Flame : public GameNode
{
private:
	Image* _img;
	int _count, _index;
	bool _start;

	// 0207 �߰�
	RECT _rc;
	float *_x;
	float *_y;
	float _flameTick;

public:

	Flame();
	~Flame();

	//HRESULT init(void);
	//0207 �߰�
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

