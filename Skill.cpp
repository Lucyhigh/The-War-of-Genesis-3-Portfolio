#include "Stdafx.h"
#include "Skill.h"

Skill::Skill(int skillIndex, string skillName, RECT* aniPosRect, Animation* animation)
{
	_skillIndex = skillIndex;
	_skillName = skillName;
	_aniPosRect = aniPosRect;
	_skillAnimation = animation;
}
