#include "Stdafx.h"
#include "ImageClass.h"

HRESULT ImageClass::init(void)
{
#pragma region PlayerImage
	//Idle
	IMAGEMANAGER->addFrameImage("pRightIdle", "Resources/Images/Player/rightIdle.bmp", 185,75, 5, 1, MGT);
	IMAGEMANAGER->addFrameImage("pLeftIdle", "Resources/Images/Player/leftIdle.bmp", 185, 75, 5, 1, MGT);
	IMAGEMANAGER->addFrameImage("pUpIdle", "Resources/Images/Player/upIdle.bmp", 265,87, 5, 1, MGT);
	IMAGEMANAGER->addFrameImage("pDownIdle", "Resources/Images/Player/downIdle.bmp", 245,78, 5, 1, MGT);
	IMAGEMANAGER->addImage("test", "Resources/Images/Player/1-1.bmp", 53,84,true, RGB(0,0,0));

	//move
	IMAGEMANAGER->addFrameImage("pRightMove", "Resources/Images/Player/rightMove.bmp",462, 76, 6, 1, MGT);
	IMAGEMANAGER->addFrameImage("pLeftMove", "Resources/Images/Player/leftMove.bmp", 462, 76, 6, 1, MGT);
	IMAGEMANAGER->addFrameImage("pUpMove", "Resources/Images/Player/upMove.bmp", 228,80, 6, 1, MGT);
	IMAGEMANAGER->addFrameImage("pDownMove", "Resources/Images/Player/downMove.bmp", 372, 91, 6, 1, MGT);

	//attack
	IMAGEMANAGER->addFrameImage("pRightAtt", "Resources/Images/Player/rightAtt.bmp", 340, 110, 4, 1, MGT);
	IMAGEMANAGER->addFrameImage("pLeftAtt", "Resources/Images/Player/leftAtt.bmp", 340, 110, 4, 1, MGT);
	IMAGEMANAGER->addFrameImage("pUpAtt", "Resources/Images/Player/upAtt.bmp", 400,80, 4, 1, MGT);
	IMAGEMANAGER->addFrameImage("pDownAtt", "Resources/Images/Player/downAtt.bmp", 352, 104, 4, 1, MGT);

#pragma endregion

#pragma region Stage Scene
	//Title
	IMAGEMANAGER->addFrameImage("TitleEfx", "Resources/Images/UI/titleEfx.bmp", 996, 225, 4, 1, MGT);


	//Scene List
	IMAGEMANAGER->addImage("TitleBg", "Resources/Images/BackGround/Title.bmp", 640, 480);
	IMAGEMANAGER->addImage("SceneList", "Resources/Images/BackGround/SceneList.bmp", 640, 480);
	// Stage 1
	IMAGEMANAGER->addImage("Field", "Resources/Images/BackGround/Field.bmp", 2120, 1536);
	// Stage 2
	//IMAGEMANAGER->addImage("Field", "Resources/Images/BackGround/Field.bmp", 2120, 1536);
	// Stage 3
	IMAGEMANAGER->addImage("Final", "Resources/Images/BackGround/Final.bmp", 1557, 1080);
#pragma endregion
#pragma region recall Scene
	// Stage 1
	IMAGEMANAGER->addImage("Field", "Resources/Images/BackGround/Field.bmp", 2120, 1536);
	// Stage 2
	IMAGEMANAGER->addImage("Field", "Resources/Images/BackGround/Field.bmp", 2120, 1536);
	// Stage 3
	IMAGEMANAGER->addImage("brother", "Resources/Images/BackGround/final.bmp", 2120, 1536);
#pragma endregion
#pragma region UI Scene
	IMAGEMANAGER->addImage("curMap", "Resources/Images/UI/curMap.bmp", 241, 111, MGT);
	IMAGEMANAGER->addImage("introtext", "Resources/Images/UI/introtext.bmp", 230, 105);
	IMAGEMANAGER->addImage("mapInfoAll", "Resources/Images/UI/mapInfoAll.bmp", 230, 105);
	IMAGEMANAGER->addImage("mapInfobg", "Resources/Images/UI/mapInfo.bmp", 230, 105);
	IMAGEMANAGER->addImage("button", "Resources/Images/UI/UI_button.bmp", 102, 28, MGT);
	IMAGEMANAGER->addImage("blockCell", "Resources/Images/UI/blockCell.bmp", 38, 24);//����

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
