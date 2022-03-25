#include "Stdafx.h"
#include "GameUI.h"

HRESULT GameUI::init(void)
{
	_image = IMAGEMANAGER->findImage("button");
	//vector 4개 포문돌려서 ...-248,-68 1 // 76,30 4

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
		/*
		_image,
			RectMake(0, 0, _image->getWidth(),_image->getHeight(),
				{i * 30, j * 20	},	i + j)
		*/
			_menuButton.push_back(_imageInfo);
		}
	}
	_isTurn = false;
	_imgPos = { 0,0 };
	return S_OK;
}

void GameUI::release(void)
{

}

void GameUI::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		showBattleMenu();
	}
	for (auto menuIter = _menuButton.begin(); menuIter != _menuButton.end(); ++menuIter) 
	{
		if (PtInRect(&menuIter->_buttonRect, _ptMouse))
		{
			_isTurn = false;
		}

	}
}

void GameUI::render(void)
{
	if (_isTurn)
	{
		for (auto menuIter = _menuButton.begin(); menuIter != _menuButton.end(); ++menuIter)
		{
			IMAGEMANAGER->render("button", getMemDC(), menuIter->_imgPos.x, menuIter->_imgPos.y);
		}
	}

}

void GameUI::showBattleMenu()
{
	_isTurn = true;
}

POINT GameUI::getPos()
{
	return _imgPos;
}

void GameUI::setPos(POINT menuPos)
{
	_imgPos = menuPos;
}
