#pragma once
#include "SingletonBase.h"

/*
C/C++
설계가 c쪽이다.
C#

FMOD
- Sound Engine 라이브러리
ㄴ Unreal Unity 에는 라인센스 계약으로 기본 내장 되어 있다.
   ㄴ 이외의 대부분의 플랫폼에선 사용하기 위해 선행 준비를 해줘야 한다.

FMOD를 사용한 대표적 게임
- 바이오쇼크

*/

/*
enum SOUNDKIND : UINT8
{
   SOUND_BGM=0,
   SOUND_EFFECT_1,
   SOUND_EFFECT_2,
   SOUND_END,
};


//여분 채널 갯수 (버퍼)
//#define EXTRA_SOUND_CHANNEL 5

// 총 사운드 갯수
//#define TOTAL_SOUND_CHANNEL SOUNDKIND::SOUND_END+EXTRA_SOUND_CHANNEL


using namespace FMOD;

class SoundManager:public SingletonBase<SoundManager>
{
private:

   System* _system;
   Sound** _sound;
   Channel** _channel;

public:
   HRESULT init(void);
   void release(void);
   void update(void);

   //사운드 파일 셋업
   void setUp(char* fileName, int soundKind, bool backGround, bool loop);
   //사운드 플레이
   void play(int soundKind, float volume);


   SoundManager();
   ~SoundManager();

};

*/

constexpr auto soundBuffer = 10;
//여분 채널 갯수 (버퍼)
constexpr auto extraSoundChannel = 5;
// 총 사운드 갯수
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
	Sound** _sound;         //사운드 음원 포인터
	Channel** _channel;      //사운드 채널

	arrSounds _mTotalSounds;
	//arrChannels _mTotalChannels;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void addSound(string keyName, string soundName, bool backGround, bool loop);

	//사운드 플레이
	void play(string keyName, float volume);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);

	int getSoundCount() { return _mTotalSounds.size(); }

	//sound 길이 
	unsigned int getLength(string keyName);
	//플레이 위치
	unsigned int getPosition(string keyName);
	void setPosition(string keyName, unsigned int position);

	float getVolume(string keyName);
	void setVolume(string keyName, float volume);
	void setAllVolume(float volume);

	SoundManager();
	~SoundManager();

};
