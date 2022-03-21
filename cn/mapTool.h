#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>

//멀까 이건
#define ISO_UNMOVE UNMOVE

//########aStar관련 변수###########
struct tagMAStarTile
{
	int tileNum;
	int parentNodeTileNum;
	int totalCost;
	int costFromStart;
	int costToGoal;
	bool isOpen;
};
//########aStar관련 변수###########

struct tagTilePoint
{
	float x;
	float y;
};

//내가 클릭한 현재 타일을 저장할 구조체
struct tagTempTile
{
	int fX;
	int fY;
};

struct tagSample
{
	RECT rc;
	int fX;
	int fY;
};

class mapTool : public gameNode
{
private:
	isoTile		_isoTile[TILEX * TILEY];
	tagTilePoint	_tilePoint;
	tagSample		_sample[SAMPLEX * SAMPLEY];
	tagTempTile		_tempTile;

	//버튼 렉트들
	RECT			_saveBt;
	RECT			_saveBt2;
	RECT			_saveBt3;

	RECT			_loadBt;
	RECT			_loadBt2;
	RECT			_loadBt3;

	RECT			_move;
	RECT			_unMove;

	RECT			_undo;
	RECT			_fill;

	RECT			_open;
	RECT			_close;

	RECT			_small;
	RECT			_medium;
	RECT			_max;

	RECT			_leftBt;
	RECT			_rightBt;

	RECT			_goldBt;

	RECT			_menuRc;
	RECT			_objDel;

	RECT			_delAll;
	RECT			_homeBt;
	RECT			_dragBt;

	RECT			_tree1;
	RECT			_tree2;
	RECT			_tree3;
	RECT			_tree4;
	RECT			_tree5;
	RECT			_lava_obj1;
	RECT			_lava_obj2_l;
	RECT			_lava_obj2_r;
	RECT			_lava_obj3;


	RECT			_wall1;
	RECT			_wall2;
	RECT			_wall3;
	RECT			_wall4;

	RECT			_playerFlagRc;
	RECT			_enemyFlagRc;
	RECT			_dragRc;
	int _savePopUp; // 0이면 없는거고 1이면 저장잘됐다 2이면 오류메세지 팝업
	int _popUpCount;

	/////////////////////////////////////
	RECT			_icZergling;
	RECT			_icMarine;
	RECT			_icCivilian;
	RECT			_icTemplar;
	RECT			_icBishop;
	RECT			_icDiablo;
	RECT			_icSkeleton;
	RECT			_icGhost;
	RECT			_icDragon;
	RECT			_icTower1;
	/////////////////////////////////////
	POINT			_pickingPt;

	POINT			_cameraPtMouse; // 걍피티마우스말고 카메라위치 보정한 피티마우스

	bool			_moveUnMove;
	bool			_tempSaved;
	bool			_brushOn;
	bool			_objDelOn;
	bool			_menuInPt;
	bool			_dragMode;

	int _currentStage; // 몇 스테이지 작업중인지 (편의상 1,2,3)

	renderSize		_rs;
	menuNum			_menuNum;
	objName			_objName;

	//########aStar관련 변수###########
	vector<tagMAStarTile*>			_vTotalList;
	vector<tagMAStarTile*>::iterator _viTotalList;
	vector<tagMAStarTile*>			_vOpenList;
	vector<tagMAStarTile*>::iterator _viOpenList;
	vector<tagMAStarTile*>			_vCloseList;
	vector<tagMAStarTile*>::iterator _viCloseList;
	int _startTile;		//시작타일의 번호
	int _endTile;			//도착타일
	int _currentTile;		//현재타일

	bool _stop; // 못찾은거
	bool _seePath;

	int _playerTile; // 플레이어 깃발이 몇타일에 있는지 로드할때 불러온다.
	int _enemyTile; // 에너미 깃발이 몇타일에 있는지 로드할때 불러온다.

	int _modifyingNum; // 몇자리수째를 수정중인지 (0=수정중x, 1천자릿수 2백자릿수 3십자리수 4일의자리수)
	int _modifyingCount; // 5초카운트

	float _dragX; float _dragY;
	bool _push;
public:
	vector<int> aStarPath(int fromTileNum, int toTileNum);

	//갈수 있는 길을 찾아내서 담아줄 함수
	vector<tagMAStarTile*> addOpenList(int currentTile);
	//빠른 경로 찾을 함수
	void pathFinder(int currentTile);
	//########aStar관련###########

public:
	mapTool();
	~mapTool();
	vector<int> _path;

	HRESULT init();
	void release();
	void update();
	void render();

	void createIsoMap(int tileX, int tileY);		//왼쪽에 베이스타일 깔아주는 함수
	void createSampleTiles();										//샘플타일 깔아주는 함수
	void ptInIso();												//샘플타일 안에 마우스가 들어갔을때
	void createTile();												//타일을 새롭게 업데이트 해주는 함수
	void imageInit();												//이미지 인잇
	void imageRender();												//이미지 렌더
	void moveUnMove();												//두개 버튼을 눌렀을때 일어나는 기능정의
	void openClose();												//브러쉬도구 접기 펼치기
	void renderSize();												//렌더 사이즈 조절
	void leftRightBt();												//브러쉬도구 메뉴 넘기기
	void ptInObj();													//오브젝트마다 고유이름을 주었기때문에 오브젝트 클릭시 효과를 다르게줄려고만듬
	void createObj();												//타일에 오브젝트 속성을 넣어주는 것
	void objDel();													//오브젝트 지우개
	void menuInPt();												//메뉴 안에 마우스가 들어갔을때 타일 안찍히게 막음
	void sampleInTemp();											//샘플 타일의 값을 템프에 담아주는 함수
	void homeBt();
	void dragPaint();												//스윽 그려서 칠하기
	void tempDrag();												//누른 포인트 담기
	void dragOnOff();												//드으래그모드 온오프

	void save();
	void load();
	void tempSave();												//뒤로가기가 되어줄 상황(?)을 저장해서 담아주는 기능
	void tempLoad();												//뒤로가기의 상황(?)을 불러와줌

	void fill(int x, int y);										//전체 타일을 칠해주는 함수
	void objDelAll();												//오브젝트 전체를 지워주는 함수

	void cameraControl();
	void sampleTileMove();

	inline POINT picking(long x, long y); // 피킹하는 함수


	void numberInput();
};

