#include "Stdafx.h"
#include "Player.h"

HRESULT Player::init(void)
{
	_image = IMAGEMANAGER->addFrameImage("ĳ���ʹ��", "Resources/Images/Object/playerIdle.bmp", 1664, 146, 13, 2, true, RGB(255, 0, 255));
	_image = IMAGEMANAGER->addFrameImage("ĳ�����̵�", "Resources/Images/Object/playerRun.bmp", 1106, 140, 14, 2, true, RGB(255, 0, 255));
	
	//_rcPlayer = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	
	_count = 0;
	_indexA = _indexB = 0;
	_alphaA = 0;
    _speed = 5;
    _playerPos.x = 0;
    _playerPos.y = WINSIZE_Y-140;
	_rcPlayer = RectMakeCenter(_playerPos.x, _playerPos.y, _image->getFrameWidth(), _image->getFrameHeight());
    
    //_camera->setCameraPos(_playerPos);

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
	if (_isThird)
	{
		_hpBar->update();
		_hpBar->setGauge(_currentHp, _maxHp);
	}
	if (_isLive)
	{
		if (_isWaiting && _count % 5 == 0)
		{
			if (_isLeft)
			{
				_indexA++;
				IMAGEMANAGER->findImage("ĳ���ʹ��")->setFrameY(1);
				if (_indexA >= 13)
				{
					_indexA = 0;
				}
				IMAGEMANAGER->findImage("ĳ���ʹ��")->setFrameX(_indexA);
			}
			else if (!_isLeft)
			{
				_indexA--;
				IMAGEMANAGER->findImage("ĳ���ʹ��")->setFrameY(0);
				if (_indexA < 0)
				{
					_indexA = 13;
				}
				IMAGEMANAGER->findImage("ĳ���ʹ��")->setFrameX(_indexA);
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_isLeft = true;
			_isWaiting = false;
          
            /*if (_playerPos.x < 0)
            {
                _playerPos.x = 0;
            }
            else
            {
            }*/
            _playerPos.x -= _speed;
			_hpBar->setX(_hpBar->getX() - _speed);
			_indexB++;
			IMAGEMANAGER->findImage("ĳ�����̵�")->setFrameY(1);
			if (_indexB >= 14)
			{
				_indexB = 0;
			}
			IMAGEMANAGER->findImage("ĳ�����̵�")->setFrameX(_indexB);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_isLeft = false;
			_isWaiting = false;
            /*if (_playerPos.x >= WINSIZE_X)
            {
                _playerPos.x = WINSIZE_X;
            }
            else
            {
            }*/
            _playerPos.x += _speed;
			_hpBar->setX(_hpBar->getX() + _speed);
			_indexB--;
			IMAGEMANAGER->findImage("ĳ�����̵�")->setFrameY(0);
			if (_indexB < 0)
			{
				_indexB = 14;
			}
			IMAGEMANAGER->findImage("ĳ�����̵�")->setFrameX(_indexB);
		}
		else
		{
			_isWaiting = true;
            //if(isLeft)���ʱ��̿� ���� �߰����� ���� ���� �� ��ŭ Ÿ�̹� �� �༭ ������ �̵���Ű��
            //else �����ʵ� ����
           // if(getDistance(_camera->getScreenRect().right- _camera->getScreenRect().left)*0.5,0,))
		}
		if (_isThird && _count % 20 == 0)
		{
			hitDamage(0.5f);
		}
		_rcPlayer = RectMakeCenter(_playerPos.x, _playerPos.y, _image->getFrameWidth(), _image->getFrameHeight());
	}
}

void Player::render(void)
{
	if (_isThird)
	{
		_hpBar->render();
	}
	if (_isLive)
	{
        float left = _rcPlayer.left - _cameraRect.left;
        float top = _rcPlayer.top - _cameraRect.top;
		if (_isWaiting)
		{
			IMAGEMANAGER->frameRender("ĳ���ʹ��", getMemDC(), left, top);
		}
		else
		{
			IMAGEMANAGER->frameRender("ĳ�����̵�", getMemDC(), left, top);
		}
	}
}

float Player::getPlayerPosX()
{
	return _playerPos.x;
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

bool Player::getThird()
{
	return _isThird;
}

bool Player::setThird(bool isThird)
{
	return _isThird = isThird;
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