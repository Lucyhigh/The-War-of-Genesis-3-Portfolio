#include "Stdafx.h"
#include "TurnSystem.h"

HRESULT TurnSystem::init(void)
{
	_playerbit = 0;	 //0은 대기(턴 맨 처음)
	_enemybit = 0;	 //0은 대기
	_changingStatus = CHANGINGSTATUS::PLAYERTURN;
	return S_OK;
}

void TurnSystem::release(void)
{
   
}

void TurnSystem::update(void)
{
    switch (_changingStatus)//걍 스위치 두개로만 해도됨
    {
    case CHANGINGSTATUS::WAIT :
            break;
    case CHANGINGSTATUS::PLAYERTURN :

            break;
           
    case CHANGINGSTATUS::ENEMYTURN :
            break;

    }
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
    _enemybit.reset();
	_changingStatus = CHANGINGSTATUS::PLAYERTURN;
	cout << (int)_changingStatus << endl;
}

void TurnSystem::changeToEnemy()
{
    _playerbit.reset();
	_enemybit.reset();
	_changingStatus = CHANGINGSTATUS::ENEMYTURN;
	cout << (int)_changingStatus << endl;
}

unsigned int TurnSystem::getPlayerBit(int index)
{
	return _playerbit[index];
}

unsigned int TurnSystem::getEnemyBit(int index)
{
	return _enemybit[index];
}

void TurnSystem::setPlayerBit(int index)
{
	_playerbit.reset();
	_playerbit.set(index);
}

void TurnSystem::setEnemyBit(int index)
{
	_enemybit.reset();
	_enemybit.set(index);
}

CHANGINGSTATUS TurnSystem::getStatus()
{
    return CHANGINGSTATUS();
}

void TurnSystem::setStatus(CHANGINGSTATUS state)
{
	_changingStatus = state;
}
