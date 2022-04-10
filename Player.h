#pragma once
#include "GameNode.h"
#include "ProgressBar.h"
#include "Inventory.h"
#include "UniteSkill.h"
#include "Skill.h"
#include "Cell.h"

enum class PLAYERSTATE
{
	RIGHT,
	LEFT,
	TOP,
	BOTTOM
};
class Player : public GameNode
{
private:
	typedef bitset<5> playerBit;
	playerBit _stateBit;
	Image* _image;
	ProgressBar* _hpBar;
	RECT _rcPlayer;
    Inventory* _inventory;
	PLAYERSTATE _imageState;
	UniteSkill uniteSkill;
	vector<Cell*>* _vSkillableCells;
    POINT _playerPos;
    POINT _skillPlayerPos;
    POINT _skillPlayerPos2;
    POINT _skillPlayerPos3;
	vector<POINT> _vSkillCellPos;
    RECT _cameraRect;
    BYTE _skillAlpha;
    BYTE _skillAlpha2;
    BYTE _skillAlpha3;

	int _tmp;
	int _cdt;
    int _speed;
	int _count;
	int _indexA;
	int _indexB;
	int _indexC;
	int _alphaA;
	int _alphaB;
	float _currentHp;
	float _maxHp;

	bool _isWaiting;
	bool _isAttack;
	bool _isDamage;
	bool _isLive;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void worldBrokenSkill();

	float getPlayerPosX();
	float getPlayerPosY();
	void setPlayerPos(POINT pos);
	void setPlayerPosX(float x);
    void setPlayerPosY(float y);

	RECT getPlayerRect();
    void setCameraRect(RECT rect);

	PLAYERSTATE getImageState();
	void setImageStage(PLAYERSTATE state);

    void setPlayerIdle();
    unsigned int getPlayerStateBit(int index);
	playerBit getPlayerStateBit();
    void setPlayerStateBit(int index);
	bool getWaiting();
	void setWaiting(bool isWaiting);

    bool getAttack();
    void setAttack(bool isAttack);
    bool getDamage();
    void setDamage(bool isDamage);

	bool getLive();
	bool setLive(bool status);

	void hitDamage(float damage);
	void setCells(vector<Cell*>* cells);
public:
	Player():_isWaiting(true),_isLive(true){}
	~Player() {}
};
