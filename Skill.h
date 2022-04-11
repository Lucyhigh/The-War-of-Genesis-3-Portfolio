#pragma once
#include "GameNode.h"
#include "Animation.h"
#include "Cell.h"
#include "Player.h"
#include "Camera.h"

class tagSkill
{
public:
    int _skillIndex;
    string _skillName;
    POINT* _aniPos;
    BYTE* _alpha;
    Animation* _skillAnimation;
    tagSkill() {}
    tagSkill(int skillIndex, string skillName, POINT* aniPos, BYTE* alpha, Animation* animation) 
    {
        _skillIndex = skillIndex;
        _skillName = skillName;
        _aniPos = aniPos;
        _alpha = alpha;
        _skillAnimation = animation;
    }
    ~tagSkill() {}
};

class Skill: public GameNode
{
private:
    tagSkill* _tagSkill;
    vector<tagSkill*> vSkillList;
    vector<tagSkill*>::iterator viSkillList;
    int _skillIndex;
    bool _isStart;

    Player* _player;
    Camera* _camera;
	BYTE _skillAlpha;
	BYTE _skillAlpha2;
	BYTE _skillAlpha3;
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
    int getSkillIndex()            { return _tagSkill->_skillIndex; }
    string getSkillName()          { return _tagSkill->_skillName; }
    POINT* getAniPos()             { return _tagSkill->_aniPos; }
    BYTE* getAlpha()                { return _tagSkill->_alpha; }
    Animation* getSkillAnimation() { return _tagSkill->_skillAnimation; }

    void startSkill();
    void add(tagSkill* skill);
    void setPlayer(Player* player);
    void setCamera(Camera* camera);
    void setCells(vector<Cell*>* cells);

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void worldBrokenSkill();

	/*
	스킬 1번
	.
	.
	.
	.	
	스킬 14번 이사...
	*/

public:
    Skill() {}
	~Skill() {}
};