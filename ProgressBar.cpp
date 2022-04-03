#include "Stdafx.h"
#include "ProgressBar.h"

HRESULT ProgressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;
	_curIndex = 0;
	_pastIndex = 1;
	//_rc = RectMakeCenter(_x, _y, width, height);//실제 피
	//움직이는 실시간 바
	//_progressBarUp = IMAGEMANAGER->addImage("BarUp", "Resources/Images/Object/HpBarUp.bmp",
	//	0, 0, width, height, true, RGB(255, 0, 255));
	//고정 디폴트로 있는 바
	_progressBarDown = ANIMATIONMANAGER->findAnimation("pHpBar");
	width = _progressBarDown->getFrameWidth();//업 만들고 수정
	return S_OK;
}

void ProgressBar::release(void)
{
}

void ProgressBar::update()
{
	//if (_curIndex != _pastIndex)
	{
		_progressBarDown->AniStop();
		_pastIndex = _curIndex;
		switch (_curIndex)
		{
		case 0:
			_progressBarDown = ANIMATIONMANAGER->findAnimation("pHpBar");
			break;
		case 1:
			_progressBarDown = ANIMATIONMANAGER->findAnimation("eHpBar");
			break;
		}
		_progressBarDown->AniStart();
	}
	//_rc = RectMakeCenter(_x, _y, _progressBarDown->getFrameWidth(), _progressBarDown->getFrameHeight());
}

void ProgressBar::render(int index, int x, int y)
{
	//_progressBarUp->render(getMemDC(), _rc.left + _progressBarDown->getFrameWidth() / 2,
	//	_y + _progressBarDown->getFrameHeight() / 2,
	//	0, 0, _width, _progressBarDown->getFrameHeight());
	switch (index)
	{
	case 0:
		IMAGEMANAGER->findImage("pHpBar")->aniRender(getMemDC(), x, y, _progressBarDown);
		break;
	case 1:
		IMAGEMANAGER->findImage("eHpBar")->aniRender(getMemDC(), x, y, _progressBarDown);
		break;
	}

}//카메라값 확인해서 적용안되면 매개변수로 카메라값 추가해주기

void ProgressBar::setGauge(float currentScore, float maxScore)
{
	_width = (currentScore / maxScore) * _progressBarDown->getFrameWidth();//업 넓이로 교체필요
}
