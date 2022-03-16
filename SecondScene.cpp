#include "Stdafx.h"
#include "SecondScene.h"

HRESULT SecondScene::init(void)
{
	IMAGEMANAGER->addImage("마을화면", "Resources/Images/BackGround/SecondBG.bmp", WINSIZE_X, WINSIZE_Y);
	
	_player = new Player;
	_player->init();
	_player->setPlayerPosX(630);
	_count = 0;
	_indexA = 0;
	return S_OK;
}

void SecondScene::release(void)
{
	_player->release();
}

void SecondScene::update(void)
{
	_count++;
	_player->update();
	
	if (_player->getPlayerPosX() > 1850)
	{
		_player->setPlayerPosX(1850);
	}
	else if (_player->getPlayerPosX() < 800)
	{
		_player->setPlayerPosX(800);
	}
	
}

void SecondScene::render(void)
{
	IMAGEMANAGER->render("마을화면", getMemDC());

	_player->render();
	
}
