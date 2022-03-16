#pragma once
#include "SingletonBase.h"

using namespace FMOD;
/*
�����Ϸ� �ܰ�
C/C++	��ó���� > 
��Ÿ ���� ������ �־ üũ�ϰ��� �Ʒ��ٷ� ��������.
�׸��� ��ũ-> .obj-> run -> �����Ϸ�
�����ֳİ� �����Ϸ��� ����� üũ�ѰŸ� �����
 -C/C++������ const ����ƴ� ->�ؼ� �ٲܼ����� �ٵ� constexpr�� ���������
C#

*/
/*
FMOD
-sound engine ���̺귯��
�� �𸮾�, ����Ƽ���� ���̼��� ������� �⺻ ����Ǿ� ����
�� �̿��� ��κ��� �÷������� ����ϱ� ���� ���� �غ� ������Ѵ�.

FMOD ����� ��ǥ�� ����
-���̿���ũ, �Ϳ�
*/
//enum SOUNDKIND -  STL�̶� �̳�Ŭ������ ���� ������ ������ ������ ���� �������� �׷��� �̳Ѿ��� ���������͸� ĸ��ȭ��Ű�½������ؾ���..
//�̳Ѻ��� �׷��� �̳�Ŭ������ ����Ѵ�(ĸ��ȭ)
//{
//	SOUND_BGM = 0,
//	SOUND_EFFECT_1,
//	SOUND_EFFECT_2,
//	SOUND_END
//};

//������ ä�� ����(����) - 2.1 / 5.1 / 7.1 ...������ ���� .1 �� ����(����)! 2�� �����뽺��Ŀ 1�� ����ͽ���Ŀ �������� ���ؼ� 5�̻��̾����
//�ڵ忡�� �����ִ� ä�� ������ 2 5 7
/*
const ,constexpr
�� const �� c++11 ������� ����
�� �ش� ��ü�� �Լ��� ���ϰ��� "������"Ÿ�ӿ� �� �� �ִ�.(��)
�� c++ 17���ʹ� ���ٽĿ��� ������ �ȴ�

�� ������ Ÿ�ӿ� ���� �����ǹǷ� �Լ� ȣ�Ⱓ ���ø� ���ڷ� �Ѱ��ٶ� �����ϴ�. ���ø��� �߸���

�� const ,constexpr �������� �ʱ�ȭ ���ο� ���� �߰� �ñ�
�� const ������ �ʱ�ȭ�� ��Ÿ�ӱ��� ������ų �� ������
   constexpr ������ �ݵ�� ������ Ÿ�ӿ� �ʱ�ȭ�� �Ǿ� �־�� �Ѵ�.

const ,constexpr,define
- ������������ ���� ����
- �� ����
- c / c++ �����Ϸ� �����̶� ��������
- const�� ��Ÿ�������� ��
- define�� ��ó���⿡���� �ְ� �޸𸮿� �ȿö�
- constexpr�� ����� ����ε� �����Ϸ����� ���� �ɷ���
- �� �ٿ� �����߸� �ű⼭ ��� ����
- �� �� �ٱ����� ���а� ������ ������ �����Ⱓ�� �ε���ٸ��� �ð��� �ſ�ª����
- �� ������ ���� �������� ���ϳ���
- ���� ���ܰ迡�� �ǳ��ֳĿ� ���� �� ��������� ������
constexpr auto ���int ���..
*/
//constexpr �����ΰ� ��ü�� ��(��ũ��)
constexpr auto soundBuffer = 10;
constexpr auto extraSoundChannel = 5;
constexpr auto totalSoundChannel = soundBuffer + extraSoundChannel;
//c++ ��Ÿ�Ϸ� �ٽ���
class SoundManager:public SingletonBase<SoundManager>
{
private:
	typedef map<string, Sound**> arrSounds; //�������� string ���� �̸� , Sound ����
	typedef map<string, Sound**>::iterator  arrSoundsIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator  arrChannelsIter;
	//�����н��� ��ƾ���
	System* _system;
	Sound** _sound; //Resource �ڿ�(����)
	Channel** _channel;//��� ���� ä��

	arrSounds _mTotalSounds;
    bool isPlay;
public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void addSound(string keyName, string soundName, bool backGround, bool loop);
	
	//���� �÷���
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

//c��Ÿ��
//enum SOUNDKIND
//{
//	SOUND_BGM = 0,
//	SOUND_EFFECT_1,
//	SOUND_EFFECT_2,
//	SOUND_END
//};
//
////������ ä�� ����(����) - 2.1 / 5.1 / 7.1 ...������ ���� .1 �� ����(����)! 2�� �����뽺��Ŀ 1�� ����ͽ���Ŀ �������� ���ؼ� 5�̻��̾����
////�ڵ忡�� �����ִ� ä�� ������ 2 5 7
//#define EXTRA_SOUND_CHANNEL 5
//
////�� ���� ����
//#define TOTAL_SOUND_CHANNEL SOUND_END + EXTRA_SOUND_CHANNEL
//
//class SoundManager :public SingletonBase<SoundManager>
//{
//private:
//	//�����н��� ��ƾ���
//	System* _system;
//	Sound** _sound;
//	Channel** _channel;
//public:
//	HRESULT init(void);
//	void release(void);
//	void update(void);
//
//	//���� ���� �¾�
//	void setUp(char* fileName, int soundKind, bool backGround, bool loop);
//
//	//���� �÷���
//	void play(int soundkind, float volume);
//public:
//	SoundManager();
//	~SoundManager() {}
//};
