#pragma once
#include "GameNode.h"
struct ImgInfo
{
	Image* _image;
	RECT _buttonRect;
	POINT _imgPos;
	POINT _defaultPos;
    string _textInfo;
	int _index;
};

class GameUI:public GameNode
{
private:
	Image* _image;
	vector<ImgInfo> _vMenuButton;
    vector<ImgInfo>::iterator _viMenuButton;
	POINT _uiPos;
	
    string _uiText[4];
    int _buttonIndex;
	bool _isTurn;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	POINT getPos();
	void showBattleMenu(POINT menuPos);
public:
    GameUI() :_uiText{"스 킬","휴 식","아이템","상 태"} {}
	~GameUI() {}
};

