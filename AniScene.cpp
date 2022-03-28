#include "Stdafx.h"
#include "AniScene.h"

#pragma region TitleScene Animation
HRESULT AniSceneTitle::init(void)
{
    _titleEff = new Image;
	_titleEff = IMAGEMANAGER->findImage("TitleEfx");
	
    _aniTitleEff = new Animation;
    _aniTitleEff->init(_titleEff->getWidth(), _titleEff->getHeight(), 249, 225);

    _aniTitleEff->setDefPlayFrame(false, true);
    _aniTitleEff->setFPS(3);

    //_aniTitleEff->AniStart();
	_isAniStart = false;
	return S_OK;
}

void AniSceneTitle::release(void)
{
   _titleEff->release();
	SAFE_DELETE(_titleEff);
    _aniTitleEff->release();
	SAFE_DELETE(_aniTitleEff);
}

void AniSceneTitle::update(void)
{
    if (KEYMANAGER->isOnceKeyDown('T'))
    {
       _aniTitleEff->AniStart();
        cout << "열심히 눌렀지만 움직이지 않는다..." << endl;
    }
    _aniTitleEff->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void AniSceneTitle::render(void)
{
}

void AniSceneTitle::render(int x, int y)
{
    _titleEff->aniRender(getMemDC(), x, y, _aniTitleEff);
}
#pragma endregion