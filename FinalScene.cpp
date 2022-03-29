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
	_player->setPlayerPosX(16 * TILESIZEX);
	_player->setPlayerPosY(20 * TILESIZEY);

	_saladin = new Saladin;
	_saladin->init();
	_saladin->setSaladinPosX(25 * TILESIZEX);
	_saladin->setSaladinPosY(8 * TILESIZEY);

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
	SAFE_DELETE(_generator);

	_player->release();
	SAFE_DELETE(_player);

	_saladin->release();
	SAFE_DELETE(_saladin);

	_camera->release();
	SAFE_DELETE(_camera);
}

void FinalScene::update(void)
{
	
    //검사용 버튼
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
			POINT playerPos = { _player->getPlayerPosX()-TILESIZEX,_player->getPlayerPosY() };
			for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)
			{
				Cell* cell = (*cellsIter);

				if (PtInRect(&cell->getRect(), playerPos))
				{
					if (cell->getType() != CELL_TYPE::WALL)
					{
						cell->setType(CELL_TYPE::START);
					}
					_pMoveStart = { cell->getCellX(), cell->getCellY() };
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
							cell->setType(CELL_TYPE::GOAL);
							_endPoint = { cell->getRect().left, cell->getRect().top };

							auto path = _generator->findPath({ _pMoveStart.x,_pMoveStart.y },
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
			rectMoveToPath();
		}
	}
	else if (_turnSystem->getStatus() == CHANGINGSTATUS::ENEMYTURN)
	{
        //캐릭터 위치 파악 후 이동 / 이동 후 공격 / 스킬 사용 고름
		if (_turnSystem->isEnemyIdle() == 1)
		{
			// : 대기- 대기이미지 - 캐릭터 시작타일 파악후 캐릭터 좌우상하 4개 타일 중 가까운 타일 선택해 그곳을 목표로 3칸씩 이동?
			findPlayerTile();
		}
		else if (_turnSystem->getEnemyBit(3) == 1)
		{
			rectMoveToPath();
		}
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
	int cameraTop =  _camera->getScreenRect().top;
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
			HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0)); 
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
				FillRect(getMemDC(), &rect, brush); 
				break;
			case(CELL_TYPE::START):
				brush = CreateSolidBrush(RGB(0, 0, 255));
				oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
				FillRect(getMemDC(), &rect, brush); 
				SelectObject(getMemDC(), oldBrush);
				break;
			case(CELL_TYPE::GOAL):
				brush = CreateSolidBrush(RGB(0, 255, 0)); 
				oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
				FillRect(getMemDC(), &rect, brush);
				break;
			case(CELL_TYPE::MOVEABLE):
				brush = CreateSolidBrush(RGB(205, 255, 100)); 
				oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
				FillRect(getMemDC(), &rect, brush);
				IMAGEMANAGER->alphaRender("moveTile", getMemDC(), _tileAlpha);
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
		SetTextColor(getMemDC(), RGB(255, 255, 255));
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
    
    FONTMANAGER->drawText(getMemDC(),
        WINSIZE_X - 115, 17, "가을체", 19, 13, _uiText[0],
        wcslen(_uiText[0]), TA_CENTER, RGB(255, 255, 255));
    FONTMANAGER->drawText(getMemDC(),
        WINSIZE_X - 55, 40, "가을체", 23, 13, _uiText[1],
        wcslen(_uiText[1]), TA_CENTER, RGB(255, 255, 255));
    FONTMANAGER->drawText(getMemDC(),
        WINSIZE_X - 50, 80, "가을체", 18, 13, _uiText[2],
        wcslen(_uiText[2]), TA_CENTER, RGB(255,255,255));

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
		if (_turnSystem->getStatus() == CHANGINGSTATUS::PLAYERTURN)
		{
			_turnSystem->changeToPlayer();
			 _player->setWaiting(true);
		}
		else if (_turnSystem->getStatus() == CHANGINGSTATUS::ENEMYTURN) 
		{
            //일단 이동후 턴 종료 - 3칸씩 이동하며 3칸안에 플레이어 있을 경우에 +공격
			//if(_saladin->getPos가 GOAL에 있을때 )
            //_saladin->attackPlayer();
            //_player->damage(); //쉐이킹 모션과 피 감소 숫자 
            //else 
			_turnSystem->changeToPlayer();
			_saladin->setWaiting(true);
			
		}
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

        if (_turnSystem->getStatus() == CHANGINGSTATUS::PLAYERTURN)
        {
            _player->setPlayerPos({ _moveRc.right,_moveRc.top });
        }
        else if (_turnSystem->getStatus() == CHANGINGSTATUS::ENEMYTURN)
        {
            _saladin->setSaladinPos({ _moveRc.right,_moveRc.top });
        }

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
	if (_turnSystem->getStatus() == CHANGINGSTATUS::PLAYERTURN)
	{
		_player->setWaiting(false);

		int compareBtoAX = _check[_moveIndex - 1].x - _check[_moveIndex].x;
		int compareBtoAY = _check[_moveIndex - 1].y - _check[_moveIndex].y;

		if (compareBtoAX > 0 && compareBtoAY == 0)      _player->setImageStage(PLAYERSTATE::RIGHT);
		else if (compareBtoAX < 0 && compareBtoAY == 0) _player->setImageStage(PLAYERSTATE::LEFT);
		else if (compareBtoAY > 0 && compareBtoAX == 0) _player->setImageStage(PLAYERSTATE::BOTTOM);
		else if (compareBtoAY < 0 && compareBtoAX == 0) _player->setImageStage(PLAYERSTATE::TOP);
	}
	else if (_turnSystem->getStatus() == CHANGINGSTATUS::ENEMYTURN)
	{
		_saladin->setWaiting(false);

		int compareBtoAX = _check[_moveIndex - 1].x - _check[_moveIndex].x;
		int compareBtoAY = _check[_moveIndex - 1].y - _check[_moveIndex].y;

		if (compareBtoAX > 0 && compareBtoAY == 0)      _saladin->setImageStage(SALADINSTATE::RIGHT);
		else if (compareBtoAX < 0 && compareBtoAY == 0) _saladin->setImageStage(SALADINSTATE::LEFT);
		else if (compareBtoAY > 0 && compareBtoAX == 0) _saladin->setImageStage(SALADINSTATE::BOTTOM);
		else if (compareBtoAY < 0 && compareBtoAX == 0) _saladin->setImageStage(SALADINSTATE::TOP);
	}
}

