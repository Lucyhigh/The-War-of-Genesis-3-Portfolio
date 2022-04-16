#include "Stdafx.h"
#include "Skill.h"

HRESULT Skill::init(void)
{
	_playerPos = { _player->getPlayerRect().left, _player->getPlayerRect().top };
	_skillAlpha = (BYTE)15;//
	_skillAlpha2 = (BYTE)40;//
	_skillAlpha3 = (BYTE)50;//
    _isStart = false;
    _skillIndex = 0;
	_alphaA = 0;
	_alphaB = 0;

	_count = 2;
	_cdt = 0.0f;
	_soundIndex = 0;
    _windSkillTick = 20;
    _windSkillCnt = 0;
    _windSkillIndex = 0;
	_isPlay = false;
    _skillPlayerPos = { 0,0 };
    _skillPlayerPos2 = { 0,0 };
    _skillPlayerPos3 = { 0,0 };
    worldBrokenSkill();

	string skyPath = "Resources/Sounds/world/";
	_vWorldSoundName = getFilesInDirectory(skyPath, "*.mp3");
	for (string name : _vWorldSoundName)
	{
		SOUNDMANAGER->addSound(name, skyPath + name, false, false);
	}

	string windPath = "Resources/Sounds/wind/";
	_vWindSoundName = getFilesInDirectory(windPath, "*.mp3");
	for (string name : _vWindSoundName)
	{
		SOUNDMANAGER->addSound(name, windPath + name, false, false);
	}
    _effectManager = new EffectManager;
    _effectManager->init();
	return S_OK;
}

void Skill::release(void)
{
}

