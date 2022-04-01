#include "Stdafx.h"
#include "FinalScene.h"

HRESULT FinalScene::init(void)
{
    ShowCursor(false);

	_mapTileInfo = new MapTileInfo;
	_mapTileInfo->init();
	_gameUI = new GameUI;
	_gameUI->init();

	_animation = ANIMATIONMANAGER->findAnimation("normalCursor");
	_tileClick = ANIMATIONMANAGER->findAnimation("clickTile");
	_tileClick->AniStart();
	_turnMark = ANIMATIONMANAGER->findAnimation("playerMark");
	_turnMark->AniStart();
	_image = IMAGEMANAGER->findImage("Final");
	_cells = _mapTileInfo->getCell();

	_player = new Player;
	_player->init();
	_player->setPlayerPosX(16 * TILESIZEX);
	_player->setPlayerPosY(10 * TILESIZEY);

	_saladin = new Saladin;
	_saladin->init();
	_saladin->setSaladinPosX(25 * TILESIZEX);
	_saladin->setSaladinPosY(9 * TILESIZEY);
    _saladin->setEnemyIdle();

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
	_enemyPathGoal = { 0,0 };

	_turnSystem = new TurnSystem();
	_turnSystem->init();
	_enemyBit = 0;

    _mouseType = CELL_TYPE::NORMAL;
    _beforeMouseType = CELL_TYPE::GOAL;

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

    if (_mouseType != _beforeMouseType) 
    {
        _animation->AniStop();
        _beforeMouseType = _mouseType;
        switch (_mouseType)
        {
        case CELL_TYPE::NORMAL:
            _animation = ANIMATIONMANAGER->findAnimation("normalCursor");
            break;
        case CELL_TYPE::WALL:
            _animation = ANIMATIONMANAGER->findAnimation("notMoveable");
            break;
        case CELL_TYPE::ATTACKABLE:
            _animation = ANIMATIONMANAGER->findAnimation("attackMark");
            break;
        }
        _animation->AniStart();
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
							_turnSystem->setPlayerBit(1);
							break;
						}
						else if (cell->getType() == CELL_TYPE::ATTACKABLE)
						{
							_check.clear();
							find4WaysTile();
							break;
						}
					}
                   
				}
			}

            POINT enemyPos = { _saladin->getSaladinPosX() - TILESIZEX, _saladin->getSaladinPosY() };//
            for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)
            {
                Cell* cell = (*cellsIter);

                if (PtInRect(&cell->getRect(), enemyPos))
                {
                    if (cell->getType() != CELL_TYPE::WALL)
                    {
                        cell->setType(CELL_TYPE::ATTACKABLE);
                    }
                }
                else if (cell->getType() == CELL_TYPE::ATTACKABLE)
                {
                    cell->setType(CELL_TYPE::NORMAL);
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
		// 0000 0010 : 이동중 - 메뉴창 뜨면 안됨 다른곳으로 이동못함
		else if (_turnSystem->getPlayerBit(1) == 1)
		{
			_player->setPlayerStateBit(0);
			rectMoveToPath();
		}
		// 0000 0100 : 공격
		else if (_turnSystem->getPlayerBit(2) == 1)
		{
			//_player->setPlayerStateBit(1);
			Attack();
		}
		// 0000 1000 : 피격
		else if (_turnSystem->getPlayerBit(3) == 1)
		{
			changeImage();
			cout << " 형 : 으악" << endl;
			//_player->getPlayerStateBit(2);

		}
	}
	else if (_turnSystem->getStatus() == CHANGINGSTATUS::ENEMYTURN)
	{
        //캐릭터 위치 파악 후 이동0 / 이동 후 공격1 / 스킬 사용 고름2
		if (_turnSystem->isEnemyIdle() == 1)
		{
			// : 대기- 대기이미지 - 캐릭터 시작타일 파악후 캐릭터 좌우상하 4개 타일 중 가까운 타일 선택해 그곳을 목표로 3칸씩 이동?
			find4WaysTile();
		}
		// 0000 0010 : 이동중 - 메뉴창 뜨면 안됨 다른곳으로 이동못함
		else if (_turnSystem->getEnemyBit(1) == 1)
		{
			rectMoveToPath();
		}
		// 0000 0100 : 공격
		else if (_turnSystem->getEnemyBit(2) == 1)
		{
            Attack();
		}
		// 0000 1000 : 피격
		else if (_turnSystem->getEnemyBit(3) == 1)
		{
			changeImage();
			cout << " 동생 : 으악" << endl;

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

    if (_player->getPlayerStateBit().none() == 0)
    {
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
	}
	AstarTileInfo();

	_saladin->render();
    _player->render();
    _gameUI->render();
	IMAGEMANAGER->render("mapInfoAll", getMemDC(), WINSIZE_X - 230, 0);

    FONTMANAGER->drawText(getMemDC(),
        WINSIZE_X - 115, 17, "가을체", 19, 13, _uiText[0],
        wcslen(_uiText[0]), TA_CENTER, RGB(255, 255, 255));
    FONTMANAGER->drawText(getMemDC(),
        WINSIZE_X - 55, 40, "가을체", 23, 13, _uiText[1],
        wcslen(_uiText[1]), TA_CENTER, RGB(255, 255, 255));
    FONTMANAGER->drawText(getMemDC(),
        WINSIZE_X - 50, 80, "가을체", 18, 13, _uiText[2],
        wcslen(_uiText[2]), TA_CENTER, RGB(255, 255, 255));
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

			switch(cell->getType())
			{
			case CELL_TYPE::ATTACKABLE:
				_mouseType = cell->getType();
				IMAGEMANAGER->findImage("attackMark")->aniRender(getMemDC(), _ptMouse.x, _ptMouse.y, _animation);
				break;
			case CELL_TYPE::WALL:
				_mouseType = cell->getType();
				IMAGEMANAGER->findImage("notMoveable")->aniRender(getMemDC(), _ptMouse.x - 16, _ptMouse.y - 6, _animation);
				break;
			default:
				_mouseType = cell->getType();
				IMAGEMANAGER->findImage("normalCursor")->aniRender(getMemDC(), _ptMouse.x, _ptMouse.y, _animation);
				break;
			}
        }
	}

	POINT MarkPos = { -23,-58 };
	switch (_turnSystem->getStatus())
	{
	case CHANGINGSTATUS::PLAYERTURN:
		IMAGEMANAGER->findImage("playerMark")->aniRender(getMemDC(),
			_player->getPlayerPosX() + MarkPos.x - _camera->getScreenRect().left,
			_player->getPlayerPosY() + MarkPos.y - _camera->getScreenRect().top, _turnMark);
		break;
	case CHANGINGSTATUS::ENEMYTURN:
		IMAGEMANAGER->findImage("enemyMark")->aniRender(getMemDC(),
			_saladin->getSaladinPosX() + MarkPos.x - _camera->getScreenRect().left,
			_saladin->getSaladinPosY() + MarkPos.y - _camera->getScreenRect().top, _turnMark);
		break;
	}
}

