#include "Stdafx.h"
#include "FinalScene.h"

HRESULT FinalScene::init(void)
{
	SOUNDMANAGER->addSound("Unknown Blood", "Resources/Sounds/Unknown Blood.mp3", true, true);
	SOUNDMANAGER->play("Unknown Blood", 1.0f);
	_mapTileInfo = new MapTileInfo;
	_mapTileInfo->init();

	_gameUI = new GameUI;
	_gameUI->init();

	_aniCursor = ANIMATIONMANAGER->findAnimation("normalCursor");
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
	_saladin->setSaladinPosX(18 * TILESIZEX);
	_saladin->setSaladinPosY(10 * TILESIZEY);
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
		if (cell->getType() == CELL_TYPE::WALL || cell->getType() == CELL_TYPE::ENEMY)
		{
			_generator->addCollision({ cell->getCellX(),cell->getCellY() });
		}
	}
	_moveRc = RectMake(-50, -50, TILESIZEX, TILESIZEY);
	_endPointIndex = 0;
	_moveIndex = 0;
	_lerpPercentage = 0.0f;
	_yPos = 0.0f;
	_enemyPathGoal = { 0,0 };

	_skill = new Skill;
	_skill->setPlayer(_player);
	_skill->setSaladin(_saladin);
	_skill->setCamera(_camera);
	_skill->setCells(_cells);
	_skill->init();

	_turnSystem = new TurnSystem();
	_turnSystem->init();
	_enemyBit = 0;
	_moveTileBit = 0;
	_tileAlpha = 100;
    _mouseType = CELL_TYPE::NORMAL;
    _beforeMouseType = CELL_TYPE::GOAL;
	_isMoveTileOn = false;
	_isAlphaIncrese = true;
	_isPosIncrese = true;
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

    _skill->release();
    SAFE_DELETE(_skill);
}

