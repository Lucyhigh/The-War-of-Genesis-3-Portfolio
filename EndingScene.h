#pragma once
#include "GameNode.h"
#include "Text.h"

#define TEXTNumTWO 4
#define BgImageNUMTWO 12
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
	int _soundIndex;

    float _bgMoved;
    float _textAlpha;
    float _eventAlpha;
    float _bgAlpha;
    float _alpha;
    float _fadeAlpha;

    int _textBufferCnt;
    int _textIndex;
    int _bgIndex;
    int _count;
    int _cdt;
    bool _isStory;
    bool _isFadeOut;
    bool _isFadeIn;

public:
    HRESULT init(void);
    void release(void);
    void update(void);
    void render(void);
    void fadeout();
    void fadeIn();
public:
    EndingScene() :
        _bgImage
    {
        {0,"battleAfter1"},
        {1,"battleAfter2"},
        {2,"battleAfter3"},
        {3,"song"},
        {4,"01past"},
        {5,"02past"},
        {6,"brother"},
        {7,"endingScript1"},
        {8,"endingScript2"},
        {9,"endingScript3"},
        {10,"endingScript4"},
        {11,"ending"}
    }, _text
    {
        L"버몬트",{"vermont"},L"죽여라...",
        L"살라딘",{"saladin"},L"...",
        L"버몬트",{"vermont"},L"그것만은... 제발 돌려줘 그것만은...",
        L"살라딘",{""},L"좋은 왕이 되어야한다." //엔딩씬 띄우면서 06 이후로는 타이밍으로 성우재생
    }{}
    ~EndingScene() {}
};