#include "Stdafx.h"
#include "Inventory.h"
HRESULT Inventory::init(void)
{
    IMAGEMANAGER->addImage("�κ�â", "Resources/Images/BackGround/Inventory.bmp", WINSIZE_X, WINSIZE_Y); 


    return S_OK;
}
void Inventory::release(void)
{
}
void Inventory::update(void)
{
    if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
    {
        SCENEMANAGER->changeScene("����");
    }
}
void Inventory::render(void)
{
    IMAGEMANAGER->render("�κ�â", getMemDC());
   
}
Inventory::Inventory()
{
}


Inventory::~Inventory()
{
}
