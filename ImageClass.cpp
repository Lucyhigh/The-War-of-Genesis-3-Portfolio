#include "Stdafx.h"
#include "ImageClass.h"

HRESULT ImageClass::init(void)
{
#pragma region PlayerImage
#pragma endregion

#pragma region Stage Scene
	// Stage 1
	IMAGEMANAGER->addImage("Field", "Resources/Images/BackGround/Field.bmp", 2120, 1536);
	IMAGEMANAGER->addFrameImage("curTile", "Resources/Images/UI/Tile.bmp", 240, 32, 6, 1);
	IMAGEMANAGER->addImage("curTile2", "Resources/Images/UI/1.bmp", 40, 32);
#pragma endregion

#pragma region UI Scene
	IMAGEMANAGER->addImage("curMap", "Resources/Images/UI/curMap.bmp", 241, 111, MGT);
	IMAGEMANAGER->addImage("introtext", "Resources/Images/UI/introtext.bmp", 230, 105);
#pragma endregion
	return S_OK;
}

ImageClass::ImageClass()
{
}

ImageClass::~ImageClass()
{
}
