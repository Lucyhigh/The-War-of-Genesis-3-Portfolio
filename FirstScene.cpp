#include "Stdafx.h"
#include "FirstScene.h"

HRESULT FirstScene::init(void)
{
	_mapTileInfo = new MapTileInfo;
	_mapTileInfo->init();
	_image = IMAGEMANAGER->findImage("Field");
	_cells = _mapTileInfo->getCell();

	_player = new Player;
	_player->init();
	_player->setPlayerPosX(4 * TILESIZEX);
	_player->setPlayerPosY(10 * TILESIZEY);

	_camera = new Camera;
	_camera->init();
	_camera->setLimitsX(CENTER_X, _image->getWidth());
	_camera->setLimitsY(CENTER_Y, _image->getHeight());

	_generator = new AStar::Generator;
	_generator->setWorldSize({ STAGE1TILEX, STAGE1TILEY });

	for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)
	{
		Cell* cell = (*cellsIter);
		if (cell->getType() == CELL_TYPE::WALL)
		{
			_generator->addCollision({ cell->getCellX(),cell->getCellY() });
		}
	}
    _moveRc = RectMake(-50, -50, TILESIZEX, TILESIZEY);
	_endPointIndex = 0;
    _moveIndex = 0;
	_lerpPercentage = 0.0f;
    _isMove = false;
	return S_OK;
}

void FirstScene::release(void)
{
	SAFE_DELETE(_mapTileInfo);
	_player->release();
	SAFE_DELETE(_player);
	_camera->release();
	SAFE_DELETE(_camera);
	SAFE_DELETE(_generator);
}

void FirstScene::update(void)
{
	POINT cameraPos;
	cameraPos.x = _player->getPlayerPosX();
	cameraPos.y = _player->getPlayerPosY();
	_camera->setCameraPos(cameraPos);
	_camera->update();
	_player->setCameraRect(_camera->getScreenRect());
	_player->update();

	POINT playerPos = { _player->getPlayerPosX(),_player->getPlayerPosY()};

    for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)
    {
        Cell* cell = (*cellsIter);

        if (PtInRect(&cell->getRect(), playerPos))
        {
            if (cell->getType() != CELL_TYPE::WALL)
            {
                cell->setType(CELL_TYPE::START);
            }
            _pPlayer = { cell->getCellX(),cell->getCellY() };
        }
        else if (cell->getType() == CELL_TYPE::START)
        {
            cell->setType(CELL_TYPE::NORMAL);
        }

        POINT cameraMouse = {
                              _ptMouse.x + _camera->getScreenRect().left,
                              _ptMouse.y + _camera->getScreenRect().top
        };
        if (PtInRect(&cell->getRect(), cameraMouse))
        {
            if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
            {
                cell->setEndCellX(cell->getCellX());
                cell->setEndCellY(cell->getCellY());
                cell->setType(CELL_TYPE::GOAL);
                _endPoint = { cell->getRect().left, cell->getRect().top };

                auto path = _generator->findPath({ _pPlayer.x,_pPlayer.y },
                    { cell->getCellX(),cell->getCellY() });
                _check.clear();
                for (auto &coordinate : path)
                {
                    if (cell->getType() == CELL_TYPE::NORMAL)
                    {
                        cell->setType(CELL_TYPE::MOVEPATH);
                    }
					_check.push_back({ coordinate.x, coordinate.y });
                }
				_isMove = true;
				_moveIndex = _check.size()-1;
                break;
            }


        }
    }
    if (_isMove)
    {
        rectMoveToPath();
    }
   
	
}

