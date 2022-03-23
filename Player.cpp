#include "Stdafx.h"
#include "Player.h"

HRESULT Player::init(void)
{
	_image = IMAGEMANAGER->findImage("pRightIdle");
	_image = IMAGEMANAGER->findImage("pRightMove");
	
	_count = 0;
	_indexA = _indexB = 0;
	_alphaA = 0;
    _speed = 5;
    _playerPos.x = 0;
    _playerPos.y = WINSIZE_Y-140;
	_rcPlayer = RectMakeCenter(_playerPos.x, _playerPos.y, _image->getFrameWidth(), _image->getFrameHeight());

	_currentHp = 10;
	_maxHp = 10;
	_hpBar = new ProgressBar;
	_hpBar->init(280, WINSIZE_Y - 250, 52, 4);
	return S_OK;
}

void Player::release(void)
{
	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void Player::update(void)
{
	_count++;
	//if (_isThird)
	//{
	//	_hpBar->update();
	//	_hpBar->setGauge(_currentHp, _maxHp);
	//}
	if (_isLive)
	{
		if (_isWaiting && _count % 30 == 0)
		{
			if (_isLeft)
			{
				_indexA++;
				IMAGEMANAGER->findImage("pRightIdle")->setFrameY(1);
				if (_indexA >= 3)
				{
					_indexA = 0;
				}
				IMAGEMANAGER->findImage("pRightIdle")->setFrameX(_indexA);
			}
			else if (!_isLeft)
			{
				_indexA--;
				IMAGEMANAGER->findImage("pRightIdle")->setFrameY(0);
				if (_indexA < 0)
				{
					_indexA = 3;
				}
				IMAGEMANAGER->findImage("pRightIdle")->setFrameX(_indexA);
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_isLeft = true;
			_isWaiting = false;
          
            _playerPos.x -= _speed;
			_hpBar->setX(_hpBar->getX() - _speed);
			if(_count%30 ==0)	_indexB++;
			IMAGEMANAGER->findImage("pRightMove")->setFrameY(1);
			if (_indexB >= 6)
			{
				_indexB = 0;
			}
			IMAGEMANAGER->findImage("pRightMove")->setFrameX(_indexB);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_isLeft = false;
			_isWaiting = false;
     
            _playerPos.x += _speed;
			_hpBar->setX(_hpBar->getX() + _speed);
			if (_count % 30 == 0)	_indexB--;
			IMAGEMANAGER->findImage("pRightMove")->setFrameY(0);
			if (_indexB < 0)
			{
				_indexB = 6;
			}
			IMAGEMANAGER->findImage("pRightMove")->setFrameX(_indexB);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_isLeft = true;
			_isWaiting = false;

			_playerPos.y -= _speed;
			_hpBar->setY(_hpBar->getY() - _speed);
			if (_count % 30 == 0)	_indexB++;
			IMAGEMANAGER->findImage("pRightMove")->setFrameY(1);
			if (_indexB >= 6)
			{
				_indexB = 0;
			}
			IMAGEMANAGER->findImage("pRightMove")->setFrameX(_indexB);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_isLeft = false;
			_isWaiting = false;

			_playerPos.y += _speed;
			_hpBar->setY(_hpBar->getY() + _speed);
			if (_count % 30 == 0)	_indexB--;
			IMAGEMANAGER->findImage("pRightMove")->setFrameY(0);
			if (_indexB < 0)
			{
				_indexB = 6;
			}
			IMAGEMANAGER->findImage("pRightMove")->setFrameX(_indexB);
		}
		else
		{
			_isWaiting = true;
		}
	/*	if (_isThird && _count % 20 == 0)
		{
			hitDamage(0.5f);
		}*/
		_rcPlayer = RectMakeCenter(_playerPos.x, _playerPos.y, _image->getFrameWidth(), _image->getFrameHeight());
	}
}

void Player::render(void)
{
	/*if (_isThird)
	{
		_hpBar->render();
	}*/
	if (_isLive)
	{
        float left = _rcPlayer.left - _cameraRect.left;
        float top = _rcPlayer.top - _cameraRect.top;
		if (_isWaiting)
		{
			IMAGEMANAGER->frameRender("pRightIdle", getMemDC(), left, top);
		}
		else
		{
			IMAGEMANAGER->frameRender("pRightMove", getMemDC(), left, top);
		}
	}
}

float Player::getPlayerPosX()
{
	return _playerPos.x;
}

float Player::getPlayerPosY()
{
	return _playerPos.y;
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

bool Player::getLeft()
{
	return _isLeft;
}

bool Player::getWaiting()
{
	return _isWaiting;
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