#include "Stdafx.h"
#include "Player.h"

HRESULT Player::init(void)
{
	_image = IMAGEMANAGER->findImage("pRightIdle");
	_image = IMAGEMANAGER->findImage("pRightMove");
	_image = IMAGEMANAGER->findImage("pDamageSheet");
	_image = IMAGEMANAGER->findImage("skillStart");
	worldBrokenSkill();

    _stateBit = 0;//Idle
	_count = 0;
	_indexA = _indexB = 0;
	_alphaA = 0;
    _speed = 10;
    _playerPos.x = 0;
    _playerPos.y = WINSIZE_Y-140;
	_rcPlayer = RectMakeCenter(_playerPos.x, _playerPos.y, _image->getFrameWidth(), _image->getFrameHeight());
	_tmp = 1;
	_cdt = 0;
	_currentHp = 10;
	_maxHp = 10;
	//_hpBar = new ProgressBar;
	//_hpBar->init(280, WINSIZE_Y - 250, 52, 4);
	_imageState = PLAYERSTATE::BOTTOM;
	return S_OK;
}

void Player::release(void)
{
	//_hpBar->release();
	//SAFE_DELETE(_hpBar);
}

void Player::update(void)
{
	_count+= 4;
    if (KEYMANAGER->isOnceKeyDown('1'))
    {
        _imageState = PLAYERSTATE::RIGHT;
    }
    else if (KEYMANAGER->isOnceKeyDown('2'))
    {
        _imageState = PLAYERSTATE::LEFT;
    }
    else if (KEYMANAGER->isOnceKeyDown('3'))
    {
        _imageState = PLAYERSTATE::TOP;
    }
    else if (KEYMANAGER->isOnceKeyDown('4'))
    {
        _imageState = PLAYERSTATE::BOTTOM;
    }
    else if (KEYMANAGER->isOnceKeyDown('5'))
    {
        this->setPlayerIdle();
    }
    else if (KEYMANAGER->isOnceKeyDown('6'))
    {
        this->setPlayerStateBit(0);
    }
    //00000 대기 
    if (_stateBit.none() == 1)
    {
        if (_count % 30 == 0)
        {
            switch (_imageState)
            {
            case PLAYERSTATE::RIGHT:
                _indexA--;
                IMAGEMANAGER->findImage("pRightIdle")->setFrameY(0);
                if (_indexA < 0)
                {
                    _indexA = 5;
                }
                IMAGEMANAGER->findImage("pRightIdle")->setFrameX(_indexA);
                
                break;
            case PLAYERSTATE::LEFT:
                _indexA++;
                IMAGEMANAGER->findImage("pLeftIdle")->setFrameY(1);
                if (_indexA >= 5)
                {
                    _indexA = 0;
                }
                IMAGEMANAGER->findImage("pLeftIdle")->setFrameX(_indexA);
                
                break;
            case PLAYERSTATE::TOP:
                _indexA--;
                IMAGEMANAGER->findImage("pUpIdle")->setFrameY(0);
                if (_indexA < 0)
                {
                    _indexA = 5;
                }
                IMAGEMANAGER->findImage("pUpIdle")->setFrameX(_indexA);
                
                break;
            case PLAYERSTATE::BOTTOM:
                _indexA--;
                IMAGEMANAGER->findImage("pDownIdle")->setFrameY(0);
                if (_indexA < 0)
                {
                    _indexA = 5;
                }
                IMAGEMANAGER->findImage("pDownIdle")->setFrameX(_indexA);
                
                break;
            }
        }
    }
    //00001 이동중 
    else if (_stateBit.test(0) == 1)
    {
        if (_count % 30 == 0)
        {
            switch (_imageState)
            {
            case PLAYERSTATE::RIGHT:
                _indexB++;
                IMAGEMANAGER->findImage("pRightMove")->setFrameY(1);
                if (_indexB >= 6)
                {
                    _indexB = 0;
                }
                IMAGEMANAGER->findImage("pRightMove")->setFrameX(_indexB);
                
                break;
            case PLAYERSTATE::LEFT:
                _indexB++;
                IMAGEMANAGER->findImage("pLeftMove")->setFrameY(1);
                if (_indexB >= 6)
                {
                    _indexB = 0;
                }
                IMAGEMANAGER->findImage("pLeftMove")->setFrameX(_indexB);
                break;
            case PLAYERSTATE::TOP:
                _indexB++;
                IMAGEMANAGER->findImage("pUpMove")->setFrameY(1);
                if (_indexB >= 6)
                {
                    _indexB = 0;
                }
                IMAGEMANAGER->findImage("pUpMove")->setFrameX(_indexB);
                
                break;
            case PLAYERSTATE::BOTTOM:
                _indexB++;
                IMAGEMANAGER->findImage("pDownMove")->setFrameY(1);
                if (_indexB >= 6)
                {
                    _indexB = 0;
                }
                IMAGEMANAGER->findImage("pDownMove")->setFrameX(_indexB);
                
                break;
            }
        }
    }
    //00010 공격 
    else if (_stateBit.test(1) == 1)
    {
        if (_count % 30 == 0)
        {
            switch (_imageState)
            {
            case PLAYERSTATE::RIGHT:
                _indexB++;
                IMAGEMANAGER->findImage("pRightAtt")->setFrameY(1);
                if (_indexB >= 4)
                {
                    _indexB = 0;
                    _isAttack = true;
                    setPlayerIdle();
                }
                IMAGEMANAGER->findImage("pRightAtt")->setFrameX(_indexB);
                break;
            case PLAYERSTATE::LEFT:
                _indexB--;
                IMAGEMANAGER->findImage("pLeftAtt")->setFrameY(1);
                if (_indexB < 0)
                {
                    _indexB = 4;
                    _isAttack = true;
                    setPlayerIdle();
                }
                IMAGEMANAGER->findImage("pLeftAtt")->setFrameX(_indexB);
                break;
            case PLAYERSTATE::TOP:
                _indexB++;
                IMAGEMANAGER->findImage("pUpAtt")->setFrameY(1);
                if (_indexB >= 4)
                {
                    _indexB = 0;
                    _isAttack = true;
                    setPlayerIdle();
                }
                IMAGEMANAGER->findImage("pUpAtt")->setFrameX(_indexB);
                break;
            case PLAYERSTATE::BOTTOM:
                _indexB++;
                IMAGEMANAGER->findImage("pDownAtt")->setFrameY(1);
                if (_indexB >= 4)
                {
                    _indexB = 0;
                    _isAttack = true;
                    setPlayerIdle();
                }
                IMAGEMANAGER->findImage("pDownAtt")->setFrameX(_indexB);
                break;
            }
        }
    }
    //00100 피격 
    else if (_stateBit.test(2) == 1)
    {
        switch (_imageState)
        {
            case PLAYERSTATE::RIGHT:
            {
                IMAGEMANAGER->findImage("pDamageSheet")->setFrameY(0);
                IMAGEMANAGER->findImage("pDamageSheet")->setFrameX(3);
            }
            break;
            case PLAYERSTATE::LEFT:
            {
                IMAGEMANAGER->findImage("pDamageSheet")->setFrameY(0);
                IMAGEMANAGER->findImage("pDamageSheet")->setFrameX(2);
            }
            break;
            case PLAYERSTATE::TOP:
            {
                IMAGEMANAGER->findImage("pDamageSheet")->setFrameY(0);
                IMAGEMANAGER->findImage("pDamageSheet")->setFrameX(0);
            }
            break;
            case PLAYERSTATE::BOTTOM:
            {
                IMAGEMANAGER->findImage("pDamageSheet")->setFrameY(0);
                IMAGEMANAGER->findImage("pDamageSheet")->setFrameX(1);
            }
            break;
        }
		if (_count % 20 == 0)
		{
			_tmp *= -1;
			_cdt++;
		}
        if (_cdt >5)
        {
            setPlayerIdle();
			_cdt = 0;
        }
    //01000 스킬
		else if (_stateBit.test(3) == 1)
		{
			if (_count % 60 == 0)
			{
				if(_indexB < 4)_indexB++;
				IMAGEMANAGER->findImage("skillStart")->setFrameY(0);
				IMAGEMANAGER->findImage("skillStart")->setFrameX(_indexB);
				//setPlayerIdle();타이밍은 나중에 잡아주기
				uniteSkill.update();

			}
		}
    //10000 죽음
    }
	_rcPlayer = RectMakeCenter(_playerPos.x, _playerPos.y, _image->getFrameWidth(), _image->getFrameHeight());
	//cout << _stateBit.to_string() << endl;
}