void FinalScene::update(void)
{
	POINT playerUI = {
						_player->getPlayerPosX() - _camera->getScreenRect().left,
						_player->getPlayerPosY() - _camera->getScreenRect().top
					 };

    //검사용 버튼
	if (KEYMANAGER->isOnceKeyDown('H'))
	{
		_turnSystem->changeToEnemy();
		for (auto iter = _vAttackableTile.begin(); iter != _vAttackableTile.end(); ++iter)
		{
			(*iter)->setType(CELL_TYPE::NORMAL);
		}
		_vAttackableTile.clear();
        _moveTileBit.reset();
	}
	else if (KEYMANAGER->isOnceKeyDown('N'))
	{
		_turnSystem->changeToPlayer();
        _moveTileBit.reset();
		for (auto iter = _vAttackableTile.begin(); iter != _vAttackableTile.end(); ++iter)
		{
			(*iter)->setType(CELL_TYPE::NORMAL);
		}
		_vAttackableTile.clear();
	}

    if (_mouseType != _beforeMouseType) 
    {
        _aniCursor->AniStop();
        _beforeMouseType = _mouseType;
        switch (_mouseType)
        {
        case CELL_TYPE::NORMAL:
            _aniCursor = ANIMATIONMANAGER->findAnimation("normalCursor");
            break;
        case CELL_TYPE::SKILLABLE:
            _aniCursor = ANIMATIONMANAGER->findAnimation("attackMark");
            break;
        case CELL_TYPE::WALL:
            _aniCursor = ANIMATIONMANAGER->findAnimation("notMoveable");
            break;
        case CELL_TYPE::ATTACKABLE:
            _aniCursor = ANIMATIONMANAGER->findAnimation("normalCursor");
            break;
		case CELL_TYPE::MOVEABLE:
            _aniCursor = ANIMATIONMANAGER->findAnimation("normalCursor");
            break;
		case CELL_TYPE::ENEMY:
            _aniCursor = ANIMATIONMANAGER->findAnimation("attackMark");
			_saladin->getEnemyHpBar()->setType(1);
            break;
        case CELL_TYPE::START:
            _aniCursor = ANIMATIONMANAGER->findAnimation("normalCursor");
			_player->getPlayerHpBar()->setType(0);
            break;
        }
        _aniCursor->AniStart();
    }

    for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)
    {
        POINT cameraMouse = {
                              _ptMouse.x + _camera->getScreenRect().left,
                              _ptMouse.y + _camera->getScreenRect().top
        };

        Cell* cell = (*cellsIter);
        if (PtInRect(&cell->getRect(), cameraMouse))
        {
            switch (cell->getType())
            {
            case CELL_TYPE::ENEMY:
				_saladin->getEnemyHpBar()->setGauge(100,100);
				_saladin->getEnemyHpBar()->update();
                break;
            case CELL_TYPE::START:
				_player->getPlayerHpBar()->setGauge(100, 100);
				_player->getPlayerHpBar()->update();
                break;
            default:
				_player->getPlayerHpBar()->resetImgIdx();
				_saladin->getEnemyHpBar()->resetImgIdx();
                break;
            }
        }
    }

    POINT cameraMouse = {
                            _ptMouse.x + _camera->getScreenRect().left,
                            _ptMouse.y + _camera->getScreenRect().top
                        };

	if (_turnSystem->getStatus() == CHANGINGSTATUS::PLAYERTURN)
	{
		// 대기 - 대기이미지 타일클릭시 이동가능상태 /메뉴창 열수있고 공격타일 만들수잇음
		if (_turnSystem->isPlayerIdle() == 1)
		{
			if (_tileAlpha < 100 || _tileAlpha >= 200) _isAlphaIncrese = !_isAlphaIncrese;
			if (_isAlphaIncrese)_tileAlpha += 1.0f; else _tileAlpha -= 1.0f;

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_moveTileBit.none() == 1)//000
				{
					_moveTileBit.set();//111
				}
                else if (_moveTileBit.test(2) == 1 && _moveTileBit.test(1) == 1 && _moveTileBit.test(0) == 0)//110 - 이동타일 활성화 상태
                {
                    for (auto iterator = _vMoveableTile.begin(); iterator != _vMoveableTile.end(); ++iterator)
                    {
                        if (PtInRect(&(*iterator)->getRect(), cameraMouse))
                        {
                            if ((*iterator)->getType() == CELL_TYPE::MOVEABLE)
                            {
                                (*iterator)->setType(CELL_TYPE::GOAL);
                                _endPoint = { (*iterator)->getRect().left, (*iterator)->getRect().top };

                                auto path = _generator->findPath({ _cMoveStart->getCellX(),_cMoveStart->getCellY() },
                                    { (*iterator)->getCellX(),(*iterator)->getCellY() });
                                _check.clear();
                                for (auto &coordinate : path)
                                {
                                    if ((*iterator)->getType() == CELL_TYPE::NORMAL)
                                    {
                                        (*iterator)->setType(CELL_TYPE::MOVEPATH);
                                    }
                                    _check.push_back({ coordinate.x, coordinate.y });
                                }
                                _moveIndex = _check.size() - 1;
                                _turnSystem->setPlayerBit(1);
                                break;
                            }
                            else if ((*iterator)->getType() == CELL_TYPE::ENEMY)
                            {
                                _check.clear();
                                find4WaysTile();
                                break;
                            }
                        }
                    }
                }
				else if (_moveTileBit.test(2) == 1 && _moveTileBit.test(1) == 0 && _moveTileBit.test(0) == 0)//100
				{
					_moveTileBit.set(0);//101
				}
				else if (_moveTileBit.test(2) == 1 && _moveTileBit.test(1) == 0 && _moveTileBit.test(0) == 1)//101- 공격타일 활성화 상태
				{
                    for (auto iterator = _vAttackableTile.begin(); iterator != _vAttackableTile.end(); ++iterator)
                    {
                        if (PtInRect(&(*iterator)->getRect(), cameraMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
                        {
                           if((*iterator)->getType() == CELL_TYPE::ENEMY) _turnSystem->setPlayerBit(2);
                        }
                    }
				}
			}
			POINT playerPos = { _player->getPlayerPosX()-TILESIZEX, _player->getPlayerPosY()};
			for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)//클릭 가능한 타일만 되게 지정
			{
				Cell* cell = (*cellsIter);
				if (PtInRect(&cell->getRect(), playerPos))
				{
					if (cell->getType() != CELL_TYPE::WALL)
					{
						cell->setType(CELL_TYPE::START);
						_cMoveStart = cell;
					}
				}
				else if (cell->getType() == CELL_TYPE::START)
				{
					cell->setType(CELL_TYPE::NORMAL);
				}
			}
            POINT enemyPos = { _saladin->getSaladinPosX() - TILESIZEX, _saladin->getSaladinPosY() };
            for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)
            {
                Cell* cell = (*cellsIter);

                if (PtInRect(&cell->getRect(), enemyPos))
                {
                    if (cell->getType() != CELL_TYPE::WALL)
                    {
                        cell->setType(CELL_TYPE::ENEMY);
                    }
                }
                else if (cell->getType() == CELL_TYPE::ENEMY)
                {
                    cell->setType(CELL_TYPE::NORMAL);
                }
            }
			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				_turnSystem->setPlayerBit(0);
				_gameUI->showBattleMenu(playerUI);
			}
		}
		// 0000 0001 : 메뉴창염 - 타일클릭해도 이동안되어야함 버튼클릭상태
		else if (_turnSystem->getPlayerBit(0) == 1)
		{
			/*	if (_vMoveableTile.size() > 0)
			{
				for (auto iter = _vMoveableTile.begin(); iter != _vMoveableTile.end(); ++iter)
				{
					(*iter)->setType(CELL_TYPE::NORMAL);
				}
				_vMoveableTile.clear();
			}*/ //=================================================================================스타트 에너미 지정도 다시 해줘야해서 보류

			_moveTileBit.set(2);//100
			_gameUI->update();

			if (!_gameUI->getMenu())
			{
				if (_gameUI->getPlayerTurn() &&!_gameUI->getSkillMenu() && _gameUI->getSkillNum() == SKILL_INDEX_NULL)
				{
					_turnSystem->changeToPlayer();
					_moveTileBit.reset();
				}
				else if(!_gameUI->getPlayerTurn() && !_gameUI->getSkillMenu() && _gameUI->getSkillNum() == SKILL_INDEX_NULL)
				{
					_vAttackableTile.clear();
					_turnSystem->changeToEnemy();
					_moveTileBit.reset();
				}

				if (_gameUI->getSkillMenu())
				{
					_gameUI->showSkillMenu(playerUI);
				}

				if (_gameUI->getSkillNum() == SKILL_INDEX_WINDEYUN)
                {
					_moveTileBit.set(0,true); //101- 공격타일 활성화 상태
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						for (auto iterator = _vAttackableTile.begin(); iterator != _vAttackableTile.end(); ++iterator)
						{
							if (PtInRect(&(*iterator)->getRect(), cameraMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
							{
								if ((*iterator)->getType() == CELL_TYPE::ENEMY)
								{
									_turnSystem->setPlayerBit(5);
									_player->setPlayerStateBit(4);
									_skill->setplaySound(true);
								}
								else
								{
									_gameUI->setSkillNum(SKILL_NUMBER::SKILL_INDEX_NULL);
									_turnSystem->setPlayerBit(0);
									_moveTileBit.reset();
								}
							}
							if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
							{
                                _turnSystem->changeToPlayer();
								_moveTileBit.reset();
							}
						}
					}

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
            Attack();
		}
		// 0000 1000 : 피격
		else if (_turnSystem->getPlayerBit(3) == 1)
		{
			changeImage();
		}
		//0001 0000 : 천지파열무 스킬 사용
		else if (_turnSystem->getPlayerBit(4) == 1)
		{
			cout << "버몬트 스킬 파업" << endl;
		}
        //0010 0000 : 풍아열공참 스킬 사용
        else if (_turnSystem->getPlayerBit(5) == 1)
        {
			_skill->windEyun();
            _skill->update();
            if (_player->getPlayerStateBit(4) == 0)
            {
                _vAttackableTile.clear();
                _gameUI->setSkillNum(SKILL_NUMBER::SKILL_INDEX_NULL);
				_skill->reset();
                _turnSystem->changeToEnemy();
                _moveTileBit.reset();
            }
        }
	}
	else if (_turnSystem->getStatus() == CHANGINGSTATUS::ENEMYTURN)
	{
        //캐릭터 위치 파악 후 이동0 / 이동 후 공격1 / 스킬 사용 고름2
		if (_turnSystem->isEnemyIdle() == 1)
		{
			// : 대기- 대기이미지 - 캐릭터 시작타일 파악후 캐릭터 좌우상하 4개 타일 중 가까운 타일 선택해 그곳을 목표로 3칸씩 이동?
            POINT playerPos = { _player->getPlayerPosX() - TILESIZEX, _player->getPlayerPosY() };
            for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)//클릭 가능한 타일만 되게 지정
            {
                Cell* cell = (*cellsIter);
                if (PtInRect(&cell->getRect(), playerPos))
                {
                    if (cell->getType() != CELL_TYPE::WALL)
                    {
                        cell->setType(CELL_TYPE::START);
                        _cMoveStart = cell;
                    }
                }
            }
            find4WaysTile();
		}
		// 0000 0010 : 이동중 - 
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

    if (_turnSystem->isPlayerIdle() == 1 && _turnSystem->getStatus() == CHANGINGSTATUS::PLAYERTURN)
    {
	    if (_moveTileBit.test(0) == 1 && _moveTileBit.test(1) == 1 && _moveTileBit.test(2) == 1)//111의 경우에서 쓰음
	    {
	    	startShowMoveableTile(6, _cMoveStart, false);
	    	_moveTileBit.reset(0);
	    }
    }

	if (_moveTileBit.test(0) == 1 && _moveTileBit.test(1) == 0 && _moveTileBit.test(2) == 1)//101
	{
	    startShowAttackableTile(1, _cMoveStart, false);
	}

	if (_yPos < 0 || _yPos >= 3) _isPosIncrese = !_isPosIncrese;
	if (_isPosIncrese)_yPos += 0.15f; else _yPos -= 0.15f;
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

	if (_moveTileBit.test(0) == 0 && _moveTileBit.test(1) == 1)
	{
		for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)
		{
			Cell* cell = (*cellsIter);
			int left = cell->getRect().left - cameraLeft;
			int top = cell->getRect().top - cameraTop;
			switch (cell->getType())
			{
			case(CELL_TYPE::START):
				IMAGEMANAGER->alphaRender("attackTile", getMemDC(), (int)left, (int)top, _tileAlpha+20);
				break;
			case(CELL_TYPE::MOVEABLE):
				IMAGEMANAGER->alphaRender("moveTile", getMemDC(), (int)left, (int)top, _tileAlpha);
				break;
			case(CELL_TYPE::ATTACKABLE):
				IMAGEMANAGER->alphaRender("attackTile", getMemDC(), (int)left, (int)top, _tileAlpha);
				break;
			case(CELL_TYPE::ENEMY):
				IMAGEMANAGER->alphaRender("attackTile", getMemDC(), (int)left, (int)top, _tileAlpha+40);
				break;
            case(CELL_TYPE::SKILLABLE):
                IMAGEMANAGER->alphaRender("skillTile", getMemDC(), (int)left, (int)top, _tileAlpha);
                break;
			}
		}
	}
	else if (_moveTileBit.test(0) == 1 && _moveTileBit.test(1) == 0 && _moveTileBit.test(2) == 1)
	{
		for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)
		{
			Cell* cell = (*cellsIter);
			int left = cell->getRect().left - cameraLeft;
			int top = cell->getRect().top - cameraTop;
			switch (cell->getType())
			{
			case(CELL_TYPE::START):
				IMAGEMANAGER->alphaRender("attackTile", getMemDC(), (int)left, (int)top, _tileAlpha + 20);
				break;
            case(CELL_TYPE::MOVEABLE):
                IMAGEMANAGER->alphaRender("moveTile", getMemDC(), (int)left, (int)top, _tileAlpha);
                break;
			case(CELL_TYPE::ATTACKABLE):
				IMAGEMANAGER->alphaRender("attackTile", getMemDC(), (int)left, (int)top, _tileAlpha);
				break;
			case(CELL_TYPE::ENEMY):
				IMAGEMANAGER->alphaRender("attackTile", getMemDC(), (int)left, (int)top, _tileAlpha - 40);
				break;
            case(CELL_TYPE::SKILLABLE):
                IMAGEMANAGER->alphaRender("skillTile", getMemDC(), (int)left, (int)top, _tileAlpha );
				break;
			}
		}
	}
	AstarTileInfo();
	IMAGEMANAGER->alphaRender("shadow", getMemDC(), _player->getPlayerPosX()- cameraLeft-47, _player->getPlayerPosY()+10- cameraTop, 150);
	IMAGEMANAGER->alphaRender("shadow", getMemDC(), _saladin->getSaladinPosX()- cameraLeft-50, _saladin->getSaladinPosY()+10- cameraTop, 150);

	
	if (_player->getPlayerStateBit(3) == 1 || _player->getPlayerStateBit(4) == 1 || _saladin->getSkillCount() >= 5)
	{
		_skill->render();
	}
	_saladin->render();
	if (_player->getLive())_player->render();
    _gameUI->render();
	IMAGEMANAGER->render("mapInfoAll", getMemDC(), WINSIZE_X - 230, 0);

    FONTMANAGER->drawText(getMemDC(),
        WINSIZE_X - 115, 17, "가을체", 19, 13, _uiText[0],
        wcslen(_uiText[0]), TA_CENTER, RGB(255, 255, 255));
    FONTMANAGER->drawText(getMemDC(),
        WINSIZE_X - 50, 40, "가을체", 21, 13, _uiText[1],
        wcslen(_uiText[1]), TA_CENTER, RGB(255, 255, 255));
    FONTMANAGER->drawText(getMemDC(),
        WINSIZE_X - 50, 80, "가을체", 17, 13, _uiText[2],
        wcslen(_uiText[2]), TA_CENTER, RGB(255, 255, 255));
	FONTMANAGER->drawText(getMemDC(),
		WINSIZE_X - 10, 82, "가을체", 15, 13, _uiText[3],
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
			sprintf_s(cellIndex, "%d", cell->getCellX());
			TextOut(getMemDC(), WINSIZE_X - 195, 80, cellIndex, strlen(cellIndex));
			sprintf_s(cellIndex, "%d", cell->getCellY());
			TextOut(getMemDC(), WINSIZE_X - 130, 65, cellIndex, strlen(cellIndex));
			int zPos = cell->getCellX() - cell->getCellY();

			if (zPos < 0)      zPos = 1;
			else if (zPos >= 5)      zPos = 3;
			sprintf_s(cellIndex, "%d", zPos);//z축위치
			TextOut(getMemDC(), WINSIZE_X - 150, 45, cellIndex, strlen(cellIndex));

			int left = cell->getRect().left - 20 - cameraLeft;
			int top = cell->getRect().top - TILESIZEY - cameraTop;
			_mouseType = cell->getType();
			switch(cell->getType())
			{
			case CELL_TYPE::ENEMY:
				IMAGEMANAGER->findImage("attackMark")->aniRender(getMemDC(), _ptMouse.x, _ptMouse.y, _aniCursor);
				_saladin->getEnemyHpBar()->render(left,top);
				break;
            case CELL_TYPE::SKILLABLE:
                IMAGEMANAGER->findImage("attackMark")->aniRender(getMemDC(), _ptMouse.x, _ptMouse.y, _aniCursor);
                break;
			case CELL_TYPE::WALL:
				IMAGEMANAGER->findImage("notMoveable")->aniRender(getMemDC(), _ptMouse.x - 16, _ptMouse.y - 6, _aniCursor);
				break;
            case CELL_TYPE::START:
				IMAGEMANAGER->findImage("normalCursor")->aniRender(getMemDC(), _ptMouse.x, _ptMouse.y, _aniCursor);
				_player->getPlayerHpBar()->render(left, top);

				break;
			default:
				IMAGEMANAGER->findImage("normalCursor")->aniRender(getMemDC(), _ptMouse.x, _ptMouse.y, _aniCursor);
				break;
			}
        }
	}


	POINT MarkPos = { -23,-63 + _yPos };
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

