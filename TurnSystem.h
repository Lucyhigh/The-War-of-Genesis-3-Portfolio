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

   	// 0000 0000 : ���
   	// 0000 0001 : �̵���
    // 0000 0010 : ���ݸ�ǹߵ�
    // 0000 0100 : �ǰݸ�ǹߵ�
    // 0000 1000 : �ϳѱ�
    // 0001 0000 : ��ų (��ü��ų)
    // 0010 0000 : ��ų (�Ѹ�ų)
    // 0100 0000 : 
    // 1000 0000 : ����
#pragma endregion
#pragma region enemy status

// 0000 0000 : ���
// 0000 0001 : �̵���
// 0000 0010 : ���ݸ�ǹߵ�
// 0000 0100 : �ǰݸ�ǹߵ�
// 0000 1000 : �ϳѱ�
// 0001 0000 : ��ų (��ü��ų)
// 0010 0000 : ��ų (�Ѹ�ų)
// 0100 0000 : 
// 1000 0000 : ����
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

