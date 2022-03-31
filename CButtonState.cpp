#include "Stdafx.h"
#include "CButtonState.h"

HRESULT CButtonState::init(const char * imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint)
{
	return S_OK;
}

HRESULT CButtonState::init(const char * imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, CALLBACK_FUNCTION cbFunction)
{
	_callBackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);

//	this->init(imageName, ...);
	return S_OK;
}

void CButtonState::release(void)
{
}

void CButtonState::update(void)
{
	if (PtInRect(&_rc, _ptMouse))
	{
		if (_leftButtonDown) _direction = BUTTON_DIRECTION_DOWN;
		else if ()
		{
			if(_callBackFunction != nullptr) _callBackFunction();
		}
	}
	else
	{
		_callBackFunction = nullptr;
	}
}

void CButtonState::render(void)
{
	switch (_direction)
		case BUTTON_DIRECTION_NULL:
			_image->frameRender();
			break;
		case BUTTON_DIRECTION_DOWN:
			break;
		case BUTTON_DIRECTION_UP:
			break;

}
