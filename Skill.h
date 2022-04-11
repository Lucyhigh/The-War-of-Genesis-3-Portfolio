#pragma once
#include "GameNode.h"
#include "Animation.h"
#include "UniteSkill.h"
#include "Player.h"
#include "Cell.h"

class Skill: public GameNode
{
private:
	int _skillIndex;
	string _skillName;
	POINT* _aniPos;
	BYTE* _alpha;
	Animation* _skillAnimation;

	Player* _player;
	BYTE _skillAlpha;
	BYTE _skillAlpha2;
	BYTE _skillAlpha3;
	UniteSkill uniteSkill;
	vector<Cell*>* _vSkillableCells;
	vector<POINT> _vSkillCellPos;
	POINT _playerPos;
	POINT _skillPlayerPos;
	POINT _skillPlayerPos2;
	POINT _skillPlayerPos3;
	int _cdt;
	int _alphaA;
	int _alphaB;

public:
    int getSkillIndex()            { return _skillIndex; }
    string getSkillName()          { return _skillName; }
    POINT* getAniPos()             { return _aniPos; }
    BYTE* getAlpha()                { return _alpha; }
    Animation* getSkillAnimation() { return _skillAnimation; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void worldBrokenSkill();
	void setCells(vector<Cell*>* cells)
	{
		_vSkillableCells = cells;
	}
	/*
	스킬 1번
	.
	.
	.
	.	
	스킬 14번 이사...
	*/

public:
	Skill(int skillIndex,string skillName, POINT* aniPos, BYTE* alpha, Animation* animation);
	~Skill() {}
};