#include "Stdafx.h"
#include "UniteSkill.h"

HRESULT UniteSkill::init(void)
{
	return S_OK;
}

void UniteSkill::release(void)
{
}

void UniteSkill::update(void)
{
	if (!_isStart) return;
	//for(viSkillList)
	//if (_behavior == SKILL_INDEX_NUMBER::SKILL_INDEX_SECOND)
	//{
	// if (_currentAnimation->getNowPlayIdx() == _attackIndex)
	//	 return true;
	//}
}

void UniteSkill::render(void)
{
	if (!_isStart) return;
}

void UniteSkill::startSkill()
{
	_isStart = true;
}

void UniteSkill::add(Skill* skill)
{
	vSkillList.push_back(skill);
}
