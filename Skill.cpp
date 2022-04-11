#include "Stdafx.h"
#include "Skill.h"

HRESULT Skill::init(void)
{
	_playerPos = { _player->getPlayerRect().left, _player->getPlayerRect().top };
	_skillAlpha = (BYTE)40;
	_skillAlpha2 = (BYTE)40;
	_skillAlpha3 = (BYTE)50;
    _isStart = false;
    _skillIndex = 0;
	_alphaA = 0;
	_alphaB = 0;
    _skillPlayerPos = { 0,0 };
    _skillPlayerPos2 = { 0,0 };
    _skillPlayerPos3 = { 0,0 };
    worldBrokenSkill();

	return S_OK;
}

void Skill::release(void)
{
	//_player->release();
	//SAFE_DELETE(_player);

    for (viSkillList = vSkillList.begin(); viSkillList != vSkillList.end(); ++viSkillList)
    {
        tagSkill* skill = (*viSkillList);
        SAFE_DELETE(skill);
    }
}

void Skill::update(void)
{
    if(!_isStart) return;
    for (viSkillList = vSkillList.begin(); viSkillList != vSkillList.end(); ++viSkillList)
    {
        tagSkill* skill = (*viSkillList);
        if (skill->_skillIndex == _skillIndex)
        {
            skill->_skillAnimation->AniStart();
        }
    }
    _skillIndex++;

	_cdt++;
	if (_cdt == 10)
	{
		_alphaB = 200;
	}
	else _alphaB = 0;
	//cout << _cdt << endl;
}

void Skill::render(void)
{
    float left = _player->getPlayerRect().left -_camera->getScreenRect().left;
    float top = _player->getPlayerRect().top -_camera->getScreenRect().top;
    _skillPlayerPos  = { (long)left - 95, (long)top - 40 };
    _skillPlayerPos2 = { (long)left - 95, (long)top - 40 };
    _skillPlayerPos3 = { (long)left - 65, (long)top - 40 };

    Cell* playerCell = nullptr;
    for (auto cellsiter = _vSkillableCells->begin(); cellsiter != _vSkillableCells->end(); ++cellsiter)
    {
        if ((*cellsiter)->getType() == CELL_TYPE::START)
        {
            playerCell = (*cellsiter);
            break;
        }
    }

    int pCellPosNum = 1;
    for (int i = 0; i < _vSkillCellPos.size(); i += 4)
    {
        _vSkillCellPos[i] = { (long)(playerCell->getCellX() - 1)* TILESIZEX, (long)(playerCell->getCellY() - 1)* TILESIZEY };
        _vSkillCellPos[i + 1] = { (long)(playerCell->getCellX() - 1)* TILESIZEX, (long)(playerCell->getCellY() + 1)* TILESIZEY };
        _vSkillCellPos[i + 2] = { (long)(playerCell->getCellX() + 1)* TILESIZEX, (long)(playerCell->getCellY() - 1)* TILESIZEY };
        _vSkillCellPos[i + 3] = { (long)(playerCell->getCellX() + 1)* TILESIZEX, (long)(playerCell->getCellY() + 1)* TILESIZEY };
        pCellPosNum++;
    }
    if (!_isStart) return;
    for (viSkillList = vSkillList.begin(); viSkillList != vSkillList.end(); ++viSkillList)
    {
        tagSkill* skill = (*viSkillList);
        if (skill->_skillAnimation->getIsPlay() == false) continue;

        IMAGEMANAGER->findImage(skill->_skillName)->
                aniAlphaRender(getMemDC(),
                skill->_aniPos->x,
                skill->_aniPos->y,
                *skill->_alpha,
                skill->_skillAnimation);
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

    tagSkill* skill =  new tagSkill{ 0, "184light", &_skillPlayerPos, &_skillAlpha, _skillAni1 };
    tagSkill* skill2 = new tagSkill{ 10, "circle", &_skillPlayerPos2, &_skillAlpha2, _skillAni2 };
    tagSkill* skill3 = new tagSkill{ 20, "smog2", &_skillPlayerPos3, &_skillAlpha3, _skillAni3 };
   
    Animation* _skillAni12 = ANIMATIONMANAGER->findAnimation("triple");
    int cellPosIdx = 0;
    for (int i = 1; i < 5; ++i)
    {
        //Cell* cellLT = (*_vSkillableCells)[tempPosX - i + (tempPosY - i) * STAGE3TILEX];
        _vSkillCellPos.push_back({ 0,0 });// { cellLT->getCellX()*STAGE3TILEX, cellLT->getCellY()*STAGE3TILEY });
        tagSkill skillLT = { 1, "triple", &_vSkillCellPos[cellPosIdx++], &_skillAlpha, _skillAni12 };
        add(&skillLT);

        //Cell* cellLB = (*_vSkillableCells)[tempPosX - i + (tempPosY + i) * STAGE3TILEX];
        _vSkillCellPos.push_back({ 0,0 });//({ cellLB->getCellX()*STAGE3TILEX,cellLB->getCellY()*STAGE3TILEY });
        tagSkill skillLB = { 1, "triple", &_vSkillCellPos[cellPosIdx++], &_skillAlpha, _skillAni12 };
        //tagSkill* skillLB = new tagSkill(1, "triple", &_vSkillCellPos[cellPosIdx++], &_skillAlpha, _skillAni12);
        add(&skillLB);

        //Cell* cellRT = (*_vSkillableCells)[tempPosX + i + (tempPosY - i) * STAGE3TILEX];
        _vSkillCellPos.push_back({ 0,0 });//({ cellRT->getCellX()*STAGE3TILEX,cellRT->getCellY()*STAGE3TILEY });
        tagSkill skillRT = { 1, "triple", &_vSkillCellPos[cellPosIdx++], &_skillAlpha, _skillAni12 };
        //tagSkill* skillRT = new tagSkill(1, "triple", &_vSkillCellPos[cellPosIdx++], &_skillAlpha, _skillAni12);
        add(&skillRT);

        //Cell* cellRB = (*_vSkillableCells)[tempPosX + i + (tempPosY + i) * STAGE3TILEX];
        _vSkillCellPos.push_back({ 0,0 });//({ cellRB->getCellX()*STAGE3TILEX,cellRB->getCellY()*STAGE3TILEY });
        tagSkill skillRB = { 1, "triple", &_vSkillCellPos[cellPosIdx++], &_skillAlpha, _skillAni12 };
        //tagSkill* skillRB = new tagSkill(1, "triple", &_vSkillCellPos[cellPosIdx++], &_skillAlpha, _skillAni12);
        add(&skillRB);
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

	add(skill);
	add(skill2);
	add(skill3);
    startSkill();
	/*
		uniteSkill.add(skill3);
		uniteSkill.add(skill4);
		uniteSkill.add(skill6);
		uniteSkill.add(skill7);
		uniteSkill.add(skill8);
		uniteSkill.add(skill10);*/
}

void Skill::startSkill()
{
    _isStart = true;
    if (_alphaA < 160) _alphaA += 10;
}

void Skill::add(tagSkill* skill)
{
    vSkillList.push_back(skill);
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