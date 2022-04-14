#include "Stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager():_system(nullptr),
							_channel(nullptr),
							_sound(nullptr),
    isPlay(false)
{
}

HRESULT SoundManager::init(void)
{
	//사운드 시스템 생성
	System_Create(&_system);

	//시스템 초기화
	_system->init(totalSoundChannel, FMOD_INIT_NORMAL,0);

	//채널 수 만큼 메모리 버퍼 및 사운드를 생성
	_sound = new Sound*[totalSoundChannel];
	_channel = new Channel*[totalSoundChannel];

	//메모리 한번 밀자
	memset(_sound, 0, sizeof(Sound*) * (totalSoundChannel));
	memset(_channel, 0, sizeof(Channel*) * (totalSoundChannel));
	
	return S_OK;
}

void SoundManager::release(void)
{
	//destroy - 소리는 중지를 시킨다음 지워야한다
	if (_channel != nullptr || _sound != nullptr)
	{
		for (int i = 0; i < totalSoundChannel; i++)
		{
			if (_channel != nullptr)
			{
				if(_channel[i])_channel[i]->stop();
			}
			if (_sound != nullptr)
			{   
                //리소스 해제
				if(_sound != nullptr)_sound[i]->release();

			}
		}
	}
	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);
    //시스템 닫기
	if (_system != nullptr)
	{
		_system->release();
		_system->close();
	}
    
}

void SoundManager::addSound(string keyName, string soundName, bool backGround,bool loop)
{
	if (loop)
	{
		if (backGround)
		{
			//파일이름, 사운드를 열기 위한 옵션, 피드백(개발자에게 사운드가 재생되는 동안 정보를 제공할거냐?)
			//soundKind는 변수의 주소
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			//효과음
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		//FMOD_DEFAULT : 한번 플레이
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
	}
	//맵에 넣기 (_sound[keyName] = &_sound[_mTotalSounds.size()];)
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

void SoundManager::update(void)
{
	//사운드 시스템 업데이트
	//ㄴ 볼륨이 바뀌거나 재생이 끝난 사운드를 채널에서 빼는 등 다양한 작업을 자동으로 한다.
	_system->update();
}
void SoundManager::play(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_system->playSound(FMOD_CHANNEL_FREE,  
                *iter->second,
                false,                              
                &_channel[count]);

			_channel[count]->setVolume(volume);
			cout << count << endl;
			break;
		}
	}
}
//맵 검색특화  - 메모리에 정렬이 아니여도 키도 파인드로 찾아서 지울수있음 - 버퍼가 중요한 사운드의 채널 불일치
//++iter 컨테이너 찾아갈때 널포인터 안뜨게 유니크 포인터 사용

void SoundManager::stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first) 
			_channel[count]->stop();
		break;
	}
}

void SoundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
			_channel[count]->setPaused(true);
		break;
	}
}

void SoundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
			_channel[count]->setPaused(false);
		break;
	}
}

bool SoundManager::isPlaySound(string keyName)
{
	int count = 0;
	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
			_channel[count]->isPlaying(&isPlay);
		break;
	}
	return isPlay;
    cout << isPlay << endl;
}

bool SoundManager::isPauseSound(string keyName)
{
	bool isPause;
	int count = 0;
	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
			_channel[count]->isPlaying(&isPause);
		break;
	}
	return isPause;
}