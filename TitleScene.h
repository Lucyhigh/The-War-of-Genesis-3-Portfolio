#pragma once
#include "GameNode.h"
#include "AniScene.h"

class TitleScene : public GameNode
{
private:
	Image* _image;
	bool _anyButton;
	bool _title;

	//bool _pushButton;
	int _alpha;
	bool _isAlphaIncrese;
	AniSceneTitle* _ani;
	int _menuIndex;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	TitleScene() {}
	~TitleScene() {}

};