void Player::render(void)
{
    float left = _rcPlayer.left - _cameraRect.left;
    float top = _rcPlayer.top - _cameraRect.top;
	cout << left << endl;
    if (_stateBit.none() == 1)
    {
        switch (_imageState)
        {
        case PLAYERSTATE::RIGHT:
            IMAGEMANAGER->frameRender("pRightIdle", getMemDC(), left-10, top);
            break;
        case PLAYERSTATE::LEFT:
            IMAGEMANAGER->frameRender("pLeftIdle", getMemDC(), left-10, top);
            break;
        case PLAYERSTATE::TOP:
            IMAGEMANAGER->frameRender("pUpIdle", getMemDC(), left, top);
            break;
        case PLAYERSTATE::BOTTOM:
            IMAGEMANAGER->frameRender("pDownIdle", getMemDC(), left-20, top-5);
            break;
        }
    }
    else if (_stateBit.test(0) == 1)
    {
        switch (_imageState)
        {
        case PLAYERSTATE::RIGHT:
            IMAGEMANAGER->frameRender("pRightMove", getMemDC(), left, top);
            break;
        case PLAYERSTATE::LEFT:
            IMAGEMANAGER->frameRender("pLeftMove", getMemDC(), left-40, top);
            break;
        case PLAYERSTATE::TOP:
            IMAGEMANAGER->frameRender("pUpMove", getMemDC(), left, top);
            break;
        case PLAYERSTATE::BOTTOM:
            IMAGEMANAGER->frameRender("pDownMove", getMemDC(), left-20, top);
            break;
        }
    }
    else if (_stateBit.test(1) == 1)
    {
		POINT addAttPos = { -40,-30 };
        switch (_imageState)
        {
        case PLAYERSTATE::RIGHT:
            IMAGEMANAGER->frameRender("pRightAtt", getMemDC(), left -43, top + addAttPos.y);
            break;
        case PLAYERSTATE::LEFT:
            IMAGEMANAGER->frameRender("pLeftAtt", getMemDC(), left -37, top + addAttPos.y);
            break;
        case PLAYERSTATE::TOP:
            IMAGEMANAGER->frameRender("pUpAtt", getMemDC(), left -30, top);
            break;
        case PLAYERSTATE::BOTTOM:
            IMAGEMANAGER->frameRender("pDownAtt", getMemDC(), left + addAttPos.x, top + addAttPos.y);
            break;
        }
    }
    else if (_stateBit.test(2) == 1)
    {
		int damagePos = -20 +(7 * _tmp);
        switch (_imageState)
        {
        case PLAYERSTATE::RIGHT:
            IMAGEMANAGER->frameRender("pDamageSheet", getMemDC(), left + damagePos, top);
            break;
        case PLAYERSTATE::LEFT:
            IMAGEMANAGER->frameRender("pDamageSheet", getMemDC(), left + damagePos, top);
            break;
        case PLAYERSTATE::TOP:
            IMAGEMANAGER->frameRender("pDamageSheet", getMemDC(), left + damagePos, top);
            break;
        case PLAYERSTATE::BOTTOM:
            IMAGEMANAGER->frameRender("pDamageSheet", getMemDC(), left + damagePos, top);
            break;
        }
    }
	else if (_stateBit.test(3) == 1)
	{
		IMAGEMANAGER->frameRender("skillStart", getMemDC(), left, top);
		uniteSkill.render();
	}
}

