#pragma once
#include "Animation.h"
class Skill
{
private:
	int _skillIndex;
	string _skillName;
    POINT* _aniPos;
    BYTE* _alpha;
	Animation* _skillAnimation;
public:
    inline int getSkillIndex()            { return _skillIndex; }
    inline string getSkillName()          { return _skillName; }
    inline POINT* getAniPos()             { return _aniPos; }
    inline BYTE* getAlpha()                { return _alpha; }
    inline Animation* getSkillAnimation() { return _skillAnimation; }
public:
	Skill(int skillIndex,string skillName, POINT* aniPos, BYTE* alpha, Animation* animation);
	~Skill() {}
};