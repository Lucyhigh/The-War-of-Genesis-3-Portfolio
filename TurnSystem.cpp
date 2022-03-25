#include "Stdafx.h"
#include "TurnSystem.h"

HRESULT TurnSystem::init(void)
{
	_playerbit = 0;	 //0은 대기(턴 맨 처음)
	_enemybit = 0;	 //0은 대기
	return S_OK;
}

void TurnSystem::release(void)
{
   
}

void TurnSystem::update(void)
{
    switch (_changingStatus)
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
}

void TurnSystem::changeToEnemy()
{
    _playerbit.reset();
	_enemybit.reset();
	_changingStatus = CHANGINGSTATUS::ENEMYTURN;
}

CHANGINGSTATUS TurnSystem::getStatus()
{
    return CHANGINGSTATUS();
}

void TurnSystem::setStatus(CHANGINGSTATUS state)
{
}
