#include "Stdafx.h"
#include "EndingScene.h"

HRESULT EndingScene::init(void)
{
    _aniCursor = ANIMATIONMANAGER->findAnimation("normalCursor");
    _aniCursor->AniStart();
    SOUNDMANAGER->addSound("changeScene", "Resources/Sounds/changeScene.mp3", false, false);
    SOUNDMANAGER->addSound("Tears", "Resources/Sounds/Tears.mp3", true, true);
    _soundIndex = 0;

	string path = "Resources/Sounds/endingScript/";
	_vSoundName = getFilesInDirectory(path, "*.mp3");
	for (string name : _vSoundName)
	{
		SOUNDMANAGER->addSound(name, path + name, false, false);
	}
    SOUNDMANAGER->play(_vSoundName[_soundIndex], 1.0f);

    _count = 0;
    _cdt = 200;
    _textBufferCnt = 0;
    _textIndex = 0;
    _bgIndex = 0;
    _alpha = 255;
    _eventAlpha = 0;
    _bgAlpha = 0;
    _textAlpha = 0;
    _fadeAlpha = 255;
    _isFadeOut =false;
    _isFadeIn =true;
    _bgMoved = WINSIZE_X;
    _isStory = false;

    return S_OK;
}

void EndingScene::release(void)
{
}

void EndingScene::update(void)
{
    _count++;
   
    if (!_isFadeIn && _isStory && KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        if (_textBufferCnt < wcslen(_text[_textIndex].script))
        {
			_textBufferCnt = wcslen(_text[_textIndex].script);
        }
        else if (_textBufferCnt == wcslen(_text[_textIndex].script))
        {
            SOUNDMANAGER->play("changeScene", 0.5f);

            _textBufferCnt = 0;
            _alpha = 150;
            _fadeAlpha = 255;
            _isStory = false;
			_bgIndex++;
			_textIndex++;

			SOUNDMANAGER->stop(_vSoundName[_soundIndex]);
			if (_soundIndex < _vSoundName.size() - 1)
			{
				_soundIndex++;
			}
			else
			{
				_soundIndex = _vSoundName.size() - 1;
			}
			SOUNDMANAGER->play(_vSoundName[_soundIndex], 1.0f);
        }
    }
    
    if (_count % 5 == 0 && _textBufferCnt < wcslen(_text[_textIndex].script))
    {
        _textBufferCnt++;
    }

    if (!_isStory)
    {
        if (_textIndex <= 2)
        {
            if (_count % 200 ==0)
            {
                _count = 0;
                _textBufferCnt = 0;
                _cdt = 40;
                _isStory = true;
            }
        }
		else if (_textIndex >= 3)
		{
			float soundPos = 0.0f;
			float maxSoundSize = 0.0f;
			float cdt = 5;
			soundPos = SOUNDMANAGER->getPosition(_vSoundName[3]);
			maxSoundSize = SOUNDMANAGER->getLength(_vSoundName[3]);//getLength 122070
			float indexCount = soundPos / maxSoundSize * 100;
			if (indexCount < 100)
			{
				if (_count % 500 == 0 || KEYMANAGER->isOnceKeyDown(VK_SPACE))
				{
					if (2 <= _bgIndex && _bgIndex  <=10)
					{
                        _bgIndex++;
                        _count = 0;
                        _fadeAlpha = 255;
                        _isFadeIn = true;
						if (!(_soundIndex == 3 || _bgIndex == 8 || _bgIndex ==10)) SOUNDMANAGER->stop(_vSoundName[_soundIndex]);

						if (_soundIndex < 6 || _bgIndex == 7 || _bgIndex == 9)
						{
							SOUNDMANAGER->play(_vSoundName[++_soundIndex], 1.0f);
						}
					}

                    if (_bgIndex == 11)
                    {
                        _isStory = true;
                        _count = 0;
                        SOUNDMANAGER->play(_vSoundName[++_soundIndex], 1.0f);
                    }
				}
			}
		}
    }
    
    if (_bgIndex == 11)
    {
        if (_count % 300 == 0)
        {
            _fadeAlpha = 0;
            _isFadeOut = true;
        }
        else if (_count % 700 == 0)
        {
            SOUNDMANAGER->stop(_vSoundName[_soundIndex]);
            SOUNDMANAGER->stop(_vSoundName[3]);
            SCENEMANAGER->changeScene("title");
        }
    }
   //cout << "  _bgIndex " << _bgIndex << "_soundIndex " << _soundIndex << endl;

    _alpha -= 10.0f;
    _bgAlpha += 4.0f;
    _textAlpha += 4.0f;

    if (_bgMoved <= -WINSIZE_X) _bgMoved = WINSIZE_X;
    if (_bgAlpha >= 255) _bgAlpha = 255;
    if (_alpha < 10) _alpha = 0;
    if (_eventAlpha >= 255) _eventAlpha = 255;
    if (_textAlpha >= 210) _textAlpha = 210;

	if (_isFadeIn ||_bgIndex ==3)
	{
		fadeIn();
	}
    if (_isFadeOut)
    {
        fadeout();
    }
}

void EndingScene::render(void)
{
    for (size_t i = 0; i < BgImageNUMTWO; i++)
    {
        if (_bgIndex <= _bgImage[i]._textIndex)
        {
            IMAGEMANAGER->alphaRender(_bgImage[i]._fileName, getMemDC(), _bgAlpha);
            break;
        }
    }

    if (_isStory)
    {
        int size = _text[_textIndex].imageVec.size();
        for (int i = 0; i < size; i++)
        {
            if (size == 1)
            {
                IMAGEMANAGER->alphaRender(_text[_textIndex].imageVec[i], getMemDC(), CENTER_X - 230, CENTER_Y - 120, _alpha);
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
    }
    if (_isFadeOut || _isFadeIn)
    {
        IMAGEMANAGER->alphaRender("cutChange", getMemDC(), _fadeAlpha);
    }

    IMAGEMANAGER->findImage("normalCursor")->aniRender(getMemDC(), _ptMouse.x, _ptMouse.y, _aniCursor);
}

void EndingScene::fadeout()
{
    if (_isFadeOut)
    {
        _fadeAlpha += 1.0f;
        if (_fadeAlpha > 253)
        {
            _isFadeOut = false;
            _fadeAlpha = 0;
           
        }
    }
}

void EndingScene::fadeIn()
{
    if (_isFadeIn)
    {
        if (_fadeAlpha > 10)
        {
            _fadeAlpha -= 1.0f;
        }
        else
        {
            _isFadeIn = false;
            _fadeAlpha = 255;
        }
    }
}