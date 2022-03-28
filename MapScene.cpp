#include "Stdafx.h"
#include "MapScene.h"

HRESULT MapScene::init(void)
{
	_image = new Image;
	_seaX = 0.0f;
	_seaY = -800.0f;
	return S_OK;
}

void MapScene::release(void)
{
	_image->release();
	SAFE_DELETE(_image);
}

void MapScene::update(void)
{
	_seaX += 0.05f;
}

void MapScene::render(void)
{
	RECT seaRc = { 0,0,WINSIZE_X,WINSIZE_Y };
	IMAGEMANAGER->loopRender("Sea",getMemDC(),&seaRc, _seaX, _seaY);
	IMAGEMANAGER->render("Map",getMemDC());
}

void MapScene::fadeout()
{
}
