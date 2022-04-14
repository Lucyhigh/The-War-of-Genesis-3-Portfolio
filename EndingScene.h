#pragma once
#include "GameNode.h"
#include "Text.h"

#define TEXTNumTWO 9
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
        L"����Ʈ",{"vermont"},L"�׿���...",
        L"����",{"saladin"},L"...",
        L"",{""},L"",
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