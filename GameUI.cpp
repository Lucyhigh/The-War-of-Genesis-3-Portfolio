#include "Stdafx.h"
#include "GameUI.h"
HRESULT GameUI::init(void)
{
    _image = new Image;
	_image = IMAGEMANAGER->findImage("button");
    _buttonIndex = 0;
    _uiPos = { 0,0 };
	for (int i = -1; i < 1; i++)
	{
		for (int j = -1; j < 1; j++)
		{
            ImgInfo _imageInfo;
            _imageInfo._buttonRect = RectMake(0, 0, _image->getWidth(), _image->getHeight());//
            _imageInfo._imgPos = { -250 * (-1)*i, -50 * (-2)*j };
            _imageInfo._defaultPos = { -250 * (-1)*i, -50 * (-2)*j };
            _imageInfo._index = _buttonIndex;
                
			_vMenuButton.push_back(_imageInfo);
            _vMenuButton[_buttonIndex]._textInfo = _uiText[_buttonIndex];
            _buttonIndex++;
        };
	}

  /*  _vMenuButton[0]._textInfo = { "ぞし0" };
    _vMenuButton[1]._textInfo = { "ぞし1" };
    _vMenuButton[2]._textInfo = { "ぞし2" };
    _vMenuButton[3]._textInfo = { "ぞし3" };
		*/
	_isTurn = false;
	return S_OK;
}

void GameUI::release(void)
{
    _image->release();
    SAFE_DELETE(_image);
}

void GameUI::update(void)
{
	
    if (_isTurn)
    {

        for (_viMenuButton = _vMenuButton.begin(); _viMenuButton != _vMenuButton.end(); ++_viMenuButton)
        {
            if (PtInRect(&_viMenuButton->_buttonRect, _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
            {
                cout << "hkkkkkkkkk" << endl;
                _isTurn = false;
            }
        }
    }

}

void GameUI::render(void)
{
	if (_isTurn)
	{
        for (_viMenuButton = _vMenuButton.begin(); _viMenuButton != _vMenuButton.end(); ++_viMenuButton)
		{
			IMAGEMANAGER->render("button", getMemDC(), _viMenuButton->_imgPos.x, _viMenuButton->_imgPos.y);
		}
	}
            
    IMAGEMANAGER->render("mapInfoAll", getMemDC(), WINSIZE_X - 230, 0);
}

POINT GameUI::getPos()
{
	return _uiPos;
}

void GameUI::showBattleMenu(POINT menuPos)
{
    _isTurn = true;
    for (_viMenuButton = _vMenuButton.begin(); _viMenuButton != _vMenuButton.end(); ++_viMenuButton)
    {
        _uiPos = { menuPos.x + _viMenuButton->_defaultPos.x, menuPos.y + _viMenuButton->_defaultPos.y };
        _viMenuButton->_imgPos = _uiPos;
        _viMenuButton->_buttonRect.left = _uiPos.x;
        _viMenuButton->_buttonRect.top = _uiPos.y;
    }
}
