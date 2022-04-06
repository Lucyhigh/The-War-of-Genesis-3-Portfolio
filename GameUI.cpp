#include "Stdafx.h"
#include "GameUI.h"
HRESULT GameUI::init(void)
{
	_image = new Image;
	_image = IMAGEMANAGER->findImage("button");

	_iconImage = new Image;
	_iconImage = IMAGEMANAGER->findImage("selectIcon");

	_tileImage = new Image;
	_tileImage = IMAGEMANAGER->findImage("moveTile");

	_uiPos = { 0,0 };
	_tileCenter = { 0, 0 };
	
	_tileAlpha = 0.0f;
	_buttonIndex = 0;
	_moveRange = 5;

	_isPlayerTurn = true;
	_isMenu = false;
	_isTileSetting = false;

	float startX = -250;
	float startY = -30;
	int _indexY = 0;

	for (int i = -1; i < 1; i++)
	{
		for (int j = -1; j < 1; j++)
		{
			
			tagBattleMenu _battleImageInfo;
			POINT _buttomPos = { startX * (-1)*i - 27, startY * (-2.5)*j - 40 };
			_battleImageInfo._imgPos = _buttomPos;
			_battleImageInfo._iconPos = _buttomPos;
			_battleImageInfo._buttonRect = RectMake(_buttomPos.x, _buttomPos.y, _image->getWidth(), _image->getHeight());//
			_battleImageInfo._defaultPos = _buttomPos;
			_battleImageInfo._index = _buttonIndex;

			_vMenuButton.push_back(_battleImageInfo);
			_vMenuButton[_buttonIndex]._textInfo = _uiText[_buttonIndex];
			_buttonIndex++;
		};
	}

	for (int i = -1; i < _moveRange ; i++)
	{
		for (int j = _moveRange - i; j > 0; j--) 
		{
			continue;
		}
		for (int j = i * 2+1; j > 0; j--)
		{
			tagMoveTile _tagMoveTile;
			POINT _movePos = { i ,_indexY};
			_indexY++;
			_vMoveTile.push_back(_tagMoveTile);
		}
		_indexY = 0;
	}

	for (int i = _moveRange; i >= 0; i--)
	{
		for (int j = 1; j < _moveRange - i; j++) 
		{
			continue;
		}
		for (int j = 0; j < i * 2 + 1 ; j++)
		{
			tagMoveTile _tagMoveTile;
			POINT _movePos = { i , _indexY };
			_indexY++;
			_vMoveTile.push_back(_tagMoveTile);
		}
		_indexY=0;
	}

	return S_OK;
}

void GameUI::release(void)
{
    _image->release();
    SAFE_DELETE(_image);
	_iconImage->release();
	SAFE_DELETE(_iconImage);
	_tileImage->release();
	SAFE_DELETE(_tileImage);
}

void GameUI::update(void)
{
    if (_isMenu)
    {
        for (_viMenuButton = _vMenuButton.begin(); _viMenuButton != _vMenuButton.end(); ++_viMenuButton)
        {
			if (PtInRect(&_viMenuButton->_buttonRect, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				switch (_viMenuButton->_index)
				{
				case 0:
					cout << "어빌리티" << endl;
					break;
				case 1:
					break;
				case 2:
					_isPlayerTurn = false;
					break;
				case 3:
					break;
				}
				_isMenu = false;
			}
        }
    }
}

void GameUI::render(void)
{
	int _buttonAlpha = 100;
	int _textPosX = -57;
	int _textPosY = 8;
	char buttomText[512];
	if (_isMenu)
	{
        for (_viMenuButton = _vMenuButton.begin(); _viMenuButton != _vMenuButton.end(); ++_viMenuButton)
		{
			if (PtInRect(&_viMenuButton->_buttonRect, _ptMouse))
			{
				_buttonAlpha = 30;
			}
			else _buttonAlpha = 100;
			IMAGEMANAGER->alphaRender("button", getMemDC(), _viMenuButton->_imgPos.x, _viMenuButton->_imgPos.y, _buttonAlpha);
			IMAGEMANAGER->frameRender("selectIcon", getMemDC(), _viMenuButton->_imgPos.x+ 13, _viMenuButton->_imgPos.y+4, _viMenuButton->_index,1);

			FONTMANAGER->drawText(getMemDC(), _viMenuButton->_buttonRect.right + _textPosX,
											  _viMenuButton->_buttonRect.top + _textPosY, "가을체",
								  20, 13, _viMenuButton->_textInfo, wcslen(_viMenuButton->_textInfo), TA_CENTER, RGB(255,255,255));
		}
	}           
}

POINT GameUI::getPos()
{
	return _uiPos;
}

bool GameUI::getPlayerTurn()
{
	return _isPlayerTurn;
}

bool GameUI::getMenu()
{
	return _isMenu;
}

void GameUI::showBattleMenu(POINT menuPos)
{
    _isMenu = true;
    for (_viMenuButton = _vMenuButton.begin(); _viMenuButton != _vMenuButton.end(); ++_viMenuButton)
    {
        _uiPos = { menuPos.x + _viMenuButton->_defaultPos.x, menuPos.y + _viMenuButton->_defaultPos.y };
        _viMenuButton->_imgPos = _uiPos;
        _viMenuButton->_iconPos = _uiPos;
        _viMenuButton->_buttonRect.left = _uiPos.x;
        _viMenuButton->_buttonRect.top = _uiPos.y;
		_viMenuButton->_buttonRect.right = _uiPos.x+_image->getWidth();
		_viMenuButton->_buttonRect.bottom = _uiPos.y+ _image->getHeight();
    }
}

void GameUI::showMoveTile(POINT center)
{
}

void GameUI::MakeMoveTile()
{
}

void GameUI::setMoveTileRange(int range)
{
	_moveRange = range;
}

void GameUI::setMoveCenter(POINT center)
{
	_tileCenter = center;
}
