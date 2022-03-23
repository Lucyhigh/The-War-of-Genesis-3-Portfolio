#include "Stdafx.h"
#include "MainGame.h"
#pragma region include Scene
//UI
#include "ImageClass.h"
//Stage
#include "FirstScene.h"
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

	SCENEMANAGER->addScene("�κ��丮", new Inventory);
	SCENEMANAGER->addScene("����", new Store);
	//SCENEMANAGER->addScene("�ȼ�", new PixelScene);
	//SCENEMANAGER->addScene("����", new SoundScene);
	SCENEMANAGER->addScene("���̽�", new JsonDataScene);
	SCENEMANAGER->addScene("Ÿ��", new FirstScene);

	SCENEMANAGER->changeScene("Ÿ��");
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
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());

	this->getBackBuffer()->render(getHDC()); 
}