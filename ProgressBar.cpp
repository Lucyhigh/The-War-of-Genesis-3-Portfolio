#include "Stdafx.h"
#include "ProgressBar.h"

HRESULT ProgressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;
	_curIndex = 0;
	_pastIndex = 1;
	//_rc = RectMakeCenter(_x, _y, width, height);//���� ��
	//�����̴� �ǽð� ��
	//_progressBarUp = IMAGEMANAGER->addImage("BarUp", "Resources/Images/Object/HpBarUp.bmp",
	//	0, 0, width, height, true, RGB(255, 0, 255));
	//���� ����Ʈ�� �ִ� ��
	_progressBarDown = ANIMATIONMANAGER->findAnimation("pHpBar");
	width = _progressBarDown->getFrameWidth();//�� ����� ����
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

}//ī�޶� Ȯ���ؼ� ����ȵǸ� �Ű������� ī�޶� �߰����ֱ�

void ProgressBar::setGauge(float currentScore, float maxScore)
{
	_width = (currentScore / maxScore) * _progressBarDown->getFrameWidth();//�� ���̷� ��ü�ʿ�
}
