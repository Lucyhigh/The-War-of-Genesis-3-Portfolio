#include "Stdafx.h"
#include "SecondScene.h"

HRESULT SecondScene::init(void)
{
    _count = 0;
    _moveCount = 0;
    _textBufferCnt = 0;
    _textIndex = 0;
    _frameIndex = 0;
    _loofIndex = 0;
    _alpha = 0;
    _eventAlpha = 0;
    _bgAlpha = 0;
    _textAlpha = 0;
    _bgMoved = WINSIZE_X;
    return S_OK;
}

void SecondScene::release(void)
{
}

void SecondScene::update(void)
{
    _count++;
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
    {
        if (_textBufferCnt < wcslen(_text[_textIndex].script))
        {
            _textBufferCnt = wcslen(_text[_textIndex].script);
        }
        else if (266 <= _textIndex && _textIndex <= 292)
        {
            _eventAlpha += RND->getInt(10);
            _textBufferCnt = 0;
            _textIndex++;
        }
        else if (_textIndex == 647 || _textIndex == 722 || _textIndex == 753)
        {
        }
        else
        {
            _textBufferCnt = 0;
            _textIndex++;
        }
    }

   
        if (_count % 3 == 0 && 35 < _loofIndex && _loofIndex <= 36)
        {
            _bgAlpha = 0;
            _textIndex++;
            _textBufferCnt = 0;
            _loofIndex = 0;
        }
    

    if (_count % 2 == 0 && _textBufferCnt < wcslen(_text[_textIndex].script))
    {
        _textBufferCnt++;
    }

    if (_textIndex == 9 || _textIndex == 85 || _textIndex == 199 || _textIndex == 210
        || _textIndex == 298 || _textIndex == 318 || _textIndex == 339 || _textIndex == 550)
    {
        _bgMoved -= 60;
        _alpha = 100;
        if (_bgMoved >= -WINSIZE_X * 0.7)
        {
            _alpha = 0;

        }
        else if (_bgMoved <= -WINSIZE_X)
        {
            _textIndex++;
            _alpha = 0;
        }
    }
    else
    {
        _alpha += 30.0f;
        _bgAlpha += 4.0f;
        _textAlpha += 4.0f;
    }

    if (_bgMoved <= -WINSIZE_X) _bgMoved = WINSIZE_X;
    if (_bgAlpha >= 255) _bgAlpha = 255;
    if (_alpha >= 255) _alpha = 255;
    if (_eventAlpha >= 255) _eventAlpha = 255;
    if (_textAlpha >= 230) _textAlpha = 230;
}

void SecondScene::render(void)
{
   /* for (size_t i = 0; i < BgImageNUMTWO; i++)
    {
        if (_textIndex <= _bgImage[i]._textIndex)
        {
            IMAGEMANAGER->alphaRender(_bgImage[i]._fileName, getMemDC(), _bgAlpha);
            break;
        }
    }*/

    if (_textIndex == 350 || _textIndex == 650)
    {
        IMAGEMANAGER->alphaRender("동아리skill배경", getMemDC(), _bgAlpha);
    }
   
   // int size = _text[_textIndex].imageMoodVec.size();

    if (259 <= _textIndex && _textIndex <= 297)
    {
        IMAGEMANAGER->alphaRender("노이즈", getMemDC(), -RND->getInt(3), -RND->getInt(3), _eventAlpha);
    }
    else if (_textIndex == 722)
    {

        IMAGEMANAGER->alphaRender("동아리skill배경2", getMemDC(), 100 + _eventAlpha);

        if (0 <= _loofIndex && _loofIndex <= 30)
        {
            if (_loofIndex % 3 == 1)
            {
                IMAGEMANAGER->render("유리킬2", getMemDC(), WINSIZE_X / 2 - WINSIZE_X / 4, WINSIZE_Y / 10);
                IMAGEMANAGER->alphaRender("컷전환", getMemDC(), 0, 0, _eventAlpha);
            }
            else
            {
                IMAGEMANAGER->render("유리킬", getMemDC(), WINSIZE_X / 2 - WINSIZE_X / 4, WINSIZE_Y / 10);
            }
        }
        else if (40 < _loofIndex && _loofIndex <= 70)
        {
            if (40 < _loofIndex && _loofIndex <= 48)IMAGEMANAGER->alphaRender("유리킬배경", getMemDC(), 0, 0, _bgAlpha);
            else if (48 < _loofIndex && _loofIndex <= 54)IMAGEMANAGER->alphaRender("유리킬배경2", getMemDC(), 0, 0, _bgAlpha);
            else if (54 < _loofIndex && _loofIndex <= 62)IMAGEMANAGER->alphaRender("유리킬배경3", getMemDC(), 0, 0, _bgAlpha);
            else if (62 < _loofIndex && _loofIndex <= 70)IMAGEMANAGER->alphaRender("유리킬배경4", getMemDC(), 0, 0, _bgAlpha);
        }
    }

    //for (int i = 0; i < size; i++)
    //{
    //    IMAGEMANAGER->alphaRender(_text[_textIndex].imageMoodVec[i], getMemDC(), (WINSIZE_X * (i + 1) / (size + 1)) - WINSIZE_X / 4, WINSIZE_Y / 10, _alpha);
    //}


    IMAGEMANAGER->alphaRender("텍스트창", getMemDC(), _textAlpha);
    FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.26, WINSIZE_Y*0.75, "a어린이날M", 27, 15, _text[_textIndex].name, wcslen(_text[_textIndex].name), RGB(0, 0, 0));

    const int SCRIPT_MAX_LENGTH = 55;
    FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.22, WINSIZE_Y*0.84, "나눔스퀘어_ac", 30, 100, _text[_textIndex].script, ((_textBufferCnt) > SCRIPT_MAX_LENGTH ? SCRIPT_MAX_LENGTH : (_textBufferCnt)), RGB(255, 255, 255));

    if (wcslen(_text[_textIndex].script) > SCRIPT_MAX_LENGTH && _textBufferCnt > SCRIPT_MAX_LENGTH)
    {
        FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.22, WINSIZE_Y*0.90, "나눔스퀘어_ac", 30, 100,
            _text[_textIndex].script + SCRIPT_MAX_LENGTH, (_textBufferCnt > wcslen(_text[_textIndex].script)) ?
            wcslen(_text[_textIndex].script) - SCRIPT_MAX_LENGTH : _textBufferCnt - SCRIPT_MAX_LENGTH, RGB(255, 255, 255));
    }

}
