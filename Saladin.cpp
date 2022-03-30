#include "Stdafx.h"
#include "Saladin.h"

HRESULT Saladin::init(void)
{
	_image = IMAGEMANAGER->findImage("sDownIdle");
	_image = IMAGEMANAGER->findImage("sMovesheet");
	_image = IMAGEMANAGER->findImage("sDamageSheet");
    _stateBit = 0;//Idle
	_count = 0;
	_indexA = _indexB = _indexC= 0;
	_alphaA = 0;
	_speed = 5;
	_saladinPos.x = 0;
	_saladinPos.y = WINSIZE_Y - 140;
	_rcSaladin = RectMakeCenter(_saladinPos.x, _saladinPos.y, _image->getFrameWidth(), _image->getFrameHeight());
   
	_currentHp = 10;
	_maxHp = 10;
	//_hpBar = new ProgressBar;
	//_hpBar->init(280, WINSIZE_Y - 250, 52, 4);
	_imageState = SALADINSTATE::BOTTOM;
	return S_OK;
}

void Saladin::release(void)
{
}

void Saladin::update(void)
{
    _count += 4;
    
    //00000 대기 
    if (_stateBit.none() == 1)
    {
        switch (_imageState)
        {
        case SALADINSTATE::RIGHT:
            if (_count % 30 == 0)
            {
                _indexA--;
                IMAGEMANAGER->findImage("sRightIdle")->setFrameY(0);
                if (_indexA < 0)
                {
                    _indexA = 4;
                }
                IMAGEMANAGER->findImage("sRightIdle")->setFrameX(_indexA);
            }
            break;
        case SALADINSTATE::LEFT:
            if (_count % 30 == 0)
            {
                if (_isWaiting &&_count % 30 == 0)
                {
                    _indexA++;
                    IMAGEMANAGER->findImage("sLeftIdle")->setFrameY(1);
                    if (_indexA >= 4)
                    {
                        _indexA = 0;
                    }
                    IMAGEMANAGER->findImage("sLeftIdle")->setFrameX(_indexA);
                }
            }
            break;
        case SALADINSTATE::TOP:
            if (_count % 30 == 0)
            {
                _indexA--;
                IMAGEMANAGER->findImage("sUpIdle")->setFrameY(0);
                if (_indexA < 0)
                {
                    _indexA = 4;
                }
                IMAGEMANAGER->findImage("sUpIdle")->setFrameX(_indexA);
            }
            break;
        case SALADINSTATE::BOTTOM:
            if (_count % 30 == 0)
            {
                _indexA--;
                IMAGEMANAGER->findImage("sDownIdle")->setFrameY(0);
                if (_indexA < 0)
                {
                    _indexA = 4;
                }
                IMAGEMANAGER->findImage("sDownIdle")->setFrameX(_indexA);
            }
            break;
        }
    }
    //00001 이동중 
    else if (_stateBit.test(0) == 1)
    {
        switch (_imageState)
        {
        case SALADINSTATE::RIGHT:
            if (_count % 30 == 0)
            {
                _indexB--;
                IMAGEMANAGER->findImage("sMovesheet")->setFrameY(3);
                if (_indexB < 0)
                {
                    _indexB = 6;
                }
                IMAGEMANAGER->findImage("sMovesheet")->setFrameX(_indexB);
            }
            break;
        case SALADINSTATE::LEFT:
            if (_count % 30 == 0)
            {
                _indexB++;
                IMAGEMANAGER->findImage("sMovesheet")->setFrameY(2);
                if (_indexB >= 6)
                {
                    _indexB = 0;
                }
                IMAGEMANAGER->findImage("sMovesheet")->setFrameX(_indexB);
            }
            break;
        case SALADINSTATE::TOP:
            if (_count % 30 == 0)
            {
                _indexB++;
                IMAGEMANAGER->findImage("sMovesheet")->setFrameY(0);
                if (_indexB >= 6)
                {
                    _indexB = 0;
                }
                IMAGEMANAGER->findImage("sMovesheet")->setFrameX(_indexB);
            }
            break;
        case SALADINSTATE::BOTTOM:
            if (_count % 30 == 0)
            {
                _indexB++;
                IMAGEMANAGER->findImage("sMovesheet")->setFrameY(1);
                if (_indexB >= 6)
                {
                    _indexB = 0;
                }
                IMAGEMANAGER->findImage("sMovesheet")->setFrameX(_indexB);
            }
            break;
        }
    }
    //00010 공격 
    else if (_stateBit.test(1) == 1)
    {
        switch (_imageState)
        {
        case SALADINSTATE::RIGHT:
            if (_count % 30 == 0)
            {
                _indexC--;
                IMAGEMANAGER->findImage("sAttacksheet")->setFrameY(3);
                if (_indexC < 0)
                {
                    _indexC = 5;
                    _isAttack = true;
                    setEnemyIdle();
                    
                }
                IMAGEMANAGER->findImage("sAttacksheet")->setFrameX(_indexC);
            }
            break;
        case SALADINSTATE::LEFT:
            if (_count % 30 == 0)
            {
                _indexC++;
                IMAGEMANAGER->findImage("sAttacksheet")->setFrameY(2);
                if (_indexC >= 5)
                {
                    _indexC = 0;
                    _isAttack = true;
                    setEnemyIdle();
                }
                IMAGEMANAGER->findImage("sAttacksheet")->setFrameX(_indexC);
            }
            break;
        case SALADINSTATE::TOP:
            if (_count % 30 == 0)
            {
                _indexC++;
                IMAGEMANAGER->findImage("sAttacksheet")->setFrameY(0);
                if (_indexC >= 5)
                {
                    _indexC = 0;
                    _isAttack = true;
                    setEnemyIdle();
                }
                IMAGEMANAGER->findImage("sAttacksheet")->setFrameX(_indexC);
            }
            break;
        case SALADINSTATE::BOTTOM:
            if (_count % 30 == 0)
            {
                _indexC++;
                IMAGEMANAGER->findImage("sAttacksheet")->setFrameY(1);
                if (_indexC >= 5)
                {
                    _indexC = 0;
                    _isAttack = true;
                    setEnemyIdle();
                }
                IMAGEMANAGER->findImage("sAttacksheet")->setFrameX(_indexC);
            }
            break;
        }
        
    }
    //00100 피격 
    else if (_stateBit.test(2) == 1)
    {
        switch (_imageState)
        {
            case SALADINSTATE::RIGHT:
            {
                IMAGEMANAGER->findImage("sDamageSheet")->setFrameY(0);
                IMAGEMANAGER->findImage("sDamageSheet")->setFrameX(3);
            }
            break;
            case SALADINSTATE::LEFT:
            {
                IMAGEMANAGER->findImage("sDamageSheet")->setFrameY(2);
                IMAGEMANAGER->findImage("sDamageSheet")->setFrameX(2);
            }
            break;
            case SALADINSTATE::TOP:
            {
                IMAGEMANAGER->findImage("sDamageSheet")->setFrameY(0);
                IMAGEMANAGER->findImage("sDamageSheet")->setFrameX(0);
            }
            break;
            case SALADINSTATE::BOTTOM:
            {
                IMAGEMANAGER->findImage("sDamageSheet")->setFrameY(1);
                IMAGEMANAGER->findImage("sDamageSheet")->setFrameX(1);
            }
            break;
        }
        if (_count % 50 == 0) setEnemyIdle();//===============================================
        //01000 죽음
    }
     _rcSaladin = RectMakeCenter(_saladinPos.x, _saladinPos.y, _image->getFrameWidth(), _image->getFrameHeight());
}

