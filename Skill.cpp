#include "Stdafx.h"
#include "Skill.h"

HRESULT Skill::init(void)
{
	_playerPos = { _player->getPlayerRect().left, _player->getPlayerRect().top };
	_skillAlpha = (BYTE)10;
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

    //for (viSkillList = vSkillList.begin(); viSkillList != vSkillList.end(); ++viSkillList)
    //{
    //    tagSkill skill = (*viSkillList);
    //    SAFE_DELETE(skill);
    //}
}

void Skill::update(void)
{
    float left = _player->getPlayerRect().left - _camera->getScreenRect().left;
    float top = _player->getPlayerRect().top - _camera->getScreenRect().top;
    float cellLeft = _player->getPlayerRect().left-25 - _camera->getScreenRect().left;
    float cellTop = _player->getPlayerRect().top-215 - _camera->getScreenRect().top;

    _skillPlayerPos = { (long)left - 95, (long)top - 40 };
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
	int skillArr1 = 24;
	int skillArr2 = 72;
	int skillArr3 = 120;
    for (int i = 0; i < skillArr1; i += 4)
    {
		if (skillArr1 > i)
		{
			_vSkillCellPos[i]     = { (long)cellLeft - 20 * (i + 1), (long)cellTop - 16 * (i + 1) };//LT
			_vSkillCellPos[i + 2] = { (long)cellLeft + 20 * (i + 1), (long)cellTop + 16 * (i + 1) };//RB
			_vSkillCellPos[i + 1] = { (long)cellLeft - 20 * (i + 1), (long)cellTop + 16 * (i + 1) };//LB
			_vSkillCellPos[i + 3] = { (long)cellLeft + 20 * (i + 1), (long)cellTop - 16 * (i + 1) };//RT========== triple ����, �� ���������ʿ�
		}
    }

	for (int i = 0; i < 48; i += 4)
	{
		_vSkillCellPos[i + skillArr1]	  = { (long)cellLeft - 10 * (i + 1), (long)cellTop + 50 - 8 * (i + 1) };
		_vSkillCellPos[i + skillArr1 + 2] = { (long)cellLeft + 10 * (i + 1), (long)cellTop + 50 + 8 * (i + 1) };
		_vSkillCellPos[i + skillArr1 + 1] = { (long)cellLeft - 10 * (i + 1), (long)cellTop + 50 + 8 * (i + 1) };
		_vSkillCellPos[i + skillArr1 + 3] = { (long)cellLeft + 10 * (i + 1), (long)cellTop + 50 - 8 * (i + 1) };//========== fire 4���� ���������ʿ� / �����ź��� �������� �ʿ�
	}

	for (int i = 0; i < 48; i += 4)
	{
		_vSkillCellPos[i + skillArr2]	  = { (long)left- 60 - 10 * (i + 1), (long)top - 40 - 8 * (i + 1) };
		_vSkillCellPos[i + skillArr2 + 2] = { (long)left- 60 + 10 * (i + 1), (long)top - 40 + 8 * (i + 1) };
		_vSkillCellPos[i + skillArr2 + 1] = { (long)left- 60 - 10 * (i + 1), (long)top - 40 + 8 * (i + 1) };
		_vSkillCellPos[i + skillArr2 + 3] = { (long)left- 60 + 10 * (i + 1), (long)top - 40 - 8 * (i + 1) };//========== 48fire /�����ź��� �������� �ʿ�
	}
	for (int i = 0; i < 48; i += 4)
	{
		_vSkillCellPos[i + skillArr3] = { (long)left - 60 - 10 * (i + 1), (long)top - 40 - 8 * (i + 1) };
		_vSkillCellPos[i + skillArr3 + 2] = { (long)left - 60 + 10 * (i + 1), (long)top - 40 + 8 * (i + 1) };
		_vSkillCellPos[i + skillArr3 + 1] = { (long)left - 60 - 10 * (i + 1), (long)top - 40 + 8 * (i + 1) };
		_vSkillCellPos[i + skillArr3 + 3] = { (long)left - 60 + 10 * (i + 1), (long)top - 40 - 8 * (i + 1) };//========== groundCrack /�����ź��� �������� �ʿ�
	}
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
    if (!_isStart) return;
    for (viSkillList = vSkillList.begin(); viSkillList != vSkillList.end(); ++viSkillList)
    {
        tagSkill skill = (*viSkillList);
        if (skill._skillIndex == _skillIndex)
        {
            skill._skillAnimation->AniStart();
        }
    }
    _skillIndex++;
   
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

    tagSkill skill =  tagSkill{ 0, "184light", &_skillPlayerPos, &_skillAlpha, _skillAni1 };
    tagSkill skill2 = tagSkill{ 50, "circle", &_skillPlayerPos2, &_skillAlpha2, _skillAni2 };
    tagSkill skill3 = tagSkill{ 30, "smog2", &_skillPlayerPos3, &_skillAlpha3, _skillAni3 };    

    int cellPosIdx = 0;
	int skillArr1 = 24;
	int skillArr2 = 48;
	//��ü �ִϸ��̼� Ǫ�ù�
    for (int i = 0; i < 120; ++i) _vSkillCellPos.push_back({ 0,0 });
	
	Animation* _skillAni4 = ANIMATIONMANAGER->findAnimation("tripleR");
	Animation* _skillAni5 = ANIMATIONMANAGER->findAnimation("tripleL");
	Animation* _skillAni6 = ANIMATIONMANAGER->findAnimation("fire");
	Animation* _skillAni7 = ANIMATIONMANAGER->findAnimation("fireL");
	Animation* _skillAni8 = ANIMATIONMANAGER->findAnimation("48fire");
	Animation* _skillAni9 = ANIMATIONMANAGER->findAnimation("groundCrack");
	for (int i = 0; i < skillArr1; ++i)
    {
		if (i % 2 == 1 )					pushCellSkill(10, "tripleR", cellPosIdx++,240, _skillAni4);
		else if (i % 2 == 0)				pushCellSkill(10, "tripleL", cellPosIdx++,20, _skillAni5);
    }

	for (int i = 0; i < skillArr2; ++i)
	{
		if (i % 2 == 1)						pushCellSkill(40, "fire", cellPosIdx++, 70,_skillAni6);
		else if (i % 2 == 0)				pushCellSkill(40, "fireL", cellPosIdx++,100, _skillAni7);
	}

	for (int i = 0; i < skillArr2; ++i)
	{
		pushCellSkill(60, "48fire", cellPosIdx++, 100, _skillAni8);
	}


	//Skill* skill13 = new Skill(1, "one", &_skillPlayerPos, _skillAni12);//���� �� �ٸ���...
	//Skill* skill14 = new Skill(1, "double",  &_skillPlayerPos, _skillAni12);
	//Skill* skill3 = new Skill(2, "fire", &_skillPlayerPos, _skillAni4);//���ʺ��� ���� - ����ٰ� ĳ���� ���ֺ��� �ٽý��� 2 / 3
	//Skill* skill7 = new Skill(3, "48fire", &_skillPlayerPos, _skillAni7);
	//Skill* skill4 = new Skill(3, "smog", &_skillPlayerPos, _skillAni5);
	//Skill* skill11 = new Skill(20, "115stone", &_skillPlayerPos, _skillAni11);//�� Ƣ�� ������ �����
	//Skill* skill6 = new Skill(1, "enemyAttack", &_skillPlayerPos, _skillAni12);
	////skill13 = new Skill(2, "one", testRc, _skillAni12);//���ʹ̵� �� ����
	//Skill* skill8 = new Skill(3, "95light", &_skillPlayerPos, _skillAni8);
	//Skill* skill10 = new Skill(3, "203smog", &_skillPlayerPos, _skillAni10);//���� �ƺ�ȭ ��������- ���⼭ ���� ������
	//// skill11 = new Skill(20, "115stone", testRc, _skillAni11);//�� ���� Ƣ�� ������ �����

    vSkillList.push_back(skill);
    vSkillList.push_back(skill2);
    vSkillList.push_back(skill3);
    startSkill();
}

void Skill::pushCellSkill(int idx,string imgKey, int vNum, BYTE alpha,Animation* anim)//���İ� �̻���
{
	tagSkill skill = tagSkill(idx, imgKey, &_vSkillCellPos[vNum], &_skillAlpha, anim);

	vSkillList.push_back(skill);
}

void Skill::startSkill()
{
    _isStart = true;
    if (_alphaA < 160) _alphaA += 10;
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