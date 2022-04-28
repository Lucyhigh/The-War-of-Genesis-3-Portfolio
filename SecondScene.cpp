#include "Stdafx.h"
#include "SecondScene.h"

HRESULT SecondScene::init(void)
{
	_aniCursor = ANIMATIONMANAGER->findAnimation("normalCursor");
	_aniCursor->AniStart();
	SOUNDMANAGER->addSound("changeScene", "Resources/Sounds/changeScene.mp3", false, false);
	SOUNDMANAGER->addSound("Tears", "Resources/Sounds/Tears.mp3", true, true);
	SOUNDMANAGER->play("Tears", 0.8f);
	_playIndex = 0;

	string path = "Resources/Sounds/secondScript/";
	_vSoundName = getFilesInDirectory(path, "*.mp3");
	for (string name : _vSoundName)
	{
		SOUNDMANAGER->addSound(name, path + name, false, false);
	}
	SOUNDMANAGER->play(_vSoundName[_playIndex], 1.0f);

	_count = 0;
	_moveCount = 0;
	_textBufferCnt = 0;
	_frameIndex = 0;
	_textIndex = 0;
	_bgIndex = 0;
	_alpha = 255;
	_eventAlpha = 0;
	_bgAlpha = 0;
	_textAlpha = 0;
	_fadeAlpha = 0;
	_bgMoved = WINSIZE_X;
	_isFadeOut = false;
	_isFadeIn = true;

	return S_OK;
}

void SecondScene::release(void){
}

void SecondScene::update(void)
{
	_count++;
	int size = _text[_textIndex].imageVec.size();
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _textIndex != 9 && _textIndex < 47)
	{
		if (_textBufferCnt < wcslen(_text[_textIndex].script))
		{
			_textBufferCnt = wcslen(_text[_textIndex].script);
		}
		else if (_textBufferCnt == wcslen(_text[_textIndex].script))
		{
			_textBufferCnt = 0;
			SOUNDMANAGER->play("changeScene", 0.5f);
			if (_textIndex == _bgImage[_bgIndex]._textIndex)
			{
				_bgIndex++;
			}
			if (_textIndex < TEXTNum) _textIndex++;
			_alpha = 150;

			SOUNDMANAGER->stop(_vSoundName[_playIndex]);
			if (_playIndex < _vSoundName.size() - 1)
			{
				_playIndex++;
			}
			else
			{
				_playIndex = _vSoundName.size() - 1;
			}
			SOUNDMANAGER->play(_vSoundName[_playIndex], 1.0f);
		}
	}
	if (_count % 100 == 0 && (_textIndex == 9 || _textIndex == 46))
	{
		_isFadeOut = true;
	}

	if (_count % 2 == 0 && _textBufferCnt < wcslen(_text[_textIndex].script))
	{
		_textBufferCnt++;
	}

	_alpha -= 10.0f;
	_bgAlpha += 4.0f;
	_textAlpha += 4.0f;

	if (_bgMoved <= -WINSIZE_X) _bgMoved = WINSIZE_X;
	if (_bgAlpha >= 255) _bgAlpha = 255;
	if (_alpha < 0) _alpha = 0;
	if (_eventAlpha >= 255) _eventAlpha = 255;
	if (_textAlpha >= 210) _textAlpha = 210;

	if (_isFadeOut)
	{
		fadeout();
	}
}

void SecondScene::render(void)
{
	IMAGEMANAGER->alphaRender(_bgImage[_bgIndex]._fileName, getMemDC(), _bgAlpha);

	int size = _text[_textIndex].imageVec.size();
	IMAGEMANAGER->alphaRender(_text[_textIndex].imageVec[0], getMemDC(), CENTER_X - 230, CENTER_Y - 120, _alpha);


	IMAGEMANAGER->alphaRender("storyText", getMemDC(), WINSIZE_X*0.16, WINSIZE_Y*0.76, _textAlpha);
	FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.17, WINSIZE_Y*0.79, "가을체", 20, 15, _text[_textIndex].name, wcslen(_text[_textIndex].name), TA_LEFT, RGB(72, 221, 157));

	const int SCRIPT_MAX_LENGTH = 44;
	FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.17, WINSIZE_Y*0.85, "가을체", 18, 100, _text[_textIndex].script,
		((_textBufferCnt) > SCRIPT_MAX_LENGTH ? SCRIPT_MAX_LENGTH : (_textBufferCnt)), TA_LEFT, RGB(255, 255, 255));

	if (wcslen(_text[_textIndex].script) > SCRIPT_MAX_LENGTH && _textBufferCnt > SCRIPT_MAX_LENGTH)
	{
		FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.17, WINSIZE_Y * 0.89, "가을체", 18, 100,
			_text[_textIndex].script + SCRIPT_MAX_LENGTH, (_textBufferCnt > wcslen(_text[_textIndex].script)) ?
			wcslen(_text[_textIndex].script) - SCRIPT_MAX_LENGTH : _textBufferCnt - SCRIPT_MAX_LENGTH, TA_LEFT, RGB(255, 255, 255));
	}

	if (_isFadeOut)
	{
		IMAGEMANAGER->alphaRender("cutChange", getMemDC(), _fadeAlpha);
	}

	IMAGEMANAGER->findImage("normalCursor")->aniRender(getMemDC(), _ptMouse.x, _ptMouse.y, _aniCursor);
}
void SecondScene::fadeout()
{
	if (_isFadeOut)
	{
		_fadeAlpha += 2.0f;
		if (_fadeAlpha > 253)
		{
			_isFadeOut = false;
			_fadeAlpha = 0;
			_textBufferCnt = 0;
			_alpha = 150;
			if (_textIndex == 9)
			{
				_playIndex++;
				SOUNDMANAGER->play(_vSoundName[_playIndex], 1.0f);
				_textIndex++;
			}
			if (_textIndex == 46)
			{
				SOUNDMANAGER->stop("Tears");
				SOUNDMANAGER->stop(_vSoundName[_playIndex]);
				SCENEMANAGER->changeScene("final");
			}
		}
	}
}