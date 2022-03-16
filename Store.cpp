#include "Stdafx.h"
#include "Store.h"


HRESULT Store::init(void)
{
    IMAGEMANAGER->addImage("상점창", "Resources/Images/BackGround/Store.bmp", WINSIZE_X, WINSIZE_Y);
    IMAGEMANAGER->addFrameImage("아이템", "Resources/Images/Object/Items.bmp", 288, 72, 4, 1, true, RGB(255, 0, 255));
    _image = IMAGEMANAGER->addFrameImage("아이템선택버튼", "Resources/Images/Object/Items.bmp", 288, 72, 4, 1, true, RGB(255, 0, 255));

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
        SCENEMANAGER->changeScene("인벤토리");
    }
}

void Store::render(void)
{
    IMAGEMANAGER->render("상점창", getMemDC());
    IMAGEMANAGER->frameRender("아이템선택버튼", getMemDC(), 65, 212, 0, 0);
    IMAGEMANAGER->frameRender("아이템", getMemDC(), 64, 210, 1, 0);
    IMAGEMANAGER->frameRender("아이템", getMemDC(), 64, 290, 2, 0);
    IMAGEMANAGER->frameRender("아이템", getMemDC(), 64, 370, 3, 0);
}

Store::Store()
{
}


Store::~Store()
{
}
