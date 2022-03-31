#pragma once
#include "GameNode.h"
#include "MapTileInfo.h"
#include "Text.h"
#include "BgImage.h"
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
    Text _text[TEXTNumTWO];
    BgImage _bgImage[BgImageNUMTWO];
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
	SecondScene():_bgImage
    {
        {9,"길거리배경"},
        {85,"교실배경"},
        {199,"동아리배경"},
        {210,"길거리배경"},
        {298,"동아리배경"},
        {318,"복도배경"},
        {339,"동아리배경"},
        {550,"동아리배경"},
        {755,"동아리배경"},

    },
    _text
    {
        L"",{},{},L"저 멀리서 성가신 여자아이가 주변 사람들 시선은 아랑곳하지 않은 채 팔을 허공에 흔들며 달려온다.",
        L"",{},{},L"저 여자애는 옆집에 사는 아주 어릴 때부터 알고 지낸 소꿉친구 ?痢r?ㅼt寃?臾댁r_q다." }{}
	~SecondScene(){}
};