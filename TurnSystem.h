#pragma once
#include "GameNode.h"

enum class CHANGINGSTATUS
{
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

	unsigned int getPlayerBit(int index);
	unsigned int getEnemyBit(int index);
	void setPlayerBit(int index);
	void setEnemyBit(int index);

	unsigned int isPlayerIdle();
	unsigned int isEnemyIdle();

    CHANGINGSTATUS getStatus();
    void setStatus(CHANGINGSTATUS state);
public:
	TurnSystem (){}
	~TurnSystem(){}
};