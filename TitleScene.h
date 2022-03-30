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
    // 0000 타이틀화면
    // 0001 스타트버튼 - 씬 리스트씬으로 넘어감
    // 0010 세이브화면
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
    L"동방밀사",  L"시지아의 결전", L"백의 검객",    L"",               L"불타는 자비단",     L"광휘의 후예", L"사막의 광풍",
    L"난공불락",  L"",             L"호수의 여왕",  L"커티스 침공작전",  L"아스타니아의 바람", L" ",          L"크림슨 크루세이더", 
    L"흑전사",    L"생츄어리",      L"망국의 후예",  L"기즈공작의 최후", L"",                 L"사막의 검",   L""
    }{}
	~TitleScene() {}

};