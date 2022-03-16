#include "Stdafx.h"
#include "SoundScene.h"

HRESULT SoundScene::init(void)
{
	IMAGEMANAGER->addImage("���縵","Resources/Images/BackGround/Ring.bmp",WINSIZE_X, CENTER_Y);//YENA ���
	IMAGEMANAGER->addImage("��","Resources/Images/BackGround/CHUU.bmp",WINSIZE_X, CENTER_Y);
	IMAGEMANAGER->addImage("����","Resources/Images/BackGround/SS.bmp",WINSIZE_X, CENTER_Y);
	IMAGEMANAGER->addImage("�׳�","Resources/Images/BackGround/JUSTRing.bmp",WINSIZE_X, CENTER_Y);
	IMAGEMANAGER->addImage("��ī","Resources/Images/BackGround/MIKA.bmp",WINSIZE_X, CENTER_Y);
	IMAGEMANAGER->addImage("�����","Resources/Images/BackGround/JGH.bmp",WINSIZE_X, CENTER_Y);
	IMAGEMANAGER->addImage("�̳���","Resources/Images/BackGround/MINOI.bmp",WINSIZE_X, CENTER_Y);

	//SOUNDMANAGER->addSound("����","Resources/Sounds/OBLIVION.wav", true, true);
	SOUNDMANAGER->addSound("LightSwitch","Resources/Sounds/LightSwitch.mp3", true, false);
	SOUNDMANAGER->addSound("GraceKelly","Resources/Sounds/GraceKelly.mp3", true, true);
	//SOUNDMANAGER->addSound("SRSR","Resources/Sounds/SRSR.mp3", true, true);
	//SOUNDMANAGER->addSound("Lxxk2U","Resources/Sounds/Lxxk2U.mp3", true, true);
	//SOUNDMANAGER->addSound("Just","Resources/Sounds/Just.mp3", true, true);
	//SOUNDMANAGER->addSound("Not","Resources/Sounds/Not.mp3", true, true);
	//SOUNDMANAGER->addSound("HeartAttack","Resources/Sounds/HeartAttack.mp3", true, true);
	//SOUNDMANAGER->setUp("Resources/Sounds/Golden.mp3", SOUND_BGM, true, true); c��Ÿ��

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
     
		//SOUNDMANAGER->play(SOUND_BGM, 1.0f);  c��Ÿ��
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
	IMAGEMANAGER->render("���縵", getMemDC(),0,CENTER_Y);
}

SoundScene::SoundScene()
{
}
