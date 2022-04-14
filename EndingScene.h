#pragma once
#include "GameNode.h"
#include "Text.h"

#define TEXTNumTWO 9
#define BgImageNUMTWO 10
class EndingScene:public GameNode
{
private:
    tagBgImage _bgImage[BgImageNUMTWO];
    tagText _text[TEXTNumTWO];//이후 json에 대사 이동
    Animation* _aniCursor;
    RECT _mouseRc;
    RECT _endRc;
    RECT _moveRc;

	vector<string> _vSoundName;
	float _soundVolume;
	int _playIndex;

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
    EndingScene() :_isfadeOut(false),
        _bgImage
    {
        {0,"cutChange"},
        {1,"battleAfter1"},
        {2,"battleAfter2"},
        {2,"battleAfter3"},
        {3,"0154"},
        {4,"0110"},
        {5,"0129"},
        {6,"0151"},
        {7,"0167"}
        {8,"cutChange"},
    }, _text
    {
        L"버몬트",{"vermont"},L"죽여라...",
        L"살라딘",{"saladin"},L"...",
        L"",{""},L"",
        L"버몬트",{"vermont"},L"그것만은... 제발 돌려줘 그것만은...",
		//노래재생 이 후 + 타이밍 주고 성우 재생 2부터 애니메이션 재생
        L"",{"이미지1"},L"우리는 이렇게 다시 만났습니다.",
        L"",{"이미지2"},L"너무나도 기나긴 시간들이 흘러 버렸습니다.",
        L"",{"이미지3"},L"너무나도 많은 것이 변해 버렸습니다.",
        L"",{"이미지4"},L"그래도 나는 동생을 사랑합니다.",
        L"",{"이미지4"},L"좋은 왕이 되어야한다." //엔딩씬 띄우면서 06 이후로는 타이밍으로 성우재생
    }{}
    ~EndingScene() {}
};