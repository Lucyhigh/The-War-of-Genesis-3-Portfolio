#include "Stdafx.h"
#include "MapScene.h"

HRESULT MapScene::init(void)
{
    _image = new Image;
    _image = IMAGEMANAGER->findImage("Map");
	_animation = ANIMATIONMANAGER->findAnimation("npcBar");
	_animation->AniStart();
    _seaX = 0.0f;
    _seaY = -800.0f;

    _camera = new Camera;
    _camera->init();
    _camera->setLimitsX(CENTER_X, _image->getWidth());
    _camera->setLimitsY(CENTER_Y, _image->getHeight());
    _camera->setCameraPos({0, _image->getHeight()-CENTER_Y });
	return S_OK;
}

void MapScene::release(void)
{
    _camera->release();
    SAFE_DELETE(_camera);
}

void MapScene::update(void)
{
	_seaX += 0.05f;
 
    _camera->update();
    _camera->setCameraPos(_camera->getCameraPos());
    _camera->setScreenRect(_camera->getScreenRect());
}

void MapScene::render(void)
{
	RECT seaRc = { 0,0,WINSIZE_X,WINSIZE_Y };
	IMAGEMANAGER->loopRender("Sea",getMemDC(),&seaRc, _seaX, _seaY);
    
    int cameraLeft = _camera->getScreenRect().left;
    int cameraTop = _camera->getScreenRect().top;
    IMAGEMANAGER->render("Map", getMemDC(), 0, 0,
        cameraLeft,
        cameraTop,
        WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->findImage("npcBar")->aniRender(getMemDC(), 200 - _camera->getScreenRect().left,
															 900 - _camera->getScreenRect().top, _animation);
    _camera->render();

}
