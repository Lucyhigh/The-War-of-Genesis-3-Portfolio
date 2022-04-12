#include "Stdafx.h"
#include "Skill.h"

HRESULT Skill::init(void)
{
	_playerPos = { _player->getPlayerRect().left, _player->getPlayerRect().top };
	_skillAlpha = (BYTE)15;
	_skillAlpha2 = (BYTE)40;
	_skillAlpha3 = (BYTE)50;
    _isStart = false;
    _skillIndex = 0;
	_alphaA = 0;
	_alphaB = 0;
	_cdt = 0;
    _skillPlayerPos = { 0,0 };
    _skillPlayerPos2 = { 0,0 };
    _skillPlayerPos3 = { 0,0 };
    worldBrokenSkill();

	return S_OK;
}

void Skill::release(void)
{
}

void Skill::update(void)
{
    float left = _player->getPlayerRect().left - _camera->getScreenRect().left;
    float top = _player->getPlayerRect().top   - _camera->getScreenRect().top;
    float cellLeft = _player->getPlayerRect().left-20 - _camera->getScreenRect().left;
    float cellTop = _player->getPlayerRect().top-175 - _camera->getScreenRect().top;

    _skillPlayerPos = { (long)left - 95, (long)top - 40 };
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
			_vSkillCellPos[i]     = { (long)cellLeft - 20 * (i + 1), (long)cellTop - 16 * (i + 1) };//LT
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
		_vSkillCellPos[i + skillArr1 + 3] = { (long)cellLeft + 10 * (i + 1), (long)cellTop + 50 - 8 * (i + 1) };//========== fire 4가지 랜덤랜더필요 / 가까운거부터 먼저랜더 필요
	}

	for (int i = 0; i < 48; i += 4)
	{
		_vSkillCellPos[i + skillArr2]	  = { (long)left- 30 - 10 * (i + 1), (long)top - 10 - 8 * (i + 1) };
		_vSkillCellPos[i + skillArr2 + 2] = { (long)left- 30 + 10 * (i + 1), (long)top - 10 + 8 * (i + 1) };
		_vSkillCellPos[i + skillArr2 + 1] = { (long)left- 30 - 10 * (i + 1), (long)top - 10 + 8 * (i + 1) };
		_vSkillCellPos[i + skillArr2 + 3] = { (long)left- 30 + 10 * (i + 1), (long)top - 10 - 8 * (i + 1) };//========== smog /가까운거부터 먼저랜더 필요
	}
	for (int i = 0; i < 48; i += 4)
	{
		_vSkillCellPos[i + skillArr3]	  = { (long)left - 20 - 10 * (i + 1), (long)top + 10 - 8 * (i + 1) };
		_vSkillCellPos[i + skillArr3 + 2] = { (long)left - 20 + 10 * (i + 1), (long)top + 10 + 8 * (i + 1) };
		_vSkillCellPos[i + skillArr3 + 1] = { (long)left - 20 - 10 * (i + 1), (long)top + 10 + 8 * (i + 1) };
		_vSkillCellPos[i + skillArr3 + 3] = { (long)left - 20 + 10 * (i + 1), (long)top + 10 - 8 * (i + 1) };//========== groundCrack /가까운거부터 먼저랜더 필요 / 4가지 랜덤랜더필요 
	}
	POINT enemyPos = { (long)enemyCell->getCellX()*TILESIZEX -_camera->getScreenRect().left ,
					   (long)enemyCell->getCellY()*TILESIZEY -_camera->getScreenRect().top };
	for (int i = 0; i < 4; i += 4)
	{																																		 
		_vSkillCellPos[i + skillArr4]	  = { enemyPos.x - 30, enemyPos.y - 50 };																  //"one");
		_vSkillCellPos[i + skillArr4 + 1] = { enemyPos.x - 90, enemyPos.y - 80 };																  //"95light");
		_vSkillCellPos[i + skillArr4 + 2] = { enemyPos.x - 30, enemyPos.y - 50 };																  //"48fire");
		_vSkillCellPos[i + skillArr4 + 3] = { enemyPos.x - 30, enemyPos.y - 30 };//========== enemy /가까운거부터 먼저랜더 필요 / 4가지 랜덤랜더필요  //"enemyAttack");
	}
	_cdt++;
	if ( 200 <= _cdt && _cdt <= 230 )
	{
		_alphaB = 200;
	}
	else _alphaB = 0;
	cout << _cdt << endl;

	if (!_isStart) return;
	for (viSkillList = vSkillList.begin(); viSkillList != vSkillList.end(); ++viSkillList)
	{
		tagSkill skill = (*viSkillList);
		if (skill._skillIndex == _skillIndex)
		{
			skill._skillAnimation->AniStart();
		}
		if (skill._skillIndex == 80 || skill._skillIndex == 210)
		{
			_camera->shakeStart(0.5f);
		}
		cout<<skill._skillIndex << endl;
	}
	if (_cdt % 3 == 0) _skillIndex++;
}

