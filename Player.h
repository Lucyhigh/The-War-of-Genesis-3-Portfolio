#pragma once
#include "GameNode.h"
#include "ProgressBar.h"
#include "Inventory.h"
//#include "Camera.h"

class Player : public GameNode
{
private:
	Image* _image;
	ProgressBar* _hpBar;
	RECT _rcPlayer;
    Inventory* _inventory;

    POINT _playerPos;

    RECT _cameraRect;

    int _speed;
	int _count;
	int _indexA;
	int _indexB;
	int _indexC;
	int _alphaA;
	float _currentHp;
	float _maxHp;

	bool _isLeft;
	bool _isWaiting;
	bool _isLive;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	float getPlayerPosX();
	float getPlayerPosY();
	void setPlayerPosX(float x);
    void setPlayerPosY(float y);

	RECT getPlayerRect();
    void setCameraRect(RECT rect);



	bool getLeft();
	bool getWaiting();
	bool getLive();
	bool setLive(bool status);

	void hitDamage(float damage);
	
public:
	Player():_isLeft(false),_isWaiting(true),_isLive(true){}
	~Player() {}
};
