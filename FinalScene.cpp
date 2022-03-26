#include "Stdafx.h"
#include "FinalScene.h"


HRESULT FinalScene::init(void)
{
	_mapTileInfo = new MapTileInfo;
	_mapTileInfo->init();

	_gameUI = new GameUI;
	_gameUI->init();
	_image = IMAGEMANAGER->findImage("Final");
	_cells = _mapTileInfo->getCell();

	_player = new Player;
	_player->init();
	_player->setPlayerPosX(6 * TILESIZEX);
	_player->setPlayerPosY(8 * TILESIZEY);

	_saladin = new Saladin;
	_saladin->init();
	_saladin->setSaladinPosX(32 * TILESIZEX);
	_saladin->setSaladinPosY(25 * TILESIZEY);

	_camera = new Camera;
	_camera->init();
	_camera->setLimitsX(CENTER_X, _image->getWidth());
	_camera->setLimitsY(CENTER_Y, _image->getHeight());

	_generator = new AStar::Generator;
	_generator->setWorldSize({ STAGE3TILEX, STAGE3TILEY });

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

	_turnSystem = new TurnSystem();
	_turnSystem->init();
	_enemyBit = 0;

	return S_OK;
}

void FinalScene::release(void)
{
	SAFE_DELETE(_mapTileInfo);
	SAFE_DELETE(_turnSystem);
	SAFE_DELETE(_gameUI);
	_player->release();
	SAFE_DELETE(_player);
	_saladin->release();
	SAFE_DELETE(_saladin);
	_camera->release();
	SAFE_DELETE(_camera);
	SAFE_DELETE(_generator);
}

void FinalScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('H'))
	{
		_turnSystem->changeToEnemy();

	}
	if (KEYMANAGER->isOnceKeyDown('N'))
	{
		_turnSystem->changeToPlayer();

	}

	if (_turnSystem->getStatus() == CHANGINGSTATUS::PLAYERTURN)
	{
		// : 대기- 대기이미지 타일클릭시 이동가능상태 /메뉴창 열수있고 공격타일 만들수잇음
		if (_turnSystem->isPlayerIdle() == 1)
		{
			POINT playerPos = { _player->getPlayerPosX(),_player->getPlayerPosY() };
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
						if (cell->getType() == CELL_TYPE::NORMAL)
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
								_check.push_back({ coordinate.x, coordinate.y });
							}
							_moveIndex = _check.size() - 1;
							_turnSystem->setPlayerBit(3);
						}
						break;
					}
				}
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				int posUI = 60;
				POINT playerUI = {
									_player->getPlayerPosX() + posUI - _camera->getScreenRect().left,
									_player->getPlayerPosY() + posUI - _camera->getScreenRect().top
				};
				_gameUI->showBattleMenu(playerUI);
				_turnSystem->setPlayerBit(0);
			}
		}
		// 0000 0001 : 메뉴창염 - 타일클릭해도 이동안됨 버튼클릭상태
		else if (_turnSystem->getPlayerBit(0) == 1)
		{
			cout << "메뉴" << endl;
			_gameUI->update();
			if (!_gameUI->getMenu())
			{

				if (_gameUI->getPlayerTurn())
				{
					_turnSystem->changeToPlayer();
				}
				else
				{
					_turnSystem->changeToEnemy();
				}
			}
		}
		// 0000 1000 : 이동중 - 메뉴창 뜨면 안됨 다른곳으로 이동못함
		else if (_turnSystem->getPlayerBit(3) == 1)
		{
			{
				rectMoveToPath();
			}
		}


	}
	else if (_turnSystem->getStatus() == CHANGINGSTATUS::ENEMYTURN)
	{

	}

	

	POINT cameraPos;
	if (_turnSystem->getStatus() == CHANGINGSTATUS::PLAYERTURN)
	{
		cameraPos.x = _player->getPlayerPosX();
		cameraPos.y = _player->getPlayerPosY();
	}
	else if (_turnSystem->getStatus() == CHANGINGSTATUS::ENEMYTURN)
	{
		cameraPos.x = _saladin->getSaladinPosX();
		cameraPos.y = _saladin->getSaladinPosY();
	}
	else
	{
		cameraPos.x = _player->getPlayerPosX();
		cameraPos.y = _player->getPlayerPosY();
	}
	_camera->setCameraPos(cameraPos);
	_camera->update();

	_turnSystem->update();

	_player->setCameraRect(_camera->getScreenRect());
	_player->update();
	_saladin->setCameraRect(_camera->getScreenRect());
	_saladin->update();
}

