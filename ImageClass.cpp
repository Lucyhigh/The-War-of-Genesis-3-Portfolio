#include "Stdafx.h"
#include "ImageClass.h"

HRESULT ImageClass::init(void)
{
#pragma region Player Image
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
    //damage
	IMAGEMANAGER->addFrameImage("pDamageSheet", "Resources/Images/Player/pDamageSheet.bmp", 248,84, 4,1, MGT);

#pragma endregion
#pragma region Saladin Image
	//Idle
	IMAGEMANAGER->addFrameImage("sRightIdle", "Resources/Images/Saladin/rightIdle.bmp", 272, 90, 4, 1, MGT);
	IMAGEMANAGER->addFrameImage("sLeftIdle", "Resources/Images/Saladin/leftIdle.bmp", 272, 90, 4, 1, MGT);
	IMAGEMANAGER->addFrameImage("sUpIdle", "Resources/Images/Saladin/upIdle.bmp", 280, 90, 4, 1, MGT);
	IMAGEMANAGER->addFrameImage("sDownIdle", "Resources/Images/Saladin/downIdle.bmp", 280, 90, 4, 1, MGT);

    //move
    IMAGEMANAGER->addFrameImage("sMovesheet", "Resources/Images/Saladin/movesheet.bmp", 720, 480, 6, 4,true, RGB(168, 208, 168));
	//attack
    IMAGEMANAGER->addFrameImage("sAttacksheet", "Resources/Images/Saladin/attacksheet.bmp", 650, 520, 5, 4,true, RGB(168, 208, 168));
    //damage
    IMAGEMANAGER->addFrameImage("sDamageSheet", "Resources/Images/Saladin/damageSheet.bmp", 404, 87, 4, 1,true, RGB(168, 208, 168));

#pragma endregion
#pragma region Stage Scene
	//Title
	IMAGEMANAGER->addImage("TitleBg", "Resources/Images/BackGround/Title.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addFrameImage("TitleEfx", "Resources/Images/UI/titleEfx.bmp", 996, 225,4,1,true,RGB(4, 0, 4));// 4, 1,
	IMAGEMANAGER->addImage("TitleName", "Resources/Images/UI/TitleGameName.bmp", WINSIZE_X, WINSIZE_Y, MGT);

	//Map
	IMAGEMANAGER->addImage("Map", "Resources/Images/UI/map.bmp", 1243, 1499, true, RGB(255,255,0));
	IMAGEMANAGER->addImage("Sea", "Resources/Images/UI/sea.bmp", WINSIZE_X, WINSIZE_Y);

	//Scene List
	IMAGEMANAGER->addFrameImage("SceneList", "Resources/Images/BackGround/SceneList.bmp", 1900, WINSIZE_Y,2,1);
	// Stage 1
	IMAGEMANAGER->addImage("Field", "Resources/Images/BackGround/Field.bmp", 2120, 1536);
	// Stage 2
	// Stage 3
	IMAGEMANAGER->addImage("Final", "Resources/Images/BackGround/Final.bmp", 1557, 1080);
#pragma endregion
#pragma region recall Scene
	// Stage 1
	IMAGEMANAGER->addImage("Devil", "Resources/Images/BackGround/Devil.bmp", WINSIZE_X, WINSIZE_Y);
	// Stage 2
	IMAGEMANAGER->addImage("Field", "Resources/Images/BackGround/Field.bmp", 2120, 1536);
	// Stage 3
	IMAGEMANAGER->addImage("brother", "Resources/Images/BackGround/final.bmp", 2120, 1536);
#pragma endregion
#pragma region UI Scene
	IMAGEMANAGER->addImage("cutChange", "Resources/Images/BackGround/cutChange.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("curMap", "Resources/Images/UI/curMap.bmp", 241, 111, MGT);
	IMAGEMANAGER->addImage("introtext", "Resources/Images/UI/introtext.bmp", 230, 105);
	IMAGEMANAGER->addImage("mapInfoAll", "Resources/Images/UI/mapInfoAll.bmp", 230, 105);
	IMAGEMANAGER->addImage("mapInfobg", "Resources/Images/UI/mapInfo.bmp", 230, 105);
	IMAGEMANAGER->addImage("button", "Resources/Images/UI/UI_button.bmp", 102, 28, MGT);
	IMAGEMANAGER->addImage("storyText", "Resources/Images/UI/storyText.bmp", 511, 111);
	IMAGEMANAGER->addFrameImage("npcBar", "Resources/Images/UI/npcbar.bmp", 800, 91,8,1,MGT);
	IMAGEMANAGER->addFrameImage("hpBar", "Resources/Images/UI/hpBar.bmp", 915, 49,15,1,true,RGB(0,44,0));//원작과 좀 달라서 수정필요

	IMAGEMANAGER->addImage("moveTile", "Resources/Images/UI/moveable.bmp", 40, 32);
	IMAGEMANAGER->addImage("attackTile", "Resources/Images/UI/attackable.bmp", 40, 32);
	IMAGEMANAGER->addFrameImage("notMoveable", "Resources/Images/UI/notMoveable.bmp", 76, 24,2,1,true, RGB(80, 120, 116));
	IMAGEMANAGER->addFrameImage("turnMark", "Resources/Images/UI/turnMark.bmp", 40, 7, 8, 1, true, RGB(80, 120, 116));
	IMAGEMANAGER->addFrameImage("playerMark", "Resources/Images/UI/playerMark.bmp", 72, 11, 8, 1, true, RGB(80, 120, 116));
	IMAGEMANAGER->addFrameImage("enemyMark", "Resources/Images/UI/enemyMark.bmp", 72, 11, 8, 1, true, RGB(80, 120, 116));
	IMAGEMANAGER->addFrameImage("attackMark", "Resources/Images/UI/attackMark.bmp", 217, 32, 7, 1, true, RGB(80, 120, 116));
	IMAGEMANAGER->addFrameImage("normalCursor", "Resources/Images/UI/normalCursor.bmp", 112, 24, 7, 1, true, RGB(80, 120, 116));
	IMAGEMANAGER->addFrameImage("clickTile", "Resources/Images/UI/clickTile.bmp", 240, 32, 6, 1);
#pragma endregion
#pragma region Animation
	ANIMATIONMANAGER->addAnimation("sMovesheet", "sMovesheet", 0, 23, 5, false, true);
    //UI
	ANIMATIONMANAGER->addAnimation("TitleEfx", "TitleEfx", 3, false, true);
	ANIMATIONMANAGER->addAnimation("notMoveable", "notMoveable",5, false, true);
	ANIMATIONMANAGER->addAnimation("turnMark", "turnMark", 5, true, true);
	ANIMATIONMANAGER->addAnimation("playerMark", "playerMark", 5, true, true);
	ANIMATIONMANAGER->addAnimation("enemyMark", "enemyMark", 5, true, true);
	ANIMATIONMANAGER->addAnimation("attackMark", "attackMark", 7, false, true);
    ANIMATIONMANAGER->addAnimation("npcBar", "npcBar", 5, true, true);
    ANIMATIONMANAGER->addAnimation("hpBar", "hpBar", 5, false, false);
    ANIMATIONMANAGER->addAnimation("normalCursor", "normalCursor", 5, false, true);
    ANIMATIONMANAGER->addAnimation("clickTile", "clickTile", 5, true, true);
#pragma endregion
	return S_OK;
}