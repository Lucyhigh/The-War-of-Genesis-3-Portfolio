#pragma once
#include "SingletonBase.h"

using namespace FMOD;

constexpr auto soundBuffer = 10;
constexpr auto extraSoundChannel = 5;
constexpr auto totalSoundChannel = soundBuffer + extraSoundChannel;

class SoundManager :public SingletonBase<SoundManager>
{
private:
	typedef map<string, Sound**> arrSounds; //음원개수 string 음원 이름 , Sound 음원
	typedef map<string, Sound**>::iterator  arrSoundsIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator  arrChannelsIter;

	System* _system;
	Sound** _sound; 
	Channel** _channel;

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
	bool isPauseSound(string keyName);
public:
	SoundManager();
	~SoundManager() {}
};