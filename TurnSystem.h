#pragma once
#include "GameNode.h"

enum class CHANGINGSTATUS
{
	WAIT,//���ĥ��
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

   	// 0000 0000 : �̵����
   	// 0000 0001 : �޴�â��
    // 0000 0010 : ���ݸ�ǹߵ�
    // 0000 0100 : �ǰݸ�ǹߵ�
    // 0000 1000 : �̵���
    // 0001 0000 : ��ų (��ü��ų)
    // 0010 0000 : ��ų (�Ѹ�ų)
    // 0100 0000 : ȸ��(�޽� �� �ϳѱ�)
    // 1000 0000 : ����
	//Ȥ��
	//0001 0000 : ��ų (��ü��ų)
	//0001 0001 : ��ų (��ü��ų)
#pragma endregion
#pragma region enemy status

// 0000 0000 : �̵����
// 0000 0001 : �̵���
// 0000 0010 : ���ݸ�ǹߵ�
// 0000 0100 : �ǰݸ�ǹߵ�
// 0000 1000 : 
// 0001 0000 : ��ų (��ü��ų)
// 0010 0000 : ��ų (�Ѹ�ų)
// 0100 0000 : ȸ��(�޽� �� �ϳѱ�)
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

