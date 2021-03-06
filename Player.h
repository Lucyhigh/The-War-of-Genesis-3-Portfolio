#pragma once
#include "GameNode.h"
#include "ProgressBar.h"
#include "Inventory.h"
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
	typedef bitset<6> playerBit;
	playerBit _stateBit;
	Image* _image;
	ProgressBar* _hpBar;
	RECT _rcPlayer;
	Cell* _playerCell;

    Inventory* _inventory;
	PLAYERSTATE _imageState;
    POINT _playerPos;
    RECT _cameraRect;
	
	int _tmp;
	int _cdt;
    int _speed;
	int _count;
    int _skillCount;
	int _indexA;
	int _indexB;
	int _worldIndex;
	int _windIndex;

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

	float getPlayerPosX();
	float getPlayerPosY();
	void setPlayerPos(POINT pos);
	void setPlayerPosX(float x);
    void setPlayerPosY(float y);

	ProgressBar* getPlayerHpBar() { return _hpBar; }
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
public:
	Player(){}
	~Player() {}
};
