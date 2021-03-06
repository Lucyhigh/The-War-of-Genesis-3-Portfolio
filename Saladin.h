#pragma once
#include "GameNode.h"
#include "ProgressBar.h"

enum class SALADINSTATE
{
	RIGHT,
	LEFT,
	TOP,
	BOTTOM
};
class Saladin:public GameNode
{
private:
    bitset<5> _stateBit;
	Image* _image;
	ProgressBar* _hpBar;
	RECT _rcSaladin;
	SALADINSTATE _imageState;
	POINT _saladinPos;
	RECT _cameraRect;

	int _tmp;
	int _cdt;
	int _speed;
	int _count;
	int _indexA;
	int _indexB;
	int _indexC;
    int _worldIndex;
    int _skillCount;
	int _alphaA;
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

	ProgressBar* getEnemyHpBar() { return _hpBar; }

	float getSaladinPosX();
	float getSaladinPosY();
	void setSaladinPos(POINT pos);
	void setSaladinPosX(float x);
	void setSaladinPosY(float y);

	RECT getSaladinRect();
	void setCameraRect(RECT rect);

	SALADINSTATE getImageState();
	void setImageStage(SALADINSTATE state);

    void setEnemyIdle();
    unsigned int getEnemyStateBit(int index);
    void setEnemyStateBit(int index);

	bool getWaiting();

    bool getAttack();
    void setAttack(bool isAttack);
    bool getDamage();
    void setDamage(bool isDamage);

	bool getLive();

	void hitDamage(float damage);
	int getSkillCount() { return _skillCount; }

	bitset<5>* getstateBit() { return &_stateBit; }
public:
	Saladin() :_isWaiting(true), _isLive(true), _isAttack(false), _isDamage(false){}
	~Saladin() {}
};