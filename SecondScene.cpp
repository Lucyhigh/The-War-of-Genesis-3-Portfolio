#include "Stdafx.h"
#include "SecondScene.h"

HRESULT SecondScene::init(void)
{
	_aniCursor = ANIMATIONMANAGER->findAnimation("normalCursor");
	_aniCursor->AniStart();
	SOUNDMANAGER->addSound("changeScene", "Resources/Sounds/changeScene.mp3", false, false);
	SOUNDMANAGER->addSound("Memory", "Resources/Sounds/Memory.mp3", true, true);
	SOUNDMANAGER->addSound("Tears", "Resources/Sounds/Tears.mp3", true, true);
	SOUNDMANAGER->play("Tears", 0.1f);

	_isPause = true;
	_isPlay = false;
	_soundVolume = 1.0f;
	_score = 0.0f;
	_maxScore = 1.0f;
	_playIndex = 0;

	string path = "Resources/Sounds/Script/";
	_vSoundName = getFilesInDirectory(path, "*.mp3");
	for (string name : _vSoundName)
	{
		//cout << name << endl;
		SOUNDMANAGER->addSound(name, path + name, false, false);
	}
	SOUNDMANAGER->play(_vSoundName[_playIndex], 1.0f);

    _count = 0;
    _moveCount = 0;
    _textBufferCnt = 0;
    _textIndex = 0;
    _frameIndex = 0;
    _loofIndex = 0;
    _alpha = 255;
    _eventAlpha = 0;
    _bgAlpha = 0;
    _textAlpha = 0;
    _fadeAlpha = 0;
    _bgMoved = WINSIZE_X;


    return S_OK;
}

void SecondScene::release(void)
{
}

void SecondScene::update(void)
{
    _count++;
	int size = _text[_textIndex].imageVec.size();
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _textIndex !=9 && _textIndex < 47)
    {
        if (_textBufferCnt < wcslen(_text[_textIndex].script))
        {
            _textBufferCnt = wcslen(_text[_textIndex].script);
        }
        else if(_textBufferCnt == wcslen(_text[_textIndex].script))
        {
            _textBufferCnt = 0;
			SOUNDMANAGER->play("changeScene", 1.0f);
           if(_textIndex<TEXTNum) _textIndex++;
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
			SOUNDMANAGER->play(_vSoundName[_playIndex], _soundVolume);
        }
    }
    if (_textIndex == 9 || _textIndex == 47)
    {
        _isfadeOut = true;
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
    if (_isfadeOut)
    {
        fadeout();
    }

	//cout << _textIndex << endl;
}

void SecondScene::render(void)
{
    for (size_t i = 0; i < BgImageNUM; i++)
    {
        if (_textIndex <= _bgImage[i]._textIndex)
        {
            IMAGEMANAGER->alphaRender(_bgImage[i]._fileName, getMemDC(), _bgAlpha);
            break;
        }
    }

	int size = _text[_textIndex].imageVec.size();
    for (int i = 0; i < size; i++)
    {
		if (size == 1)
		{
			IMAGEMANAGER->alphaRender(_text[_textIndex].imageVec[i], getMemDC(), CENTER_X - 230, CENTER_Y-120, _alpha);
		}
		else
		{
			IMAGEMANAGER->alphaRender(_text[_textIndex].imageVec[i], getMemDC(), (WINSIZE_X * (i + 1) / (size + 1)) - WINSIZE_X / 3, WINSIZE_Y / 10, _alpha);
		}
    }

    IMAGEMANAGER->alphaRender("storyText", getMemDC(), WINSIZE_X*0.16, WINSIZE_Y*0.72, _textAlpha);
    FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.17, WINSIZE_Y*0.75, "가을체", 20, 15, _text[_textIndex].name, wcslen(_text[_textIndex].name), TA_LEFT, RGB(72, 221, 157));

    const int SCRIPT_MAX_LENGTH = 48;
    FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.17, WINSIZE_Y*0.80, "가을체", 18, 100, _text[_textIndex].script, 
		((_textBufferCnt) > SCRIPT_MAX_LENGTH ? SCRIPT_MAX_LENGTH : (_textBufferCnt)), TA_LEFT, RGB(255, 255, 255));

    if (wcslen(_text[_textIndex].script) > SCRIPT_MAX_LENGTH && _textBufferCnt > SCRIPT_MAX_LENGTH)
    {
        FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.17, WINSIZE_Y*0.84, "가을체", 18, 100,
            _text[_textIndex].script + SCRIPT_MAX_LENGTH, (_textBufferCnt > wcslen(_text[_textIndex].script)) ?
            wcslen(_text[_textIndex].script) - SCRIPT_MAX_LENGTH : _textBufferCnt - SCRIPT_MAX_LENGTH, TA_LEFT, RGB(255, 255, 255));
    }

	if (_isfadeOut)
	{
		IMAGEMANAGER->alphaRender("cutChange", getMemDC(), _fadeAlpha);
	}

	IMAGEMANAGER->findImage("normalCursor")->aniRender(getMemDC(), _ptMouse.x, _ptMouse.y, _aniCursor);
}
void SecondScene::fadeout()
{
	if (_isfadeOut)
	{
		_fadeAlpha += 2.0f;
		if (_fadeAlpha > 253)
		{
			_isfadeOut = false;
			_fadeAlpha = 0;
            _textBufferCnt = 0;
            _alpha = 150;
            _textIndex++;
            if (_textIndex == 47 ) SCENEMANAGER->changeScene("final");
		}
	}
}