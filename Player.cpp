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
	_imageState = IMAGESTATE::RIGHT;
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

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_imageState = IMAGESTATE::RIGHT;
	}
	else if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_imageState = IMAGESTATE::LEFT;
	}
	else if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_imageState = IMAGESTATE::TOP;
	}
	else if (KEYMANAGER->isOnceKeyDown('4'))
	{
		_imageState = IMAGESTATE::BOTTOM;
	}
	else if (KEYMANAGER->isOnceKeyDown('5'))
	{
		_isWaiting=false;
		
	}
	else if (KEYMANAGER->isOnceKeyDown('6'))
	{
		_isWaiting = true;

	}
	cout << (int)_imageState <<" , " << _isWaiting << endl;

	switch(_imageState)
	{
	case IMAGESTATE::RIGHT:
		if (_isWaiting &&_count % 10 == 0)
		{

			_indexA--;
			IMAGEMANAGER->findImage("pRightIdle")->setFrameY(0);
			if (_indexA < 0)
			{
				_indexA = 5;
			}
			IMAGEMANAGER->findImage("pRightIdle")->setFrameX(_indexA);
		}
		else if (!_isWaiting &&_count % 10 == 0)
		{
			_indexB++;
			IMAGEMANAGER->findImage("pRightMove")->setFrameY(1);
			if (_indexB >= 6)
			{
				_indexB = 0;
			}
			IMAGEMANAGER->findImage("pRightMove")->setFrameX(_indexB);
		}
		break;
	case IMAGESTATE::LEFT:
		if (_isWaiting &&_count % 10 == 0)
		{

			_indexA++;
			IMAGEMANAGER->findImage("pLeftIdle")->setFrameY(1);
			if (_indexA >= 5)
			{
				_indexA = 0;
			}
			IMAGEMANAGER->findImage("pLeftIdle")->setFrameX(_indexA);
		}
		else if (!_isWaiting &&_count % 10 == 0)
		{
			_indexB++;
			IMAGEMANAGER->findImage("pLeftMove")->setFrameY(1);
			if (_indexB >= 6)
			{
				_indexB = 0;
			}
			IMAGEMANAGER->findImage("pLeftMove")->setFrameX(_indexB);
		}
		break;
	case IMAGESTATE::TOP:
		if (_isWaiting &&_count % 10 == 0)
		{
			_indexA--;
			IMAGEMANAGER->findImage("pUpIdle")->setFrameY(0);
			if (_indexA < 0)
			{
				_indexA = 5;
			}
			IMAGEMANAGER->findImage("pUpIdle")->setFrameX(_indexA);
		}
		else if (!_isWaiting &&_count % 10 == 0)
		{

			_indexB++;
			IMAGEMANAGER->findImage("pUpMove")->setFrameY(1);
			if (_indexB >= 6)
			{
				_indexB = 0;
			}
			IMAGEMANAGER->findImage("pUpMove")->setFrameX(_indexB);
		}
		break;
	case IMAGESTATE::BOTTOM:
		if (_isWaiting &&_count % 10 == 0)
		{
			_indexA--;
			IMAGEMANAGER->findImage("pDownIdle")->setFrameY(0);
			if (_indexA < 0)
			{
				_indexA = 5;
			}
			IMAGEMANAGER->findImage("pDownIdle")->setFrameX(_indexA);
		}
		else if (!_isWaiting &&_count % 10 == 0)
		{
			_indexB++;
			IMAGEMANAGER->findImage("pDownMove")->setFrameY(1);
			if (_indexB >= 6)
			{
				_indexB = 0;
			}
			IMAGEMANAGER->findImage("pDownMove")->setFrameX(_indexB);
		}
		break;
	}
		_rcPlayer = RectMakeCenter(_playerPos.x, _playerPos.y, _image->getFrameWidth(), _image->getFrameHeight());
	
}

void Player::render(void)
{
    float left = _rcPlayer.left - _cameraRect.left;
    float top = _rcPlayer.top - _cameraRect.top;

	switch (_imageState)
	{
	case IMAGESTATE::RIGHT:
		if (_isWaiting )
		{
			IMAGEMANAGER->frameRender("pRightIdle", getMemDC(), left, top);
		}
		else
		{
			IMAGEMANAGER->frameRender("pRightMove", getMemDC(), left, top);
		}
		break;
	case IMAGESTATE::LEFT:
		if (_isWaiting)
		{
			IMAGEMANAGER->frameRender("pLeftIdle", getMemDC(), left, top);
		}
		else
		{
			IMAGEMANAGER->frameRender("pLeftMove", getMemDC(), left - 40, top);
		}
		break;
	case IMAGESTATE::TOP:
		if (_isWaiting)
		{	
			IMAGEMANAGER->frameRender("pUpIdle", getMemDC(), left+7, top);
		}
		else
		{
			IMAGEMANAGER->frameRender("pUpMove", getMemDC(), left, top);
		}
		break;
	case IMAGESTATE::BOTTOM:
		if (_isWaiting)
		{
			IMAGEMANAGER->frameRender("pDownIdle", getMemDC(), left-12, top);
		}
		else
		{
			IMAGEMANAGER->frameRender("pDownMove", getMemDC(), left-12, top);
		}
		break;
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

IMAGESTATE Player::getImageState()
{
	return _imageState;
}

void Player::setImageStage(IMAGESTATE state)
{
	_imageState = state;
}
