#include "Stdafx.h"
#include "Skill.h"

Skill::Skill(int skillIndex, string skillName, POINT* aniPos, BYTE* alpha, Animation* animation)
{
	_skillIndex = skillIndex;
	_skillName = skillName;
	_aniPos = aniPos;
    _alpha = alpha;
	_skillAnimation = animation;
}

HRESULT Skill::init(void)
{
	_player = new Player;
	_playerPos = { _player->getPlayerRect().left, _player->getPlayerRect().top };
	
	_skillAlpha = (BYTE)40;
	_skillAlpha2 = (BYTE)40;
	_skillAlpha3 = (BYTE)50;

	_alphaA = 0;
	_alphaB = 0;
	return S_OK;
}

void Skill::release(void)
{
	_player->release();
	SAFE_DELETE(_player);
}

void Skill::update(void)
{
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
	IMAGEMANAGER->alphaRender("cutChange", getMemDC(), 0, 0, _alphaA);
	IMAGEMANAGER->alphaRender("cutChangeRed", getMemDC(), 0, 0, _alphaB);
}

void Skill::worldBrokenSkill()
{
	if (_alphaA < 160)_alphaA += 10;
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
	Skill* skill = new Skill(0, "184light", &_skillPlayerPos, &_skillAlpha, _skillAni1);
	Skill* skill2 = new Skill(3, "circle", &_skillPlayerPos2, &_skillAlpha2, _skillAni2);
	Skill* skill3 = new Skill(4, "smog2", &_skillPlayerPos3, &_skillAlpha3, _skillAni3);



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

	uniteSkill.add(skill);
	uniteSkill.add(skill2);
	uniteSkill.add(skill3);
	/*
		uniteSkill.add(skill3);
		uniteSkill.add(skill4);
		uniteSkill.add(skill6);
		uniteSkill.add(skill7);
		uniteSkill.add(skill8);
		uniteSkill.add(skill10);*/
	uniteSkill.startSkill();
}