void FinalScene::findPlayerTile()
{
    float min = 100;
    float num;
    int index = 0;
	POINT enemyPoint = { _saladin->getSaladinPosX()-TILESIZEX, _saladin->getSaladinPosY() };
	POINT _tempGoal = { 0,0 };
	POINT _enemyPathGoal = { 0,0 };
    for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)
    {
        Cell* cell = (*cellsIter);
        if (PtInRect(&cell->getRect(), enemyPoint))
        {
            _pMoveStart = { cell->getCellX(), cell->getCellY() };
        }

        if (cell->getType() == CELL_TYPE::START)
        {
            _endPoint = { cell->getRect().left, cell->getRect().top };
            _tempGoal = { cell->getCellX(), cell->getCellY() };
        }

        for (int i = -2; i <= 2; i += 2)
        {
            for (int j = -2; j <= 2; j += 2, index++)
            {
                if (i + j == -2 || i + j == 2)
                {
                    float num = getDistance(_pMoveStart.x, _pMoveStart.y, _tempGoal.x + i, _tempGoal.y + j);
                    if (index == 0) min = num;
                    //state == wall 일때는 제외 어케하지

                    if (num < min)
                    {
                        _enemyPathGoal.x = _tempGoal.x + i;
                        _enemyPathGoal.y = _tempGoal.y + j;
                        min = num;
                        cout << "거리 차: " << min << ", 인덱스 :" << index << endl;
                        cout << "x : " << i << " y : " << j << "  , 고른 타입 :" << _enemyPathGoal.x << " , " << _enemyPathGoal.y << endl;
                    }
                    else continue;

                }

            }
        }
    }
	cout <<"최종 :"<< _enemyPathGoal.x << ", " << _enemyPathGoal.y << endl;
    


	auto path = _generator->findPath(
		{ _pMoveStart.x,_pMoveStart.y },
		{ _enemyPathGoal.x,_enemyPathGoal.y } );

	_check.clear();
	int pathNum =10;
	int pathSize = path.size() < pathNum ? path.size() : pathNum;
	for (int i = path.size() - pathSize; i < path.size(); ++i)
	{
		auto coordinate = path[i];
		_check.push_back({ coordinate.x, coordinate.y });
	}
	_moveIndex = _check.size() - 1;
	_turnSystem->setEnemyBit(3);
}

POINT FinalScene::lerp(POINT start, POINT end, float percentage)
{
	if (0 > percentage) percentage = 0;
	else if (percentage > 1)percentage = 1;
	LONG x = start.x + (end.x - start.x) * percentage;
	LONG y = start.y + (end.y - start.y) * percentage;

	return { x,y };
}