void FinalScene::drawMapCellInfo()
{
	char cellIndex[1024];
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	int cameraLeft = _camera->getScreenRect().left;
	int cameraTop = _camera->getScreenRect().top;
	for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)
	{
		Cell* cell = (*cellsIter);
		
		curAstar();// 이동경로 표시

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
		case(CELL_TYPE::ATTACKABLE):
			brush = CreateSolidBrush(RGB(255, 255, 0));
			oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
			FillRect(getMemDC(), &rect, brush);
			break;
		}
		SelectObject(getMemDC(), brush);
		DeleteObject(brush);

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
	IMAGEMANAGER->findImage("clickTile")->aniRender(getMemDC(), cameraEndPoint.x, cameraEndPoint.y, _tileClick);
}

void FinalScene::rectMoveToPath()
{
	if (_turnSystem->getStatus() == CHANGINGSTATUS::PLAYERTURN)
	{
		if (_moveIndex - 1 < 0)
		{
			if (_pMoveStart.x == _enemyPathGoal.x && _pMoveStart.y == _enemyPathGoal.y)
			{
				_turnSystem->setEnemyBit(2);
			}
			else
			{
				_turnSystem->changeToPlayer();
				_player->setPlayerIdle();
			}
			_moveIndex = 0;
			_lerpPercentage = 0.0f;
			return;
		}
		else
		{
			changeImage();
			float time = 4.0f;
			float speed = TIMEMANAGER->getElapsedTime() * time;
			_lerpPercentage += speed;

			POINT start = { _check[_moveIndex].x * TILESIZEX, _check[_moveIndex].y * TILESIZEY };
			POINT end = { _check[_moveIndex - 1].x * TILESIZEX, _check[_moveIndex - 1].y * TILESIZEY };
			_moveRc = RectMake(lerp(start, end, _lerpPercentage).x,
				lerp(start, end, _lerpPercentage).y,
				TILESIZEX, TILESIZEY);

			if (_turnSystem->getStatus() == CHANGINGSTATUS::PLAYERTURN)
			{
				_player->setPlayerStateBit(0);
				_player->setPlayerPos({ _moveRc.right,_moveRc.top });
			}
			if (_lerpPercentage >= 1)
			{
				_moveIndex--;
				_lerpPercentage = 0;
			}
		}
	}
	if (_turnSystem->getStatus() == CHANGINGSTATUS::ENEMYTURN)
	{
		if (_moveIndex - 1 < 0)
		{
			if (_pMoveStart.x == _enemyPathGoal.x && _pMoveStart.y == _enemyPathGoal.y)
			{
				_turnSystem->setEnemyBit(2);
			}
			else
			{
				_turnSystem->changeToPlayer();
				_saladin->setEnemyIdle();
			}

			_moveIndex = 0;
			_lerpPercentage = 0.0f;
			return;
		}
		else
		{
			changeImage();
			float time = 4.0f;
			float speed = TIMEMANAGER->getElapsedTime() * time;
			_lerpPercentage += speed;

			POINT start = { _check[_moveIndex].x * TILESIZEX, _check[_moveIndex].y * TILESIZEY };
			POINT end = { _check[_moveIndex - 1].x * TILESIZEX, _check[_moveIndex - 1].y * TILESIZEY };
			_moveRc = RectMake(lerp(start, end, _lerpPercentage).x,
				lerp(start, end, _lerpPercentage).y,
				TILESIZEX, TILESIZEY);
			if (_turnSystem->getStatus() == CHANGINGSTATUS::ENEMYTURN)
			{
				_saladin->setEnemyStateBit(0);
				_saladin->setSaladinPos({ _moveRc.right,_moveRc.top });
			}

			if (_lerpPercentage >= 1)
			{
				_moveIndex--;
				_lerpPercentage = 0;
			}
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
		SelectObject(getMemDC(), rectBrush);
		DeleteObject(rectBrush);
	}
}

void FinalScene::changeImage()
{
	if (_turnSystem->getStatus() == CHANGINGSTATUS::PLAYERTURN)
	{
		if( _player->getPlayerStateBit(0) == 1)
		{
			int compareBtoAX = _check[_moveIndex - 1].x - _check[_moveIndex].x;
			int compareBtoAY = _check[_moveIndex - 1].y - _check[_moveIndex].y;
			if (compareBtoAX > 0 && compareBtoAY == 0)      _player->setImageStage(PLAYERSTATE::RIGHT);
			else if (compareBtoAX < 0 && compareBtoAY == 0) _player->setImageStage(PLAYERSTATE::LEFT);
			else if (compareBtoAY > 0 && compareBtoAX == 0) _player->setImageStage(PLAYERSTATE::BOTTOM);
			else if (compareBtoAY < 0 && compareBtoAX == 0) _player->setImageStage(PLAYERSTATE::TOP);
		}
		else if (_player->getPlayerStateBit(2) == 1)
		{
			int compareBtoAX = _saladin->getSaladinPosX() - _player->getPlayerPosX();
			int compareBtoAY = _saladin->getSaladinPosY() - _player->getPlayerPosY();

			if (compareBtoAX > 0 && compareBtoAY == 0)      _player->setImageStage(PLAYERSTATE::RIGHT);
			else if (compareBtoAX < 0 && compareBtoAY == 0) _player->setImageStage(PLAYERSTATE::LEFT);
			else if (compareBtoAY > 0 && compareBtoAX == 0) _player->setImageStage(PLAYERSTATE::BOTTOM);
			else if (compareBtoAY < 0 && compareBtoAX == 0) _player->setImageStage(PLAYERSTATE::TOP);
		}
	}
	else if (_turnSystem->getStatus() == CHANGINGSTATUS::ENEMYTURN)
	{
        if (_saladin->getEnemyStateBit(0) == 1)
        {
            int compareBtoAX = _check[_moveIndex - 1].x - _check[_moveIndex].x;
            int compareBtoAY = _check[_moveIndex - 1].y - _check[_moveIndex].y;

            if (compareBtoAX > 0 && compareBtoAY == 0)      _saladin->setImageStage(SALADINSTATE::RIGHT);
            else if (compareBtoAX < 0 && compareBtoAY == 0) _saladin->setImageStage(SALADINSTATE::LEFT);
            else if (compareBtoAY > 0 && compareBtoAX == 0) _saladin->setImageStage(SALADINSTATE::BOTTOM);
            else if (compareBtoAY < 0 && compareBtoAX == 0) _saladin->setImageStage(SALADINSTATE::TOP);
        }
        else if (_saladin->getEnemyStateBit(1) == 1)
        {
            int compareBtoAX = _player->getPlayerPosX() - _saladin->getSaladinPosX();
            int compareBtoAY = _player->getPlayerPosY() - _saladin->getSaladinPosY();

            if (compareBtoAX > 0 && compareBtoAY == 0)      _saladin->setImageStage(SALADINSTATE::RIGHT);
            else if (compareBtoAX < 0 && compareBtoAY == 0) _saladin->setImageStage(SALADINSTATE::LEFT);
            else if (compareBtoAY > 0 && compareBtoAX == 0) _saladin->setImageStage(SALADINSTATE::BOTTOM);
            else if (compareBtoAY < 0 && compareBtoAX == 0) _saladin->setImageStage(SALADINSTATE::TOP);
        }
	}
}

void FinalScene::find4WaysTile()
{
	if (_turnSystem->getStatus() == CHANGINGSTATUS::PLAYERTURN)
	{
		POINT playerPoint = { _player->getPlayerPosX() - TILESIZEX, _player->getPlayerPosY() };
		POINT _tempGoal = { 0,0 };
		_playerPathGoal = { 0,0 };
		for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)
		{
			Cell* cell = (*cellsIter);
			//if (PtInRect(&cell->getRect(), playerPoint))
			//{
			//	_pMoveStart = { cell->getCellX(), cell->getCellY() };
			//}

			if (cell->getType() == CELL_TYPE::ATTACKABLE)
			{
				_endPoint = { cell->getRect().left, cell->getRect().top };
				_tempGoal = { cell->getCellX(), cell->getCellY() };
			}
		}

		// Stop find path if the enemy is already near the player.
		auto currentPath = _generator->findPath(
			{ _pMoveStart.x,_pMoveStart.y },
			{ _tempGoal.x, _tempGoal.y });
		if (currentPath.size() == 3)
		{
			_turnSystem->setPlayerBit(2);
			return;
		}

		vector<POINT> vStateCheck;
		for (int i = -2; i <= 2; i += 2)
		{
			for (int j = -2; j <= 2; j += 2)
			{
				if (i + j == -2 || i + j == 2)
				{
					vStateCheck.push_back({ _tempGoal.x + i, _tempGoal.y + j });
				}
			}
		}

		float minDistance = 1000.0f;
		for (auto viStateCheck = vStateCheck.begin(); viStateCheck != vStateCheck.end(); ++viStateCheck)
		{
			POINT temp = *viStateCheck;
			for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)
			{
				Cell* cell = (*cellsIter);
				if (cell->getCellX() == temp.x && cell->getCellY() == temp.y)
				{
					if (cell->getType() == CELL_TYPE::NORMAL || cell->getType() == CELL_TYPE::MOVEABLE)
					{
						float distance = getDistance(_pMoveStart.x, _pMoveStart.y, temp.x, temp.y);
						if (distance < minDistance)
						{
							_playerPathGoal.x = temp.x;
							_playerPathGoal.y = temp.y;
							minDistance = distance;
						}
					}
				}
			}
		}

		auto path = _generator->findPath(
			{ _pMoveStart.x,_pMoveStart.y },
			{ _playerPathGoal.x,_playerPathGoal.y });

		_check.clear();
		int pathNum = 10;
		int pathSize = path.size() < pathNum ? path.size() : pathNum;
		for (int i = path.size() - pathSize; i < path.size(); ++i)
		{
			auto coordinate = path[i];
			_check.push_back({ coordinate.x, coordinate.y });
		}
		_moveIndex = _check.size() - 1;
		_turnSystem->setPlayerBit(1);
	}
	else if (_turnSystem->getStatus() == CHANGINGSTATUS::ENEMYTURN)
	{
		POINT enemyPoint = { _saladin->getSaladinPosX() - TILESIZEX, _saladin->getSaladinPosY() };
		POINT _tempGoal = { 0,0 };
		_enemyPathGoal = { 0,0 };
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
		}

		// Stop find path if the enemy is already near the player.
		auto currentPath = _generator->findPath(
			{ _pMoveStart.x,_pMoveStart.y },
			{ _tempGoal.x, _tempGoal.y });
		if (currentPath.size() == 3)
		{
			_turnSystem->setEnemyBit(2);
			return;
		}

		vector<POINT> vStateCheck;
		for (int i = -2; i <= 2; i += 2)
		{
			for (int j = -2; j <= 2; j += 2)
			{
				if (i + j == -2 || i + j == 2)
				{
					vStateCheck.push_back({ _tempGoal.x + i, _tempGoal.y + j });
				}
			}
		}

		float minDistance = 1000.0f;
		for (auto viStateCheck = vStateCheck.begin(); viStateCheck != vStateCheck.end(); ++viStateCheck)
		{
			POINT temp = *viStateCheck;
			for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)
			{
				Cell* cell = (*cellsIter);
				if (cell->getCellX() == temp.x && cell->getCellY() == temp.y)
				{
					if (cell->getType() == CELL_TYPE::NORMAL || cell->getType() == CELL_TYPE::MOVEABLE)
					{
						float distance = getDistance(_pMoveStart.x, _pMoveStart.y, temp.x, temp.y);
						if (distance < minDistance)
						{
							_enemyPathGoal.x = temp.x;
							_enemyPathGoal.y = temp.y;
							minDistance = distance;
						}
					}
				}
			}
		}

		auto path = _generator->findPath(
			{ _pMoveStart.x,_pMoveStart.y },
			{ _enemyPathGoal.x,_enemyPathGoal.y });

		_check.clear();
		int pathNum = 10;
		int pathSize = path.size() < pathNum ? path.size() : pathNum;
		for (int i = path.size() - pathSize; i < path.size(); ++i)
		{
			auto coordinate = path[i];
			_check.push_back({ coordinate.x, coordinate.y });
		}
		_moveIndex = _check.size() - 1;
		_turnSystem->setEnemyBit(1);
	}
}

void FinalScene::Attack()
{
    if (_turnSystem->getStatus() == CHANGINGSTATUS::PLAYERTURN)
    {
        _player->setPlayerStateBit(1);
        if (_player->getAttack())
        {
			_saladin->setEnemyStateBit(2);
            _player->setPlayerIdle();
            _player->setAttack(false);
        }
		if (!_saladin->getDamage())
		{
			//_turnSystem->changeToEnemy();
		}
    }
    else if (_turnSystem->getStatus() == CHANGINGSTATUS::ENEMYTURN)
    {
        _saladin->setEnemyStateBit(1);
        if (_saladin->getAttack())
        {
            _player->setPlayerStateBit(2);
            _saladin->setEnemyIdle();
            _saladin->setAttack(false);
            _turnSystem->changeToPlayer();
        }
    }
	changeImage();
}

POINT FinalScene::lerp(POINT start, POINT end, float percentage)
{
	if (0 > percentage) percentage = 0;
	else if (percentage > 1)percentage = 1;
	LONG x = start.x + (end.x - start.x) * percentage;
	LONG y = start.y + (end.y - start.y) * percentage;

	return { x,y };
}
