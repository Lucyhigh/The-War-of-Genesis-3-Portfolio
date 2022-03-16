#include "Stdafx.h"
#include "Flame.h"

Flame::Flame(){
}

Flame::~Flame(){
}

HRESULT Flame::init(const char*fileName, float* x, float* y)
{
	_img = IMAGEMANAGER->addFrameImage("부스터", "Resources/Images/Object/Flame.bmp",
		0.0f, 0.0f, 432, 297, 9, 1, true, RGB(255, 0, 255));

	_x = x;
	_y = y;

	_rc = RectMakeCenter((int)_x, (int)_y, _img->getFrameWidth(), _img->getFrameHeight());
	_flameTick = 7.0f;
	_count = _index = 0;
	_start = false;
	return S_OK;
}

void Flame::release(void){
}

void Flame::update(void)
{
	if (FLAME_COUNT + _flameTick <= GetTickCount())
	{
		_flameTick = GetTickCount();
		_img->setFrameX(_img->getFrameX() + 1);
		if (_img->getFrameX() >= _img->getMaxFrameX())
		{
			_img->setFrameX(0);
		}
	}
	_rc = RectMakeCenter(*_x, *_y+180, _img->getFrameWidth(), _img->getFrameHeight());
}

void Flame::render(void)
{
		IMAGEMANAGER->frameRender("부스터", getMemDC(), _rc.left,_rc.top,_img->getFrameX(), _img->getFrameY());
}
