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
	_isMainMenu = false;
	_isSkillMenu = false;
	_PlayerPos = { 0,0 };
	float startX = -250;
	float startY = -30;
	int _indexY = 0;

	for (int i = -1; i < 1; i++)
	{
		for (int j = -1; j < 1; j++)
		{
			tagBattleMenu _battleImageInfo;
			POINT _buttomPos = { startX * (-1)*i+30, startY * (-2.5)*j +10 };
			_battleImageInfo._imgPos = _buttomPos;
			_battleImageInfo._iconPos = _buttomPos;
			_battleImageInfo._buttonRect = RectMake(_buttomPos.x, _buttomPos.y, _image->getWidth(), _image->getHeight());
			_battleImageInfo._defaultPos = _buttomPos;
			_battleImageInfo._index = _buttonIndex;

			_vMenuButton.push_back(_battleImageInfo);
			_vMenuButton[_buttonIndex]._textInfo = _uiMainText[_buttonIndex];
			_buttonIndex++;
		};
	}

    for (int i = 0,_buttonIndex=0; i <= 3; i++)
    {
        tagSkillMenu _skillMenuInfo;
        POINT _skillTextPos = { 85,-45 + i * 36 };
        _skillMenuInfo._textPos = _skillTextPos;
        _skillMenuInfo._buttonRect = RectMake(_skillTextPos.x, _skillTextPos.y, 80, 10);
        _skillMenuInfo._defaultPos = _skillTextPos;
        _skillMenuInfo._index = _buttonIndex;

        _vSkillButton.push_back(_skillMenuInfo);
        _vSkillButton[_buttonIndex]._skillNameInfo = _uiSkillText[_buttonIndex];
        _vSkillButton[_buttonIndex]._skillLvInfo = _uiSkillLvText[_buttonIndex];
        _vSkillButton[_buttonIndex]._skillSPInfo = _uiSkillSPText[_buttonIndex];
        _buttonIndex++;
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
    if (_isMainMenu)
    {
        for (_viMenuButton = _vMenuButton.begin(); _viMenuButton != _vMenuButton.end(); ++_viMenuButton)
        {
			if (PtInRect(&_viMenuButton->_buttonRect, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				switch (_viMenuButton->_index)
				{
				case 0:
					_isSkillMenu = true;
					break;
				case 1:
					break;
				case 2:
					_isPlayerTurn = false;
					break;
				case 3:
					break;
				}
				_isMainMenu = false;
			}
        }
    }

	if (_isSkillMenu)
	{
		for (_viSkillButton = _vSkillButton.begin(); _viSkillButton != _vSkillButton.end(); ++_viSkillButton)
		{
			if (PtInRect(&_viSkillButton->_buttonRect, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				switch (_viSkillButton->_index)
				{
				case 0:
					cout << "연" << endl;
					_skillIndex = SKILL_INDEX_EYUN;
					break;
				case 1:
					cout << "댓쉬" << endl;
					_skillIndex = SKILL_INDEX_DASH;
					break;
				case 2:
					cout << "천지파열무" << endl;
					_skillIndex = SKILL_INDEX_WORLDBROKEN;
					_isSkillMenu = false;
					break;
				case 3:
					cout << "풍아열공참" << endl;
					_skillIndex = SKILL_INDEX_WINDEYUN;
                    _isSkillMenu = false;
					break;
				}
			}
            if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
            {
                _isSkillMenu = false;
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
	if (_isMainMenu)
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

	if (_isSkillMenu)
	{
		IMAGEMANAGER->alphaRender("skillText", getMemDC(), _PlayerPos.x+30, _PlayerPos.y - 60, 170);
        for (_viSkillButton = _vSkillButton.begin(); _viSkillButton != _vSkillButton.end(); ++_viSkillButton)
        {
			IMAGEMANAGER->frameRender("skillIcon", getMemDC(), _viSkillButton->_buttonRect.left-30, _viSkillButton->_buttonRect.top+5, _viSkillButton->_index, 1);
			if (PtInRect(&_viSkillButton->_buttonRect, _ptMouse))
			{
				FONTMANAGER->drawText(getMemDC(),
					_viSkillButton->_buttonRect.left,
					_viSkillButton->_buttonRect.top + _textPosY,
					"가을체", 20, 13, _viSkillButton->_skillNameInfo,
					wcslen(_viSkillButton->_skillNameInfo),
					TA_LEFT, RGB(255, 255, 255));
			}
			else
			{
				FONTMANAGER->drawText(getMemDC(),
					_viSkillButton->_buttonRect.left,
					_viSkillButton->_buttonRect.top + _textPosY,
					"가을체", 20, 13, _viSkillButton->_skillNameInfo,
					wcslen(_viSkillButton->_skillNameInfo),
					TA_LEFT, RGB(170, 170, 170));
			}
			FONTMANAGER->drawText(getMemDC(),
				_viSkillButton->_buttonRect.left + 110,
				_viSkillButton->_buttonRect.top + _textPosY,
				"가을체", 20, 13, _viSkillButton->_skillLvInfo,
				wcslen(_viSkillButton->_skillLvInfo),
				TA_LEFT, RGB(227, 155, 139));

			FONTMANAGER->drawText(getMemDC(),
				_viSkillButton->_buttonRect.left+170,
				_viSkillButton->_buttonRect.top + _textPosY,
				"가을체", 20, 13, _viSkillButton->_skillSPInfo,
				wcslen(_viSkillButton->_skillSPInfo),
				TA_LEFT, RGB(252, 255, 181));
        }
	}
}

bool GameUI::getSkillMenu()
{
	return _isSkillMenu;
}

bool GameUI::getPlayerTurn()
{
	return _isPlayerTurn;
}

bool GameUI::getMenu()
{
	return _isMainMenu;
}

void GameUI::showBattleMenu(POINT menuPos)
{
    _isMainMenu = true;
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

void GameUI::showSkillMenu(POINT menuPos)
{
    _isSkillMenu = true;
	_PlayerPos = menuPos;
    for (_viSkillButton = _vSkillButton.begin(); _viSkillButton != _vSkillButton.end(); ++_viSkillButton)
    {
        _uiPos = { menuPos.x + _viSkillButton->_defaultPos.x, menuPos.y + _viSkillButton->_defaultPos.y };
        _viSkillButton->_textPos = _uiPos;
        _viSkillButton->_buttonRect.left = _uiPos.x;
        _viSkillButton->_buttonRect.top = _uiPos.y;
        _viSkillButton->_buttonRect.right = _uiPos.x + _image->getWidth();
        _viSkillButton->_buttonRect.bottom = _uiPos.y + _image->getHeight();
    }
}

void GameUI::setMoveTileRange(int range)
{
	_moveRange = range;
}

void GameUI::setMoveCenter(POINT center)
{
	_tileCenter = center;
}

SKILL_NUMBER GameUI::getSkillNum()
{
	return _skillIndex;
}
void GameUI::setSkillNum(SKILL_NUMBER state)
{
    _skillIndex = state;
}