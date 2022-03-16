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

	SCENEMANAGER->addScene("Ÿ��Ʋ", new StartScene);
	SCENEMANAGER->addScene("����", new FirstScene);
	SCENEMANAGER->addScene("����", new SecondScene);
	SCENEMANAGER->addScene("������", new ThirdScene);

	SCENEMANAGER->addScene("�κ��丮", new Inventory);
	SCENEMANAGER->addScene("����", new Store);
	SCENEMANAGER->addScene("�ȼ�", new PixelScene);
	SCENEMANAGER->addScene("����", new SoundScene);
	SCENEMANAGER->addScene("���̽�", new JsonDataScene);
	SCENEMANAGER->addScene("Ÿ��", new TileScene);

	SCENEMANAGER->changeScene("Ÿ��");
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
	//������ �� ��Ʈ��
	//PatBlt() : �簢�� ������ �귯���� ä��� �Լ�
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	//==================================================

	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());

	//==================================================
	this->getBackBuffer()->render(getHDC()); //������� ������ HDC�� �׸���.
}