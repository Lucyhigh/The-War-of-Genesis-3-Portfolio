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
	//���� �ý��� ����
	System_Create(&_system);

	//�ý��� �ʱ�ȭ
	_system->init(totalSoundChannel, FMOD_INIT_NORMAL,0);

	//ä�� �� ��ŭ �޸� ���� �� ���带 ����
	_sound = new Sound*[totalSoundChannel];
	_channel = new Channel*[totalSoundChannel];

	//�޸� �ѹ� ����
	memset(_sound, 0, sizeof(Sound*) * (totalSoundChannel));
	memset(_channel, 0, sizeof(Channel*) * (totalSoundChannel));
	/*
	//���� �ý��� ����
	System_Create(&_system);

	//�ý��� �ʱ�ȭ
	_system->init(TOTAL_SOUND_CHANNEL, FMOD_INIT_NORMAL,0);

	//ä�� �� ��ŭ �޸� ���� �� ���带 ����
	_sound = new Sound*[TOTAL_SOUND_CHANNEL];
	_channel = new Channel*[TOTAL_SOUND_CHANNEL];

	//�޸� �ѹ� ����
	memset(_sound, 0, sizeof(Sound*) * (TOTAL_SOUND_CHANNEL));
	memset(_channel, 0, sizeof(Channel*) * (TOTAL_SOUND_CHANNEL));
	
	*/
	return S_OK;
}

void SoundManager::release(void)
{
	//destroy - �Ҹ��� ������ ��Ų���� �������Ѵ�
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
                //���ҽ� ����
				if(_sound != nullptr)_sound[i]->release();

			}
		}
	}
	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);
    //�ý��� �ݱ�
	if (_system != nullptr)
	{
		_system->release();
		_system->close();
	}
    //Map ����
    //sounds.clear();
	/*
	//destroy
	if (_channel != nullptr || _sound != nullptr)
	{
		for (int i = 0; i < TOTAL_SOUND_CHANNEL; i++)
		{
			if (_channel != nullptr)
			{
				if(_channel[i])_channel[i]->stop();
			}
			if (_sound != nullptr)
			{
				if(_sound != nullptr)_sound[i]->release();

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
	
	*/
}


void SoundManager::addSound(string keyName, string soundName, bool backGround,bool loop)
{
	if (loop)
	{
		if (backGround)
		{
			//�����̸�, ���带 ���� ���� �ɼ�, �ǵ��(�����ڿ��� ���尡 ����Ǵ� ���� ������ �����Ұų�?)
			//soundKind�� ������ �ּ�
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			//ȿ����
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		//FMOD_DEFAULT : �ѹ� �÷���
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
	}
	//�ʿ� �ֱ� (_sound[keyName] = &_sound[_mTotalSounds.size()];)
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

void SoundManager::update(void)
{
	//���� �ý��� ������Ʈ
	//�� ������ �ٲ�ų� ����� ���� ���带 ä�ο��� ���� �� �پ��� �۾��� �ڵ����� �Ѵ�.
	_system->update();
}
void SoundManager::play(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	//������ ã�� : ���带 5�� �������...++iter, count++.....
	//for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	//������ �� ����...ã�⵵ ����� ��ƴ� count �� �׻� ������ ������ �����Ѵ�
	//_system->playSound(FMOD_CHANNEL_FREE, _sound[count], false, &_channel[count]);
	//_system->playSound(FMOD_CHANNEL_FREE, _sound[*iter->second], false, &_channel[count]);
	//2���̻����� �Ҷ� 2��°���� ��ã�����̴�..*iter->second�� �ص� ������� ��ã�� �����Ұ�
	// 0 0 
	// 0 1
	// 1 2
	// 2 3.....�̷��� ��..�׷��� ù��°���� ��
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �÷���
            //auto next == iter->second;
			_system->playSound(FMOD_CHANNEL_FREE,   //����ִ� ä�� ���
                *iter->second,
                false,                              //�ȸ���
                &_channel[count]);

			//���� ����
			_channel[count]->setVolume(volume);
			break;
		}
	}
}

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
    //��� ä�� �˻��ؼ� �ϳ��� �÷��� ���̸� true��ȯ
	//bool isPlay;
	int count = 0;
	arrSoundsIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
        //keyName�� ��ġ�ϴ� ������ �ִٸ�
		if (keyName == iter->first)
            //������̶�� isPlay�� true�� ����
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


/*

void SoundManager::setUp(char * fileName, int soundKind, bool backGround, bool loop)
{
	if (loop)
	{
		if (backGround)
		{
			//�����̸�, ���带 ���� ���� �ɼ�, �ǵ��(�����ڿ��� ���尡 ����Ǵ� ���� ������ �����Ұų�?)
			//soundKind�� ������ �ּ�
			_system->createStream(fileName, FMOD_LOOP_NORMAL, 0, &_sound[soundKind]);
		}
		else
		{
			//ȿ����
			_system->createSound(fileName, FMOD_LOOP_NORMAL, 0, &_sound[soundKind]);
		}
	}
	else
	{
		//FMOD_DEFAULT : �ѹ� �÷���
			_system->createSound(fileName, FMOD_DEFAULT, 0, &_sound[soundKind]);
	}
}
//���� �÷���(volume ������ Max -> 1.0)
void SoundManager::play(int soundkind, float volume)
{
	//���� �÷���
	_system->playSound(FMOD_CHANNEL_FREE, _sound[soundkind], false, &_channel[soundkind]);

	//���� ����
	_channel[soundkind]->setVolume(volume);
}

*/