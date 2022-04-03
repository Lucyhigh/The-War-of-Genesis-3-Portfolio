#pragma once
#include "GameNode.h"
#include "Camera.h"
#include "Animation.h"

struct MapbuttomInfo
{
	Image _image;
	RECT _buttonRect;
	LPCWSTR _textInfo;
	int _index;
};
class MapScene:public GameNode
{
private:
	Image* _image;
	Image _buttonImage;
    Image* _moveMark;
	Animation* _animation;
	Animation* _aniCursor;
    Camera* _camera;
    RECT _moveButton[2];
	LPCWSTR _uiText[4];
	vector<MapbuttomInfo> _vMapButton;
	vector<MapbuttomInfo>::iterator _viMapButton;
	POINT _buttonSize;
	POINT _SceneBoxSize;

	int _menuIndex;
	float _seaX;
	float _seaY;
	float _alpha;
	float _fadeAlpha;
    bool _moveNext;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
public:
	MapScene() :_moveNext(false),_uiText{ L"이 동", L"진 입", L"상 태",L"턴종료" } {}
	~MapScene() {}
};

