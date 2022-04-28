#pragma once
#include "GameNode.h"

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
	Animation* _animation;
	Animation* _aniCursor;
	Image* _image;
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
	TitleScene():_uiText { L"Start Game", L"Saved Game", L"Exit" }{}
	~TitleScene() {}

};