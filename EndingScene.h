#pragma once
#include "GameNode.h"
#include "Text.h"

#define TEXTNumTWO 8
#define BgImageNUMTWO 9
class EndingScene:public GameNode
{
private:
    tagBgImage _bgImage[BgImageNUMTWO];
    tagText _text[TEXTNumTWO];//���� json�� ��� �̵�
    Animation* _aniCursor;
    RECT _mouseRc;
    RECT _endRc;
    RECT _moveRc;

	vector<string> _vSoundName;
	int _playIndex;

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
    bool _isfadeOut;
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
        {3,"0154"},
        {4,"0110"},
        {5,"0129"},
        {6,"0151"},
        {7,"0167"},
        {8,"cutChange"}
    }, _text
    {
        L"����Ʈ",{"vermont"},L"�׿���...",
        L"����",{"saladin"},L"...",
        L"����Ʈ",{"vermont"},L"�װ͸���... ���� ������ �װ͸���...",
		//�뷡��� �� �� + Ÿ�̹� �ְ� ���� ��� 2���� �ִϸ��̼� ���
        L"",{"�̹���1"},L"�츮�� �̷��� �ٽ� �������ϴ�.",
        L"",{"�̹���2"},L"�ʹ����� �⳪�� �ð����� �귯 ���Ƚ��ϴ�.",
        L"",{"�̹���3"},L"�ʹ����� ���� ���� ���� ���Ƚ��ϴ�.",
        L"",{"�̹���4"},L"�׷��� ���� ������ ����մϴ�.",
        L"",{"�̹���4"},L"���� ���� �Ǿ���Ѵ�." //������ ���鼭 06 ���ķδ� Ÿ�̹����� �������
    }{}
    ~EndingScene() {}
};