void Saladin::render(void)
{
	float left = _rcSaladin.left - _cameraRect.left;
	float top = _rcSaladin.top - _cameraRect.top;

    if (_stateBit.none() == 1)
    {
        switch (_imageState)
        {
        case SALADINSTATE::RIGHT:
            IMAGEMANAGER->frameRender("sRightIdle", getMemDC(), left, top);
            break;
        case SALADINSTATE::LEFT:
            IMAGEMANAGER->frameRender("sLeftIdle", getMemDC(), left, top);
            break;
        case SALADINSTATE::TOP:
            IMAGEMANAGER->frameRender("sUpIdle", getMemDC(), left, top);
            break;
        case SALADINSTATE::BOTTOM:
            IMAGEMANAGER->frameRender("sDownIdle", getMemDC(), left, top);
            break;
        }
    }
    else if(_stateBit.test(0)==1)
    {
        POINT addMovePos = { -23,-20 };

        switch (_imageState)
        {
        case SALADINSTATE::RIGHT:
            {
                IMAGEMANAGER->frameRender("sMovesheet", getMemDC(), left + addMovePos.x, top + addMovePos.y);
            }
            break;
        case SALADINSTATE::LEFT:
            {
                IMAGEMANAGER->frameRender("sMovesheet", getMemDC(), left + addMovePos.x, top + addMovePos.y);
            }
            break;
        case SALADINSTATE::TOP:
            {
                IMAGEMANAGER->frameRender("sMovesheet", getMemDC(), left + addMovePos.x, top + addMovePos.y);
            }
            break;
        case SALADINSTATE::BOTTOM:
            {
                IMAGEMANAGER->frameRender("sMovesheet", getMemDC(), left + addMovePos.x, top + addMovePos.y);
            }
            break;
        }
    }
    else if (_stateBit.test(1) == 1)
    {
        POINT addAttPos = { -35,-40 };
        switch (_imageState)
        {
        case SALADINSTATE::RIGHT:
            {
                IMAGEMANAGER->frameRender("sAttacksheet", getMemDC(), left + addAttPos.x, top + addAttPos.y);
            }
            break;
        case SALADINSTATE::LEFT:
            {
                IMAGEMANAGER->frameRender("sAttacksheet", getMemDC(), left + addAttPos.x, top + addAttPos.y);
            }
            break;
        case SALADINSTATE::TOP:
            {
                IMAGEMANAGER->frameRender("sAttacksheet", getMemDC(), left + addAttPos.x, top + addAttPos.y);
            }
            break;
        case SALADINSTATE::BOTTOM:
            {
                IMAGEMANAGER->frameRender("sAttacksheet", getMemDC(), left + addAttPos.x, top + addAttPos.y);
            }
            break;
        }
    }
    else if (_stateBit.test(2) == 1)
    {
        POINT addDamagePos = { -20,-10 };
        switch (_imageState)
        {
        case SALADINSTATE::RIGHT:
            {
                IMAGEMANAGER->frameRender("sAttacksheet", getMemDC(), left + addDamagePos.x, top + addDamagePos.y);
            }
            break;
        case SALADINSTATE::LEFT:
            {
                IMAGEMANAGER->frameRender("sAttacksheet", getMemDC(), left + addDamagePos.x, top + addDamagePos.y);
            }
            break;
        case SALADINSTATE::TOP:
            {
                IMAGEMANAGER->frameRender("sAttacksheet", getMemDC(), left + addDamagePos.x, top + addDamagePos.y);
            }
            break;
        case SALADINSTATE::BOTTOM:
            {
                IMAGEMANAGER->frameRender("sAttacksheet", getMemDC(), left + addDamagePos.x, top + addDamagePos.y);
            }
            break;
        }
    }
}

