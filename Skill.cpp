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

	_count = 10;
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
	}

	string windPath = "Resources/Sounds/wind/";
	_vWindSoundName = getFilesInDirectory(windPath, "*.mp3");
	for (string name : _vWindSoundName)
	{
		SOUNDMANAGER->addSound(name, windPath + name, false, false);
	}

	return S_OK;
}

void Skill::release(void)
{
}

void Skill::update(void)
{
    if (_player->getPlayerStateBit(3) == 1)
    {
		SOUNDMANAGER->play(_vSkySoundName[_soundIndex], 1.0f);
        if (_alphaA < 80) _alphaA += 5;

        float left = _player->getPlayerRect().left - _camera->getScreenRect().left;
        float top = _player->getPlayerRect().top - _camera->getScreenRect().top;
        float cellLeft = _player->getPlayerRect().left - 20 - _camera->getScreenRect().left;
        float cellTop = _player->getPlayerRect().top - 185 - _camera->getScreenRect().top;

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
        //cout << _cdt << endl;

        if (!_isStart) return;
        for (viSkillList = vSkillList.begin(); viSkillList != vSkillList.end(); ++viSkillList)
        {
            tagSkill skill = (*viSkillList);
            if (skill._skillIndex == _skillIndex)
            {
                skill._skillAnimation->AniStart();
            }
            if (_skillIndex == 80 || _skillIndex == 210)
            {
                _camera->shakeStart(0.5f);
            }
        }
        if ((int)_cdt % 3 == 0) _skillIndex++;
    }
    else if (_player->getPlayerStateBit(4) == 1)
    {
        if (_alphaA < 200) _alphaA += 10;
		_cdt++;
		if (_count < _cdt)
		{
			_cdt = 0.0f;
			for (auto iter = _vWindSkill.begin(); iter != _vWindSkill.end();)
			{
				Image* img = IMAGEMANAGER->findImage(iter->imgKey);

                if (iter->frameX != img->getMaxFrameX())
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
        if (!_isStart) return;
        for (viSkillList = vSkillList.begin(); viSkillList != vSkillList.end(); ++viSkillList)
        {
            tagSkill skill = (*viSkillList);
            if (skill._skillAnimation->getIsPlay() == false) continue;

            IMAGEMANAGER->findImage(skill._skillName)-> aniAlphaRender(getMemDC(),
														skill._aniPos->x,
														skill._aniPos->y,
														*skill._alpha,
														skill._skillAnimation);
        }
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
	Animation* _skillAni6  = ANIMATIONMANAGER->findAnimation("fire");
	Animation* _skillAni7  = ANIMATIONMANAGER->findAnimation("fireL");
	Animation* _skillAni8  = ANIMATIONMANAGER->findAnimation("smog");
	Animation* _skillAni9  = ANIMATIONMANAGER->findAnimation("groundCrack");
	Animation* _skillAni10 = ANIMATIONMANAGER->findAnimation("groundCrackL");
	Animation* _skillAni11 = ANIMATIONMANAGER->findAnimation("one");
	Animation* _skillAni12 = ANIMATIONMANAGER->findAnimation("95light");
	Animation* _skillAni13 = ANIMATIONMANAGER->findAnimation("48fire");
	Animation* _skillAni14 = ANIMATIONMANAGER->findAnimation("enemyAttack");

	for (int i = 0; i < skillArr1; ++i)
    {
		if (i % 2 == 1 )					pushCellSkill(90, "tripleR", cellPosIdx++, _skillAlpha, _skillAni4);
		else if (i % 2 == 0)				pushCellSkill(90, "tripleL", cellPosIdx++, _skillAlpha, _skillAni5);
    }

	for (int i = 0; i < skillArr2; ++i)
	{
		if (i % 2 == 1)						pushCellSkill(120, "fire", cellPosIdx++, (BYTE)10,_skillAni6);
		else if (i % 2 == 0)				pushCellSkill(120, "fireL", cellPosIdx++, (BYTE)10, _skillAni7);
	}

	for (int i = 0; i < skillArr2; ++i)
	{
		pushCellSkill(150, "smog", cellPosIdx++, (BYTE)30, _skillAni8);
	}

	for (int i = 0; i < skillArr2; ++i)
	{
		if (i % 2 == 1)						pushCellSkill(150, "groundCrack", cellPosIdx++, (BYTE)10, _skillAni9);
		else if (i % 2 == 0)				pushCellSkill(150, "groundCrackL", cellPosIdx++, (BYTE)10, _skillAni10);
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
    //오른쪽기준으로 맞춤
	string skillArr[14] = { "184light" ,"skill10R", "skill8", "skill9", "skill4R","skill10R", "skill7", "skill8", "skill9", "184light", "skill7","skill8","skill9","skill3" };
    POINT skillPosArr[14] =
    {
		{left ,		 top },		// "184light"
		{left + 50,  top + 60},	// "skill10R"
		{left + 40 , top - 10}, // "skill8",
		{left + 40,  top - 10}, // "skill9",
		{left + 40,  top},		// "skill4R",
		{left + 50,  top + 60}, // "skill10R"
		{left + 40 , top - 10}, // "skill7",
		{left + 40 , top - 10}, // "skill8",
		{left + 40,  top - 10}, // "skill9", 
		{left ,		 top + 30},	// "184light"
		{left + 40 , top - 10}, // "skill7"	
		{left + 40 , top - 10}, // "skill8"	
		{left + 40,  top - 10}, // "skill9" 
		{left + 60,  top}		// "skill3" 
    };			
	BYTE skillAlpha[14] = { 180,255,140,180,220,220,140,140,200,180,140,140,180,255 };
    switch(_player->getImageState())
    {
    case PLAYERSTATE::RIGHT:
		skillArr[1] = { "skill10R" };
		skillArr[4] = {  "skill4R" };
		skillArr[5] = { "skill10R" };
        break;
    case PLAYERSTATE::LEFT:
		skillArr[1] = { "skill10L" };
		skillArr[4] = {  "skill4L" };
		skillArr[5] = { "skill10L" };
        break;
    case PLAYERSTATE::TOP:
		skillArr[1] = { "skill10T" };
		skillArr[4] = {  "skill4T" };
		skillArr[5] = { "skill10T" };
        break;
    case PLAYERSTATE::BOTTOM:
		skillArr[1] = { "skill10B" };
		skillArr[4] = {  "skill4B" };
		skillArr[5] = { "skill10B" };
        break;
    }

    //BYTE skillAlpha[11];
	_windSkillCnt++;
	if (_windSkillCnt > _windSkillTick &&_windSkillIndex <= 13)
	{
		_windSkillCnt = 0;
		if (_windSkillIndex > 13) return;
		tagWindSkill skill = tagWindSkill{ skillArr[_windSkillIndex],0,0,
                                           (int)skillPosArr[_windSkillIndex].x,
                                           (int)skillPosArr[_windSkillIndex].y,skillAlpha[_windSkillIndex++] };
		_vWindSkill.push_back(skill);
	

		if (_windSkillIndex == 1) _windSkillTick = 85;//
        else if (_windSkillIndex == 2 || _windSkillIndex == 3) _windSkillTick = 30;
        else if (_windSkillIndex == 4 || _windSkillIndex == 5) _windSkillTick = 10;
        else if (_windSkillIndex == 6|| _windSkillIndex == 7) _windSkillTick = 10;
        else if (_windSkillIndex == 8 || _windSkillIndex == 9 || _windSkillIndex == 10 || _windSkillIndex == 11) _windSkillTick = 30;
        else if (_windSkillIndex == 12) _windSkillTick = 10;
        else if (_windSkillIndex == 13) _windSkillTick = 10;
	
        if (_windSkillIndex == 4 || _windSkillIndex == 7 || _windSkillIndex == 11)
        {
            _alphaB = 110;
        }
        else _alphaB = 0;
	}
}

void Skill::setplaySound(bool isPlay)
{
	_isPlay = isPlay;
}

void Skill::playSound()
{
	if (_player->getPlayerStateBit(3) == 1)
	{

	}
	else if (_player->getPlayerStateBit(4) == 1)
	{
		if (_isPlay)
		{
			SOUNDMANAGER->play(_vWindSoundName[_soundIndex], 1.0f);
			_isPlay = false;
		}
		if (SOUNDMANAGER->getPosition(_vWindSoundName[_soundIndex]) == SOUNDMANAGER->getLength(_vWindSoundName[_soundIndex]))
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
    _cdt = 0;
    _windSkillIndex = 0;
    _windSkillTick = 20;
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