void Skill::update(void)
{
    if (_player->getPlayerStateBit(3) == 1)
    {
        if (_alphaA < 100) _alphaA += 5;

        float left = _player->getPlayerRect().left - _camera->getScreenRect().left;
        float top = _player->getPlayerRect().top - _camera->getScreenRect().top;
        float cellLeft = _player->getPlayerRect().left  - _camera->getScreenRect().left;
        float cellTop = _player->getPlayerRect().top - _camera->getScreenRect().top;

        _skillPlayerPos  = { (long)left, (long)top+30};
        _skillPlayerPos2 = { (long)left, (long)top+30};
        _skillPlayerPos3 = { (long)left, (long)top+30};

        Cell* enemyCell = nullptr;//일단 1명
        for (auto cellsiter = _vSkillableCells->begin(); cellsiter != _vSkillableCells->end(); ++cellsiter)
        {
            if ((*cellsiter)->getType() == CELL_TYPE::ENEMY)
            {
                enemyCell = (*cellsiter);
                break;
            }
        }

        int skillArr1 = 24;
        int skillArr2 = 72;
        int skillArr3 = 120;
        int skillArr4 = 168;
        for (int i = 0; i < skillArr1; i += 4)
        {
            if (skillArr1 > i)
            {
                _vSkillCellPos[i]	  = { (long)cellLeft - 20 * (i + 1), (long)cellTop - 16 * (i + 1) };//LT
                _vSkillCellPos[i + 2] = { (long)cellLeft + 20 * (i + 1), (long)cellTop + 16 * (i + 1) };//RB
                _vSkillCellPos[i + 1] = { (long)cellLeft - 20 * (i + 1), (long)cellTop + 16 * (i + 1) };//LB
                _vSkillCellPos[i + 3] = { (long)cellLeft + 20 * (i + 1), (long)cellTop - 16 * (i + 1) };//RT========== triple 더블, 원 랜덤랜더필요
            }
        }

        for (int i = 0; i < 48; i += 4)
        {
            _vSkillCellPos[i + skillArr1]	  = { (long)cellLeft - 10 * (i + 1), (long)cellTop + 50 - 8 * (i + 1) };
            _vSkillCellPos[i + skillArr1 + 2] = { (long)cellLeft + 10 * (i + 1), (long)cellTop + 50 + 8 * (i + 1) };
            _vSkillCellPos[i + skillArr1 + 1] = { (long)cellLeft - 10 * (i + 1), (long)cellTop + 50 + 8 * (i + 1) };
            _vSkillCellPos[i + skillArr1 + 3] = { (long)cellLeft + 10 * (i + 1), (long)cellTop + 50 - 8 * (i + 1) };//========== fire 4가지 랜덤랜더필요 / 가까운거부터 먼저랜더 필요================
        }

        for (int i = 0; i < 48; i += 4)
        {
            _vSkillCellPos[i + skillArr2]	  = { (long)left - 10 - 10 * (i + 1), (long)top + 30 - 8 * (i + 1) };
            _vSkillCellPos[i + skillArr2 + 2] = { (long)left - 10 + 10 * (i + 1), (long)top + 30 + 8 * (i + 1) };
            _vSkillCellPos[i + skillArr2 + 1] = { (long)left - 10 - 10 * (i + 1), (long)top + 30 + 8 * (i + 1) };
            _vSkillCellPos[i + skillArr2 + 3] = { (long)left - 10 + 10 * (i + 1), (long)top + 30 - 8 * (i + 1) };//========== smog /가까운거부터 먼저랜더 필요=================
        }
        for (int i = 0; i < 48; i += 4)
        {
            _vSkillCellPos[i + skillArr3]	  = { (long)left+20 - 10 * (i + 1), (long)top + 80 - 8 * (i + 1) };
            _vSkillCellPos[i + skillArr3 + 2] = { (long)left+20 + 10 * (i + 1), (long)top + 80 + 8 * (i + 1) };
            _vSkillCellPos[i + skillArr3 + 1] = { (long)left+20 - 10 * (i + 1), (long)top + 80 + 8 * (i + 1) };
            _vSkillCellPos[i + skillArr3 + 3] = { (long)left+20 + 10 * (i + 1), (long)top + 80 - 8 * (i + 1) };//========== groundCrack /가까운거부터 먼저랜더 필요 / 4가지 랜덤랜더필요 =============
        }

        POINT enemyPos = { (long)enemyCell->getCellX()*TILESIZEX - _camera->getScreenRect().left ,
                           (long)enemyCell->getCellY()*TILESIZEY - _camera->getScreenRect().top };
        for (int i = 0; i < 4; i += 4)
        {
            _vSkillCellPos[i + skillArr4]     = { enemyPos.x+10	 , enemyPos.y - 100 };		  //"one");
            _vSkillCellPos[i + skillArr4 + 1] = { enemyPos.x+10	 , enemyPos.y - 40 };		  //"95light");
            _vSkillCellPos[i + skillArr4 + 2] = { enemyPos.x+10, enemyPos.y - 20 };		  //"48fire");
            _vSkillCellPos[i + skillArr4 + 3] = { enemyPos.x+10, enemyPos.y	   };//========== enemy /가까운거부터 먼저랜더 필요 / 4가지 랜덤랜더필요  //"enemyAttack");==============
        }
        _cdt++;
        if (200 <= _cdt && _cdt <= 230)
        {
            _alphaB = 200;
        }
        else _alphaB = 0;
        if (!_isStart) return;

        if (_cdt > 3)
        {
            _cdt = 0;
            _skillIndex++;
        }

        for (viSkillList = vSkillList.begin(); viSkillList != vSkillList.end(); ++viSkillList)
        {
            if ((*viSkillList)._skillIndex == _skillIndex)
            {
                _effectManager->createEffect((*viSkillList)._skillName.c_str(), 
											  *(*viSkillList)._aniPos, (*viSkillList)._fps, false,
											  (*viSkillList)._alpha, (*viSkillList)._alpha-40,10.0f);
            }
            if (_skillIndex == 20 || _skillIndex == 50 || _skillIndex == 110)
            {
                _camera->shakeStart(0.5f);
            }
        }
        _effectManager->update();
    }
    else if (_player->getPlayerStateBit(4) == 1)
    {
        if (_alphaA < 120) _alphaA += 5;
		_cdt++;
		if (_count < _cdt)
		{
			_cdt = 0.0f;
			for (auto iter = _vWindSkill.begin(); iter != _vWindSkill.end();)
			{
				Image* img = IMAGEMANAGER->findImage(iter->imgKey);

                if (iter->frameX < img->getMaxFrameX())
                {
                    iter->frameX++;
                    ++iter;
                }
                else if (iter->frameX == img->getMaxFrameX() && iter->frameY != img->getMaxFrameY())
                {
                    iter->frameX = 0;
                    iter->frameY++;
                    ++iter;
                }
                else if (iter->frameX == img->getMaxFrameX() && iter->frameY == img->getMaxFrameY())
                {
                    iter = _vWindSkill.erase(iter);
                }
                
			}
		}
    }
	playSound();
}

