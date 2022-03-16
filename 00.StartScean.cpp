#include "Stdafx.h"
#include "00.StartScean.h"

HRESULT StartScean::init(void)
{


	_alpha = _bgAlpha = 0;
	_isAlphaIncrese = false;

	return S_OK;
}

void StartScean::release(void)
{
}

void StartScean::update(void)
{

	_bgAlpha += 1.5f;
	if (_bgAlpha >= 225) _bgAlpha = 255;


	if (_bgAlpha == 255)
	{
		if (_alpha == 0 || _alpha == 255) _isAlphaIncrese != _isAlphaIncrese;
		if (_isAlphaIncrese)_alpha += 1.0f; else _alpha -= 1.5f;
	}

}

void StartScean::render(void)
{
	
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS); 

	char text[128];
	sprintf(text, " ¿À·ù ¾Æ´Ô. ¾Æ¹«Æ° ¾Æ´Ô ");
	TextOut(getMemDC(), WINSIZE_X / 2-40 , WINSIZE_Y / 2, text, strlen(text));
}
