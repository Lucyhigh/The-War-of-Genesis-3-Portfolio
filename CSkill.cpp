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
        //ȣ������˷��ֱ�
        //�̺�Ʈó�����Ѵ� - ���� �ó������ �˷��ְ� ���ƿð���
        //��ų��ŸƮ 0~10������ �̺�Ʈ �� 10
        //�ƿ�ǲ�� ������������ 
        //���ξ�����Ʈ�� ���ư����� �븮�ڸ� ���� ���� ó���Ҽ��ְ�
        //���� ó���� ������ �ٽ� ����
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