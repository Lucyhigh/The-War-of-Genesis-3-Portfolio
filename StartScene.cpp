#include "Stdafx.h"
#include "StartScene.h"

HRESULT StartScene::init(void)
{
	IMAGEMANAGER->addImage("Ÿ��Ʋ���", "Resources/Images/BackGround/Title.bmp", WINSIZE_X, WINSIZE_Y);


	return S_OK;
}

void StartScene::release(void)
{
}

void StartScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		SCENEMANAGER->changeScene("����");
	}
}

void StartScene::render(void)
{
	IMAGEMANAGER->render("Ÿ��Ʋ���", getMemDC());
}