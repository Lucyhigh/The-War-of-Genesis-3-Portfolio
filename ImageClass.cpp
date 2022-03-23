#include "Stdafx.h"
#include "ImageClass.h"

HRESULT ImageClass::init(void)
{
#pragma region PlayerImage
	//Idle
	IMAGEMANAGER->addFrameImage("pLeftIdle", "Resources/Images/Player/leftIdle.bmp", 111, 75, 3, 1, MGT);
	IMAGEMANAGER->addFrameImage("pRightIdle", "Resources/Images/Player/rightIdle.bmp", 111,75, 3, 1, MGT);
	IMAGEMANAGER->addFrameImage("pUpIdle", "Resources/Images/Player/upIdle.bmp", 159,84, 3, 1, MGT);
	IMAGEMANAGER->addFrameImage("pDownIdle", "Resources/Images/Player/downIdle.bmp", 147,76, 3, 1, MGT);

	//move
	IMAGEMANAGER->addFrameImage("pLeftMove", "Resources/Images/Player/leftIdle.bmp", 462, 75, 6, 1, MGT);
	IMAGEMANAGER->addFrameImage("pRightMove", "Resources/Images/Player/rightMove.bmp",462, 75, 6, 1, MGT);
	IMAGEMANAGER->addFrameImage("pUpMove", "Resources/Images/Player/upMove.bmp", 270,80, 6, 1, MGT);
	IMAGEMANAGER->addFrameImage("pDownMove", "Resources/Images/Player/downIdle.bmp", 352, 100, 6, 1, MGT);

	//attack
	IMAGEMANAGER->addFrameImage("pLeftAtt", "Resources/Images/Player/leftAtt.bmp", 340, 110, 4, 1, MGT);
	IMAGEMANAGER->addFrameImage("pRightAtt", "Resources/Images/Player/rightAtt.bmp", 340, 110, 4, 1, MGT);
	IMAGEMANAGER->addFrameImage("pUpAtt", "Resources/Images/Player/upAtt.bmp", 400,80, 4, 1, MGT);
	IMAGEMANAGER->addFrameImage("pDownAtt", "Resources/Images/Player/downAtt.bmp", 300, 90, 4, 1, MGT);

#pragma endregion

#pragma region Stage Scene
	// Stage 1
	IMAGEMANAGER->addImage("Field", "Resources/Images/BackGround/Field.bmp", 2120, 1536);
#pragma endregion

#pragma region UI Scene
	IMAGEMANAGER->addImage("curMap", "Resources/Images/UI/curMap.bmp", 241, 111, MGT);
	IMAGEMANAGER->addImage("introtext", "Resources/Images/UI/introtext.bmp", 230, 105);
	IMAGEMANAGER->addImage("mapInfoAll", "Resources/Images/UI/mapInfoAll.bmp", 230, 105);
	IMAGEMANAGER->addImage("mapInfoAll", "Resources/Images/UI/mapInfo.bmp", 230, 105);
	IMAGEMANAGER->addImage("button", "Resources/Images/UI/UI_button.bmp", 102, 28, MGT);
	IMAGEMANAGER->addImage("blockCell", "Resources/Images/UI/blockCell.bmp", 38, 24);//40 32으로 써야할지도

	IMAGEMANAGER->addImage("curTile2", "Resources/Images/UI/1.bmp", 40, 32);
	IMAGEMANAGER->addImage("moveTile", "Resources/Images/UI/moveable.bmp", 40, 32);
	IMAGEMANAGER->addImage("attackTile", "Resources/Images/UI/attackable.bmp", 40, 32);
	IMAGEMANAGER->addFrameImage("curTile", "Resources/Images/UI/Tile.bmp", 240, 32, 6, 1);
#pragma endregion
	return S_OK;
}

ImageClass::ImageClass()
{
}

ImageClass::~ImageClass()
{
}
