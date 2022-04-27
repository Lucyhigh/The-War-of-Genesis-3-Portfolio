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
    _width = width;

    _hpRc = RectMakeCenter(_x, _y,width,height);//실제 피
    _mpRc = RectMakeCenter(_x, _y,width,height);//실제 피
	//움직이는 실시간 바
    _progressHpBarUp = IMAGEMANAGER->addImage("pHpGauge", "Resources/Images/UI/pHpGauge.bmp", 0, 0, width, height, MGT);
    _progressMpBarUp = IMAGEMANAGER->addImage("pMpGauge", "Resources/Images/UI/pMpGauge.bmp", 0, 0, width, height, MGT);

    //width = _progressHpBarUp->getWidth();

	//고정 디폴트로 있는 바
	_progressBarDown = IMAGEMANAGER->findImage("pHpBar");

	return S_OK;
}

void ProgressBar::release(void)
{
}

void ProgressBar::update()
{
    if (_pastIndex != _curIndex)
    {
        _cdt++;
        if (_count < _cdt)
        {
            _cdt = 0;
            switch (_curIndex)
            {
            case 0:
                _progressBarDown = IMAGEMANAGER->findImage("pHpBar");
                if (_progressBarDown->getMaxFrameX() > _hpIndex)
                {
                    _hpIndex++;
                }
                if (_hpIndex >= 10)
                {
                    _hpRc = RectMakeCenter(_x, _y, _progressBarDown->getWidth(), _progressBarDown->getHeight());
                    _mpRc = RectMakeCenter(_x, _y, _progressBarDown->getWidth(), _progressBarDown->getHeight());
                }
                break;
            case 1:
                _progressBarDown = IMAGEMANAGER->findImage("eHpBar");
                if (_progressBarDown->getMaxFrameX() > _hpIndex)
                {
                    _hpIndex++;
                }
                if (_hpIndex >= 14)
                {
                    _hpRc = RectMakeCenter(_x, _y, _progressBarDown->getWidth(), _progressBarDown->getHeight());
                    _mpRc = RectMakeCenter(_x, _y, _progressBarDown->getWidth(), _progressBarDown->getHeight());
                }
                break;
            }
        }
    }
}
	//setGauge랑 curHp 두개 다 업데이트 계속 필요
	//

      
void ProgressBar::render(int x, int y)
{
    int progressPosX = 40;

    switch (_curIndex)
    {
    case 0:
        IMAGEMANAGER->frameRender("pHpBar", getMemDC(), x, y, _hpIndex, 0);
		if (_hpIndex >= 10)
		{
			_progressHpBarUp->render(getMemDC(), x + progressPosX, y + 17, 0, 0, _width, _progressHpBarUp->getHeight());
			_progressMpBarUp->render(getMemDC(), x + progressPosX, y + 25, 0, 0, _width, _progressMpBarUp->getHeight());
			//renderHpSpNumImg();
		}
        break;

    case 1:
        IMAGEMANAGER->frameRender("eHpBar", getMemDC(), x, y, _hpIndex, 0);
		if (_hpIndex >= 10)
		{
			_progressHpBarUp->render(getMemDC(), x + progressPosX, y + 13, 0, 0, _width, _progressHpBarUp->getHeight());
			_progressMpBarUp->render(getMemDC(), x + progressPosX, y + 25, 0, 0, _width, _progressMpBarUp->getHeight());
		}
        break;
    }
}

void ProgressBar::setGauge(float currentScore, float maxScore)
{
	_width = (currentScore / maxScore) * _progressHpBarUp->getWidth();
	_width = (currentScore / maxScore) * _progressMpBarUp->getWidth();
}

void ProgressBar::resetImgIdx()
{
     _hpIndex = 0;
}

void ProgressBar::renderHpSpNumImg(int x, int y, int curHp, int curSp, int MaxHp, int MaxSp)
{
	// HP
	if (curHp > 99)      IMAGEMANAGER->frameRender("pHpBarNum", getMemDC(), x, y, curHp / 100 % 10, 0);
	if (curHp > 9)       IMAGEMANAGER->frameRender("pHpBarNum", getMemDC(), x, y, curHp / 10 % 10, 0);
	IMAGEMANAGER->frameRender("pHpBarNum", getMemDC(), 176, 11, curHp % 10, 0);

	if (MaxHp > 99)      IMAGEMANAGER->frameRender("pHpBarNum", getMemDC(), x, y, MaxHp / 100 % 10, 0);
	if (MaxHp > 9)       IMAGEMANAGER->frameRender("pHpBarNum", getMemDC(), x, y, MaxHp / 10 % 10, 0);
	IMAGEMANAGER->frameRender("pHpBarNum", getMemDC(), 266, 21, MaxHp % 10, 0);

	// SP
	if (curSp > 99)      IMAGEMANAGER->frameRender("pHpBarNum", getMemDC(), x, y, curSp / 100 % 10, 0);
	if (curSp > 9)       IMAGEMANAGER->frameRender("pHpBarNum", getMemDC(), x, y, curSp / 10 % 10, 0);
	IMAGEMANAGER->frameRender("pHpBarNum", getMemDC(), 468, 11, curSp % 10, 0);

	if (MaxSp > 99)      IMAGEMANAGER->frameRender("pHpBarNum", getMemDC(), x, y, MaxSp / 100 % 10, 0);
	if (MaxSp > 9)       IMAGEMANAGER->frameRender("pHpBarNum", getMemDC(), x, y, MaxSp / 10 % 10, 0);
	IMAGEMANAGER->frameRender("pHpBarNum", getMemDC(), 560, 21, MaxSp % 10, 0);

	if (curHp <= 0)       IMAGEMANAGER->frameRender("pHpBarNum", getMemDC(), x, y, 0, 0);
	if (curSp <= 0)       IMAGEMANAGER->frameRender("pHpBarNum", getMemDC(), x, y, 0, 0);


}