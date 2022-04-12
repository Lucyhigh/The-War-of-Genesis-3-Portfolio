#pragma once
#include "GameNode.h"
enum SKILL_NUMBER
{
	SKILL_INDEX_NULL,
	SKILL_INDEX_EYUN,
	SKILL_INDEX_DASH,
	SKILL_INDEX_WORLDBROKEN,
	SKILL_INDEX_WINDEYUN,
	SKILL_INDEX_END
};

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

struct tagSkillMenu
{
	RECT _buttonRect;
	POINT _textPos;
	POINT _defaultPos;
	LPCWSTR _skillNameInfo;
	LPCWSTR _skillLvInfo;
	LPCWSTR _skillSPInfo;
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

    vector<tagSkillMenu> _vSkillButton;
    vector<tagSkillMenu>::iterator _viSkillButton;

	vector<tagMoveTile> _vMoveTile;
	vector<tagMoveTile>::iterator _viMoveTile;
	POINT _uiPos;
	POINT _PlayerPos;
	POINT _tileCenter;
	LPCWSTR _uiMainText[4];
	LPCWSTR _uiSkillText[4];
	LPCWSTR _uiSkillLvText[4];
	LPCWSTR _uiSkillSPText[4];
	SKILL_NUMBER _skillIndex;
	float _tileAlpha;
    int _buttonIndex;
    int _moveRange;
	bool _isMainMenu;
	bool _isSkillMenu;
	bool _isPlayerTurn;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	bool getSkillMenu();
	bool getPlayerTurn();
	bool getMenu();
	void showBattleMenu(POINT menuPos);
	void showSkillMenu(POINT menuPos);
	void setMoveTileRange(int range);
	void setMoveCenter(POINT center);
	SKILL_NUMBER getSkillNum();
    void setSkillNum(SKILL_NUMBER state);
public:
	GameUI() :_skillIndex(SKILL_INDEX_NULL),_uiMainText{ L"어빌리티",L"아이템",L"휴 식",L"상 태" }, _uiSkillText{ L"  연",L"댓쉬",L"천지파열무",L"풍아열공참" },
		_uiSkillLvText{ L"LV10", L"LV5", L"LV1", L"LV1"}, _uiSkillSPText{ L"30", L"40", L"140", L"200"}{}
	~GameUI() {}
};

