#include "Stdafx.h"
#include "SoundManager.h"
/*
SoundManager::SoundManager():_system(nullptr),
					  _channel(nullptr),
					  _sound(nullptr)
{
}

SoundManager::~SoundManager()
{
}


HRESULT SoundManager::init(void)
{
   //사운드 시스템 생성
   System_Create(&_system);
   //시스템 초기화
   _system->init(TOTAL_SOUND_CHANNEL, FMOD_INIT_NORMAL, 0);
   //사운드랑 채널수를 맞춰놓는게 좋다.
   //채널 수 만큼
   _sound = new Sound*[TOTAL_SOUND_CHANNEL];
   _channel = new Channel*[TOTAL_SOUND_CHANNEL];

   //메모리 한번 밀자
   memset(_sound,0, sizeof(Sound*)*(TOTAL_SOUND_CHANNEL));
   memset(_channel,0, sizeof(Channel*)*(TOTAL_SOUND_CHANNEL));
   return S_OK;
}

void SoundManager::release(void)
{
   if (_channel != nullptr || _sound != nullptr)
   {
	  for (int i = 0; i < TOTAL_SOUND_CHANNEL; i++)
	  {
		 if (_channel != nullptr)
		 {
			if (_channel[i]) _channel[i]->stop();
		 }
		 if (_sound != nullptr)
		 {
			if (_sound[i]) _sound[i]->release();

		 }
	  }
   }

   SAFE_DELETE_ARRAY(_channel);
   SAFE_DELETE_ARRAY(_sound);
   if (_system != nullptr)
   {
	  _system->release();
	  _system->close();
   }

}

void SoundManager::update(void)
{
   //사운드 시스템 업데이트
   //ㄴ 불륨이 바뀌거나 재생이 끝난 사운드를 채널에서 빼는 등 다양한 작업을 자동으로 한다.
   _system->update();
}

void SoundManager::setUp(char* fileName, int soundKind, bool backGround, bool loop)
{
   if (loop)
   {
	  if (backGround)
	  {
		 //파일이름, 사운드를 열기위한 옵션, 피드백(개발자에게 사운드가 재생되는 동안 정보를 제공할거냐),
		 _system->createStream(fileName, FMOD_LOOP_NORMAL, 0, &_sound[soundKind]);
	  }
	  else
	  {
		 //효과음은 사운드로 만들어 준다. 동시재생을 위해 크리에이트 사운드를 사용
		 _system->createSound(fileName, FMOD_LOOP_NORMAL, 0, &_sound[soundKind]);
	  }
   }
   else
   {
	  _system->createSound(fileName, FMOD_DEFAULT, 0, &_sound[soundKind]);
   }
}

//사운드 플레이(volume 영역은 max -> 1.0)
void SoundManager::play(int soundKind, float volume)
{
   //사운드 플레이
   _system->playSound(FMOD_CHANNEL_FREE, _sound[soundKind], false, &_channel[soundKind]);
   //볼륨설정
   _channel[soundKind]->setVolume(volume);
}

*/



SoundManager::SoundManager() :_system(nullptr),
_channel(nullptr),
_sound(nullptr)
{
}

SoundManager::~SoundManager()
{
}


HRESULT SoundManager::init(void)
{
	//사운드 시스템 생성
	System_Create(&_system);
	//시스템 초기화(채널 갯수, 초기화 방식 다른드라이버)
	_system->init(totalSoundChannel, FMOD_INIT_NORMAL, 0);
	//사운드랑 채널수를 맞춰놓는게 좋다.
	//채널 수 만큼
	_sound = new Sound*[totalSoundChannel];
	_channel = new Channel*[totalSoundChannel];

	//메모리 한번 밀자 
	memset(_sound, 0, sizeof(Sound*)*(totalSoundChannel));
	memset(_channel, 0, sizeof(Channel*)*(totalSoundChannel));
	return S_OK;
}

void SoundManager::release(void)
{
	if (_channel != nullptr || _sound != nullptr)
	{
		for (int i = 0; i < totalSoundChannel; i++)
		{
			if (_channel != nullptr)
			{
				if (_channel[i]) _channel[i]->stop();
			}
			if (_sound != nullptr)
			{
				if (_sound[i]) _sound[i]->release();

			}
		}
	}

	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);
	if (_system != nullptr)
	{
		_system->release();
		_system->close();
	}

}

void SoundManager::update(void)
{
	_system->update();
}

void SoundManager::addSound(string keyName, string soundName, bool backGround, bool loop)
{
	if (loop)
	{
		if (backGround)
		{
			//파일이름, 사운드를 열기위한 옵션, 피드백(개발자에게 사운드가 재생되는 동안 정보를 제공할거냐),사운드 음원 포인터
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			//효과음은 사운드로 만들어 준다. 동시재생을 위해 크리에이트 사운드를 사용
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		//FMOD_DEFAULT 한번 플레이
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
	}
	_mTotalSounds.insert(make_pair(keyName.c_str(), &_sound[_mTotalSounds.size()]));
}


void SoundManager::play(string keyName, float volume)
{
	int count = 0;
	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);
			_channel[count]->setVolume(volume);
			break;
		}
	}

}

void SoundManager::stop(string keyName)
{
	int count = 0;
	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}

void SoundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void SoundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}

bool SoundManager::isPlaySound(string keyName)
{
	bool isPlay;

	arrSoundsIter iter = _mTotalSounds.begin();
	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}
	return isPlay;
}

bool SoundManager::isPauseSound(string keyName)
{
	bool isPause;
	int count = 0;

	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPause);
			break;
		}
	}
	return isPause;
}

unsigned int SoundManager::getLength(string keyName)
{
	Sound* currentSound = nullptr;
	unsigned int length = 0;
	int count = 0;
	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getCurrentSound(&currentSound);
			currentSound->getLength(&length, FMOD_TIMEUNIT_MS);
			break;
		}
	}
	return length;
}

unsigned int SoundManager::getPosition(string keyName)
{
	unsigned int position = 0;
	int count = 0;
	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPosition(&position, FMOD_TIMEUNIT_MS);
			break;
		}
	}
	return position;
}

void SoundManager::setPosition(string keyName, unsigned int position)
{
	int count = 0;
	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPosition(position, FMOD_TIMEUNIT_MS);
			break;
		}
	}
}

float SoundManager::getVolume(string keyName)
{
	float volume;
	int count = 0;
	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getVolume(&volume);
			break;
		}
	}
	return volume;
}

void SoundManager::setVolume(string keyName, float volume)
{
	int count = 0;
	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setVolume(volume);
			break;
		}
	}
}


void SoundManager::setAllVolume(float volume)
{
	int count = 0;
	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		_channel[count]->setVolume(volume);
	}
}