void FinalScene::render(void)
{
	_camera->render();

	int cameraLeft = _camera->getScreenRect().left;
	int cameraTop = _camera->getScreenRect().top;
	IMAGEMANAGER->render("Final", getMemDC(), 0, 0,
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
	curAstar();
	AstarTileInfo();

    _player->render();
	_saladin->render();
    _gameUI->render();
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
	if (_turnSystem->getStatus() == CHANGINGSTATUS::PLAYERTURN && _isMove)
	{
		Rectangle(getMemDC(), _moveRc.left - _camera->getScreenRect().left,
			_moveRc.top - _camera->getScreenRect().top,
			_moveRc.right - _camera->getScreenRect().left,
			_moveRc.bottom - _camera->getScreenRect().top);
	}

	

}

void FinalScene::drawMapCellInfo()
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

void FinalScene::AstarTileInfo()
{
	POINT cameraEndPoint = {
							 _endPoint.x - _camera->getScreenRect().left,
							 _endPoint.y - _camera->getScreenRect().top
	};
	IMAGEMANAGER->render("curTile2", getMemDC(), cameraEndPoint.x, cameraEndPoint.y);
}

void FinalScene::rectMoveToPath()
{

	if (_moveIndex - 1 < 0)
	{
		_turnSystem->changeToPlayer();
        _player->setWaiting(true);
		_moveIndex = 0;
		_lerpPercentage = 0.0f;
		return;
	}
    else
    {
		
        float time = 0.5f;
        float speed = TIMEMANAGER->getElapsedTime() / time;
        _lerpPercentage += speed;

        POINT start = { _check[_moveIndex].x * TILESIZEX, _check[_moveIndex].y * TILESIZEY };
        POINT end = { _check[_moveIndex - 1].x * TILESIZEX, _check[_moveIndex - 1].y * TILESIZEY };

        changeImage();
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
}

void FinalScene::curAstar()
{
	int cameraLeft = _camera->getScreenRect().left;
	int cameraTop = _camera->getScreenRect().top;
	for (auto checkIter = _check.begin(); checkIter != _check.end(); ++checkIter)
	{
		HBRUSH rectBrush = CreateSolidBrush(RGB(0, 120, 120)); // 색 설정
		HBRUSH oldRectBrush = (HBRUSH)SelectObject(getMemDC(), rectBrush);
		int left = (checkIter->x * TILESIZEX) - cameraLeft;
		int top = (checkIter->y * TILESIZEY) - cameraTop;
		RECT rect = RectMake(left, top, TILESIZEX, TILESIZEY);
		FillRect(getMemDC(), &rect, rectBrush);
		DeleteObject(rectBrush);

	}
}

void FinalScene::changeImage()
{
    _player->setWaiting(false);
    
    int compareBtoAX = _check[_moveIndex - 1].x - _check[_moveIndex].x;
    int compareBtoAY = _check[_moveIndex - 1].y - _check[_moveIndex].y;

    if (compareBtoAX > 0 && compareBtoAY == 0)      _player->setImageStage(PLAYERSTATE::RIGHT);
    else if (compareBtoAX < 0 && compareBtoAY == 0) _player->setImageStage(PLAYERSTATE::LEFT);
    else if (compareBtoAY > 0 && compareBtoAX == 0) _player->setImageStage(PLAYERSTATE::BOTTOM);
    else if (compareBtoAY < 0 && compareBtoAX == 0) _player->setImageStage(PLAYERSTATE::TOP);
}

POINT FinalScene::lerp(POINT start, POINT end, float percentage)
{
	if (0 > percentage) percentage = 0;
	else if (percentage > 1)percentage = 1;
	LONG x = start.x + (end.x - start.x) * percentage;
	LONG y = start.y + (end.y - start.y) * percentage;

	return { x,y };
}
