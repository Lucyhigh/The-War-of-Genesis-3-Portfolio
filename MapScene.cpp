#include "Stdafx.h"
#include "MapScene.h"

HRESULT MapScene::init(void)
{
    _image = new Image;
    _image = IMAGEMANAGER->findImage("Map");
	_buttonImage = *IMAGEMANAGER->findImage("MapButton");
	_animation = new Animation;
	_animation = ANIMATIONMANAGER->findAnimation("npcBar");
	_animation->AniStart();
    _seaX = 0.0f;
    _seaY = -800.0f;
	int buttonNum = 4;
	for (int i = 0; i < buttonNum; i++)
	{
		MapbuttomInfo _mapButtomInfo;
		POINT _buttomPos = { WINSIZE_X-170, 50 + i *( _buttonImage.getHeight()+30) };
		_mapButtomInfo._buttonRect = RectMake(_buttomPos.x, _buttomPos.y, _buttonImage.getWidth(), _buttonImage.getHeight());
		_mapButtomInfo._index = i;
		_mapButtomInfo._image = _buttonImage;

		_vMapButton.push_back(_mapButtomInfo);
		_vMapButton[i]._textInfo = _uiText[i];
	}
    _moveButton[0] = RectMake(120,600,80,80);
    _moveButton[1] = RectMake(120,600,80,80);
    _camera = new Camera;
    _camera->init();
    _camera->setLimitsX(CENTER_X, _image->getWidth());
    _camera->setLimitsY(CENTER_Y, _image->getHeight());
    _camera->setCameraPos({0, _image->getHeight()-500 });
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
    if (PtInRect(&_moveButton[0], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
    {
        _moveNext = true;
    }
    else if (PtInRect(&_moveButton[1], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
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
    POINT playerPos = { 180 - cameraLeft,  880 - cameraTop };
    if (_moveNext)
    {
        IMAGEMANAGER->findImage("npcBar")->aniRender(getMemDC(), _moveButton.left - cameraLeft,
            _moveButton.top - cameraTop, _animation);
        cout << "버몬트이동" << endl;
        playerPos = { _moveButton.left - cameraLeft,
            _moveButton.top - cameraTop };
    }
    else
    {
	    IMAGEMANAGER->findImage("npcBar")->aniRender(getMemDC(), playerPos.x, playerPos.y, _animation);
    }

    Rectangle(getMemDC(), _moveButton.left - cameraLeft,
        _moveButton.top- cameraTop,
        _moveButton.right - cameraLeft,
        _moveButton.bottom- cameraTop);
	IMAGEMANAGER->render("curMap",getMemDC());
	int alphaChange = 20;
	for (_viMapButton = _vMapButton.begin(); _viMapButton != _vMapButton.end(); ++_viMapButton)
	{
		if (PtInRect(&_viMapButton->_buttonRect, _ptMouse))
		{
			IMAGEMANAGER->alphaRender("MapButton", getMemDC(), _viMapButton->_buttonRect.left, _viMapButton->_buttonRect.top - 5, alphaChange);
			FONTMANAGER->drawText(getMemDC(),
				(_viMapButton->_buttonRect.left + _viMapButton->_buttonRect.right) / 2,
				_viMapButton->_buttonRect.top + 5 , "가을체", 25, 13, _viMapButton->_textInfo,
				wcslen(_viMapButton->_textInfo), TA_CENTER, RGB(255, 255, 255));
			alphaChange = 0;
		}
		else
		{
			IMAGEMANAGER->alphaRender("MapButton", getMemDC(), _viMapButton->_buttonRect.left, _viMapButton->_buttonRect.top, alphaChange);
			FONTMANAGER->drawText(getMemDC(),
				(_viMapButton->_buttonRect.left + _viMapButton->_buttonRect.right) / 2,
				_viMapButton->_buttonRect.top + 20 / 2, "가을체", 23, 13, _viMapButton->_textInfo,
				wcslen(_viMapButton->_textInfo), TA_CENTER, RGB(207, 207, 207));
			alphaChange = 20;
		}
	}
    _camera->render();

}
