#include "Stdafx.h"
#include "SoundScene.h"

HRESULT SoundScene::init(void)
{
	_isPause = true;
	_isPlay = false;
	_soundVolume = 1.0f;
	_score = 0.0f;
	_maxScore = 1.0f;



	//SOUNDMANAGER->play();
	//path = "Resource/Images/mp3player/button/";
	//vector<string> vBtnImg = getFilesInDirectory(path, "*.mp3");
	//int index = 0;
	//for (string imgName : vBtnImg)
	//{
	//	string temp = path + imgName;
	//	_controlBtnImg[index] = IMAGEMANAGER->addImage(imgName, temp.c_str(), 48, 48);
	//	index++;
	//	cout << temp << endl;
	//}

	//path = "Resource/Images/mp3player/";
	//_vMp3ImgStr = getFilesInDirectory(path, "*.bmp");
	//index = 0;
	//for (string imgName : _vMp3ImgStr)
	//{
	//	string temp = path + imgName;
	//	IMAGEMANAGER->addImage(imgName, temp.c_str(), WINSIZE_X, WINSIZE_X);
	//	index++;
	//}

	//_progressBar = new ProgressBar;
	//_progressBar->init(0, WINSIZE_Y - 78, WINSIZE_X, 20);
	//_progressRc = RectMake(0, WINSIZE_Y - 68, WINSIZE_X, 20);

	//_controlBtn/Rect[PLAY] = RectMake(48, WINSIZE_Y - 48, 48, 48);
	//_controlBtnRect[PAUSE] = RectMake(48, WINSIZE_Y - 48, 48, 48);
	//_controlBtnRect[NEXT] = RectMake(48 * 2, WINSIZE_Y - 48, 48, 48);
	//_controlBtnRect[STOP] = RectMake(48 * 4, WINSIZE_Y - 48, 48, 48);

	//_rcBottomBar = RectMake(0, WINSIZE_Y - 48, WINSIZE_X, 55);
	
	return S_OK;
}

void SoundScene::release(void)
{
	//SAFE_DELETE(_progressBar);
}

void SoundScene::update(void)
{
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (_isPlay)
		{
			if (_isPause)
			{
				resumeSound();
				_isPause = !_isPause;
			}
			else
			{
				pauseSound();
				_isPause = !_isPause;
			}
		}
		else
		{
			playSound();
			_isPlay = true;
			_isPause = false;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		nextSound();
		_isPause = false;
	}

	SOUNDMANAGER->update();

	if (_isPlay && !_isPause)
	{
		if (_score >= _maxScore)
		{
			nextSound();
		}
	}
}

void SoundScene::render(void)
{
	/*IMAGEMANAGER->render(_vMp3ImgStr[_playIndex], getMemDC());
	_whiteBox->render(getMemDC(), 0, WINSIZE_Y - 48);
	if (_isPlay)
	{
		if (_isPause)
		{
			_controlBtnImg[PLAY]->render(getMemDC(), _controlBtnRect[PLAY].left, _controlBtnRect[PLAY].top);
		}
		else
		{
			_controlBtnImg[PAUSE]->render(getMemDC(), _controlBtnRect[PAUSE].left, _controlBtnRect[PAUSE].top);
		}
	}
	else
	{
		_controlBtnImg[PLAY]->render(getMemDC(), _controlBtnRect[PLAY].left, _controlBtnRect[PLAY].top);
	}

	_controlBtnImg[NEXT]->render(getMemDC(), _controlBtnRect[NEXT].left, _controlBtnRect[NEXT].top);*/
}


void SoundScene::resumeSound()
{
	SOUNDMANAGER->resume(_vMp3Name[_playIndex]);
}

void SoundScene::pauseSound()
{
	SOUNDMANAGER->pause(_vMp3Name[_playIndex]);
}

void SoundScene::playSound()
{
	SOUNDMANAGER->play(_vMp3Name[_playIndex], 1.0f);
}

void SoundScene::nextSound()
{
	cout << "NEXT" << endl;
	SOUNDMANAGER->stop(_vMp3Name[_playIndex]);
	if (_playIndex < _vMp3Name.size() - 1)
	{
		_playIndex++;
		SOUNDMANAGER->play(_vMp3Name[_playIndex], _soundVolume);
	}
	else
	{
		SOUNDMANAGER->stop(_vMp3Name[_playIndex]);
	}
}