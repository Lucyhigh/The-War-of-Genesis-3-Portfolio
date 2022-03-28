#include "Stdafx.h"
#include "GameUI.h"
HRESULT GameUI::init(void)
{
	_image = new Image;
	_image = IMAGEMANAGER->findImage("button");

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

	int startX = -250;
	int startY = -50;
	int _indexY = 0;
	for (int i = -1; i < 1; i++)
	{
		for (int j = -1; j < 1; j++)
		{
			
			tagBattleMenu _battleImageInfo;
			POINT _buttomPos = { startX * (-1)*i, startY * (-2)*j };
			_battleImageInfo._imgPos = _buttomPos;
			_battleImageInfo._buttonRect = RectMake(_buttomPos.x, _buttomPos.y, _image->getWidth(), _image->getHeight());//
			_battleImageInfo._defaultPos = _buttomPos;
			_battleImageInfo._index = _buttonIndex;

			_vMenuButton.push_back(_battleImageInfo);
			_vMenuButton[_buttonIndex]._textInfo = _uiText[_buttonIndex];
			_buttonIndex++;
		};
	}
	//MakeMoveTile();
	//함수로 다하고 지정해줄거임
	//아래방향
	//for (int i = _moveRange - 2; i > -1; i--)
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
			cout << i << "," << _indexY <<",";
			_indexY++;
			_vMoveTile.push_back(_tagMoveTile);
		}
		cout << endl;
		_indexY = 0;
	}
	//위방향
	for (int i = _moveRange; i >= 0; i--)
	//for (int i = 0; i < _moveRange; i++)
	{
		for (int j = 1; j < _moveRange - i; j++) 
		{
			continue;
		}
		for (int j = 0; j < i * 2 + 1 ; j++)
		{
			tagMoveTile _tagMoveTile;
			POINT _movePos = { i , _indexY };
			cout << i <<","<< _indexY << ",";
			_indexY++;
			_vMoveTile.push_back(_tagMoveTile);
		}
		cout << endl;
		_indexY=0;
	}

	
	return S_OK;
}

void GameUI::release(void)
{
    _image->release();
    SAFE_DELETE(_image);
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
					cout << "00000000" << endl;
					break;
				case 1:
					cout << "11111111" << endl;
					break;
				case 2:
					cout << "2222222" << endl;
					_isPlayerTurn = false;
					break;
				case 3:
					cout << "3333333" << endl;
					break;
				}
				_isMenu = false;
			}
        }
    }
}

void GameUI::render(void)
{
	int _buttonAlpha = 30;
	int _textPosY = 5;
	char buttomText[512];
	if (_isMenu)
	{
        for (_viMenuButton = _vMenuButton.begin(); _viMenuButton != _vMenuButton.end(); ++_viMenuButton)
		{
			IMAGEMANAGER->alphaRender("button", getMemDC(), _viMenuButton->_imgPos.x, _viMenuButton->_imgPos.y,_buttonAlpha);
			FONTMANAGER->drawText(getMemDC(), (_viMenuButton->_buttonRect.left+_viMenuButton->_buttonRect.right)/2,
											  _viMenuButton->_buttonRect.top+ _textPosY, "가을체",
								  18, 13, _viMenuButton->_textInfo, wcslen(_viMenuButton->_textInfo), TA_CENTER, RGB(255,255,255));
		}
	}
	//if (_tileAlpha == 0 || _tileAlpha == 255) _isAlphaIncrese = !_isAlphaIncrese;
	//if (_isAlphaIncrese)_tileAlpha += 1.0f; else _tileAlpha -= 1.5f;
            
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
