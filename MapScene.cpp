#include "Stdafx.h"
#include "MapScene.h"

HRESULT MapScene::init(void)
{
    _image = new Image;
    _image = IMAGEMANAGER->findImage("Map");
	_buttonImage = *IMAGEMANAGER->findImage("MapButton");
	_animation = ANIMATIONMANAGER->findAnimation("npcBar");
	_animation->AniStart();
	_aniCursor = ANIMATIONMANAGER->findAnimation("normalCursor");
	_aniCursor->AniStart();
	SOUNDMANAGER->addSound("Rage of Lion", "Resources/Sounds/Rage of Lion.mp3", true, true);

	SOUNDMANAGER->play("Rage of Lion", 1.0f);
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
    _moveButton[0] = RectMake(655,833,120,120);
    _moveButton[1] = RectMake(340,228,120,120);

	_alpha = 15;
    _camera = new Camera;
    _camera->init();
    _camera->setLimitsX(CENTER_X, _image->getWidth());
    _camera->setLimitsY(CENTER_Y, _image->getHeight());
    _camera->setCameraPos({ _image->getWidth(),_image->getHeight() });
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

	POINT mousePos = { _ptMouse.x + _camera->getScreenRect().left,_ptMouse.y + _camera->getScreenRect().top };
	if (PtInRect(&_moveButton[0], mousePos) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
    {
        _moveNext = true;
    }
    else if (PtInRect(&_moveButton[1], mousePos) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
    {
        _moveNext = false;
    }
    else if (_moveNext && PtInRect(&_vMapButton[1]._buttonRect, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
    {
		SOUNDMANAGER->play("changeScene", 1.0f);
		SOUNDMANAGER->stop("Rage of Lion");
        SCENEMANAGER->changeScene("second");
    }

	if (_alpha < 15 || _alpha >= 190) _isAlphaIncrese = !_isAlphaIncrese;
	if (_isAlphaIncrese)_alpha += 2.5f; else _alpha -= 2.5f;
	
	if (!_isCameraArrived)
	{
		if (_camera->getCameraPos().x != _vMapButton[1]._buttonRect.left && _camera->getCameraPos().y != _vMapButton[1]._buttonRect.top)
		{
			_camera->setCameraPos({ _camera->getCameraPos().x - 8, _camera->getCameraPos().y - 8 });
		}

		if ( (_camera->getCameraPos().x == _vMapButton[1]._buttonRect.left && _camera->getCameraPos().y == _vMapButton[1]._buttonRect.top)
			|| (_camera->getCameraPos().x == _camera->getLeftLimit() && _camera->getCameraPos().y == _camera->getTopLImit()) )
		{
			_isCameraArrived = true;
		}
	}

	_camera->update();
	_camera->setCameraPos(_camera->getCameraPos());
	_camera->setScreenRect(_camera->getScreenRect());
}

void MapScene::render(void)
{
    RECT seaRc = { 0,0,WINSIZE_X,WINSIZE_Y };
    IMAGEMANAGER->loopRender("Sea", getMemDC(), &seaRc, _seaX, _seaY);

    int cameraLeft = _camera->getScreenRect().left;
    int cameraTop = _camera->getScreenRect().top;
    IMAGEMANAGER->render("Map", getMemDC(), 0, 0,
        cameraLeft,
        cameraTop,
        WINSIZE_X, WINSIZE_Y);

    IMAGEMANAGER->alphaRender("mapMark", getMemDC(), _moveButton[0].left - cameraLeft, _moveButton[0].top - cameraTop, _alpha);
    IMAGEMANAGER->alphaRender("mapMark", getMemDC(), _moveButton[1].left - cameraLeft, _moveButton[1].top - cameraTop, _alpha);

    if (_moveNext)
    {
        IMAGEMANAGER->findImage("npcBar")->aniRender(getMemDC(),
			_moveButton[0].left + 60 - cameraLeft,
			_moveButton[0].top - 10 - cameraTop, _animation);
    }
    else
    {
        IMAGEMANAGER->findImage("npcBar")->aniRender(getMemDC(), 
			_moveButton[1].left + 60 - cameraLeft,
			_moveButton[1].top - 10 - cameraTop, _animation);
    }

    IMAGEMANAGER->alphaRender("curMap", getMemDC(), 230);

    LPCWSTR mapName = L"팬드래건 중부";
    LPCWSTR mapDate = L"1281년 28일";

    FONTMANAGER->drawText(getMemDC(), 100,45, "가을체", 23, 13, mapName, wcslen(mapName), TA_LEFT,RGB(255, 255, 255));
    FONTMANAGER->drawText(getMemDC(), 120, 80, "가을체", 19, 13, mapDate, wcslen(mapDate), TA_CENTER, RGB(255, 255, 255));

	int alphaChange = 80;
	for (_viMapButton = _vMapButton.begin(); _viMapButton != _vMapButton.end(); ++_viMapButton)
	{
		if (PtInRect(&_viMapButton->_buttonRect, _ptMouse))
		{
			alphaChange = 10;
			IMAGEMANAGER->alphaRender("MapButton", getMemDC(), _viMapButton->_buttonRect.left, _viMapButton->_buttonRect.top - 5, alphaChange);
			FONTMANAGER->drawText(getMemDC(),
				(_viMapButton->_buttonRect.left + _viMapButton->_buttonRect.right) / 2,
				_viMapButton->_buttonRect.top + 5 , "가을체", 25, 13, _viMapButton->_textInfo,
				wcslen(_viMapButton->_textInfo), TA_CENTER, RGB(255, 255, 255));
		}
		else
		{
			alphaChange = 80;
			IMAGEMANAGER->alphaRender("MapButton", getMemDC(), _viMapButton->_buttonRect.left, _viMapButton->_buttonRect.top, alphaChange);
			FONTMANAGER->drawText(getMemDC(),
				(_viMapButton->_buttonRect.left + _viMapButton->_buttonRect.right) / 2,
				_viMapButton->_buttonRect.top + 13, "가을체", 23, 13, _viMapButton->_textInfo,
				wcslen(_viMapButton->_textInfo), TA_CENTER, RGB(207, 207, 207));
		}
	}

	IMAGEMANAGER->findImage("normalCursor")->aniRender(getMemDC(), _ptMouse.x, _ptMouse.y, _aniCursor);

    _camera->render();
}
