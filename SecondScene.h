#pragma once
#include "GameNode.h"
#include "Text.h"

#define TEXTNum 48
#define BgImageNUM 5
class SecondScene : public GameNode
{
private:
	tagBgImage _bgImage[BgImageNUM];
	tagText _text[TEXTNum];//이후 json에 대사 이동
	Animation* _aniCursor;
	RECT _mouseRc;
	RECT _endRc;
	RECT _moveRc;

    float _bgMoved;
    float _textAlpha;
    float _eventAlpha;
    float _bgAlpha;
    float _alpha;
    float _fadeAlpha;
    int _moveCount;
    int _textBufferCnt;
    int _textIndex;
    int _nameIndex;
    int _frameIndex;
    int _loofIndex;
	int _mouseIndex;
	int _endPointIndex;
	int _moveIndex;
	int _count;
	bool _isMove;
	bool _isfadeOut;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void fadeout();
public:
	SecondScene() :_isfadeOut(false),
	_bgImage
	{
		{0,"cutChange"},
		{1,"storyStart"},
		{29,"deadHer"},
		{44,"deadHer2"},
		{45,"battleBefore"},
	}, _text
	{
		L"[셰라자드]",{"sheherazade"},L"이 시간에 누구시죠 ? 당신은... ?",
		L"[버몬트]",{"vermont"},L"팬드래건의 버몬트 대공이요. 당신의 주인되는 사람이지.",
		L"[셰라자드]",{"sheherazade"},L"그게 무슨 말씀이시죠 ?",
		L"[버몬트]",{"vermont"},L"이미, 투르전역에 공고했소이다. 당신과 나의 결혼을.",
		L"[셰라자드]",{"sheherazade"},L"결혼이라니요...저는 당신을...",
		L"[버몬트]",{"vermont"},L"당신의 의사는 중요치 않소. 이미 모든 일은 결정되었으니 당신은 따라오기만 하면 되오.",
		L"[셰라자드]",{"sheherazade"},L"안돼요! 저에게는 이미 사랑하는 사람이 있어요.",
		L"[버몬트]",{"vermont"},L"사랑 ? 흥, 일국의 군주에게는 너무 사치스러운 이야기군. 우리가 합침으로서 투르와 팬드래건의 오랜 전쟁을 끝맺을수 있소.",
		L"[셰라자드]",{"sheherazade"},L"이방에서 나가세요! 저는 당신을 인정할수 없습니다!",
		L"[버몬트]",{"vermont"},L"당신의 운명을 저주하시오.",
		L"[살라딘]",{"saladin"},L"셰라자드 ?!",
		L"[셰라자드]",{"sheherazade"},L"오지말아요!",
		L"[버몬트]",{"vermont"},L"기다리고 있었다",
		L"[살라딘]",{"saladin"},L"...",
		L"[버몬트]",{"vermont"},L"지난번엔 운좋게 빠져나갔지만 이번엔 힘들걸 ?",
		L"[셰라자드]",{"sheherazade"},L"살라딘...",
		L"[살라딘]",{"saladin"},L"셰라자드, 걱정마시오. 곧 구해줄테니...",
		L"[버몬트]",{"vermont"},L"흥! 네놈의 이야기는 들었다.요새 두개가 네녀석에게 박살이 났더군. 자, 어서 그 칼을 버리지 않으면, 이 여자를 두번 다시 볼 수 없을 것이다.",
		L"[셰라자드]",{"sheherazade"},L"살라딘, 저는 개의치 마세요. 저는 이미 깨끗하지 못한 몸이에요.",
		L"[살라딘]",{"saladin"},L"설마...",
		L"[버몬트]",{"vermont"},L"하하하! 투르제국의 여술탄과 팬드래건 왕가의 결합. 멋지지 않나 ? 단, 투르의 영토는 지참금으로 가지고 와야지.",
		L"[살라딘]",{"saladin"},L"왜 그런짓을 하는거지?",
		L"[버몬트]",{"vermont"},L"복수다! 네놈따위는 상상도 하지 못할 증오에 찬 복수! 자, 네놈과 떠들 시간따윈 없어.어서 칼을 버리지 않으면 이 여자의 목숨은 없다!",
		L"[살라딘]",{"saladin"},L"좋다. 칼을 버리겠다.",
		L"[셰라자드]",{"sheherazade"},L"살라딘님, 안돼요!왜 자신에 대해 얘기 안하시는 거죠 ?",	
		L"[살라딘]",{"saladin"},L"셰라자드, 나는 이미 과거는 잊었다오. 단지 한사람의 투르인으로 살아왔고 투르인으로 죽을것이오.",
		L"[버몬트]",{"vermont"},L"어서 녀석을 체포해라!",
		L"[셰라자드]",{"sheherazade"},L"살라딘님!저는 언제나 당신의 짐만 되는 군요. 하지만, 이젠 저도 용기를 내겠어요...",
		L"[살라딘]",{"saladin"},L"안돼!!!!",
		L"[버몬트]",{"vermont"},L"제길, 할 수 없군.",
		L"[살라딘]",{"saladin"},L"이게 무슨 짓이오!",
		L"[셰라자드]",{"sheherazade"},L"순결을 잃었을 때 죽지 못했던 건...살라딘님께...할말이 있어서에요...",
		L"[살라딘]",{"saladin"},L"그런것이 무슨 소용이란 말이오!",
		L"[셰라자드]",{"sheherazade"},L"살라딘님...투르를 선택해줘서 고마워요...하지만 이젠 돌아가세요... 모든 사람들...용서해 주세요...",
		L"[살라딘]",{"saladin"},L"이젠 늦었소...당신이 없는 세상은 나에게도 어둠일 뿐이오.",//흐느끼며
		L"[셰라자드]",{"sheherazade"},L"언젠가...말씀하셨죠...저에게 이 투르의 빛이 되어달라고...하지만 이젠 살라딘님만이 할수있어요...",
		L"[셰라자드]",{"sheherazade"},L"이 투르와 팬드래건...아니 온 세상 모든 사람들의 빛이 되어 주실수 있겠죠... ?",
		L"[살라딘]",{"saladin"},L"죽으면 안되오. 당신없인 나도 살아갈수 없단 말이오.",
		L"[셰라자드]",{"sheherazade"},L"약속해 주실수 있으시겠죠... ? 모든 사람을 용서하고...모든 사람들의 빛이 되어 주실거죠... ?",
		L"[살라딘]",{"saladin"},L"하지만, 녀석들은 당신과 친구들의 원수일 뿐이오.",
		L"[셰라자드]",{"sheherazade"},L"...약속해 주실수 있으시죠...제발...마지막 소원이에요...",
		L"[살라딘]",{"saladin"},L"당신은 정말 나에게 어려운 약속을 남기는군.",
		L"[셰라자드]",{"sheherazade"},L"...이제는...그런 느낌이 들어요...언...젠가...언젠간...다시 만날 수 있을것 같아요.",
		L"[살라딘]",{"saladin"},L"셰라자드...!",
		L"[셰라자드]",{"sheherazade"},L"......안녕",
		L"[버몬트]",{"vermont"},L"다 끝내셨나?",
		L"[살라딘]",{"saladin"},L"복수심에 붙잡혀 있는 불쌍한 인간이군.",
		L"[버몬트]",{"vermont"},L"너 따위가 나에 대해 뭘 안단 거냐 ? 뭐,상관없지... 자, 각오해라!"
	}{}
	~SecondScene(){}
};