#include "Stdafx.h"
#include "Store.h"


HRESULT Store::init(void)
{
    IMAGEMANAGER->addImage("����â", "Resources/Images/BackGround/Store.bmp", WINSIZE_X, WINSIZE_Y);
    IMAGEMANAGER->addFrameImage("������", "Resources/Images/Object/Items.bmp", 288, 72, 4, 1, true, RGB(255, 0, 255));
    _image = IMAGEMANAGER->addFrameImage("�����ۼ��ù�ư", "Resources/Images/Object/Items.bmp", 288, 72, 4, 1, true, RGB(255, 0, 255));

    _item = new Item;
  /*  for (int i = 0; i <= _item->getItemInfo().size; i++)
    {
        _itemIlst.push_back(_item->getItemInfo()[i]);
    }*/
    _moveY = 212;
    return S_OK;
}

void Store::release(void)
{
}

void Store::update(void)
{
    if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
    {
        SCENEMANAGER->changeScene("�κ��丮");
    }
}

void Store::render(void)
{
    IMAGEMANAGER->render("����â", getMemDC());
    IMAGEMANAGER->frameRender("�����ۼ��ù�ư", getMemDC(), 65, 212, 0, 0);
    IMAGEMANAGER->frameRender("������", getMemDC(), 64, 210, 1, 0);
    IMAGEMANAGER->frameRender("������", getMemDC(), 64, 290, 2, 0);
    IMAGEMANAGER->frameRender("������", getMemDC(), 64, 370, 3, 0);
}

Store::Store()
{
}


Store::~Store()
{
}
