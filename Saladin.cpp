#include "Stdafx.h"
#include "Saladin.h"

HRESULT Saladin::init(void)
{
	_image = IMAGEMANAGER->findImage("sDownIdle");
//	_image = IMAGEMANAGER->findImage("sRightMove");

	_count = 0;
	_indexA = _indexB = 0;
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
	_count++;

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_imageState = SALADINSTATE::RIGHT;
	}
	else if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_imageState = SALADINSTATE::LEFT;
	}
	else if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_imageState = SALADINSTATE::TOP;
	}
	else if (KEYMANAGER->isOnceKeyDown('4'))
	{
		_imageState = SALADINSTATE::BOTTOM;
	}
	else if (KEYMANAGER->isOnceKeyDown('5'))
	{
		_isWaiting = false;

	}
	else if (KEYMANAGER->isOnceKeyDown('6'))
	{
		_isWaiting = true;

	}

	switch (_imageState)
	{
	case SALADINSTATE::RIGHT:
		if (_isWaiting &&_count % 10 == 0)
		{

			_indexA--;
			IMAGEMANAGER->findImage("sRightIdle")->setFrameY(0);
			if (_indexA < 0)
			{
				_indexA = 4;
			}
			IMAGEMANAGER->findImage("sRightIdle")->setFrameX(_indexA);
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
	case SALADINSTATE::LEFT:
		if (_isWaiting &&_count % 10 == 0)
		{

			_indexA++;
			IMAGEMANAGER->findImage("sLeftIdle")->setFrameY(1);
			if (_indexA >= 4)
			{
				_indexA = 0;
			}
			IMAGEMANAGER->findImage("sLeftIdle")->setFrameX(_indexA);
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
	case SALADINSTATE::TOP:
		if (_isWaiting &&_count % 10 == 0)
		{
			_indexA--;
			IMAGEMANAGER->findImage("sUpIdle")->setFrameY(0);
			if (_indexA < 0)
			{
				_indexA = 4;
			}
			IMAGEMANAGER->findImage("sUpIdle")->setFrameX(_indexA);
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
	case SALADINSTATE::BOTTOM:
		if (_isWaiting &&_count % 10 == 0)
		{
			_indexA--;
			IMAGEMANAGER->findImage("sDownIdle")->setFrameY(0);
			if (_indexA < 0)
			{
				_indexA = 4;
			}
			IMAGEMANAGER->findImage("sDownIdle")->setFrameX(_indexA);
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
	_rcSaladin = RectMakeCenter(_saladinPos.x, _saladinPos.y, _image->getFrameWidth(), _image->getFrameHeight());

}

void Saladin::render(void)
{
	float left = _rcSaladin.left - _cameraRect.left;
	float top = _rcSaladin.top - _cameraRect.top;

	switch (_imageState)
	{
	case SALADINSTATE::RIGHT:
		if (_isWaiting)
		{
			IMAGEMANAGER->frameRender("sRightIdle", getMemDC(), left, top);
		}
		else
		{
			IMAGEMANAGER->frameRender("sRightMove", getMemDC(), left, top);
		}
		break;
	case SALADINSTATE::LEFT:
		if (_isWaiting)
		{
			IMAGEMANAGER->frameRender("sLeftIdle", getMemDC(), left, top);
		}
		else
		{
			IMAGEMANAGER->frameRender("sLeftMove", getMemDC(), left - 40, top);
		}
		break;
	case SALADINSTATE::TOP:
		if (_isWaiting)
		{
			IMAGEMANAGER->frameRender("sUpIdle", getMemDC(), left + 7, top);
		}
		else
		{
			IMAGEMANAGER->frameRender("sUpMove", getMemDC(), left, top);
		}
		break;
	case SALADINSTATE::BOTTOM:
		if (_isWaiting)
		{
			IMAGEMANAGER->frameRender("sDownIdle", getMemDC(), left - 12, top);
		}
		else
		{
			IMAGEMANAGER->frameRender("sDownMove", getMemDC(), left - 12, top);
		}
		break;
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

void Saladin::setWaiting(bool isWaiting)
{
	_isWaiting = isWaiting;
}

bool Saladin::getLive()
{
	return _isLive;
}

bool Saladin::setLive(bool status)
{
	return _isLive = status;
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
