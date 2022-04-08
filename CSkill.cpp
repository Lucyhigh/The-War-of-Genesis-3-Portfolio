#include "Stdafx.h"
#include "CSkill.h"

void CSkill::release(void)
{
}

void CSkill::update(void)
{
    //if (_leftButtonDwon) _direction == BUTTON_DIRECTION_DOWN;
        //else if ()
        //{
        //	if(_callBackFunction != nullptr) _callBackFunction();
        //}
    if ()
    {
        //호출시점알려주기
        //이벤트처리를한다 - 언제 운영처리에게 알려주고 돌아올건지
        //스킬스타트 0~10번까지 이벤트 끝 10
        //아웃풋이 정해져있을때 
        //메인업데이트는 돌아가지만 대리자를 통해 빨리 처리할수있게
        //이후 처리후 대기모드로 다시 돌림
        //
    }
    else
    {
        _skillIndexNum = SKILL_INDEX_NULL;
    }
}

void CSkill::render(void)
{
}

bool IsAttackIndex(void)
{
    if (_behavior == SKILL_INDEX_NUMBER::SKILL_INDEX_SECOND)
    {
        if (_currentAnimation->getNowPlayIdx() == _attackIndex)
            return true;
    }
    return false;
}