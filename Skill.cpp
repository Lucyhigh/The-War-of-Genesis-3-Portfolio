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

	string skyPath = "Resources/Sounds/sky/";
	_vSkySoundName = getFilesInDirectory(skyPath, "*.mp3");
	for (string name : _vSkySoundName)
	{
		SOUNDMANAGER->addSound(name, skyPath + name, false, false);
        cout << name << endl;
	}

	string windPath = "Resources/Sounds/wind/";
	_vWindSoundName = getFilesInDirectory(windPath, "*.mp3");
	for (string name : _vWindSoundName)
	{
		SOUNDMANAGER->addSound(name, windPath + name, false, false);
	}
    _effectManager = new EffectManager;
    _effectManager->init();
    _effectManager->setCamera(_camera);
	return S_OK;
}

void Skill::release(void)
{
}

void Skill::update(void)
{
    if (_player->getPlayerStateBit(3) == 1)
    {
        if (_alphaA < 80) _alphaA += 5;

        float left = _player->getPlayerRect().left - _camera->getScreenRect().left;
        float top = _player->getPlayerRect().top - _camera->getScreenRect().top;
        float cellLeft = _player->getPlayerRect().left - 20;
        float cellTop = _player->getPlayerRect().top - 185 ;

        _skillPlayerPos  = { (long)left - 95, (long)top - 40 };
        _skillPlayerPos2 = { (long)left - 95, (long)top - 40 };
        _skillPlayerPos3 = { (long)left - 55, (long)top - 40 };

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
                _vSkillCellPos[i] = { (long)cellLeft - 20 * (i + 1), (long)cellTop - 16 * (i + 1) };//LT
                _vSkillCellPos[i + 2] = { (long)cellLeft + 20 * (i + 1), (long)cellTop + 16 * (i + 1) };//RB
                _vSkillCellPos[i + 1] = { (long)cellLeft - 20 * (i + 1), (long)cellTop + 16 * (i + 1) };//LB
                _vSkillCellPos[i + 3] = { (long)cellLeft + 20 * (i + 1), (long)cellTop - 16 * (i + 1) };//RT========== triple 더블, 원 랜덤랜더필요
            }
        }

        for (int i = 0; i < 48; i += 4)
        {
            _vSkillCellPos[i + skillArr1] = { (long)cellLeft - 10 * (i + 1), (long)cellTop + 50 - 8 * (i + 1) };
            _vSkillCellPos[i + skillArr1 + 2] = { (long)cellLeft + 10 * (i + 1), (long)cellTop + 50 + 8 * (i + 1) };
            _vSkillCellPos[i + skillArr1 + 1] = { (long)cellLeft - 10 * (i + 1), (long)cellTop + 50 + 8 * (i + 1) };
            _vSkillCellPos[i + skillArr1 + 3] = { (long)cellLeft + 10 * (i + 1), (long)cellTop + 50 - 8 * (i + 1) };//========== fire 4가지 랜덤랜더필요 / 가까운거부터 먼저랜더 필요================
        }

        for (int i = 0; i < 48; i += 4)
        {
            _vSkillCellPos[i + skillArr2] = { (long)left - 30 - 10 * (i + 1), (long)top - 10 - 8 * (i + 1) };
            _vSkillCellPos[i + skillArr2 + 2] = { (long)left - 30 + 10 * (i + 1), (long)top - 10 + 8 * (i + 1) };
            _vSkillCellPos[i + skillArr2 + 1] = { (long)left - 30 - 10 * (i + 1), (long)top - 10 + 8 * (i + 1) };
            _vSkillCellPos[i + skillArr2 + 3] = { (long)left - 30 + 10 * (i + 1), (long)top - 10 - 8 * (i + 1) };//========== smog /가까운거부터 먼저랜더 필요=================
        }
        for (int i = 0; i < 48; i += 4)
        {
            _vSkillCellPos[i + skillArr3] = { (long)left - 20 - 10 * (i + 1), (long)top + 20 - 8 * (i + 1) };
            _vSkillCellPos[i + skillArr3 + 2] = { (long)left - 20 + 10 * (i + 1), (long)top + 20 + 8 * (i + 1) };
            _vSkillCellPos[i + skillArr3 + 1] = { (long)left - 20 - 10 * (i + 1), (long)top + 20 + 8 * (i + 1) };
            _vSkillCellPos[i + skillArr3 + 3] = { (long)left - 20 + 10 * (i + 1), (long)top + 20 - 8 * (i + 1) };//========== groundCrack /가까운거부터 먼저랜더 필요 / 4가지 랜덤랜더필요 =============
        }

        POINT enemyPos = { (long)enemyCell->getCellX()*TILESIZEX - _camera->getScreenRect().left ,
                           (long)enemyCell->getCellY()*TILESIZEY - _camera->getScreenRect().top };
        for (int i = 0; i < 4; i += 4)
        {
            _vSkillCellPos[i + skillArr4]     = { enemyPos.x - 20, enemyPos.y - 250 };																  //"one");
            _vSkillCellPos[i + skillArr4 + 1] = { enemyPos.x - 90, enemyPos.y - 100 };																  //"95light");
            _vSkillCellPos[i + skillArr4 + 2] = { enemyPos.x - 30, enemyPos.y - 70 };																  //"48fire");
            _vSkillCellPos[i + skillArr4 + 3] = { enemyPos.x - 40, enemyPos.y - 30 };//========== enemy /가까운거부터 먼저랜더 필요 / 4가지 랜덤랜더필요  //"enemyAttack");==============
        }
        _cdt++;
        if (200 <= _cdt && _cdt <= 230)
        {
            _alphaB = 200;
        }
        else _alphaB = 0;
        int a = 0;
        if (!_isStart) return;
        if (_cdt > 3)
        {
            _cdt = 0;
            _skillIndex++;
        }

        if (_skillIndex == 40) {
            int i = 0;
        }
        for (viSkillList = vSkillList.begin(); viSkillList != vSkillList.end(); ++viSkillList)
        {
           
            if ((*viSkillList)._skillIndex == _skillIndex)
            {
              
                _effectManager->createEffect((*viSkillList)._skillName.c_str(), *(*viSkillList)._aniPos, 8, false, 230, 210,3.0f);
            }
            if (_skillIndex == 80 || _skillIndex == 210)
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
										   iter->posX, iter->posY, 
										   iter->frameX, iter->frameY,
										   iter->alpha);
		}
    }
    IMAGEMANAGER->alphaRender("cutChangeRed", getMemDC(), 0, 0, _alphaB);
}

