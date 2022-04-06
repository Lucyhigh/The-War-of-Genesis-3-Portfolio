#pragma once
#include "GameNode.h"
struct tagBattleMenu
{
	Image* _image;
	Image* _iconImage;
	RECT _buttonRect;
	POINT _imgPos;
	POINT _iconPos;
	POINT _defaultPos;
    LPCWSTR _textInfo;
	int _index;
};

struct tagMoveTile
{
	Image* _image;
	RECT _buttonRect;
	POINT _tilePos;
};

class GameUI:public GameNode
{
private:
	Image* _image;
	Image* _tileImage;
	Image* _iconImage;
	vector<tagBattleMenu> _vMenuButton;
    vector<tagBattleMenu>::iterator _viMenuButton;

	vector<tagMoveTile> _vMoveTile;
	vector<tagMoveTile>::iterator _viMoveTile;
	POINT _uiPos;
	POINT _tileCenter;
	LPCWSTR _uiText[4];
	
	float _tileAlpha;
    int _buttonIndex;
    int _moveRange;
	bool _isMenu;
	bool _isTileSetting;
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
	void showMoveTile(POINT center);
	void MakeMoveTile();
	void setMoveTileRange(int range);
	void setMoveCenter(POINT center);
public:
    GameUI() :_uiText{L"어빌리티",L"아이템",L"휴 식",L"상 태"} {}
	~GameUI() {}
};

