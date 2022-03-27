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
	//다른 창 열었을 때 비트를 정해주는게 좋을려나 해보면서 조절하기
	//
	//
#pragma endregion
#pragma region enemy status

// 0000 0000 : 적1
// 0000 0001 : 적2
// 0000 0010 : 적3
// 0000 0100 : 적4
// 0000 1000 : 적...
// 0001 0000 : 적
// 0010 0000 : 적
// 0100 0000 : 적
// 1000 0000 : 적
    //적 죽었을 경우엔 인덱스수의 비트는 키지않도록 함
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

