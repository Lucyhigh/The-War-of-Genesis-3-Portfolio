#pragma once
#include "GameNode.h"
#include "Text.h"

#define TEXTNumTWO 8
#define BgImageNUMTWO 10
class EndingScene:public GameNode
{
private:
    tagBgImage _bgImage[BgImageNUMTWO];
    tagText _text[TEXTNumTWO];//���� json�� ��� �̵�
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
    EndingScene() :_isfadeOut(false),
        _bgImage
    {
        {0,"cutChange"},
        {11,"battleAfter1"},
        {13,"battleAfter2"},
        {13,"battleAfter3"},
        {15,"0154"},
        {15,"0110"},
        {15,"0129"},
        {30,"0151"},
        {55,"0167"}
    }, _text
    {
        L"����Ʈ",{"vermont"},L"�׿���...",
        L"����",{"saladin"},L"...",
        L"����Ʈ",{"vermont"},L"�װ͸���... ���� ������ �װ͸���...",
        L"",{"�̹���1"},L"�츮�� �̷��� �ٽ� �������ϴ�.",
        L"",{"�̹���2"},L"�ʹ����� �⳪�� �ð����� �귯 ���Ƚ��ϴ�.",
        L"",{"�̹���3"},L"�ʹ����� ���� ���� ���� ���Ƚ��ϴ�.",
        L"",{"�̹���4"},L"�׷��� ���� ������ ����մϴ�.",
        L"",{"�̹���4"},L"���� ���� �Ǿ���Ѵ�."
    }{}
    ~EndingScene() {}
};