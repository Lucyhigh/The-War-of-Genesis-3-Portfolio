#pragma once
#include "GameNode.h"
struct ImgInfo
{
	Image* _image;
	RECT _buttonRect;
	POINT _imgPos;
	int _index;
};

class GameUI:public GameNode
{
private:
	Image* _image;
	ImgInfo _imageInfo;
	vector<ImgInfo> _menuButton;
	POINT _imgPos;
	bool _isTurn;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void showBattleMenu();
	POINT getPos();
	void setPos(POINT menuPos);
public:
	GameUI() {}
	~GameUI() {}
};

