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
#include "Store.h"
#include "PixelScene.h"
//#include "SoundScene.h"
#include "JsonDataScene.h"
#pragma endregion 
HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);
	ImageClass imageClass = ImageClass();
	imageClass.init();

	SCENEMANAGER->addScene("inven", new Inventory);
	SCENEMANAGER->addScene("store", new Store);
	//SCENEMANAGER->addScene("ÇÈ¼¿", new PixelScene);
	//SCENEMANAGER->addScene("»ç¿îµå", new SoundScene);
	SCENEMANAGER->addScene("json", new JsonDataScene);
	//Scene
	SCENEMANAGER->addScene("title", new TitleScene);
	SCENEMANAGER->addScene("first", new FirstScene);
	SCENEMANAGER->addScene("secind", new SecondScene);
	SCENEMANAGER->addScene("final", new FinalScene);
	SCENEMANAGER->addScene("ending", new EndingScene);
	SCENEMANAGER->addScene("map", new MapScene);

	SCENEMANAGER->changeScene("map");
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