void Player::worldBrokenSkill()
{
	RECT* testRc = &_rcPlayer;

	Animation* _skillAni1  = ANIMATIONMANAGER->findAnimation("184light");
	Animation* _skillAni2  = ANIMATIONMANAGER->findAnimation("circle");
	Animation* _skillAni3  = ANIMATIONMANAGER->findAnimation("smog2");

	Animation* _skillAni4  = ANIMATIONMANAGER->findAnimation("fire");
	Animation* _skillAni5  = ANIMATIONMANAGER->findAnimation("smog");
	Animation* _skillAni7  = ANIMATIONMANAGER->findAnimation("48fire");
	Animation* _skillAni8  = ANIMATIONMANAGER->findAnimation("95light");
	Animation* _skillAni10 = ANIMATIONMANAGER->findAnimation("203smog");
	Animation* _skillAni11 = ANIMATIONMANAGER->findAnimation("115stone");
	Animation* _skillAni12 = ANIMATIONMANAGER->findAnimation("enemyAttack");
	Animation* _skillAni13 = ANIMATIONMANAGER->findAnimation("one");
	Animation* _skillAni14 = ANIMATIONMANAGER->findAnimation("double");
	Animation* _skillAni15 = ANIMATIONMANAGER->findAnimation("triple");

	Skill* skill   = new Skill(1, "184light", testRc, _skillAni1);
	Skill* skill2  = new Skill(2, "circle", testRc, _skillAni2);
	Skill* skill5  = new Skill(3, "smog2", testRc, _skillAni3);

	//타일 적용필요
	Skill* skill13 = new Skill(1, "one", testRc, _skillAni12);//셋이 다 다르넹...
	Skill* skill14 = new Skill(1, "double", testRc, _skillAni12);
	Skill* skill15 = new Skill(1, "triple", testRc, _skillAni12);
	Skill* skill3  = new Skill(2, "fire", testRc, _skillAni4);//왼쪽부터 시작 - 멈췄다가 캐릭터 위주부터 다시시작 2 / 3
	Skill* skill7  = new Skill(3, "48fire", testRc, _skillAni7);
	Skill* skill4  = new Skill(3, "smog", testRc, _skillAni5);
	Skill* skill11 = new Skill(20, "115stone", testRc, _skillAni11);//돌 튀어 오르며 사라짐

	Skill* skill6  = new Skill(1, "enemyAttack", testRc, _skillAni12);
	//skill13 = new Skill(2, "one", testRc, _skillAni12);//에너미도 셋 랜덤
	Skill* skill8  = new Skill(3, "95light", testRc, _skillAni8);
	Skill* skill10 = new Skill(3, "203smog", testRc, _skillAni10);//이후 컷변화 레드켜짐- 여기서 같이 돌릴가
	// skill11 = new Skill(20, "115stone", testRc, _skillAni11);//돌 높이 튀어 오르며 사라짐

	uniteSkill.add(skill);
	uniteSkill.add(skill2);
	uniteSkill.add(skill3);

	uniteSkill.add(skill4);
	uniteSkill.add(skill5);
	uniteSkill.add(skill6);
	uniteSkill.add(skill7);
	uniteSkill.add(skill8);
	uniteSkill.add(skill10);
	uniteSkill.startSkill();
}