void Skill::render(void)
{
	IMAGEMANAGER->alphaRender("cutChange", getMemDC(), 0, 0, _alphaA);
    if (_player->getPlayerStateBit(3) == 1)
    {
        _effectManager->render();
    }
    else if (_player->getPlayerStateBit(4) == 1)
    {
		for (auto iter = _vWindSkill.begin(); iter != _vWindSkill.end(); ++iter)
		{
			IMAGEMANAGER->alphaFrameRender(iter->imgKey,getMemDC(),
										   iter->posX,	 iter->posY, 
										   iter->frameX, iter->frameY,
										   iter->alpha);
		}
    }
    IMAGEMANAGER->alphaRender("cutChangeRed", getMemDC(), 0, 0, _alphaB);
}

void Skill::worldBrokenSkill()
{
	tagSkill skill  = tagSkill{ 5, "184light", &_skillPlayerPos, (BYTE)100,20 };
	tagSkill skill2 = tagSkill{ 5, "circle", &_skillPlayerPos2,(BYTE)100,10 };
	tagSkill skill3 = tagSkill{ 5, "smog2", &_skillPlayerPos3,(BYTE)100,20 };

    int cellPosIdx = 0;
	int skillArr1 = 24;
	int skillArr2 = 48;

    for (int i = 0; i < 172; ++i) _vSkillCellPos.push_back({ 0,0 });
	
	for (int i = 0; i < skillArr1; ++i)
    {
		if (i % 2 == 1 )					pushCellSkill(30 +i, "tripleR", cellPosIdx++, _skillAlpha,8);
		else if (i % 2 == 0)				pushCellSkill(30 +i, "tripleL", cellPosIdx++, _skillAlpha,8);
    }

	for (int i = 0; i < skillArr2; ++i)
	{
		if (i % 2 == 1)						pushCellSkill(35 + i, "fire", cellPosIdx++, (BYTE)170,20);
        else if (i % 2 == 0)				pushCellSkill(40 + i, "fireL", cellPosIdx++, (BYTE)170,20);
	}

	for (int i = 0; i < skillArr2; ++i)
	{
		pushCellSkill(70 + i, "smog", cellPosIdx++, (BYTE)30,20);
	}

	for (int i = 0; i < skillArr2; ++i)
	{
		if (i % 2 == 1)						pushCellSkill(70 + i, "groundCrack", cellPosIdx++, (BYTE)170,10);
		else if (i % 2 == 0)				pushCellSkill(70 + i, "groundCrackL", cellPosIdx++, (BYTE)170,10);
    }

	//enemy Effect - 검출후에 리스트에 수 넣고 사이즈 잰 이후에 업데이트에서 구현 필요 일단 1개로
	for (int i = 0; i < 1; ++i)
	{
		pushCellSkill(120, "one", cellPosIdx++, (BYTE)190,15);
	}

	for (int i = 0; i < 1; ++i)
	{
		pushCellSkill(125, "95light", cellPosIdx++, (BYTE)190,20);
	}

	for (int i = 0; i < 1; ++i)
	{
		pushCellSkill(130, "48fire", cellPosIdx++, (BYTE)190,10);
	}

	for (int i = 0; i < 1; ++i)
	{
		pushCellSkill(135, "enemyAttack", cellPosIdx++, (BYTE)190,20);
	}
	vSkillList.push_back(skill);
	vSkillList.push_back(skill2);
	vSkillList.push_back(skill3);
    startSkill();
}


