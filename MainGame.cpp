#include "Stdafx.h"
#include "MainGame.h"
#pragma region include Scene
//UI
#include "ImageClass.h"
//Stage
#include "TitleScene.h"
#include "FirstScene.h"
#include "SecondScene.h"
#include "FinalScene.h"
#include "EndingScene.h"
#include "MapScene.h"
#include "Inventory.h"
#include "PixelScene.h"
#include "JsonDataScene.h"
#pragma endregion 
HRESULT MainGame::init(void)
{
    ShowCursor(false);

	GameNode::init(TRUE);
	ImageClass imageClass = ImageClass();
	imageClass.init();

	SCENEMANAGER->addScene("inven", new Inventory);
	SCENEMANAGER->addScene("json", new JsonDataScene);

	//Scene
	SCENEMANAGER->addScene("title", new TitleScene);
	SCENEMANAGER->addScene("map", new MapScene);
	//SCENEMANAGER->addScene("first", new FirstScene);
	SCENEMANAGER->addScene("second", new SecondScene);
	SCENEMANAGER->addScene("final", new FinalScene);
	SCENEMANAGER->addScene("ending", new EndingScene);

    SCENEMANAGER->changeScene("second");
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	SCENEMANAGER->release();
}

void MainGame::update(void)
{
	GameNode::update();
	SCENEMANAGER->update();
    ANIMATIONMANAGER->update();
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());

	this->getBackBuffer()->render(getHDC()); 
}