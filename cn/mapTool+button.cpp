#include "stdafx.h"
#include "mapTool.h"

//무브 언무브 버튼
void mapTool::moveUnMove()
{
	if (PtInRect(&_move, _cameraPtMouse))
	{
		_moveUnMove = false;
	}

	if (PtInRect(&_unMove, _cameraPtMouse))
	{
		_moveUnMove = true;
	}
}
//접기 펼치기 버튼
void mapTool::openClose()
{
	if (PtInRect(&_open, _cameraPtMouse) && !_brushOn)
	{
		_brushOn = true;
	}
	else if (PtInRect(&_close, _cameraPtMouse) && _brushOn)
	{
		_brushOn = false;
	}
}
//렌더사이즈 버튼
void mapTool::renderSize()
{
	if (PtInRect(&_small, _cameraPtMouse) && _rs == SMALL)
	{
		_rs = MEDIUM;
	}
	else if (PtInRect(&_medium, _cameraPtMouse) && _rs == MEDIUM)
	{
		_rs = MAX;
	}
	else if (PtInRect(&_max, _cameraPtMouse) && _rs == MAX)
	{
		_rs = SMALL;
	}
}
//얘는 메뉴 안에 마우스가 들어가있는동안에는 타일을 그리지말라는 신호를 쏴주는 거에요
void mapTool::menuInPt()
{
	if (PtInRect(&_menuRc, _cameraPtMouse) && _brushOn) _menuInPt = true;
	else if (PtInRect(&_saveBt, _cameraPtMouse))  _menuInPt = true;
	else if (PtInRect(&_saveBt2, _cameraPtMouse)) _menuInPt = true;
	else if (PtInRect(&_saveBt3, _cameraPtMouse)) _menuInPt = true;
	else if (PtInRect(&_loadBt, _cameraPtMouse))  _menuInPt = true;
	else if (PtInRect(&_loadBt2, _cameraPtMouse)) _menuInPt = true;
	else if (PtInRect(&_loadBt3, _cameraPtMouse)) _menuInPt = true;
	else if (PtInRect(&_move, _cameraPtMouse))    _menuInPt = true;
	else if (PtInRect(&_unMove, _cameraPtMouse))  _menuInPt = true;
	else if (PtInRect(&_undo, _cameraPtMouse))    _menuInPt = true;
	else if (PtInRect(&_fill, _cameraPtMouse))    _menuInPt = true;
	else if (PtInRect(&_open, _cameraPtMouse))    _menuInPt = true;
	else if (PtInRect(&_close, _cameraPtMouse))   _menuInPt = true;
	else if (PtInRect(&_small, _cameraPtMouse))   _menuInPt = true;
	else if (PtInRect(&_medium, _cameraPtMouse))  _menuInPt = true;
	else if (PtInRect(&_max, _cameraPtMouse))     _menuInPt = true;
	else if (PtInRect(&_leftBt, _cameraPtMouse))  _menuInPt = true;
	else if (PtInRect(&_rightBt, _cameraPtMouse)) _menuInPt = true;
	else if (PtInRect(&_objDel, _cameraPtMouse))  _menuInPt = true;
	else if (PtInRect(&_delAll, _cameraPtMouse))  _menuInPt = true;
	else if (PtInRect(&_homeBt, _cameraPtMouse))  _menuInPt = true;
	else if (PtInRect(&_goldBt, _cameraPtMouse))  _menuInPt = true;	
	else if (PtInRect(&_dragBt, _cameraPtMouse))  _menuInPt = true;
	else _menuInPt = false;
}

//얘는 left right 화살표 버튼인데 현재 어떤 메뉴가 열려있는지 + 버튼과 마우스가 만났는지 검사해서
//상황에 따라 맞는 행동을 해주는거에요
void mapTool::leftRightBt()
{
	if (PtInRect(&_rightBt, _cameraPtMouse) && _menuNum == ONE)
	{
		_menuNum = TWO;
		_objName = NONE;
	}
	else if (PtInRect(&_rightBt, _cameraPtMouse) && _menuNum == TWO)
	{
		_menuNum = THREE;
		_objName = NONE;
	}
	else if (PtInRect(&_rightBt, _cameraPtMouse) && _menuNum == THREE)
	{
		_menuNum = THREE;
		_objName = NONE;
	}
	else if (PtInRect(&_leftBt, _cameraPtMouse) && _menuNum == TWO)
	{
		_menuNum = ONE;
		_objName = NONE;
	}
	else if (PtInRect(&_leftBt, _cameraPtMouse) && _menuNum == THREE)
	{
		_menuNum = TWO;
		_objName = NONE;
	}
}

//얘는 오브젝트 지우기를 켤지 끌지
void mapTool::objDel()
{
	if (!_objDelOn) _objDelOn = true;
	else if (_objDelOn) _objDelOn = false;
}

//이거 선택한 타일로 맵 전체를 가득 채워주는 기능
void mapTool::fill(int x, int y)
{
	for (int i = 0; i < TILEX* TILEY; ++i)
	{
		if (!_moveUnMove) _isoTile[i].MUM = MOVE;
		else  _isoTile[i].MUM = UNMOVE;
		_isoTile[i].fX = x;
		_isoTile[i].fY = y;
	}
}

//얘는 모든 오브젝트를 NONE으로 돌려서 마치 삭제된것처럼 보여주는 친구에요
void mapTool::objDelAll()
{
	for (int i = 0; i < TILEX* TILEY; ++i)
	{
		_isoTile[i].name = NONE;
		_isoTile[i].MUM = MOVE;
	}
	_playerTile = -1;
	_enemyTile = -1;
}

void mapTool::homeBt()
{
	SCENEMANAGER->changeScene("타이틀씬");
}

void mapTool::dragOnOff()
{
	if (!_dragMode) _dragMode = true;
	else if (_dragMode) _dragMode = false;
}