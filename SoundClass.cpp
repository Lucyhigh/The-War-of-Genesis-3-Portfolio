#include "Stdafx.h"
#include "SoundClass.h"

HRESULT SoundClass::init(void)
{
	SOUNDMANAGER->addSound("Tutorial", "Resources/Sounds/Tutorial.mp3", true, true);
	SOUNDMANAGER->addSound("Prologue", "Resources/Sounds/Prologue.mp3", true, true);
	SOUNDMANAGER->addSound("Rage of Lion", "Resources/Sounds/Rage of Lion.mp3", true, true);
	SOUNDMANAGER->addSound("UnknownBlood", "Resources/Sounds/UnknownBlood.mp3", true, true);

	SOUNDMANAGER->addSound("changeScene", "Resources/Sounds/changeScene.mp3", false, false);
	SOUNDMANAGER->addSound("YouDied", "Resources/Sounds/YouDied.mp3", false, false);

	return S_OK;
}