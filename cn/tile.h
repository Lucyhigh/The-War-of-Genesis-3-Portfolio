#pragma once

//타일 사이즈
#define TILESIZEX 64
#define TILESIZEY 32

//타일 갯수
#define TILEX 30
#define TILEY 30

//타일셋(샘플타일) 범위
#define SAMPLEX 8
#define SAMPLEY 12

enum moveUnMove
{
	MOVE, UNMOVE
};

enum renderSize
{
	SMALL, MEDIUM, MAX
};

enum menuNum
{
	ONE = 1, TWO, THREE
};

enum objName
{
	//오브젝트 0 ~ 10
	NONE, TREE1, TREE2, TREE3, TREE4, TREE5, PLAYERFLAG, ENEMYFLAG, WALL1, WALL2, WALL3, WALL4,
	PLAYEROCCUPIED, LAVA_OBJ1, LAVA_OBJ2_L, LAVA_OBJ2_R, LAVA_OBJ3,
	//적 21 ~
	ZERGLING = 21, MARINE, CIVILIAN, TEMPLAR, BISHOP, DIABLO, SKELETON, GHOST, DRAGON, TOWER1
};

//그려지는 iso타일
class isoTile
{
public:
	float drawX;
	float drawY;
	float centerX;
	float centerY;
	int nX;
	int nY;
	int fX;
	int fY;
	bool inRect;
	int gold; // 오직 0번타일에만 저장됨. 스테이지 지급골드
	moveUnMove MUM;
	objName    name;
};