void FinalScene::drawMapCellInfo()//디버그용
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
			break;
		case(CELL_TYPE::GOAL):
			brush = CreateSolidBrush(RGB(0, 255, 0));
			oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
			FillRect(getMemDC(), &rect, brush);
			break;
		case(CELL_TYPE::MOVEABLE):
			brush = CreateSolidBrush(RGB(205, 205, 100));
			oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
			FillRect(getMemDC(), &rect, brush);
			break;
        case(CELL_TYPE::MOVEPATH):
            brush = CreateSolidBrush(RGB(205, 255, 100));
            oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
            FillRect(getMemDC(), &rect, brush);
            break;
		case(CELL_TYPE::ENEMY):
            brush = CreateSolidBrush(RGB(255, 255, 0));
            oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
            FillRect(getMemDC(), &rect, brush);
			break;
		case(CELL_TYPE::ATTACKABLE):
			break;
		case(CELL_TYPE::SKILLABLE):
			break;
		}
		SelectObject(getMemDC(), brush);
		DeleteObject(brush);

		sprintf_s(cellIndex, "%d,%d", cell->getCellX(), cell->getCellY());
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
			for (auto iter = _vMoveableTile.begin(); iter != _vMoveableTile.end(); ++iter)
			{
				(*iter)->setType(CELL_TYPE::NORMAL);
			}
			_vMoveableTile.clear();
			_vAttackableTile.clear();
			//_moveTileBit.reset();

			_moveTileBit.reset(1);
			if (_cMoveStart->getCellX() == _enemyPathGoal.x && _cMoveStart->getCellY() == _enemyPathGoal.y)
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
			float time = 7.0f;
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
			if (_cMoveStart->getCellX() == _enemyPathGoal.x && _cMoveStart->getCellY() == _enemyPathGoal.y)
			{
				_turnSystem->setEnemyBit(2);
			}
			else
			{
				_turnSystem->changeToPlayer();
				_saladin->setEnemyIdle();
                _moveTileBit.reset();
			}

			_moveIndex = 0;
			_lerpPercentage = 0.0f;
			_check.clear();//==============================================================================================
			return;
		}
		else
		{
			changeImage();
			float time = 7.0f;
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
		else if (_player->getPlayerStateBit(1) == 1 || _player->getPlayerStateBit(2) == 1)
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
        else if (_saladin->getEnemyStateBit(1) == 1 || _saladin->getEnemyStateBit(2) == 1)
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

			if (cell->getType() == CELL_TYPE::ENEMY)
			{
				_endPoint = { cell->getRect().left, cell->getRect().top };
				_tempGoal = { cell->getCellX(), cell->getCellY() };
			}
		}

		// Stop find path if the enemy is already near the player.
		auto currentPath = _generator->findPath({ _cMoveStart->getCellX(), _cMoveStart->getCellY() },
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
					if(cell->getType() != CELL_TYPE::WALL && cell->getType() != CELL_TYPE::GOAL )
					{
						float distance = getDistance(_cMoveStart->getCellX(), _cMoveStart->getCellY(), temp.x, temp.y);
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
			{ _cMoveStart->getCellX(), _cMoveStart->getCellY() },
			{ _playerPathGoal.x,_playerPathGoal.y });

		_check.clear();
		int pathNum = 20;
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
				_cMoveStart = cell;
			}

			if (cell->getType() == CELL_TYPE::START)
			{
				_endPoint = { cell->getRect().left, cell->getRect().top };
				_tempGoal = { cell->getCellX(), cell->getCellY() };
			}
		}

		// Stop find path if the enemy is already near the player.
		auto currentPath = _generator->findPath(
			{ _cMoveStart->getCellX(), _cMoveStart->getCellY() },
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
					//if (cell->getType() == CELL_TYPE::NORMAL || cell->getType() == CELL_TYPE::MOVEPATH || cell->getType() == CELL_TYPE::MOVEABLE || cell->getType() == CELL_TYPE::ATTACKABLE)//==================================
					if (cell->getType() != CELL_TYPE::WALL && cell->getType() != CELL_TYPE::GOAL )
					{
						float distance = getDistance(_cMoveStart->getCellX(), _cMoveStart->getCellY(), temp.x, temp.y);
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
			{ _cMoveStart->getCellX(), _cMoveStart->getCellY() },
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
		else
		{
			if (_saladin->getEnemyStateBit(2) == 0)
			{
				_turnSystem->changeToEnemy();
				for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)//클릭 가능한 타일만 되게 지정
				{
					Cell* cell = (*cellsIter);
					if (PtInRect(&cell->getRect(), { (long)_player->getPlayerPosX() - TILESIZEX, (long)_player->getPlayerPosY() }))
					{
						if (cell->getType() != CELL_TYPE::WALL)
						{
							cell->setType(CELL_TYPE::START);
						}
					}
				}
			}
		}
    }
    else if (_turnSystem->getStatus() == CHANGINGSTATUS::ENEMYTURN)
    {
        _saladin->setEnemyStateBit(1);
        if (_saladin->getAttack() && _saladin->getSkillCount() < 5)
        {
            _player->setPlayerStateBit(2);
            _saladin->setEnemyIdle();
            _saladin->setAttack(false);
            _turnSystem->changeToPlayer();
        }
		else if(_saladin->getSkillCount() >= 5)
		{
			_saladin->setEnemyStateBit(4);//
			_skill->setplaySound(true);//한번만 돌아야함
			_skill->update();
		}
    }
	changeImage();
}

