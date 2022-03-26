#pragma once
#include "GameNode.h"

enum class CHANGINGSTATUS
{
	WAIT,//대사칠때
	PLAYERTURN,
	ENEMYTURN
};
class TurnSystem : public GameNode
{
private:
	bitset<8> _playerbit;
	bitset<8> _enemybit;
	CHANGINGSTATUS _changingStatus;

#pragma region playerbit status

   	// 0000 0000 : 이동대기
   	// 0000 0001 : 메뉴창염
    // 0000 0010 : 공격모션발동
    // 0000 0100 : 피격모션발동
    // 0000 1000 : 이동중
    // 0001 0000 : 스킬 (전체스킬)
    // 0010 0000 : 스킬 (한명스킬)
    // 0100 0000 : 회복(휴식 후 턴넘김)
    // 1000 0000 : 죽음
	//혹은
	//0001 0000 : 스킬 (전체스킬)
	//0001 0001 : 스킬 (전체스킬)
#pragma endregion
#pragma region enemy status

// 0000 0000 : 이동대기
// 0000 0001 : 이동중
// 0000 0010 : 공격모션발동
// 0000 0100 : 피격모션발동
// 0000 1000 : 
// 0001 0000 : 스킬 (전체스킬)
// 0010 0000 : 스킬 (한명스킬)
// 0100 0000 : 회복(휴식 후 턴넘김)
// 1000 0000 : 죽음
#pragma endregion

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

