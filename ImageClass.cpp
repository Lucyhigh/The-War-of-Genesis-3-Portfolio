#include "Stdafx.h"
#include "ImageClass.h"

HRESULT ImageClass::init(void)
{
#pragma region Script Image
	IMAGEMANAGER->addImage("store", "Resources/Images/UI/store.bmp", 300,333, MGT);
	IMAGEMANAGER->addImage("weaponShop", "Resources/Images/UI/weaponShop.bmp", 300, 360, MGT);
	IMAGEMANAGER->addImage("vermont", "Resources/Images/UI/vermont.bmp", 360, 480,MGT);
	IMAGEMANAGER->addImage("saladin", "Resources/Images/UI/saladin.bmp", 400,480,MGT);
	IMAGEMANAGER->addImage("sheherazade", "Resources/Images/UI/sheherazade.bmp", 524, 480, MGT);

#pragma endregion
#pragma region Player Image
	IMAGEMANAGER->addFrameImage("pRightIdle", "Resources/Images/Player/rightIdle.bmp", 185,75, 5, 1, MGT);
	IMAGEMANAGER->addFrameImage("pLeftIdle", "Resources/Images/Player/leftIdle.bmp", 185, 75, 5, 1, MGT);
	IMAGEMANAGER->addFrameImage("pUpIdle", "Resources/Images/Player/upIdle.bmp", 265,87, 5, 1, MGT);
	IMAGEMANAGER->addFrameImage("pDownIdle", "Resources/Images/Player/downIdle.bmp", 245,78, 5, 1, MGT);
	IMAGEMANAGER->addImage("test", "Resources/Images/Player/1-1.bmp", 53,84,true, RGB(0,0,0));

	IMAGEMANAGER->addFrameImage("pRightMove", "Resources/Images/Player/rightMove.bmp",462, 76, 6, 1, MGT);
	IMAGEMANAGER->addFrameImage("pLeftMove", "Resources/Images/Player/leftMove.bmp", 462, 76, 6, 1, MGT);
	IMAGEMANAGER->addFrameImage("pUpMove", "Resources/Images/Player/upMove.bmp", 228,80, 6, 1, MGT);
	IMAGEMANAGER->addFrameImage("pDownMove", "Resources/Images/Player/downMove.bmp", 372, 91, 6, 1, MGT);

	IMAGEMANAGER->addFrameImage("pRightAtt", "Resources/Images/Player/rightAtt.bmp", 340, 110, 4, 1, MGT);
	IMAGEMANAGER->addFrameImage("pLeftAtt", "Resources/Images/Player/leftAtt.bmp", 340, 110, 4, 1, MGT);
	IMAGEMANAGER->addFrameImage("pUpAtt", "Resources/Images/Player/upAtt.bmp", 400,80, 4, 1, MGT);
	IMAGEMANAGER->addFrameImage("pDownAtt", "Resources/Images/Player/downAtt.bmp", 352, 104, 4, 1, MGT);
	IMAGEMANAGER->addFrameImage("pDamageSheet", "Resources/Images/Player/pDamageSheet.bmp", 248,84, 4,1, MGT);

#pragma endregion
#pragma region Saladin Image
	IMAGEMANAGER->addFrameImage("sRightIdle", "Resources/Images/Saladin/rightIdle.bmp", 272, 90, 4, 1, MGT);
	IMAGEMANAGER->addFrameImage("sLeftIdle", "Resources/Images/Saladin/leftIdle.bmp", 272, 90, 4, 1, MGT);
	IMAGEMANAGER->addFrameImage("sUpIdle", "Resources/Images/Saladin/upIdle.bmp", 280, 90, 4, 1, MGT);
	IMAGEMANAGER->addFrameImage("sDownIdle", "Resources/Images/Saladin/downIdle.bmp", 280, 90, 4, 1, MGT);

    IMAGEMANAGER->addFrameImage("sMovesheet", "Resources/Images/Saladin/movesheet.bmp", 720, 480, 6, 4,true, RGB(168, 208, 168));
    IMAGEMANAGER->addFrameImage("sAttacksheet", "Resources/Images/Saladin/attacksheet.bmp", 650, 520, 5, 4,true, RGB(168, 208, 168));
    IMAGEMANAGER->addFrameImage("sDamageSheet", "Resources/Images/Saladin/damageSheet.bmp", 404, 87, 4, 1,true, RGB(168, 208, 168));
    IMAGEMANAGER->addFrameImage("sSkill", "Resources/Images/Saladin/skill.bmp", 1100, 101, 11, 1,true, RGB(168, 208, 168));

#pragma endregion
#pragma region Stage Scene
	IMAGEMANAGER->addImage("TitleBg", "Resources/Images/BackGround/Title.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("TitleName", "Resources/Images/UI/TitleGameName.bmp", WINSIZE_X, WINSIZE_Y, MGT);
	IMAGEMANAGER->addFrameImage("TitleEfx", "Resources/Images/UI/titleEfx.bmp", 2241,2025,6,6,true,RGB(4, 0, 4));
	IMAGEMANAGER->addImage("Map", "Resources/Images/UI/map.bmp", 1657, 1737, true, RGB(255,252,0));
	IMAGEMANAGER->addImage("Sea", "Resources/Images/UI/sea.bmp", WINSIZE_X, WINSIZE_Y);

	IMAGEMANAGER->addFrameImage("SceneList", "Resources/Images/BackGround/SceneList.bmp", 1900, WINSIZE_Y,2,1);
	IMAGEMANAGER->addImage("Field", "Resources/Images/BackGround/Field.bmp", 2120, 1536);
	IMAGEMANAGER->addImage("battleScene", "Resources/Images/BackGround/Field.bmp", 839, 1121);
	IMAGEMANAGER->addImage("storyStart", "Resources/Images/BackGround/storyStart.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("battleBefore", "Resources/Images/BackGround/battleBefore.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("battleAfter1", "Resources/Images/BackGround/battleAfter1.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("battleAfter2", "Resources/Images/BackGround/battleAfter2.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("battleAfter3", "Resources/Images/BackGround/battleAfter3.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("deadHer", "Resources/Images/BackGround/deadHer.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("deadHer2", "Resources/Images/BackGround/deadHer2.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("song", "Resources/Images/BackGround/song.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("01past", "Resources/Images/BackGround/01past.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("02past", "Resources/Images/BackGround/02past.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("brother", "Resources/Images/BackGround/brother.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("ending", "Resources/Images/BackGround/ending.bmp", WINSIZE_X, WINSIZE_Y);	
	IMAGEMANAGER->addImage("endingScript1", "Resources/Images/BackGround/endingScript1.bmp", WINSIZE_X, WINSIZE_Y);
    IMAGEMANAGER->addImage("endingScript2", "Resources/Images/BackGround/endingScript2.bmp", WINSIZE_X, WINSIZE_Y);
    IMAGEMANAGER->addImage("endingScript3", "Resources/Images/BackGround/endingScript3.bmp", WINSIZE_X, WINSIZE_Y);
    IMAGEMANAGER->addImage("endingScript4", "Resources/Images/BackGround/endingScript4.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addFrameImage("deadHer", "Resources/Images/UI/story/deadHer.bmp", 258,75,3,1, true, RGB(72, 221, 157));
	IMAGEMANAGER->addFrameImage("truth", "Resources/Images/UI/story/truth.bmp", 432, 80,6,1, true, RGB(72, 221, 157));
	IMAGEMANAGER->addImage("Final", "Resources/Images/BackGround/Final.bmp", 1557, 1080);
#pragma endregion
#pragma region recall Scene
	IMAGEMANAGER->addImage("Devil", "Resources/Images/BackGround/Devil.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("Field", "Resources/Images/BackGround/Field.bmp", 2120, 1536);
	IMAGEMANAGER->addImage("brother", "Resources/Images/BackGround/final.bmp", 2120, 1536);
#pragma endregion
#pragma region UI Scene
	IMAGEMANAGER->addImage("cutChange", "Resources/Images/BackGround/cutChange.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("cutChangeRed", "Resources/Images/BackGround/cutChangeRed.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("curMap", "Resources/Images/UI/curMap.bmp", 241, 111, MGT);
	IMAGEMANAGER->addImage("introtext", "Resources/Images/UI/introtext.bmp", 230, 105);
	IMAGEMANAGER->addImage("storyText", "Resources/Images/UI/storyText.bmp", 511*1.33,111 * 1.33);
	IMAGEMANAGER->addImage("mapInfoAll", "Resources/Images/UI/mapInfoAll.bmp", 230, 105);
	IMAGEMANAGER->addImage("button", "Resources/Images/UI/UI_button.bmp", 102*1.3, 28*1.3, MGT);
	IMAGEMANAGER->addImage("MapButton", "Resources/Images/UI/UI_buttonMap.bmp", 164,48, MGT);
	IMAGEMANAGER->addImage("mapMark", "Resources/Images/UI/mapMark.bmp", 127,136, MGT);
	IMAGEMANAGER->addImage("battleMark", "Resources/Images/UI/battleMark.bmp", 36,32, true, RGB(0, 252, 0));
	IMAGEMANAGER->addImage("storyText", "Resources/Images/UI/storyText.bmp", 511, 111);
	IMAGEMANAGER->addImage("skillText", "Resources/Images/UI/skillText.bmp", 328, 171);
	IMAGEMANAGER->addImage("shadow", "Resources/Images/UI/shadow.bmp", 42, 29, true, RGB(252, 252, 0));
	IMAGEMANAGER->addImage("moveTile", "Resources/Images/UI/moveable.bmp", 40, 32);
	IMAGEMANAGER->addImage("attackTile", "Resources/Images/UI/attackable.bmp", 40, 32);
	IMAGEMANAGER->addImage("skillTile", "Resources/Images/UI/skillable.bmp", 40, 32);
	IMAGEMANAGER->addImage("ScenarioClear", "Resources/Images/UI/ScenarioClear.bmp", 960, 90);

	IMAGEMANAGER->addFrameImage("selectIcon", "Resources/Images/UI/selectIcon.bmp", 96,25,4,1, MGT);
	IMAGEMANAGER->addFrameImage("skillIcon", "Resources/Images/UI/skillIcon.bmp", 68*1.5,17*1.5,4,1, MGT);
	IMAGEMANAGER->addFrameImage("npcBar", "Resources/Images/UI/npcbar.bmp", 800, 91,8,1,MGT);
	IMAGEMANAGER->addFrameImage("pHpBar", "Resources/Images/UI/pHpBar.bmp", 5400 * 0.2, 300 * 0.2, 15, 1, true, RGB(0, 44, 0));
	IMAGEMANAGER->addFrameImage("eHpBar", "Resources/Images/UI/eHpBar.bmp", 5400 * 0.2, 300 * 0.2, 15, 1, true, RGB(0, 44, 0));
	IMAGEMANAGER->addFrameImage("pHpBarNum", "Resources/Images/UI/pHpBarNum.bmp", 110, 14, 14, 1, true, RGB(80, 120, 116));

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
	ANIMATIONMANAGER->addAnimation("TitleEfx", "TitleEfx", 10, false, true);
	ANIMATIONMANAGER->addAnimation("notMoveable", "notMoveable",5, false, true);
	ANIMATIONMANAGER->addAnimation("turnMark", "turnMark", 5, false, true);
	ANIMATIONMANAGER->addAnimation("playerMark", "playerMark", 5, false, true);
	ANIMATIONMANAGER->addAnimation("enemyMark", "enemyMark", 5, false, true);
	ANIMATIONMANAGER->addAnimation("attackMark", "attackMark", 7, false, true);
    ANIMATIONMANAGER->addAnimation("npcBar", "npcBar", 10, false, true);
    ANIMATIONMANAGER->addAnimation("pHpBar", "pHpBar", 10, false, false);
    ANIMATIONMANAGER->addAnimation("eHpBar", "eHpBar", 10, false, false);
    ANIMATIONMANAGER->addAnimation("normalCursor", "normalCursor", 5, false, true);
    ANIMATIONMANAGER->addAnimation("clickTile", "clickTile", 5, false, true);
	
#pragma endregion
#pragma region Skill
	IMAGEMANAGER->addFrameImage("skillStart", "Resources/Images/Player/skillStart.bmp", 832, 223, 4,1,MGT);
	IMAGEMANAGER->addFrameImage("smog", "Resources/Images/Effect/all/smog.bmp", 448*1.2, 146 * 1.2,7,2,true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("smog2", "Resources/Images/Effect/all/smog2.bmp", 650, 650, 5,5,true,RGB(4,72,4));
	IMAGEMANAGER->addFrameImage("circle", "Resources/Images/Effect/all/circle.bmp", 1592, 628, 8,4,true,RGB(4,108,0));
	IMAGEMANAGER->addFrameImage("fire", "Resources/Images/Effect/all/fire.bmp", 660, 230, 12,1,true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("fire2", "Resources/Images/Effect/all/fire2.bmp", 660, 230, 12,1,true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("fire3", "Resources/Images/Effect/all/fire3.bmp", 660, 230, 12,1,true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("fire4", "Resources/Images/Effect/all/fire4.bmp", 660, 230, 12,1,true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("fireL", "Resources/Images/Effect/all/fireL.bmp", 660, 230, 12,1,true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("fireL2", "Resources/Images/Effect/all/fireL2.bmp", 660, 230, 12, 1, true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("fireL3", "Resources/Images/Effect/all/fireL3.bmp", 660, 230, 12, 1, true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("fireL4", "Resources/Images/Effect/all/fireL4.bmp", 660, 230, 12,1,true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("groundCrack", "Resources/Images/Effect/all/groundCrack.bmp", 600, 50, 12,1,true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("groundCrackL", "Resources/Images/Effect/all/groundCrackL3.bmp", 600, 50, 12,1,true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("48fire", "Resources/Images/Effect/all/48fire.bmp", 872, 131, 8,1,true, RGB(252, 252, 236));
	IMAGEMANAGER->addFrameImage("95light", "Resources/Images/Effect/all/95light.bmp", 3502, 218, 17,1,true, RGB(252, 252, 252));
	IMAGEMANAGER->addFrameImage("184light", "Resources/Images/Effect/single/184light.bmp", 2460, 172, 12,1,true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("203smog", "Resources/Images/Effect/all/203smog.bmp", 680, 72, 10,1,true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("115stone", "Resources/Images/Effect/all/115stone.bmp", 660, 230, 12,1,true, RGB(156, 148, 140));
	IMAGEMANAGER->addFrameImage("skillStartLight", "Resources/Images/Effect/all/skillStartLight.bmp", 1500, 1500, 5,5,true, RGB(80, 0, 0));
	IMAGEMANAGER->addFrameImage("enemyAttack", "Resources/Images/Effect/all/enemyAttack.bmp", 660, 400, 6,4,true,RGB(8,88,8));
	IMAGEMANAGER->addFrameImage("one", "Resources/Images/Effect/all/one.bmp", 200, 2400, 4,8,true, RGB(252, 236, 212));
	IMAGEMANAGER->addFrameImage("double", "Resources/Images/Effect/all/double.bmp", 300, 1500, 6,5,true, RGB(252, 236, 212));
	IMAGEMANAGER->addFrameImage("tripleR", "Resources/Images/Effect/all/tripleR.bmp", 400, 1200, 8,4,true, RGB(252, 236, 212));
	IMAGEMANAGER->addFrameImage("tripleL", "Resources/Images/Effect/all/tripleL.bmp", 400, 1200, 8,4,true, RGB(252, 236, 212));

	IMAGEMANAGER->addFrameImage("playerSkillFrame", "Resources/Images/Player/playerSkillFrame.bmp", 3990, 400, 19,2,MGT);
	
	IMAGEMANAGER->addFrameImage("skill2", "Resources/Images/Effect/single/skill2.bmp", 1200, 2400, 4, 8, true, RGB(152, 0, 0));
	IMAGEMANAGER->addFrameImage("skill3", "Resources/Images/Effect/single/skill3.bmp", 2700, 900, 9, 3, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("skill4L", "Resources/Images/Effect/single/skill4L.bmp", 1200, 300, 4, 1, true, RGB(0, 0, 0));
    IMAGEMANAGER->addFrameImage("skill4R", "Resources/Images/Effect/single/skill4R.bmp", 1200, 300, 4, 1, true, RGB(0, 0, 0));
    IMAGEMANAGER->addFrameImage("skill4T", "Resources/Images/Effect/single/skill4T.bmp", 1200, 300, 4, 1, true, RGB(0, 0, 0));
    IMAGEMANAGER->addFrameImage("skill4B", "Resources/Images/Effect/single/skill4B.bmp", 1200, 300, 4, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("skill6", "Resources/Images/Effect/single/skill6.bmp", 3000, 300, 10, 1, true, RGB(4, 64, 0));
	IMAGEMANAGER->addFrameImage("skill7", "Resources/Images/Effect/single/skill7.bmp", 3300, 300, 11, 1, true, RGB(4, 96, 4));
	IMAGEMANAGER->addFrameImage("skill8", "Resources/Images/Effect/single/skill8.bmp", 3300, 300, 11, 1, true, RGB(4, 100, 4));
	IMAGEMANAGER->addFrameImage("skill9", "Resources/Images/Effect/single/skill9.bmp", 1500, 900, 5, 3, true,RGB(0,0,0));
	IMAGEMANAGER->addFrameImage("skill10L", "Resources/Images/Effect/single/skill10L.bmp", 636, 150, 4, 1, true, RGB(0,0,0));
    IMAGEMANAGER->addFrameImage("skill10R", "Resources/Images/Effect/single/skill10R.bmp", 636, 150, 4, 1, true, RGB(0,0,0));
    IMAGEMANAGER->addFrameImage("skill10T", "Resources/Images/Effect/single/skill10T.bmp", 636, 150, 4, 1, true, RGB(0,0,0));
    IMAGEMANAGER->addFrameImage("skill10B", "Resources/Images/Effect/single/skill10B.bmp", 636, 150, 4, 1, true, RGB(0,0,0));

#pragma endregion
	return S_OK;
}