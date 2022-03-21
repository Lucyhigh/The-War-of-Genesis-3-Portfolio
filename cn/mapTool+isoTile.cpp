#include "stdafx.h"
#include "mapTool.h"

//이걸로 isoTile 값을 샘플에서 입력받고 왼쪽에 그리는거에요
void mapTool::createTile()
{
	if (!_menuInPt && !_objDelOn)
	{
		if (!_moveUnMove && _tempTile.fX >= 0 && _tempTile.fY >= 0 && _menuNum == ONE)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].fX = _tempTile.fX;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].fY = _tempTile.fY;
			if(_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name == NONE) _isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM = MOVE;
			InvalidateRect(_hWnd, NULL, false);
		}
		else if (_moveUnMove && _tempTile.fX >= 0 && _tempTile.fY >= 0 && _menuNum == ONE)
		{
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].fX = _tempTile.fX;
			_isoTile[_pickingPt.y * TILEX + _pickingPt.x].fY = _tempTile.fY;
			if (_isoTile[_pickingPt.y * TILEX + _pickingPt.x].name == NONE) _isoTile[_pickingPt.y * TILEX + _pickingPt.x].MUM = UNMOVE;
			InvalidateRect(_hWnd, NULL, false);
		}
	}
}

void mapTool::sampleInTemp()
{
	//이부분으로 메뉴 넘긴뒤에 타일그려지는거 방지함
	if (_brushOn && _menuNum == ONE)
	{
		//새로운 타일을 만들어보즈아!!
		for (int i = 0; i < SAMPLEX * SAMPLEY; ++i)
		{
			if (PtInRect(&_sample[i].rc, _cameraPtMouse))
			{
				_tempTile.fX = _sample[i].fX;
				_tempTile.fY = _sample[i].fY;
				return;
			}
		}
	}
}

//이게 마우스가 아이소타일안에 들어갔는지 확인해주는거 그래서 지금 마우스가 어디타일에있다 띄워줄때 쓰려고 만듬
void mapTool::ptInIso()
{
	//마우스포인트가 아이소타일안에 들어왔는지 확인해줌
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (i == _pickingPt.y * TILEX + _pickingPt.x)
		{
			_isoTile[i].inRect = true;
		}
		else _isoTile[i].inRect = false;
	}
}

//이건 우측에 isoTile 샘플을 만들어주는 기능이에요 (init)
void mapTool::createSampleTiles()
{
	for (int i = 0; i < SAMPLEY; ++i)
	{
		for (int j = 0; j < SAMPLEX; ++j)
		{
			//이게 샘플의 위치를 저장해두는거 그래야 몇번째 타일인지 알고 가져다 쓸수있음
			_sample[i * SAMPLEX + j].fX = j;
			_sample[i * SAMPLEX + j].fY = i;

			_sample[i * SAMPLEX + j].rc = RectMake((WINSIZEX - 512) + (j*TILESIZEX), 0 + (i*TILESIZEY), TILESIZEX, TILESIZEY);
		}
	}
}

//드래그할때 최초 누른 영역 저장해둠
void mapTool::tempDrag()
{
	_dragX = _cameraPtMouse.x;
	_dragY = _cameraPtMouse.y;
}

//드래그 범위로 페인트 칠해주는기능
void mapTool::dragPaint()
{
	_dragRc = RectMake(_dragX, _dragY, _cameraPtMouse.x - _dragX, _cameraPtMouse.y - _dragY);

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		POINT tempPoint = { _isoTile[i].centerX, _isoTile[i].centerY };
		if (PtInRect(&_dragRc, tempPoint))
		{
			if (!_moveUnMove && _tempTile.fX >= 0 && _tempTile.fY >= 0 && _menuNum == ONE)
			{//언무브 타일 off면 무브타일로 깔아줌
				_isoTile[i].fX = _tempTile.fX;
				_isoTile[i].fY = _tempTile.fY;
				_isoTile[i].MUM = MOVE;
				InvalidateRect(_hWnd, NULL, false);
			}
			else if (_moveUnMove && _tempTile.fX >= 0 && _tempTile.fY >= 0 && _menuNum == ONE)
			{//언무브 타일 on이면 언무브타일로 깔아줌
				_isoTile[i].fX = _tempTile.fX;
				_isoTile[i].fY = _tempTile.fY;
				_isoTile[i].MUM = UNMOVE;
				InvalidateRect(_hWnd, NULL, false);
			}
			else if (_tempTile.fX >= 0 && _tempTile.fY >= 0 && !_objDelOn && _menuNum == TWO && _objName != PLAYERFLAG && _objName != ENEMYFLAG)
			{//obj del 안켜진 상태에서 오브젝트를 드래그로 그리게 해줌
				if (_isoTile[i].name != PLAYERFLAG && _isoTile[i].name != ENEMYFLAG) _isoTile[i].name = _objName; //깃발은 생성, 삭제 예외처리 해줌
				_isoTile[i].MUM = UNMOVE;
				InvalidateRect(_hWnd, NULL, false);
			}
			else if (_tempTile.fX >= 0 && _tempTile.fY >= 0 && !_objDelOn && _menuNum == THREE && _objName != PLAYERFLAG && _objName != ENEMYFLAG)
			{//obj del 안켜진 상태에서 적 유닛을 드래그로 그리게 해줌
				if (_isoTile[i].name != PLAYERFLAG && _isoTile[i].name != ENEMYFLAG) _isoTile[i].name = _objName; //깃발은 생성, 삭제 예외처리 해줌
				_isoTile[i].MUM = MOVE;
				InvalidateRect(_hWnd, NULL, false);
			}
			else if (_tempTile.fX >= 0 && _tempTile.fY >= 0 && _objDelOn)
			{//obj del 켜졌을때는 타일은 안건들고 오브젝트 초기화 및 무브타일로 초기화
				_isoTile[i].MUM = MOVE;
				_isoTile[i].name = NONE;
				InvalidateRect(_hWnd, NULL, false);
			}
		}
	}
}