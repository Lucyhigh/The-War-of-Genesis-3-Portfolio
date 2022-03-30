#pragma once
#include "GameNode.h"
#include "AniScene.h"
struct TitlebuttomInfo
{
    RECT _buttonRect;
    LPCWSTR _textInfo;
    int _index;
};
class TitleScene : public GameNode
{
private:
    bitset<4> _startBit;
    // 0000 Ÿ��Ʋȭ��
    // 0001 ��ŸƮ��ư - �� ����Ʈ������ �Ѿ
    // 0010 ���̺�ȭ��
	Animation* _animation;
	Image* _image;
	AniSceneTitle* _ani;
    vector<TitlebuttomInfo> _vTitleButton;
    vector<TitlebuttomInfo>::iterator _viTitleButton;
    LPCWSTR _uiText[3];
    LPCWSTR _sceneText[21];
    POINT _buttonSize;
    POINT _SceneBoxSize;
    vector<TitlebuttomInfo> _vSceneButton;
    vector<TitlebuttomInfo>::iterator _viSceneButton;
	float _alpha;
	float _fadeAlpha;
	int _menuIndex;
	
    bool _isfadeOut;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
    void fadeout();

public:
	TitleScene():_uiText { L"Start Game", L"Load Game", L"Exit" }, 
        _sceneText{
    L"����л�",  L"�������� ����", L"���� �˰�",    L"",               L"��Ÿ�� �ں��",     L"������ �Ŀ�", L"�縷�� ��ǳ",
    L"�����Ҷ�",  L"",             L"ȣ���� ����",  L"ĿƼ�� ħ������",  L"�ƽ�Ÿ�Ͼ��� �ٶ�", L" ",          L"ũ���� ũ�缼�̴�", 
    L"������",    L"����",      L"������ �Ŀ�",  L"��������� ����", L"",                 L"�縷�� ��",   L""
    }{}
	~TitleScene() {}

};