void FinalScene::computeShowMoveableTile(int range, Cell* cell, bool isMoveable)
{
    if (range < 0) return;
	if (cell->getType() == CELL_TYPE::WALL) return;

	int tempX = cell->getCellX();
    int tempY = cell->getCellY();
    
	if (std::find(_vMoveableTile.begin(), _vMoveableTile.end(), cell) == _vMoveableTile.end())
		_vMoveableTile.push_back(cell);
	
	_qMoveTile.push(make_pair(range - 1, (*_cells)[tempX + 1 + tempY * STAGE3TILEX]));
	_qMoveTile.push(make_pair(range - 1, (*_cells)[tempX - 1 + tempY * STAGE3TILEX]));
	_qMoveTile.push(make_pair(range - 1, (*_cells)[tempX + (tempY + 1) * STAGE3TILEX]));
	_qMoveTile.push(make_pair(range - 1, (*_cells)[tempX + (tempY - 1)* STAGE3TILEX]));
}

void FinalScene::startShowMoveableTile(int range, Cell* cell, bool isMoveable)
{
	_vMoveableTile.clear();
    _qMoveTile.push(make_pair(range,cell));
    while(!_qMoveTile.empty())
    {
        computeShowMoveableTile(_qMoveTile.front().first, _qMoveTile.front().second, isMoveable);
        _qMoveTile.pop();
    }

	for (auto iter = _vMoveableTile.begin(); iter != _vMoveableTile.end(); ++iter)
	{
		if (iter >= _vMoveableTile.end() - (_vMoveableTile.size()*0.125))
		{
			(*iter)->setType(CELL_TYPE::ATTACKABLE);//갯수 설정 필요
		}
		else (*iter)->setType(CELL_TYPE::MOVEABLE);
	}
}

