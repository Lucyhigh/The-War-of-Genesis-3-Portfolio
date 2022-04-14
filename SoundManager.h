#pragma once
#include "SingletonBase.h"

constexpr auto soundBuffer = 10;
//���� ä�� ���� (����)
constexpr auto extraSoundChannel = 5;
// �� ���� ����
constexpr auto totalSoundChannel = soundBuffer + extraSoundChannel;

using namespace FMOD;

class SoundManager :public SingletonBase<SoundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundsIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator arrChannelsIter;

	System* _system;
	Sound** _sound;         //���� ���� ������
	Channel** _channel;      //���� ä��

	arrSounds _mTotalSounds;
    bool isPlay;
public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void addSound(string keyName, string soundName, bool backGround, bool loop);

	void play(string keyName, float volume);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);
    bool isPlaySound(string keyName);

    unsigned int getLength(string keyName);
    unsigned int getPosition(string keyName);
	SoundManager();
	~SoundManager();

};
