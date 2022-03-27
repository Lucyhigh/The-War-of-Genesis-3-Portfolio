#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init(void)
{
    _startBit = 0;

	_image= IMAGEMANAGER->findImage("TitleBg");
    _buttonSize = {140, 30};
    _SceneBoxSize = {150, 50};
    _fadeAlpha = 0;
    int buttonNum = 3;
    for (int i = 0; i < buttonNum; i++)
    {
            TitlebuttomInfo _titleButtomInfo;
            POINT _buttomPos = { CENTER_X, (WINSIZE_Y - 200) + i*50 };
           _titleButtomInfo._buttonRect = RectMakeCenter(_buttomPos.x, _buttomPos.y, _buttonSize.x, _buttonSize.y);
           _titleButtomInfo._index = i;

           _vTitleButton.push_back(_titleButtomInfo);
           _vTitleButton[i]._textInfo = _uiText[i];
    }

    int SceneIndex = 0;
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 7; y++)
        {
            TitlebuttomInfo _sceneButtomInfo;
            POINT _buttomPos = { 200 + x* 280,  200 + y * 80 };
            _sceneButtomInfo._buttonRect = RectMakeCenter(_buttomPos.x, _buttomPos.y, _buttonSize.x, _buttonSize.y);
            _sceneButtomInfo._index = SceneIndex;

            _vSceneButton.push_back(_sceneButtomInfo);
            _vSceneButton[SceneIndex]._textInfo = _sceneText[SceneIndex];
            SceneIndex++;
        }
    }
	_ani = new AniSceneTitle;
	_ani->init();
    _isfadeOut = false;
	_alpha = 0.0f;
	_isAlphaIncrese = false;

	return S_OK;
}

void TitleScene::release(void)
{
   // _ani->release();
	SAFE_DELETE(_ani);
}

void TitleScene::update(void)
{
    // 0000 타이틀화면
    if (_startBit.none() == 1)
    {
        _ani->update();
        for (_viTitleButton = _vTitleButton.begin(); _viTitleButton != _vTitleButton.end(); ++_viTitleButton)
        {
            if (PtInRect(&_viTitleButton->_buttonRect, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
            {
                    //애니메이션이 다 돌면 다른 화면으로 넘어가야함
                switch (_viTitleButton->_index)
                {
                case 0:
                    _isfadeOut = true;
                    if (_fadeAlpha > 248)
                    {
                        _startBit.reset();
                        _startBit.set(0);
                    }
                    break;
                case 1:
                    _startBit.reset();
                    _startBit.set(1);
                    break;
                case 2:
                    PostQuitMessage(0);
                    break;
                }
            }
        }
    }
    // 0001 스타트게임
    else if (_startBit.test(0) == 1)
    {
        for (_viSceneButton = _vSceneButton.begin(); _viSceneButton != _vSceneButton.end(); ++_viSceneButton)
        {
            if (PtInRect(&_viSceneButton->_buttonRect, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
            {
                cout << _viSceneButton->_index << endl;
                switch (_viSceneButton->_index)
                {
                case 13:
                    _isfadeOut = true;
                    if (_fadeAlpha > 248) SCENEMANAGER->changeScene("final");
                    break;
                }
            }
        }
    }
    // 0010 로드게임
    else if (_startBit.test(1) == 1)
    {

    }
	if (_alpha == 0 || _alpha == 255) _isAlphaIncrese = !_isAlphaIncrese;
	if (_isAlphaIncrese)_alpha += 1.0f; 
    else _alpha -= 1.0f;

    if (_isfadeOut)
    {
        fadeout();
    }
}

void TitleScene::render(void)
{
    int _textPosY = 5;
    if (_startBit.none() == 1)
    {
        IMAGEMANAGER->render("TitleBg", getMemDC());
        _ani->render(CENTER_X - 110, CENTER_Y-90);
        IMAGEMANAGER->alphaRender("TitleName",getMemDC(),CENTER_X,CENTER_Y-50,_alpha);
        for (_viTitleButton = _vTitleButton.begin(); _viTitleButton != _vTitleButton.end(); ++_viTitleButton)
        {
            if (PtInRect(&_viTitleButton->_buttonRect, _ptMouse))
            {
                FONTMANAGER->drawText(getMemDC(), 
                    (_viTitleButton->_buttonRect.left + _viTitleButton->_buttonRect.right) / 2,
                    _viTitleButton->_buttonRect.top , "가을체", 28, 13, _viTitleButton->_textInfo,
                    wcslen(_viTitleButton->_textInfo), TA_CENTER, RGB(170, 170, 170));
            }
            else
            {
                FONTMANAGER->drawText(getMemDC(),
                    (_viTitleButton->_buttonRect.left + _viTitleButton->_buttonRect.right) / 2,
                    _viTitleButton->_buttonRect.top, "가을체", 28, 13, _viTitleButton->_textInfo,
                    wcslen(_viTitleButton->_textInfo), TA_CENTER, RGB(255, 255, 255));
            }
        }
    }
    else if (_startBit.test(0) == 1)
    {
        IMAGEMANAGER->render("SceneList", getMemDC());

        for (_viSceneButton = _vSceneButton.begin(); _viSceneButton != _vSceneButton.end(); ++_viSceneButton)
        {
            if (PtInRect(&_viSceneButton->_buttonRect, _ptMouse))
            {
                FONTMANAGER->drawText(getMemDC(),
                    (_viSceneButton->_buttonRect.left + _viSceneButton->_buttonRect.right) / 2,
                    _viSceneButton->_buttonRect.top, "가을체", 28, 13, _viSceneButton->_textInfo,
                    wcslen(_viSceneButton->_textInfo), TA_CENTER, RGB(255, 255, 255));
            }
            else
            {
                FONTMANAGER->drawText(getMemDC(),
                    (_viSceneButton->_buttonRect.left + _viSceneButton->_buttonRect.right) / 2,
                    _viSceneButton->_buttonRect.top, "가을체", 28, 13, _viSceneButton->_textInfo,
                    wcslen(_viSceneButton->_textInfo), TA_CENTER, RGB(170, 170, 170));

            }
        }
    }
    else if (_startBit.test(1) == 1)
    {
        IMAGEMANAGER->render("Devil", getMemDC());
    }
    IMAGEMANAGER->alphaRender("cutChange", getMemDC(), _fadeAlpha);
}

void TitleScene::fadeout()
{
    _fadeAlpha += 2.0f;
   
    if (_fadeAlpha >= 254)
    {
        _fadeAlpha = 0;
        _isfadeOut = false; 
        cout << _isfadeOut << endl;
    }
}
