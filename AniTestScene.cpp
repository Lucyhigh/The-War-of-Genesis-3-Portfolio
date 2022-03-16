#include "Stdafx.h"
#include "AniTestScene.h"

HRESULT AniTestScene::init(void)
{
    //������ �̹����� �ƴ� �׳� �̹����� �ް��ִ�
    _image = IMAGEMANAGER->addImage("������", "Resources/Images/Object/Elephant.bmp",
        660, 268, true, RGB(255, 0, 255));
    _ani = new Animation;

    //x 6 y 4 ������
    _ani->init(_image->getWidth(), _image->getHeight(), 110, 67);
    //_image->getWidth() / 6, _image->getHeight() / 4);<<������ ���� ������..
    //Ȯ�强�� ���� ������� ������ ���������� ���ҽ��� ������ Ư�� ������ ��������
    _ani->setDefPlayFrame(false, true);
    _ani->setFPS(12);
    return S_OK;
}

void AniTestScene::release(void)
{
    _ani->release();
    SAFE_DELETE(_ani);
}

void AniTestScene::update(void)
{
    if (KEYMANAGER->isOnceKeyDown('B'))
    {
        _ani->AniStart();
    }
    _ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void AniTestScene::render(void)
{
    _image->aniRender(getMemDC(), CENTER_X - 50, CENTER_Y, _ani);
}
