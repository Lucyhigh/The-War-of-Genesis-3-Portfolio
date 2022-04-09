#include "Stdafx.h"
#include "UniteSkill.h"

HRESULT UniteSkill::init(void)
{
	return S_OK;
}

void UniteSkill::release(void)
{
	for (viSkillList = vSkillList.begin(); viSkillList != vSkillList.end(); ++viSkillList)
	{
		Skill* skill = (*viSkillList);
		SAFE_DELETE(skill);
	}
}

void UniteSkill::update(void)
{
	if (!_isStart) return;
	for (viSkillList = vSkillList.begin(); viSkillList != vSkillList.end(); ++viSkillList)
	{
		Skill* skill = (*viSkillList);
		if (skill->getSkillIndex() == _skillIndex)
		{
			skill->getSkillAnimation()->AniStart();
		}
	}
	_skillIndex++;
}

void UniteSkill::render(void)
{
	if (!_isStart) return;
	for (viSkillList = vSkillList.begin(); viSkillList != vSkillList.end(); ++viSkillList)
	{
		Skill* skill = (*viSkillList);
		if (skill->getSkillAnimation()->getIsPlay() == false)
			continue;

		IMAGEMANAGER->findImage(skill->getSkillName())->aniRender(getMemDC(),
																  skill->getAniPosRect()->left,
																  skill->getAniPosRect()->top,
																  skill->getSkillAnimation());
	}
}

void UniteSkill::startSkill()
{
	_isStart = true;
}

void UniteSkill::add(Skill* skill)
{
	vSkillList.push_back(skill);
}
