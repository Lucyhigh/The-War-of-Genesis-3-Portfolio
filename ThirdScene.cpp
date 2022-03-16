#include "Stdafx.h"
#include "ThirdScene.h"

HRESULT ThirdScene::init(void)
{
	IMAGEMANAGER->addImage("������ȭ��", "Resources/Images/BackGround/ThirdBG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("���", "Resources/Images/Object/Dead.bmp", 512, 256,true,RGB(0,0,255));
	IMAGEMANAGER->addImage("������", "Resources/Images/BackGround/DeadBG.bmp", WINSIZE_X, WINSIZE_Y);
	_player = new Player;
	_player->init();
	_player->setPlayerPosX(630);
	
	_player->setThird(true);
	_bgAlpha = 0;
	_count = 0;
	return S_OK;
}

void ThirdScene::release(void)
{
	_player->release();
}

void ThirdScene::update(void)
{
	_count++;
	_player->update();
	if (_player->getLive() == false && _count%5==0)
	{
		if (_bgAlpha < 220)_bgAlpha+= 2;
	}
	if (_player->getLive() == false && _bgAlpha >= 220)
	{
		SCENEMANAGER->changeScene("Ÿ��Ʋ");
	}
	if (_player->getPlayerPosX() > 1850)
	{
		_player->setPlayerPosX(1850);
	}
	else if (_player->getPlayerPosX() < 800)
	{
		_player->setPlayerPosX(800);
	}
}

void ThirdScene::render(void)
{
	//cout << _bgAlpha << endl;
	IMAGEMANAGER->render("������ȭ��", getMemDC());
	_player->render();
	if (_player->getLive()==false)
	{
		IMAGEMANAGER->alphaRender("������", getMemDC(),_bgAlpha);
		IMAGEMANAGER->render("���", getMemDC(), CENTER_X-250, CENTER_Y-180);
	}
}
