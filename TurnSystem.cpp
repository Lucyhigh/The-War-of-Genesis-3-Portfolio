#include "Stdafx.h"
#include "TurnSystem.h"

HRESULT TurnSystem::init(void)
{
	_playerbit = 0;	 //0�� ���(�� �� ó��)
	_enemybit = 0;	 //0�� ���
	return S_OK;
}

void TurnSystem::release(void)
{

}

void TurnSystem::update(void)
{

}

void TurnSystem::render(void)
{

}

void TurnSystem::changeState()
{
}

void TurnSystem::changeToPlayer()
{
	_playerbit.reset();
	_changingStatus = CHANGINGSTATUS::PLAYERTURN;
}

void TurnSystem::changeToEnemy()
{
	_enemybit.reset();
	_changingStatus = CHANGINGSTATUS::ENEMYTURN;
}
