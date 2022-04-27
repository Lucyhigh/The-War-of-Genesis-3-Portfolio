#include "Stdafx.h"
#include "Saladin.h"

HRESULT Saladin::init(void)
{
	_image = IMAGEMANAGER->findImage("sDownIdle");
	_image = IMAGEMANAGER->findImage("sMovesheet");
	_image = IMAGEMANAGER->findImage("sDamageSheet");
    _stateBit = 0;

	_tmp=1;
	_cdt=0;
	_count = 0;
	_indexA = _indexB = _indexC = _worldIndex = 0;
    _skillCount = 5;
	_alphaA = 0;
	_speed = 5;
	_saladinPos.x = 0;
	_saladinPos.y = WINSIZE_Y - 140;
	_rcSaladin = RectMakeCenter(_saladinPos.x, _saladinPos.y, _image->getFrameWidth(), _image->getFrameHeight());
	_currentHp = 10;
	_maxHp = 10;
	_hpBar = new ProgressBar;
	_hpBar->init(0, 0, 30, 4);
	_currentHp = 500;
	_maxHp = 500;
	_imageState = SALADINSTATE::BOTTOM;
	return S_OK;
}

void Saladin::release(void)
{
	_hpBar->release();
	SAFE_DELETE(_hpBar);
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
        if (_count % 30 == 0)
        {
            switch (_imageState)
            {
            case SALADINSTATE::RIGHT:
                _indexC--;
                IMAGEMANAGER->findImage("sAttacksheet")->setFrameY(3);
                if (_indexC < 0)
                {
                    _indexC = 5;
                    _isAttack = true;
                    _skillCount++;

                    setEnemyIdle();
                }
                IMAGEMANAGER->findImage("sAttacksheet")->setFrameX(_indexC);
                break;
            case SALADINSTATE::LEFT:
                _indexC++;
                IMAGEMANAGER->findImage("sAttacksheet")->setFrameY(2);
                if (_indexC >= 5)
                {
                    _indexC = 0;
                    _isAttack = true;
                    _skillCount++;

                    setEnemyIdle();
                }
                IMAGEMANAGER->findImage("sAttacksheet")->setFrameX(_indexC);
                break;
            case SALADINSTATE::TOP:
                _indexC++;
                IMAGEMANAGER->findImage("sAttacksheet")->setFrameY(0);
                if (_indexC >= 5)
                {
                    _indexC = 0;
                    _isAttack = true;
                    _skillCount++;

                    setEnemyIdle();
                }
                IMAGEMANAGER->findImage("sAttacksheet")->setFrameX(_indexC);
                break;
            case SALADINSTATE::BOTTOM:
                _indexC++;
                IMAGEMANAGER->findImage("sAttacksheet")->setFrameY(1);
                if (_indexC >= 5)
                {
                    _indexC = 0;
                    _isAttack = true;
                    _skillCount++;

                    setEnemyIdle();
                }
                IMAGEMANAGER->findImage("sAttacksheet")->setFrameX(_indexC);
                break;
            }
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
		if (_count % 20 == 0)
		{
			_tmp *= -1;
			_cdt++;
			_isDamage = true;
		}
		else if(5 < _cdt && _cdt < 6 && _count % 20)
		{
			_isDamage = false;
		}
		else if (_cdt >= 6)
		{
			_cdt = 0;
			setEnemyIdle();
		}
    }
    //01000 죽음
	else if (_stateBit.test(3) == 1)
	{
		_isLive = false;
	}
    //10000 천지파열무
    if (_stateBit.test(4) == 1)
    {
		_cdt++;
		//cout <<"_cdt : "<< _cdt << endl;
        IMAGEMANAGER->findImage("sSkill")->setFrameY(0);
        IMAGEMANAGER->findImage("sSkill")->setFrameX(_worldIndex);

        if (_worldIndex == 0)
        {
			if (_cdt > 120)
			{
				_worldIndex++;
				_cdt = 0;
			}
        }
        else if (_worldIndex == 1 || _worldIndex == 2)
        {
            if (_cdt > 5)
			{
				_worldIndex++;
				_cdt = 0;
			}
        }
        else if (_worldIndex == 3 || _worldIndex == 4 || _worldIndex == 5 || _worldIndex == 6|| _worldIndex == 7 )
        {
            if (_cdt > 2)
			{
				_worldIndex++;
				_cdt = 0;
			}
        }
        else if (_worldIndex == 8 || _worldIndex == 9 )
        {
            if (_cdt > 3)
			{
				_worldIndex++;
				_cdt = 0;
			}
        }
        else if (_worldIndex == 10)
        {
            _isAttack = true;
            if (_cdt >500)
            {
                _skillCount = 10;
				//_cdt = 0;
				//setEnemyIdle();
            }
        }
		//cout << _worldIndex << endl;
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
            IMAGEMANAGER->frameRender("sDownIdle", getMemDC(), left-10, top-15);
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
        POINT addAttPos = { -35,-30 };
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
                IMAGEMANAGER->frameRender("sAttacksheet", getMemDC(), left -30, top -20);//==========
            }
            break;
        }
    }
    else if (_stateBit.test(2) == 1)
    {
        POINT addDamagePos = { -20 + (7 * _tmp),-10 }; 
        switch (_imageState)
        {
        case SALADINSTATE::RIGHT:
            {
                IMAGEMANAGER->frameRender("sDamageSheet", getMemDC(), left + addDamagePos.x, top + addDamagePos.y);
            }
            break;
        case SALADINSTATE::LEFT:
            {
                IMAGEMANAGER->frameRender("sDamageSheet", getMemDC(), left + addDamagePos.x, top + addDamagePos.y);
            }
            break;
        case SALADINSTATE::TOP:
            {
                IMAGEMANAGER->frameRender("sDamageSheet", getMemDC(), left + addDamagePos.x, top + addDamagePos.y);
            }
            break;
        case SALADINSTATE::BOTTOM:
            {
                IMAGEMANAGER->frameRender("sDamageSheet", getMemDC(), left + addDamagePos.x, top + addDamagePos.y);
            }
            break;
        }
    }
	else if (_stateBit.test(3) == 1)
	{
		//죽음
	}
    else if (_stateBit.test(4) == 1)
    {
        IMAGEMANAGER->frameRender("sSkill", getMemDC(), left - 30, top - 20);
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
