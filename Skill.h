#pragma once
#include "Animation.h"
class Skill
{
private:
	int _skillIndex;
	Animation* _efxAnimation;
public:
	Skill(int skillIndex, Animation* animation);
	~Skill() {}
};