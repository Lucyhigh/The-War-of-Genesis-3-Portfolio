#pragma once
#include "GameNode.h"
#include "Camera.h"
struct MapbuttomInfo
{
	RECT _buttonRect;
	LPCWSTR _textInfo;
	int _index;
};
class MapScene:public GameNode
{
private:
	Image* _image;
	vector<MapbuttomInfo> _vMapButton;
	vector<MapbuttomInfo>::iterator _viMapButton;

	float _seaX;
	float _seaY;
	float _alpha;
	float _fadeAlpha;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void fadeout();
public:
	MapScene() {}
	~MapScene() {}
};

