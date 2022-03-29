#include "Stdafx.h"
#include "Camera.h"

Camera::Camera()
{
	_trace.x = CENTER_X;
	_trace.y = CENTER_Y;
	_count = 0;

	_screen = RectMakeCenter(_trace.x, _trace.y, WINSIZE_X, WINSIZE_Y);
	_leftLimit = CENTER_X;
}

HRESULT Camera::init(void)
{
	return S_OK;
}

void Camera::release(void)
{

}

void Camera::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) || _ptMouse.x >WINSIZE_X -10)
	{
		_trace.x += 10;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
        _trace.x -= 10;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
        _trace.y -= 10;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN) || _ptMouse.y > WINSIZE_Y - 10)
	{
        _trace.y += 10;
	}
	_screen = RectMakeCenter(_trace.x, _trace.y, WINSIZE_X, WINSIZE_Y);
}

void Camera::render(void)
{
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