void Skill::render(void)
{
    if (!_isStart) return;
    for (viSkillList = vSkillList.begin(); viSkillList != vSkillList.end(); ++viSkillList)
    {
        tagSkill skill = (*viSkillList);
        if (skill._skillAnimation->getIsPlay() == false) continue;

        IMAGEMANAGER->findImage(skill._skillName)->
                aniAlphaRender(getMemDC(),
                skill._aniPos->x,
                skill._aniPos->y,
                *skill._alpha,
                skill._skillAnimation);
    }

	IMAGEMANAGER->alphaRender("cutChange", getMemDC(), 0, 0, _alphaA);
	IMAGEMANAGER->alphaRender("cutChangeRed", getMemDC(), 0, 0, _alphaB);
}

void Skill::worldBrokenSkill()
{
	Animation* _skillAni1 = ANIMATIONMANAGER->findAnimation("184light");
	Animation* _skillAni2 = ANIMATIONMANAGER->findAnimation("circle");
	Animation* _skillAni3 = ANIMATIONMANAGER->findAnimation("smog2");

	//Animation* _skillAni4 = ANIMATIONMANAGER->findAnimation("fire");
	//Animation* _skillAni5 = ANIMATIONMANAGER->findAnimation("smog");
	//Animation* _skillAni7 = ANIMATIONMANAGER->findAnimation("48fire");
	//Animation* _skillAni8 = ANIMATIONMANAGER->findAnimation("95light");
	//Animation* _skillAni10 = ANIMATIONMANAGER->findAnimation("203smog");
	//Animation* _skillAni11 = ANIMATIONMANAGER->findAnimation("115stone");
	//Animation* _skillAni12 = ANIMATIONMANAGER->findAnimation("enemyAttack");
	//Animation* _skillAni13 = ANIMATIONMANAGER->findAnimation("one");
	//Animation* _skillAni14 = ANIMATIONMANAGER->findAnimation("double");

    tagSkill skill =  tagSkill{ 80, "184light", &_skillPlayerPos, &_skillAlpha, _skillAni1 };
    tagSkill skill2 = tagSkill{ 80, "circle", &_skillPlayerPos2, &_skillAlpha2, _skillAni2 };
    tagSkill skill3 = tagSkill{ 90, "smog2", &_skillPlayerPos3, &_skillAlpha3, _skillAni3 };    

    int cellPosIdx = 0;
	int skillArr1 = 24;
	int skillArr2 = 48;
	//전체 애니메이션 푸시백
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
		if (i % 2 == 1 )					pushCellSkill(100, "tripleR", cellPosIdx++, _skillAlpha, _skillAni4);
		else if (i % 2 == 0)				pushCellSkill(100, "tripleL", cellPosIdx++, _skillAlpha, _skillAni5);
    }

	for (int i = 0; i < skillArr2; ++i)
	{
		if (i % 2 == 1)						pushCellSkill(130, "fire", cellPosIdx++, (BYTE)10,_skillAni6);
		else if (i % 2 == 0)				pushCellSkill(130, "fireL", cellPosIdx++, (BYTE)10, _skillAni7);
	}

	for (int i = 0; i < skillArr2; ++i)
	{
		pushCellSkill(60, "smog", cellPosIdx++, (BYTE)30, _skillAni8);
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

	//Skill* skill13 = new Skill(1, "one", &_skillPlayerPos, _skillAni12);//셋이 다 다르넹...
	//Skill* skill14 = new Skill(1, "double",  &_skillPlayerPos, _skillAni12);
	//Skill* skill3 = new Skill(2, "fire", &_skillPlayerPos, _skillAni4);//왼쪽부터 시작 - 멈췄다가 캐릭터 위주부터 다시시작 2 / 3
	//Skill* skill7 = new Skill(3, "48fire", &_skillPlayerPos, _skillAni7);
	//Skill* skill4 = new Skill(3, "smog", &_skillPlayerPos, _skillAni5);
	//Skill* skill11 = new Skill(20, "115stone", &_skillPlayerPos, _skillAni11);//돌 튀어 오르며 사라짐
	//Skill* skill6 = new Skill(1, "enemyAttack", &_skillPlayerPos, _skillAni12);
	////skill13 = new Skill(2, "one", testRc, _skillAni12);//에너미도 셋 랜덤
	//Skill* skill8 = new Skill(3, "95light", &_skillPlayerPos, _skillAni8);
	//Skill* skill10 = new Skill(3, "203smog", &_skillPlayerPos, _skillAni10);//이후 컷변화 레드켜짐- 여기서 같이 돌릴가
	//// skill11 = new Skill(20, "115stone", testRc, _skillAni11);//돌 높이 튀어 오르며 사라짐

    vSkillList.push_back(skill);
    vSkillList.push_back(skill2);
    vSkillList.push_back(skill3);
    startSkill();
}

void Skill::pushCellSkill(int idx,string imgKey, int vNum, BYTE alpha,Animation* anim)//알파값 이상함
{
	tagSkill skill = tagSkill(idx, imgKey, &_vSkillCellPos[vNum], &_skillAlpha, anim);//_skillAlpha

	vSkillList.push_back(skill);
}

void Skill::startSkill()
{
    _isStart = true;
    if (_alphaA < 230) _alphaA += 10;
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