void FinalScene::computeShowAttackableTile(int range, Cell* cell, bool isMoveable)
{
	if (range < 0) return;
	if (cell->getType() == CELL_TYPE::WALL ) return;

	int tempX = cell->getCellX();
	int tempY = cell->getCellY();

	if (std::find(_vAttackableTile.begin(), _vAttackableTile.end(), cell) == _vAttackableTile.end())
		_vAttackableTile.push_back(cell);

	_qAttackTile.push(make_pair(range - 1, (*_cells)[tempX + 2 + tempY * STAGE3TILEX]));
	_qAttackTile.push(make_pair(range - 1, (*_cells)[tempX - 2 + tempY * STAGE3TILEX]));
	_qAttackTile.push(make_pair(range - 1, (*_cells)[tempX + (tempY + 2) * STAGE3TILEX]));
	_qAttackTile.push(make_pair(range - 1, (*_cells)[tempX + (tempY - 2)* STAGE3TILEX]));
}

void FinalScene::startShowAttackableTile(int range, Cell* cell, bool isMoveable)
{
    _vAttackableTile.clear();
    _qAttackTile.push(make_pair(range, cell));

    while (!_qAttackTile.empty())
    {
        computeShowAttackableTile(_qAttackTile.front().first, _qAttackTile.front().second, isMoveable);
        _qAttackTile.pop();
    }

    for (auto iter = _vAttackableTile.begin(); iter != _vAttackableTile.end(); ++iter)
    {
        if ((*iter)->getType() != CELL_TYPE::ENEMY) (*iter)->setType(CELL_TYPE::ATTACKABLE);
    }
}

