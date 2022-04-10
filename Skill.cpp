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
