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

    _hpRc = RectMakeCenter(_x, _y, width, height);//실제 피
    _mpRc = RectMakeCenter(_x, _y+50, width, height);//실제 피
	//움직이는 실시간 바
	_progressHpBarUp = IMAGEMANAGER->addImage("pHpGauge", "Resources/Images/Object/pHpGauge.bmp", 0, 0, width, height, MGT);
    _progressMpBarUp = IMAGEMANAGER->addImage("pMpGauge", "Resources/Images/Object/pMpGauge.bmp", 0, 0, width, height, MGT);

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
                if (_hpIndex >= 7)
                {
                    _hpRc = RectMakeCenter(_x, _y, _progressBarDown->getFrameWidth(), _progressBarDown->getFrameHeight());
                    _mpRc = RectMakeCenter(_x, _y, _progressBarDown->getFrameWidth(), _progressBarDown->getFrameHeight());
                }
                //else  _pastIndex =_curIndex;
                break;
            case 1:
                _progressBarDown = IMAGEMANAGER->findImage("eHpBar");
                if (_progressBarDown->getMaxFrameX() > _hpIndex)
                {
                    _hpIndex++;
                }
                if (_hpIndex >= 7)
                {
                    _hpRc = RectMakeCenter(_x, _y, _progressBarDown->getFrameWidth(), _progressBarDown->getFrameHeight());
                    _mpRc = RectMakeCenter(_x, _y, _progressBarDown->getFrameWidth(), _progressBarDown->getFrameHeight());
                }
                break;
            }
        }
    }
}
      
void ProgressBar::render(int x, int y)
{
	switch (_curIndex)
	{
	case 0:
		IMAGEMANAGER->frameRender("pHpBar",getMemDC(), x, y, _hpIndex,0);
        _progressHpBarUp->render(getMemDC(), x, y, 0, 0, _width, _progressBarDown->getFrameHeight());
        _progressMpBarUp->render(getMemDC(), x, y, 0, 0, _width, _progressBarDown->getFrameHeight());
		break;

	case 1:
		IMAGEMANAGER->frameRender("eHpBar", getMemDC(), x, y, _hpIndex,0);
        _progressHpBarUp->render(getMemDC(), x, y, 0, 0, _width, _progressBarDown->getFrameHeight());
        _progressMpBarUp->render(getMemDC(), x, y, 0, 0, _width, _progressBarDown->getFrameHeight());
		break;
	}

}//카메라값 확인해서 적용안되면 매개변수로 카메라값 추가해주기

void ProgressBar::setGauge(float currentScore, float maxScore)
{
	_width = (currentScore / maxScore) * _progressHpBarUp->getFrameWidth();
	_width = (currentScore / maxScore) * _progressMpBarUp->getFrameWidth();
}

void ProgressBar::resetImgIdx()
{
     _hpIndex = 0;
}