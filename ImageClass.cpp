#include "Stdafx.h"
#include "ImageClass.h"

HRESULT ImageClass::init(void)
{
	IMAGEMANAGER->addImage("�ʿ�", "Resources/Images/BackGround/Field.bmp", 2120, 1536);
	IMAGEMANAGER->addFrameImage("Ÿ�� ǥ��", "Resources/Images/UI/Tile.bmp", 240, 32, 6, 1, true);
	IMAGEMANAGER->addImage("Ÿ�� ǥ��2", "Resources/Images/UI/1.bmp", 40, 32);
	return S_OK;
}

ImageClass::ImageClass()
{
}

ImageClass::~ImageClass()
{
}
