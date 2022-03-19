#include "Stdafx.h"
#include "ImageClass.h"

HRESULT ImageClass::init(void)
{
	IMAGEMANAGER->addImage("초원", "Resources/Images/BackGround/Field.bmp", 2120, 1536);
	IMAGEMANAGER->addFrameImage("타일 표시", "Resources/Images/UI/Tile.bmp", 240, 32, 6, 1, true);
	IMAGEMANAGER->addImage("타일 표시2", "Resources/Images/UI/1.bmp", 40, 32);
	return S_OK;
}

ImageClass::ImageClass()
{
}

ImageClass::~ImageClass()
{
}
