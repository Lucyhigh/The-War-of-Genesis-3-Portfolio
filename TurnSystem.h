#pragma once
#include "GameNode.h"
#include <bitset>
enum class CHANGINGSTATUS
{
	WAIT,
	PLAYERTURN,
	ENEMYTURN
};
class TurnSystem : public GameNode
{
private:
	bitset<8> _playerbit;
	bitset<8> _enemybit;
	CHANGINGSTATUS _changingStatus;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void changeState();
	void changeToPlayer();
	void changeToEnemy();
public:
	TurnSystem() {}
	~TurnSystem(){}
};

