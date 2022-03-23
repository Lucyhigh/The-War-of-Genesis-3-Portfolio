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
	_player->setPlayerPosX(2*TILESIZEX);
	_player->setPlayerPosY(10* TILESIZEY);

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
    _moveCount = 0;
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

	POINT playerPos = { _player->getPlayerPosX(),_player->getPlayerPosY()+TILESIZEY};

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
                        cell->setType(CELL_TYPE::MOVEABLE);
                    }
                    _check.push_back(RectMake(coordinate.x, coordinate.y, TILESIZEX, TILESIZEY));
                }
                _isMove = true;
                break;
            }


        }
    }
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE)&&_isMove)
    {
        rectMoveToPath(5);
    }
   
    //if (_isMove)
    //{
    //    _count++;
    //    _moveCount = _check.size()-1;
    //    int centerCheckX = _check[_moveCount].right - _check[_moveCount].left;
    //    int centerCheckY = _check[_moveCount].bottom - _check[_moveCount].top;
    //    POINT movePlayer = {centerCheckX,centerCheckY};

    //    _player->setPlayerPosX(movePlayer.x);
    //    _player->setPlayerPosY(movePlayer.y);
    //        
    //    if(_count%30 == 0 && _moveCount > 0)_moveCount--;
    //    else if(_moveCount == 0)
    //    {
    //        _count = 0;
    //        _isMove = false;
    //    }
    //    cout << _moveCount << endl;

    //        //if(_player->getPlayerPosX() == _check.begin()
    //           // _isMove = false;
    //    
    //}
	
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
            case(CELL_TYPE::MOVEABLE):
                brush = CreateSolidBrush(RGB(255, 255, 0)); // 색 설정
                oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
                FillRect(getMemDC(), &rect, brush); // 사각형에 브러쉬색으로 채우기
                break;
            }
            DeleteObject(brush);
        }
    }
	//curAstar();
    AstarTileInfo();

	_player->render();
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
            sprintf(cellIndex, "%d", cell->getCellX());
            TextOut(getMemDC(), WINSIZE_X - 210, 80, cellIndex, strlen(cellIndex));
            sprintf(cellIndex, "%d", cell->getCellY());
            TextOut(getMemDC(), WINSIZE_X - 130, 65, cellIndex, strlen(cellIndex));
            int zPos = cell->getCellX() - cell->getCellY();

            if (zPos < 0)      zPos = 1;
            else if (zPos >= 5)      zPos = 3;
            sprintf(cellIndex, "%d", zPos);//z축위치
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

}

void FirstScene::drawMapCellInfo()
{
	char cellIndex[1024];
	SetTextColor(getMemDC(), RGB(0, 0, 0));

	for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)
	{
		Cell* cell = (*cellsIter);
		sprintf(cellIndex, "%d,%d", cell->getCellX(), cell->getCellY());
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

void FirstScene::rectMoveToPath(int speed)
{
    //네모가 path를 따라서 이동한다.
    //속도는 speed로 조절한다.
    //x += speed;
    for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)
    {
        Cell* cell = (*cellsIter);
        if (cell->getType() == CELL_TYPE::START)
        {
            _moveRc = cell->getRect();
        }
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
		int left = (checkIter->left * TILESIZEX) - cameraLeft;
		int top  = (checkIter->top * TILESIZEY)- cameraTop;
		RECT rect = RectMake(left, top, TILESIZEX, TILESIZEY);
		FillRect(getMemDC(), &rect, rectBrush);
		DeleteObject(rectBrush);

	}
}