void Skill::windEyun()
{
	int left = _player->getPlayerRect().left - 100 - _camera->getScreenRect().left;
	int top = _player->getPlayerRect().top - 100 - _camera->getScreenRect().top;
    //일단 오른쪽 기준으로 맞춤
	string skillArr[10] = { "184light" ,"skill10R", "skill8", "skill4R","skill10R", "skill7", "184light", "skill7","skill8","skill3" };
    POINT skillPosArr[10] =
    {
		{left ,		 top },		// "184light"
		{left + 40,  top + 60},	// "skill10R"
		{left + 40 , top - 10}, // "skill8",
		{left - 40,  top - 30},	// "skill4R",
		{left + 40,  top + 60}, // "skill10R"
		{left + 40 , top - 10}, // "skill7",
		{left + 20,	 top + 30},	// "184light"
		{left + 40 , top - 10}, // "skill7"	
		{left + 40 , top - 10}, // "skill8"	
		{left + 60,  top}		// "skill3" 
    };			
	BYTE skillAlpha[10] = { 160,235,120,200,200,120,160,120,120,235 };
    switch(_player->getImageState())
    {
    case PLAYERSTATE::RIGHT:
		skillArr[1] = { "skill10R" };
		skillArr[3] = {  "skill4R" };
		skillArr[4] = { "skill10R" };
        break;
    case PLAYERSTATE::LEFT:
		skillArr[1] = { "skill10L" };
        skillArr[3] = { "skill4L" };
        skillArr[4] = { "skill10L" };
        break;
    case PLAYERSTATE::TOP:
		skillArr[1] = { "skill10T" };
        skillArr[3] = { "skill4T" };
        skillArr[4] = { "skill10T" };
        break;
    case PLAYERSTATE::BOTTOM:
		skillArr[1] = { "skill10R" };
        skillArr[3] = { "skill4R" };
        skillArr[4] = { "skill10R" };
        break;
    }

	_windSkillCnt++;
	if (_windSkillCnt > _windSkillTick &&_windSkillIndex <= 10)
	{
		_windSkillCnt = 0;
		if (_windSkillIndex > 9) return;
		tagWindSkill skill = tagWindSkill{ skillArr[_windSkillIndex],0,0,
                                           (int)skillPosArr[_windSkillIndex].x,
                                           (int)skillPosArr[_windSkillIndex].y,
                                           skillAlpha[_windSkillIndex++] };
		_vWindSkill.push_back(skill);
	
		if (_windSkillIndex == 1) _windSkillTick = 60;//
        else if (_windSkillIndex == 2 || _windSkillIndex == 3 ) _windSkillTick = 30;
        else if ( _windSkillIndex == 4 || _windSkillIndex == 5) _windSkillTick = 5;
        else if ( _windSkillIndex == 6) _windSkillTick = 10;
        else if ( _windSkillIndex == 7 || _windSkillIndex == 8) _windSkillTick = 10;
        else if (_windSkillIndex == 9) _windSkillTick = 60;
	
        if (_windSkillIndex == 3 || _windSkillIndex == 8)
        {
            _alphaB = 80;
        }
        else _alphaB = 0;
	}
}

void Skill::setplaySound(bool isPlay)
{
	_isPlay = isPlay;
	_soundIndex = 0;
}

void Skill::playSound()
{
	if (_player->getPlayerStateBit(3) == 1)
	{
        if (_isPlay)
        {
            SOUNDMANAGER->play(_vWorldSoundName[_soundIndex], 1.0f);
            _isPlay = false;
        }

        if (_soundIndex < 5 && SOUNDMANAGER->getPosition(_vWorldSoundName[_soundIndex]) == SOUNDMANAGER->getLength(_vWorldSoundName[_soundIndex]))
        {
            SOUNDMANAGER->play(_vWorldSoundName[++_soundIndex], 1.0f);
        }
	}
	else if (_player->getPlayerStateBit(4) == 1)
	{
		if (_isPlay)
		{
			SOUNDMANAGER->play(_vWindSoundName[_soundIndex], 1.0f);
			_isPlay = false;
		}
		if (_windSkillIndex == 10)
		{
			if (_soundIndex == 0) SOUNDMANAGER->play(_vWindSoundName[++_soundIndex], 1.0f);
		}
	}
}

void Skill::pushCellSkill(int idx,string imgKey, int vNum, BYTE alpha, int fps)
{
	tagSkill skill = tagSkill(idx, imgKey, &_vSkillCellPos[vNum], _skillAlpha,fps);

	vSkillList.push_back(skill);
}

void Skill::startSkill()
{
    _isStart = true;
}

void Skill::reset()
{
    _cdt = 0.0f;
    _windSkillTick = 20;
    _windSkillCnt = 0;
    _windSkillIndex = 0;
}

void Skill::setPlayer(Player * player)
{
    _player = player;
}

void Skill::setCamera(Camera * camera)
{
    _camera = camera;
}

void Skill::setCells(vector<Cell*>* cells)
{
    _vSkillableCells = cells;
}