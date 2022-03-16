#include "Stdafx.h"
#include "MainGame.h"
#include "StartScene.h"
#include "FirstScene.h"
#include "SecondScene.h"
#include "ThirdScene.h"
#include "Inventory.h"
#include "Store.h"
#include "PixelScene.h"
#include "SoundScene.h"
#include "JsonDataScene.h"
#include "TileScene.h"
HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);

	SCENEMANAGER->addScene("타이틀", new StartScene);
	SCENEMANAGER->addScene("시작", new FirstScene);
	SCENEMANAGER->addScene("마을", new SecondScene);
	SCENEMANAGER->addScene("죽음땅", new ThirdScene);

	SCENEMANAGER->addScene("인벤토리", new Inventory);
	SCENEMANAGER->addScene("상점", new Store);
	SCENEMANAGER->addScene("픽셀", new PixelScene);
	SCENEMANAGER->addScene("사운드", new SoundScene);
	SCENEMANAGER->addScene("제이슨", new JsonDataScene);
	SCENEMANAGER->addScene("타일", new TileScene);

	SCENEMANAGER->changeScene("타일");
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
}

void MainGame::update(void)
{
	GameNode::update();
	SCENEMANAGER->update();
}

void MainGame::render(void)
{
	//검은색 빈 비트맵
	//PatBlt() : 사각형 영역을 브러쉬로 채우는 함수
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	//==================================================

	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());

	//==================================================
	this->getBackBuffer()->render(getHDC()); //백버퍼의 내용을 HDC에 그린다.
}