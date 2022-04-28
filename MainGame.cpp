#include "Stdafx.h"
#include "MainGame.h"

#pragma region include Scene
#include "ImageClass.h"
#include "SoundClass.h"
#include "TitleScene.h"
#include "StoryScene.h"
#include "FinalScene.h"
#include "EndingScene.h"
#include "MapScene.h"
#pragma endregion 
HRESULT MainGame::init(void)
{
    ShowCursor(false);

	GameNode::init(TRUE);
	ImageClass imageClass = ImageClass();
	imageClass.init();
	SoundClass soundClass = SoundClass();
	soundClass.init();

	SCENEMANAGER->addScene("title", new TitleScene);
	SCENEMANAGER->addScene("map", new MapScene);
	SCENEMANAGER->addScene("second", new StoryScene);
	SCENEMANAGER->addScene("final", new FinalScene);
	SCENEMANAGER->addScene("ending", new EndingScene);

    SCENEMANAGER->changeScene("final");
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
    SOUNDMANAGER->update();
    ANIMATIONMANAGER->update();
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());

	this->getBackBuffer()->render(getHDC()); 
}