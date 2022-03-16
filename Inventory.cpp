#include "Stdafx.h"
#include "Inventory.h"
HRESULT Inventory::init(void)
{
    IMAGEMANAGER->addImage("인벤창", "Resources/Images/BackGround/Inventory.bmp", WINSIZE_X, WINSIZE_Y); 


    return S_OK;
}
void Inventory::release(void)
{
}
void Inventory::update(void)
{
    if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
    {
        SCENEMANAGER->changeScene("상점");
    }
}
void Inventory::render(void)
{
    IMAGEMANAGER->render("인벤창", getMemDC());
   
}
Inventory::Inventory()
{
}


Inventory::~Inventory()
{
}
