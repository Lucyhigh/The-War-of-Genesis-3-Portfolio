#include "Stdafx.h"
#include "ShootingScene.h"

HRESULT ShootingScene::init(void)
{
	GameNode::init(TRUE);
	IMAGEMANAGER->addImage("전장", "Resources/Images/BackGround/ShootingBG.bmp", WINSIZE_X, WINSIZE_Y);

	_rocket = new Rocket;
	_rocket->init();
	_em = new EnemyManager;
	_em->init();
	_missileEffect = new MissileEffect;
	_missileEffect->init();

	_beamEffect = new BeamEffect;
	_beamEffect->init();

	_em->setRocketMemoryAddress(_rocket);
	_rocket->setEnemyManagerMemoryAddress(_em);

	_x, _y = 0.0f;
	wsprintf(_text, "Shooting Scene");
	return S_OK;
}

void ShootingScene::release(void)
{
	GameNode::release();

	_rocket->release();
	SAFE_DELETE(_rocket);
	_em->release();
	SAFE_DELETE(_em);

	_missileEffect->release();
	SAFE_DELETE(_missileEffect);

	_beamEffect->release();
	SAFE_DELETE(_beamEffect);
}

void ShootingScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		SCENEMANAGER->changeScene("시작");
	}

	GameNode::update();

	_rocket->update();
	_em->update();

	collision();

	/*  _missileEffect->update();
	  _beamEffect->update();*/
	_y -= 0.2f;
}

void ShootingScene::render(void)
{
	RECT rc = { 0,0, WINSIZE_X, WINSIZE_Y };
	IMAGEMANAGER->findImage("전장")->loopRender(getMemDC(), &rc, _x, _y);
	_rocket->render();
	_em->render();
	_missileEffect->render();
	_beamEffect->render();

	TextOut(getMemDC(), CENTER_X, CENTER_Y, _text, strlen(_text));

}