void FinalScene::computeShowSkillAttackableTile(int range, Cell * cell, bool isMoveable)
{
    //천지파열무
    if (range < 0) return;
    if (cell->getType() == CELL_TYPE::WALL) return;

    int tempX = cell->getCellX();
    int tempY = cell->getCellY();

    if (std::find(_vSkillableTile.begin(), _vSkillableTile.end(), cell) == _vSkillableTile.end())
        _vSkillableTile.push_back(cell);

    _qSkillTile.push(make_pair(range - 1, (*_cells)[tempX + 1 + tempY * STAGE3TILEX]));
    _qSkillTile.push(make_pair(range - 1, (*_cells)[tempX - 1 + tempY * STAGE3TILEX]));
    _qSkillTile.push(make_pair(range - 1, (*_cells)[tempX + (tempY + 1) * STAGE3TILEX]));
    _qSkillTile.push(make_pair(range - 1, (*_cells)[tempX + (tempY - 1)* STAGE3TILEX]));
    _qSkillTile.push(make_pair(range - 1, (*_cells)[tempX + 1 + (tempY - 1) * STAGE3TILEX]));
    _qSkillTile.push(make_pair(range - 1, (*_cells)[tempX + 1 + (tempY + 1) * STAGE3TILEX]));
    _qSkillTile.push(make_pair(range - 1, (*_cells)[tempX - 1 + (tempY - 1) * STAGE3TILEX]));
    _qSkillTile.push(make_pair(range - 1, (*_cells)[tempX - 1 + (tempY + 1) * STAGE3TILEX]));

}

void FinalScene::startShowSkillAttackableTile(int range, Cell * cell, bool isMoveable)
{
    _vSkillableTile.clear();
    _qSkillTile.push(make_pair(range, cell));

    while (!_qSkillTile.empty())
    {
        computeShowSkillAttackableTile(_qSkillTile.front().first, _qSkillTile.front().second, isMoveable);
        _qSkillTile.pop();
    }

    for (auto iter = _vSkillableTile.begin(); iter != _vSkillableTile.end(); ++iter)
    {
        (*iter)->setType(CELL_TYPE::SKILLABLE);
    }
}

POINT FinalScene::lerp(POINT start, POINT end, float percentage)
{
	if (0 > percentage) percentage = 0;
	else if (percentage > 1)percentage = 1;
	LONG x = start.x + (end.x - start.x) * percentage;
	LONG y = start.y + (end.y - start.y) * percentage;

	return { x,y };
}