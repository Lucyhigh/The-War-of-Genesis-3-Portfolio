#include "Stdafx.h"
#include "SoundScene.h"

HRESULT SoundScene::init(void)
{
	IMAGEMANAGER->addImage("엘든링","Resources/Images/BackGround/Ring.bmp",WINSIZE_X, CENTER_Y);//YENA 대신
	IMAGEMANAGER->addImage("츄","Resources/Images/BackGround/CHUU.bmp",WINSIZE_X, CENTER_Y);
	IMAGEMANAGER->addImage("수스","Resources/Images/BackGround/SS.bmp",WINSIZE_X, CENTER_Y);
	IMAGEMANAGER->addImage("그냥","Resources/Images/BackGround/JUSTRing.bmp",WINSIZE_X, CENTER_Y);
	IMAGEMANAGER->addImage("미카","Resources/Images/BackGround/MIKA.bmp",WINSIZE_X, CENTER_Y);
	IMAGEMANAGER->addImage("장기하","Resources/Images/BackGround/JGH.bmp",WINSIZE_X, CENTER_Y);
	IMAGEMANAGER->addImage("미노이","Resources/Images/BackGround/MINOI.bmp",WINSIZE_X, CENTER_Y);

	//SOUNDMANAGER->addSound("찬란","Resources/Sounds/OBLIVION.wav", true, true);
	SOUNDMANAGER->addSound("LightSwitch","Resources/Sounds/LightSwitch.mp3", true, false);
	SOUNDMANAGER->addSound("GraceKelly","Resources/Sounds/GraceKelly.mp3", true, true);
	//SOUNDMANAGER->addSound("SRSR","Resources/Sounds/SRSR.mp3", true, true);
	//SOUNDMANAGER->addSound("Lxxk2U","Resources/Sounds/Lxxk2U.mp3", true, true);
	//SOUNDMANAGER->addSound("Just","Resources/Sounds/Just.mp3", true, true);
	//SOUNDMANAGER->addSound("Not","Resources/Sounds/Not.mp3", true, true);
	//SOUNDMANAGER->addSound("HeartAttack","Resources/Sounds/HeartAttack.mp3", true, true);
	//SOUNDMANAGER->setUp("Resources/Sounds/Golden.mp3", SOUND_BGM, true, true); c스타일

    _volume = 1.0f;
	return S_OK;
}

void SoundScene::release(void)
{
}

void SoundScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SOUNDMANAGER->play("LightSwitch", _volume);
     
		//SOUNDMANAGER->play(SOUND_BGM, 1.0f);  c스타일
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SOUNDMANAGER->stop("LightSwitch");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SOUNDMANAGER->pause("LightSwitch");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SOUNDMANAGER->resume("LightSwitch");
	}

    if (SOUNDMANAGER->isPlaySound("LightSwitch"))
    {
        if (KEYMANAGER->isOnceKeyDown(VK_UP))
        {
            _volume += 2.0f;
        } 
        else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
        {
            _volume -= 2.0f;
        }
        cout << _volume << endl;
    }
	SOUNDMANAGER->update();
}

void SoundScene::render(void)
{
	IMAGEMANAGER->render("엘든링", getMemDC(),0,CENTER_Y);
}

SoundScene::SoundScene()
{
}
