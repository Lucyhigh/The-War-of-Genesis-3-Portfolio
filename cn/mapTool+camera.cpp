#include "stdafx.h"
#include "mapTool.h"

//이거 카메라 움직여주는 부분 -> 변경 : 카메라는 플레이그라운드에 공통카메라 이용하기로했음
void mapTool::cameraControl()
{
	_cameraPtMouse.x = _ptMouse.x + CAMX;
	_cameraPtMouse.y = _ptMouse.y + CAMY;
	sampleTileMove();
}

//이건 화면이 움직임에따라 같이 움직여야하는 샘플타일의 움직임
void mapTool::sampleTileMove()
{
	for (int i = 0; i < SAMPLEY; ++i)
	{
		for (int j = 0; j < SAMPLEX; ++j)
		{
			_sample[i * SAMPLEX + j].rc = RectMake((WINSIZEX + CAMX - 512) + (j*TILESIZEX), CAMY + (i*TILESIZEY), TILESIZEX, TILESIZEY);
		}
	}
}