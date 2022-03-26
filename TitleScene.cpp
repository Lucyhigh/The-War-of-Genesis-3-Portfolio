#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init(void)
{
	_anyButton = true;
	_title = false;

	//_pushButton = false;

	_image= IMAGEMANAGER->findImage("TitleBg");

	_alpha = 255;
	_ani = new AniSceneTitle;
	_ani->init();
	_menuIndex = 0;

	_alpha = 0;
	_isAlphaIncrese = false;

	return S_OK;
}

void TitleScene::release(void)
{
	SAFE_DELETE(_ani);
}

void TitleScene::update(void)
{
	/*if (!_pushButton)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_pushButton = true;
		}
	}
	else*/
	{
		_alpha--;
		if (_alpha <= 0)
		{
			_alpha = 0;
			_title = true;
		}
	}


	/*if (_title)
	{
		IMAGEMANAGER->findImage("titleMenu")->setFrameY(0);
		IMAGEMANAGER->findImage("titleMenu")->setFrameX(0);

		_ani->update();

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_menuIndex--;
			if (_menuIndex < 0) _menuIndex = 2;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_menuIndex++;
			if (_menuIndex > 2) _menuIndex = 0;
		}
		IMAGEMANAGER->findImage("titleMenu")->setFrameX(_menuIndex);
	}
*/
	//if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	//{
	//	if (_menuIndex == 0)SCENEMANAGER->changeScene("Map");
	//	//if (_menuIndex == 1)SCENEMANAGER->changeScene("save");
	//	if (_menuIndex == 2)PostQuitMessage(0);
	//}
	if (_alpha == 0 || _alpha == 255) _isAlphaIncrese = !_isAlphaIncrese;
	if (_isAlphaIncrese)_alpha += 1.0f; else _alpha -= 1.5f;
}

void TitleScene::render(void)
{

	_ani->render();
	IMAGEMANAGER->findImage("titleMenu")->frameRender(getMemDC(), WINSIZE_X - 200, CENTER_Y + 150);
	_ani->render(WINSIZE_X - 100, CENTER_Y + 140 + (_menuIndex * 45));
	
	IMAGEMANAGER->render("SceneList",getMemDC());//클릭으로 일로올수잇음

}