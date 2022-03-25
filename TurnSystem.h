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

#pragma region playerbit status

   	// 0000 0000 : 대기
   	// 0000 0001 : 이동중
    // 0000 0010 : 공격모션발동
    // 0000 0100 : 피격모션발동
    // 0000 1000 : 턴넘김
    // 0001 0000 : 스킬 (전체스킬)
    // 0010 0000 : 스킬 (한명스킬)
    // 0100 0000 : 
    // 1000 0000 : 죽음
#pragma endregion
#pragma region enemy status

// 0000 0000 : 대기
// 0000 0001 : 이동중
// 0000 0010 : 공격모션발동
// 0000 0100 : 피격모션발동
// 0000 1000 : 턴넘김
// 0001 0000 : 스킬 (전체스킬)
// 0010 0000 : 스킬 (한명스킬)
// 0100 0000 : 
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

    CHANGINGSTATUS getStatus();
    void setStatus(CHANGINGSTATUS state);
public:
	TurnSystem() {}
	~TurnSystem(){}
};

