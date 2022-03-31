#pragma once
#include "GameNode.h"
#include "MapTileInfo.h"
#include "Text.h"
//#include "BgImage.h"
#include "Player.h"
#include "Camera.h"
#include "AStar.h"
#define TEXTNumTWO 756
#define BgImageNUMTWO 9
#define  SELECTNUM 15
class SecondScene : public GameNode
{
private:
	MapTileInfo* _mapTileInfo;
	tagText _text[TEXTNumTWO];
    //BgImage _bgImage[BgImageNUMTWO];
	vector<Cell*>* _cells;
	Image* _image;
	Player* _player;
	Camera* _camera;
	AStar::Generator* _generator;

	POINT _pPlayer;
	POINT _endPoint;
	RECT _mouseRc;
	RECT _endRc;
	RECT _moveRc;
	vector<POINT> _check;
    float _bgMoved;
    float _textAlpha;
    float _eventAlpha;
    float _bgAlpha;
    float _alpha;
	float _lerpPercentage;
    int _moveCount;
    int _textBufferCnt;
    int _textIndex;
    int _nameIndex;
    int _frameIndex;
    int _loofIndex;
	int _mouseIndex;
	int _endPointIndex;
	int _moveIndex;
	int _count;
	bool _isMove;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void drawMapCellInfo();
	void AstarTileInfo();
	void rectMoveToPath();
	void curAstar();
	POINT lerp(POINT start, POINT end, float percentage);

public:
	SecondScene(){}
	~SecondScene(){}
};