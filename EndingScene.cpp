#include "Stdafx.h"
#include "EndingScene.h"

HRESULT EndingScene::init(void)
{
    _aniCursor = ANIMATIONMANAGER->findAnimation("normalCursor");
    _aniCursor->AniStart();
    SOUNDMANAGER->addSound("changeScene", "Resources/Sounds/changeScene.mp3", false, false);
    SOUNDMANAGER->addSound("Tears", "Resources/Sounds/Tears.mp3", true, true);
    _playIndex = 0;

	string path = "Resources/Sounds/endingScript/";
	_vSoundName = getFilesInDirectory(path, "*.mp3");
	for (string name : _vSoundName)
	{
		SOUNDMANAGER->addSound(name, path + name, false, false);
	}
    SOUNDMANAGER->play(_vSoundName[_playIndex], 1.0f);

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
    _isfadeOut =false;
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
    if (_textIndex == 0 || _textIndex == 3)
    {
        fadeIn();
    }
   
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _textIndex < 3)
    {
        if (_textBufferCnt < wcslen(_text[_textIndex].script))
        {
            _textBufferCnt = wcslen(_text[_textIndex].script);
        }
        else if (_textBufferCnt == wcslen(_text[_textIndex].script))
        {
            _textBufferCnt = 0;
            SOUNDMANAGER->play("changeScene", 0.5f);

            if (_textIndex != 2)_textIndex++;
            _bgIndex++;
            _alpha = 150;
            _fadeAlpha = 0;
            _isStory = false;
 
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
    
    if (_count % 2 == 0 && _textBufferCnt < wcslen(_text[_textIndex].script))
    {
        _textBufferCnt++;
    }

    if (!_isStory)
    {
        if (_textIndex <= 2)
        {
            if (_count > _cdt)
            {
                _count = 0;
                _isStory = true;
            }
        }
        if (SOUNDMANAGER->isPlaySound("01a"))
        {
            cout<< SOUNDMANAGER->getPosition("01a") <<endl;
            //if (SOUNDMANAGER->getPosition("01a") == SOUNDMANAGER->getLength("01a"))
            {

            }
        }
    }

    _alpha -= 10.0f;
    _bgAlpha += 4.0f;
    _textAlpha += 4.0f;

    if (_bgMoved <= -WINSIZE_X) _bgMoved = WINSIZE_X;
    if (_bgAlpha >= 255) _bgAlpha = 255;
    if (_alpha < 0) _alpha = 0;
    if (_eventAlpha >= 255) _eventAlpha = 255;
    if (_textAlpha >= 210) _textAlpha = 210;
    cout << _isStory << endl;

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
    if (_isfadeOut || _isFadeIn)
    {
        IMAGEMANAGER->alphaRender("cutChange", getMemDC(), _fadeAlpha);
    }

    IMAGEMANAGER->findImage("normalCursor")->aniRender(getMemDC(), _ptMouse.x, _ptMouse.y, _aniCursor);
}

void EndingScene::fadeout()
{
    if (_isfadeOut)
    {
        _fadeAlpha += 1.0f;
        if (_fadeAlpha > 253)
        {
            _isfadeOut = false;
            _fadeAlpha = 0;
            _textIndex++;
            //if (_textIndex == 8) SCENEMANAGER->changeScene("title");
        }
    }
}

void EndingScene::fadeIn()
{
    if (_fadeAlpha > 30) _fadeAlpha -= 2.0f;
    else
    {
        _fadeAlpha = 0;
        _isFadeIn = false;
    }
}

//if (_isPlay && !_isPause)
//{
//    if (_score >= _maxScore)
//    {
//        nextSound();
//    }
//    _score = SOUNDMANAGER->getPosition(_vMp3Name[_playIndex]);
//    _maxScore = SOUNDMANAGER->getLength(_vMp3Name[_playIndex]);
//}
