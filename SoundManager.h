#pragma once
#include "SingletonBase.h"

using namespace FMOD;
/*
컴파일러 단계
C/C++	전처리기 > 
오타 등의 오류가 있어도 체크하고나서 아랫줄로 내려간다.
그리고 링크-> .obj-> run -> 컴파일러
오류있냐고 컴파일러가 물어보면 체크한거를 띄어줌
 -C/C++에서는 const 상수아님 ->해서 바꿀수있음 근데 constexpr는 ㄹㅇ상수임
C#

*/
/*
FMOD
-sound engine 라이브러리
ㄴ 언리얼, 유니티에는 라이센스 계약으로 기본 내장되어 있음
ㄴ 이외의 대부분의 플랫폼에선 사용하기 위해 선행 준비를 해줘야한다.

FMOD 사용한 대표적 게임
-바이오쇼크, 와우
*/
//enum SOUNDKIND -  STL이랑 이넘클래스랑 궁합 별로임 쓸수는 있지만 쓰기 귀찮아짐 그래서 이넘쓰고 최종데이터만 캡슐화시키는식으로해야함..
//이넘보단 그래도 이넘클래스를 써야한다(캡슐화)
//{
//	SOUND_BGM = 0,
//	SOUND_EFFECT_1,
//	SOUND_EFFECT_2,
//	SOUND_END
//};

//여분의 채널 갯수(버퍼) - 2.1 / 5.1 / 7.1 ...서라운드 갯수 .1 은 우퍼(진폭)! 2는 가정용스피커 1은 모니터스피커 공감각을 위해선 5이상이어야함
//코드에서 맞춰주는 채널 갯수는 2 5 7
/*
const ,constexpr
ㄴ const 는 c++11 모던에서 나옴
ㄴ 해당 객체가 함수의 리턴값을 "컴파일"타임에 알 수 있다.(값)
ㄴ c++ 17부터는 람다식에도 적용이 된다

ㅇ 컴파일 타임에 값이 결정되므로 함수 호출간 템플릿 인자로 넘겨줄때 유용하다. 템플릿과 잘맞음

ㅇ const ,constexpr 차이점은 초기화 여부와 오류 발견 시기
ㄴ const 변수는 초기화를 런타임까지 지연시킬 수 있지만
   constexpr 변수는 반드시 컴파일 타임에 초기화가 되어 있어야 한다.

const ,constexpr,define
- 면접질문으로 많이 나옴
- 값 시점
- c / c++ 컴파일러 과정이랑 관련있음
- const는 런타임전까지 감
- define은 전처리기에서만 있고 메모리에 안올라감
- constexpr는 상수는 상수인데 컴파일러에서 값이 걸러짐
- ㄴ 줄에 오류뜨면 거기서 즉시 멈춤
- ㄴ 그 줄까지만 딱읽고 끝내기 때문에 디버깅기간에 로딩기다리는 시간이 매우짧아짐
- 값 오류에 대한 질문으로 마니나옴
- 값을 어디단계에서 건너주냐에 따라서 뭘 써야할지가 결정됨
constexpr auto 대신int 등등..
*/
//constexpr 디파인과 대체가 됨(매크로)
constexpr auto soundBuffer = 10;
constexpr auto extraSoundChannel = 5;
constexpr auto totalSoundChannel = soundBuffer + extraSoundChannel;
//c++ 스타일로 다시함
class SoundManager:public SingletonBase<SoundManager>
{
private:
	typedef map<string, Sound**> arrSounds; //음원개수 string 음원 이름 , Sound 음원
	typedef map<string, Sound**>::iterator  arrSoundsIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator  arrChannelsIter;
	//파일패스롤 잡아야함
	System* _system;
	Sound** _sound; //Resource 자원(음원)
	Channel** _channel;//재상 사운드 채널

	arrSounds _mTotalSounds;
    bool isPlay;
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
public:
	SoundManager();
	~SoundManager(){}
};

//c스타일
//enum SOUNDKIND
//{
//	SOUND_BGM = 0,
//	SOUND_EFFECT_1,
//	SOUND_EFFECT_2,
//	SOUND_END
//};
//
////여분의 채널 갯수(버퍼) - 2.1 / 5.1 / 7.1 ...서라운드 갯수 .1 은 우퍼(진폭)! 2는 가정용스피커 1은 모니터스피커 공감각을 위해선 5이상이어야함
////코드에서 맞춰주는 채널 갯수는 2 5 7
//#define EXTRA_SOUND_CHANNEL 5
//
////총 사운드 갯수
//#define TOTAL_SOUND_CHANNEL SOUND_END + EXTRA_SOUND_CHANNEL
//
//class SoundManager :public SingletonBase<SoundManager>
//{
//private:
//	//파일패스롤 잡아야함
//	System* _system;
//	Sound** _sound;
//	Channel** _channel;
//public:
//	HRESULT init(void);
//	void release(void);
//	void update(void);
//
//	//사운드 파일 셋업
//	void setUp(char* fileName, int soundKind, bool backGround, bool loop);
//
//	//사운드 플레이
//	void play(int soundkind, float volume);
//public:
//	SoundManager();
//	~SoundManager() {}
//};