void FirstScene::render(void)
{
	_camera->render();

	int cameraLeft = _camera->getScreenRect().left;
	int cameraTop = _camera->getScreenRect().top;
	IMAGEMANAGER->render("Field", getMemDC(), 0, 0,
		                                      cameraLeft,
		                                      cameraTop,
		                                      WINSIZE_X, WINSIZE_Y);
    if (KEYMANAGER->isToggleKey(VK_F2))
    {
        drawMapCellInfo();

        for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)
        {
            Cell* cell = (*cellsIter);
            HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0)); // 색 설정
            HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);

            int left = cell->getRect().left - cameraLeft;
            int top = cell->getRect().top - cameraTop;
            RECT rect = RectMake(left, top, TILESIZEX, TILESIZEY);
            switch (cell->getType())
            {
            case(CELL_TYPE::NORMAL):
                break;
            case(CELL_TYPE::WALL):
                oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
                FillRect(getMemDC(), &rect, brush); // 사각형에 브러쉬색으로 채우기
                break;
            case(CELL_TYPE::START):
                brush = CreateSolidBrush(RGB(0, 0, 255)); // 색 설정
                oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
                FillRect(getMemDC(), &rect, brush); // 사각형에 브러쉬색으로 채우기
                SelectObject(getMemDC(), oldBrush);
                break;
            case(CELL_TYPE::GOAL):
                brush = CreateSolidBrush(RGB(0, 255, 0)); // 색 설정
                oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
                FillRect(getMemDC(), &rect, brush); // 사각형에 브러쉬색으로 채우기
                break;
            case(CELL_TYPE::MOVEPATH):
                brush = CreateSolidBrush(RGB(255, 255, 0)); // 색 설정
                oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
                FillRect(getMemDC(), &rect, brush); // 사각형에 브러쉬색으로 채우기
                break;
            }
            DeleteObject(brush);
        }
    }
	curAstar();
    AstarTileInfo();

    IMAGEMANAGER->render("mapInfoAll", getMemDC(), WINSIZE_X - 230, 0);
    char cellIndex[512];
    for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)
    {
        POINT cameraMouse = {
                              _ptMouse.x + _camera->getScreenRect().left,
                              _ptMouse.y + _camera->getScreenRect().top
                            };

        Cell* cell = (*cellsIter);
        if (PtInRect(&cell->getRect(), cameraMouse))
        {
            sprintf_s(cellIndex, "%d", cell->getCellX());
            TextOut(getMemDC(), WINSIZE_X - 210, 80, cellIndex, strlen(cellIndex));
            sprintf_s(cellIndex, "%d", cell->getCellY());
            TextOut(getMemDC(), WINSIZE_X - 130, 65, cellIndex, strlen(cellIndex));
            int zPos = cell->getCellX() - cell->getCellY();

            if (zPos < 0)      zPos = 1;
            else if (zPos >= 5)      zPos = 3;
            sprintf_s(cellIndex, "%d", zPos);//z축위치
            TextOut(getMemDC(), WINSIZE_X - 150, 45, cellIndex, strlen(cellIndex));
            break;
        }
    }

    if (_isMove)
    {
        Rectangle(getMemDC(), _moveRc.left - _camera->getScreenRect().left,
                              _moveRc.top - _camera->getScreenRect().top,
                              _moveRc.right - _camera->getScreenRect().left,
                              _moveRc.bottom - _camera->getScreenRect().top);
    }
	_player->render();
}

void FirstScene::drawMapCellInfo()
{
	char cellIndex[1024];
	SetTextColor(getMemDC(), RGB(0, 0, 0));

	for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)
	{
		Cell* cell = (*cellsIter);
		sprintf_s(cellIndex, "%d,%d", cell->getCellX(), cell->getCellY());
		TextOut(getMemDC(), cell->getRect().left - _camera->getScreenRect().left,
			cell->getRect().top - _camera->getScreenRect().top,
			cellIndex, strlen(cellIndex));
	}
}

void FirstScene::AstarTileInfo()
{
	POINT cameraEndPoint = {
							 _endPoint.x - _camera->getScreenRect().left,
							 _endPoint.y - _camera->getScreenRect().top
	};
	IMAGEMANAGER->render("curTile2", getMemDC(), cameraEndPoint.x, cameraEndPoint.y);
}

void FirstScene::rectMoveToPath()
{
	if (_moveIndex - 1 < 0)
	{
		_isMove = false;
		_moveIndex = 0;
		_lerpPercentage = 0.0f;
		return;
	}

	float time = 0.5f;
	float speed = TIMEMANAGER->getElapsedTime() / time;
	_lerpPercentage += speed;

	POINT start = { _check[_moveIndex].x * TILESIZEX, _check[_moveIndex].y * TILESIZEY };
	POINT end = { _check[_moveIndex-1].x * TILESIZEX, _check[_moveIndex-1].y * TILESIZEY };

	_moveRc = RectMake(lerp(start, end, _lerpPercentage).x,
					   lerp(start, end, _lerpPercentage).y,
					  TILESIZEX, TILESIZEY);

	_player->setPlayerPos({ _moveRc.right,_moveRc.top });
	if (_lerpPercentage >= 1)
	{
		_moveIndex--;
		_lerpPercentage = 0;
	}
}

void FirstScene::curAstar()
{
	int cameraLeft = _camera->getScreenRect().left;
	int cameraTop = _camera->getScreenRect().top;
	for (auto checkIter = _check.begin(); checkIter != _check.end(); ++checkIter)
	{
		HBRUSH rectBrush = CreateSolidBrush(RGB(0, 120, 120)); // 색 설정
		HBRUSH oldRectBrush = (HBRUSH)SelectObject(getMemDC(), rectBrush);
		int left = (checkIter->x * TILESIZEX) - cameraLeft;
		int top  = (checkIter->y * TILESIZEY)- cameraTop;
		RECT rect = RectMake(left, top, TILESIZEX, TILESIZEY);
		FillRect(getMemDC(), &rect, rectBrush);
		DeleteObject(rectBrush);
	}
}

POINT FirstScene::lerp(POINT start,POINT end,float percentage)
{
	if (0 > percentage) percentage = 0;
	else if (percentage > 1)percentage = 1;
	LONG x = start.x + (end.x - start.x) * percentage;
	LONG y = start.y+ (end.y - start.y) * percentage;

	return {x,y};
}
