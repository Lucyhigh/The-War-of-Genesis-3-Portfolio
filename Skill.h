#pragma once
#include "Animation.h"
class Skill
{
private:
	int _skillIndex;
	string _skillName;
	RECT* _aniPosRect;
	Animation* _skillAnimation;
public:
	inline int getSkillIndex()		{ return _skillIndex; }
	inline string getSkillName()	{return _skillName;}
	inline RECT* getAniPosRect()	{return _aniPosRect;}
	inline Animation* getSkillAnimation() 	{ return _skillAnimation;}
public:
	Skill(int skillIndex,string skillName, RECT* aniPosRect,Animation* animation);
	~Skill() {}
};