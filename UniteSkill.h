#pragma once
#include "GameNode.h"
#include "Animation.h"
#include "Skill.h"

class UniteSkill:public GameNode
{
private:
	vector<Skill*> vSkillList;
	vector<Skill*>::iterator viSkillList;
	int _skillIndex;
	bool _isStart;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void startSkill();
	void add(Skill* skill);
public:
	UniteSkill() :_isStart(false) {}
	~UniteSkill() {}
};