void Skill::worldBrokenSkill()
{
	Animation* _skillAni1 = ANIMATIONMANAGER->findAnimation("184light");
	Animation* _skillAni2 = ANIMATIONMANAGER->findAnimation("circle");
	Animation* _skillAni3 = ANIMATIONMANAGER->findAnimation("smog2");

    tagSkill skill =  tagSkill{ 60, "184light", &_skillPlayerPos, &_skillAlpha, _skillAni1 };
    tagSkill skill2 = tagSkill{ 60, "circle", &_skillPlayerPos2, &_skillAlpha2, _skillAni2 };
    tagSkill skill3 = tagSkill{ 70, "smog2", &_skillPlayerPos3, &_skillAlpha3, _skillAni3 };    

    int cellPosIdx = 0;
	int skillArr1 = 24;
	int skillArr2 = 48;

    for (int i = 0; i < 172; ++i) _vSkillCellPos.push_back({ 0,0 });//168 + enemy 4
	
	Animation* _skillAni4  = ANIMATIONMANAGER->findAnimation("tripleR");
	Animation* _skillAni5  = ANIMATIONMANAGER->findAnimation("tripleL");
	Animation* _skillAni6  = ANIMATIONMANAGER->findAnimation("fire");               //
	Animation* _skillAni7  = ANIMATIONMANAGER->findAnimation("fireL");              //
	Animation* _skillAni8  = ANIMATIONMANAGER->findAnimation("smog");               //
	Animation* _skillAni9  = ANIMATIONMANAGER->findAnimation("groundCrack");        //
	Animation* _skillAni10 = ANIMATIONMANAGER->findAnimation("groundCrackL");       //
	Animation* _skillAni11 = ANIMATIONMANAGER->findAnimation("one");
	Animation* _skillAni12 = ANIMATIONMANAGER->findAnimation("95light");
	Animation* _skillAni13 = ANIMATIONMANAGER->findAnimation("48fire");
	Animation* _skillAni14 = ANIMATIONMANAGER->findAnimation("enemyAttack");

	for (int i = 0; i < skillArr1; ++i)
    {
		if (i % 2 == 1 )					pushCellSkill(90 +i *2, "tripleR", cellPosIdx++, _skillAlpha, _skillAni4);
		else if (i % 2 == 0)				pushCellSkill(90 +i *2, "tripleL", cellPosIdx++, _skillAlpha, _skillAni5);
    }

	for (int i = 0; i < skillArr2; ++i)//
	{
		if (i % 2 == 1)						pushCellSkill(120 + i * 2, "fire", cellPosIdx++, (BYTE)10, _skillAni6);
        else if (i % 2 == 0)				pushCellSkill(120 + i * 2, "fireL", cellPosIdx++, (BYTE)10, _skillAni7);
        //if (i % 2 == 1)		 _effectManager->createEffect("fire", _vSkillCellPos[cellPosIdx++],8, false,230,200,10.0f);
        //else if (i % 2 == 0) _effectManager->createEffect("fireL", _vSkillCellPos[cellPosIdx++], 8, false, 230, 200, 10.0f);
	}

	for (int i = 0; i < skillArr2; ++i)//
	{
		pushCellSkill(150 + i * 2, "smog", cellPosIdx++, (BYTE)30, _skillAni8);
        //_effectManager->createEffect("smog", _vSkillCellPos[cellPosIdx++], 10, false, 250, 210, 10.0f);
	}

	for (int i = 0; i < skillArr2; ++i)//
	{
		if (i % 2 == 1)						pushCellSkill(150 + i * 2, "groundCrack", cellPosIdx++, (BYTE)10, _skillAni9);
        else if (i % 2 == 0)				pushCellSkill(150 + i * 2, "groundCrackL", cellPosIdx++, (BYTE)10, _skillAni10);
        //if (i % 2 == 1)						 _effectManager->createEffect("groundCrack", _vSkillCellPos[cellPosIdx++], 8, false, 230, 200, 10.0f);
        //else if (i % 2 == 0)				 _effectManager->createEffect("groundCrackL", _vSkillCellPos[cellPosIdx++], 8, false, 230, 200, 10.0f);
    
    }

	//enemy Effect - 검출후에 리스트에 수 넣고 사이즈 잰 이후에 업데이트에서 구현 필요 일단 1개로
	for (int i = 0; i < 1; ++i)
	{
		pushCellSkill(180, "one", cellPosIdx++, (BYTE)30, _skillAni11);
	}

	for (int i = 0; i < 1; ++i)
	{
		pushCellSkill(210, "95light", cellPosIdx++, (BYTE)30, _skillAni12);
	}

	for (int i = 0; i < 1; ++i)
	{
		pushCellSkill(210, "48fire", cellPosIdx++, (BYTE)30, _skillAni13);
	}

	for (int i = 0; i < 1; ++i)
	{
		pushCellSkill(230, "enemyAttack", cellPosIdx++, (BYTE)30, _skillAni14);
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
            SOUNDMANAGER->play(_vSkySoundName[_soundIndex], 1.0f);
            _isPlay = false;
        }

        if (_soundIndex < 5 && SOUNDMANAGER->getPosition(_vSkySoundName[_soundIndex]) == SOUNDMANAGER->getLength(_vSkySoundName[_soundIndex]))
        {
            SOUNDMANAGER->play(_vSkySoundName[++_soundIndex], 1.0f);
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

void Skill::pushCellSkill(int idx,string imgKey, int vNum, BYTE alpha,Animation* anim)//알파값 이상함
{
	tagSkill skill = tagSkill(idx, imgKey, &_vSkillCellPos[vNum], &_skillAlpha, anim);

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