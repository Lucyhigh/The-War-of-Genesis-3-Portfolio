#include "Stdafx.h"
#include "Camera.h"

Camera::Camera()
{
	_trace.x = CENTER_X;
	_trace.y = CENTER_Y;
	_count = 0;

	_screen = RectMakeCenter(_trace.x, _trace.y, WINSIZE_X, WINSIZE_Y);
	_leftLimit = CENTER_X;

	_isShaking = false;
	_isShakingIncrease = false;
	_shakingOffsetCount =0;
	_beforeShakingPt = {0,0};
	_shakingStartTime = 0;
	_shakingTime =0;
}

HRESULT Camera::init(void)
{
	return S_OK;
}

void Camera::release(void){
}

void Camera::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) || _ptMouse.x > WINSIZE_X -10)
	{
		_trace.x += 20;
		if (_trace.x > _rightLimit)
			_trace.x = _rightLimit;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) || _ptMouse.x < 10)
	{
		_trace.x -= 20;
		if (_trace.x < _leftLimit)
			_trace.x = _leftLimit;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) || _ptMouse.y < 10)
	{
		_trace.y -= 20;
		if (_trace.y < _topLimit)
			_trace.y = _topLimit;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) || _ptMouse.y > WINSIZE_Y - 10)
	{
		_trace.y += 20;
		if (_trace.y > _bottomLimit)
			_trace.y = _bottomLimit;
	}

	if (_isShaking)
	{
		cout << "_isShaking" << endl;
		_shakingOffsetCount++;
		if (_shakingOffsetCount > 1)
		{
			_shakingOffsetCount = 0;
			_isShakingIncrease = !_isShakingIncrease;
			if (_isShakingIncrease)_trace.y += 10;
			else _trace.y -= 10;
		}
		cout << "_trace : "<< _trace.y  << endl;

		if (TIMEMANAGER->getWorldTime() > _shakingStartTime + _shakingTime)
		{
			_isShaking = false;
			_shakingStartTime = 0;
			_shakingTime = 0;
			_trace = _beforeShakingPt;
		}
	}
	
	_screen = RectMakeCenter(_trace.x, _trace.y, WINSIZE_X, WINSIZE_Y);
}

void Camera::render(void){
}

RECT Camera::getScreenRect()
{
	return _screen;
}

void Camera::setScreenRect(RECT screenRect)
{
	_screen = screenRect;
}

void Camera::setLimitsX(float leftLimit, float rightLimit)
{
	_leftLimit = leftLimit;
	_rightLimit = rightLimit - CENTER_X;
}

void Camera::setLimitsY(float topLimit, float bottomLimit)
{
	_topLimit = topLimit;
	_bottomLimit = bottomLimit - CENTER_Y;
}

void Camera::shakeStart(float time)
{
	_shakingStartTime = TIMEMANAGER->getWorldTime();
	_isShaking = true;
	_isShakingIncrease = true;
	_shakingTime = time;
	_beforeShakingPt = _trace;
}

POINT Camera::getCameraPos()
{
	return _trace;
}

void Camera::setCameraPos(POINT cameraPos)
{
	_trace = cameraPos;
	_trace.x = _trace.x < _leftLimit ? _leftLimit : _trace.x;
	_trace.x = _trace.x > _rightLimit ? _rightLimit : _trace.x;
	_trace.y = _trace.y < _topLimit ? _topLimit : _trace.y;
	_trace.y = _trace.y > _bottomLimit ? _bottomLimit : _trace.y;
}