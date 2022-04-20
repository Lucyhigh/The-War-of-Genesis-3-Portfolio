#include "Stdafx.h"
#include "ProgressBar.h"

HRESULT ProgressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_curIndex = 0;
	_pastIndex = 3;

    _hpIndex = 0;

    _cdt = 0;
    _count = 4;

	//_rc = RectMakeCenter(_x, _y, width, height);//실제 피
	//움직이는 실시간 바
	//_progressBarUp = IMAGEMANAGER->addImage("BarUp", "Resources/Images/Object/HpBarUp.bmp",
	//	0, 0, width, height, true, RGB(255, 0, 255));

	//고정 디폴트로 있는 바
	_progressBarDown = IMAGEMANAGER->findImage("pHpBar");
	width = _progressBarDown->getFrameWidth();
	return S_OK;
}

void ProgressBar::release(void)
{
}

void ProgressBar::update()
{
    if (_pastIndex != _curIndex)//
    {
        _cdt++;
        if (_count < _cdt)
        {
            _cdt = 0;
            cout << "_cdt : "<< _cdt << "_hpIndex: " << _hpIndex << endl;
            switch (_curIndex)
            {
            case 0:
                _progressBarDown = IMAGEMANAGER->findImage("pHpBar");
                if (_progressBarDown->getMaxFrameX() > _hpIndex)
                {
                    _hpIndex++;
                }
                //else if(_playerIndex > 7)//_rc = RectMakeCenter(_x, _y, _progressBarDown->getFrameWidth(), _progressBarDown->getFrameHeight());
                //else  _pastIndex =_curIndex;
                break;
            case 1:
                _progressBarDown = IMAGEMANAGER->findImage("eHpBar");
                if (_progressBarDown->getMaxFrameX() > _hpIndex)
                {
                    _hpIndex++;
                }
                //else if( _enemyIndex > 7)//_rc = RectMakeCenter(_x, _y, _progressBarDown->getFrameWidth(), _progressBarDown->getFrameHeight());
                //else  _pastIndex =_curIndex;
                break;
            }
        }
    }
    else
    {
      
    }
	
}

void ProgressBar::render(int x, int y)
{
	switch (_curIndex)
	{
	case 0:
		IMAGEMANAGER->frameRender("pHpBar",getMemDC(), x, y, _hpIndex,0);
        //_progressBarUp->render(getMemDC(), _rc.left + _progressBarDown->getFrameWidth() / 2,
        //	_y + _progressBarDown->getFrameHeight() / 2,
        //	0, 0, _width, _progressBarDown->getFrameHeight());
		break;
	case 1:
		IMAGEMANAGER->frameRender("eHpBar", getMemDC(), x, y, _hpIndex,0);
        //_progressBarUp->render(getMemDC(), _rc.left + _progressBarDown->getFrameWidth() / 2,
        //	_y + _progressBarDown->getFrameHeight() / 2,
        //	0, 0, _width, _progressBarDown->getFrameHeight());
		break;
	}

}//카메라값 확인해서 적용안되면 매개변수로 카메라값 추가해주기

void ProgressBar::setGauge(float currentScore, float maxScore)
{
	_width = (currentScore / maxScore) * _progressBarDown->getFrameWidth();//업 넓이로 교체필요
}

void ProgressBar::resetImgIdx()
{
     _hpIndex = 0;
     cout << "프레임 리셋 "<< endl;
}