float Player::getPlayerPosX()
{
	return _playerPos.x;
}

float Player::getPlayerPosY()
{
	return _playerPos.y;
}

void Player::setPlayerPos(POINT pos)
{
	_playerPos = pos;
}

void Player::setPlayerPosX(float x)
{
    _playerPos.x = x;
}
void Player::setPlayerPosY(float y)
{
    _playerPos.y = y;
}

RECT Player::getPlayerRect()
{
	return _rcPlayer;
}


bool Player::getWaiting()
{
	return _isWaiting;
}

void Player::setWaiting(bool isWaiting)
{
	_isWaiting = isWaiting;
}

bool Player::getAttack()
{
    return _isAttack;
}

void Player::setAttack(bool isAttack)
{
    _isAttack = isAttack;
}

bool Player::getDamage()
{
    return _isDamage;
}

void Player::setDamage(bool isDamage)
{
    _isDamage = isDamage;

}

bool Player::getLive()
{
	return _isLive;
}

bool Player::setLive(bool status)
{
	return _isLive = status;
}

void Player::hitDamage(float damage)
{
	if (_currentHp <= 0)
	{
		_currentHp = 0;
		_isLive = false;
		return;
	}
	_currentHp -= damage;
}

void Player::setCameraRect(RECT rect)
{
    _cameraRect = rect;
}

PLAYERSTATE Player::getImageState()
{
	return _imageState;
}

void Player::setImageStage(PLAYERSTATE state)
{
	_imageState = state;
}

void Player::setPlayerIdle()
{
    _stateBit.reset();
}

unsigned int Player::getPlayerStateBit(int index)
{
    return _stateBit[index];
}

bitset<5> Player::getPlayerStateBit()
{
	return _stateBit;
}

void Player::setPlayerStateBit(int index)
{
    _stateBit.reset();
    _stateBit.set(index,true);
}
