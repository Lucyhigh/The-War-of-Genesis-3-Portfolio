#pragma once
#include "GameNode.h"
#include "Cell.h"
#include "Player.h"
#include "Saladin.h"
#include "Camera.h"
#include "EffectManager.h"

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
    BYTE _alpha;
	int _fps;

    tagSkill() {}
    tagSkill(int skillIndex, string skillName, POINT* aniPos, BYTE alpha,int fps) //, Animation* animation
    {
        _skillIndex = skillIndex;
        _skillName = skillName;
        _aniPos = aniPos;
        _alpha = alpha;
		_fps = fps;
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

    EffectManager* _effectManager;
    Player* _player;
	Saladin* _saladin;
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

	vector<string> _vWorldSoundName;
	vector<string> _vWindSoundName;
	int _count;
	float _cdt;

	int _alphaA;
	int _alphaB;
    int _windSkillTick;
    int _windSkillCnt;
    int _windSkillIndex;
	bool _isPlay;
public:
	int getSkillIndex() { return _skillIndex; }
    void startSkill();
    void setPlayer(Player* player);
    void setSaladin(Saladin* saladin);
    void setCamera(Camera* camera);
    void setCells(vector<Cell*>* cells);
	void pushCellSkill(int idx, string imgKey, int vNum, BYTE alpha, int fps);

    void reset();
	HRESULT init(void);
	void release(void);
	void update(void);
	void worldrender(void);
	void windRender(void);
	void worldBrokenSkill();
	void windEyun();
	void setplaySound(bool isPlay);
	void playSound();

public:
    Skill() {}
	~Skill() {}
};