float Saladin::getSaladinPosX()
{
	return _saladinPos.x;
}

float Saladin::getSaladinPosY()
{
	return _saladinPos.y;
}

void Saladin::setSaladinPos(POINT pos)
{
	_saladinPos = pos;
}

void Saladin::setSaladinPosX(float x)
{
    _saladinPos.x = x;
}
void Saladin::setSaladinPosY(float y)
{
    _saladinPos.y = y;
}

RECT Saladin::getSaladinRect()
{
	return _rcSaladin;
}


bool Saladin::getWaiting()
{
	return _isWaiting;
}

bool Saladin::getAttack()
{
    return _isAttack;
}

void Saladin::setAttack(bool isAttack)
{
    _isAttack = isAttack;
}

bool Saladin::getDamage()
{
    return _isDamage;
}

void Saladin::setDamage(bool isDamage)
{
    _isDamage = isDamage;
}

bool Saladin::getLive()
{
	return _isLive;
}

void Saladin::hitDamage(float damage)
{
	if (_currentHp <= 0)
	{
		_currentHp = 0;
		_isLive = false;
		return;
	}
	_currentHp -= damage;
}

void Saladin::setCameraRect(RECT rect)
{
    _cameraRect = rect;
}

SALADINSTATE Saladin::getImageState()
{
	return _imageState;
}

void Saladin::setImageStage(SALADINSTATE state)
{
	_imageState = state;
}

void Saladin::setEnemyIdle()
{
    _stateBit.reset();
}

unsigned int Saladin::getEnemyStateBit(int index)
{
    return _stateBit[index];
}

void Saladin::setEnemyStateBit(int index)
{
    _stateBit.reset();
    _stateBit.set(index);
}
