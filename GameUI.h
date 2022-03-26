#pragma once
#include "GameNode.h"
struct battleImgInfo
{
	Image* _image;
	RECT _buttonRect;
	POINT _imgPos;
	POINT _defaultPos;
    LPCWSTR _textInfo;
	int _index;
};

class GameUI:public GameNode
{
private:
	Image* _image;
	vector<battleImgInfo> _vMenuButton;
    vector<battleImgInfo>::iterator _viMenuButton;
	POINT _uiPos;
	
	LPCWSTR _uiText[4];
    int _buttonIndex;
	bool _isMenu;
	bool _isPlayerTurn;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	POINT getPos();
	bool getPlayerTurn();
	bool getMenu();
	void showBattleMenu(POINT menuPos);
public:
    GameUI() :_uiText{L"스 킬",L"아이템",L"휴 식",L"상 태"} {}
	~GameUI() {}
};

