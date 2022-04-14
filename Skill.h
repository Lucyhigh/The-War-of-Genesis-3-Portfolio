#pragma once
#include "GameNode.h"
#include "Animation.h"
#include "Cell.h"
#include "Player.h"
#include "Camera.h"

struct tagWindSkill
{
	string imgKey;
	int frameX;
	int frameY;
	int posX;
	int posY;
	BYTE alpha;
};

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
    vector<tagSkill> vSkillList;
    vector<tagSkill>::iterator viSkillList;
    int _skillIndex;
	int _soundIndex;
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

	vector<tagWindSkill> _vWindSkill;

	vector<string> _vSkySoundName;
	vector<string> _vWindSoundName;
	int _count;
	float _cdt;

	int _alphaA;
	int _alphaB;
    int _windSkillTick;
    int _windSkillCnt;
    int _windSkillIndex;
public:
	int getSkillIndex() { return _skillIndex; }
    void startSkill();
    void setPlayer(Player* player);
    void setCamera(Camera* camera);
    void setCells(vector<Cell*>* cells);
	void pushCellSkill(int idx, string imgKey, int vNum, BYTE alpha, Animation* anim);

    void reset();
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void worldBrokenSkill();
	void windEyun();

public:
    Skill() {}
	~Skill() {}
};