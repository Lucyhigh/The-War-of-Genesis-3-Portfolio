#include "Stdafx.h"
#include "SoundScene.h"

HRESULT SoundScene::init(void)
{
	_isPause = true;
	_isPlay = false;
	_soundVolume = 1.0f;
	_score = 0.0f;
	_maxScore = 1.0f;

	string path = "Resource/Sound/mp3player/";
	_vMp3Name = getFilesInDirectory(path,"*.mp3");
	for (string name : _vMp3Name)
	{
		SOUNDMANAGER->addSound(name, path + name, true, false);
	}

	path = "Resource/Images/mp3player/button/";
	vector<string> vBtnImg = getFilesInDirectory(path, "*.bmp");
	int index = 0;
	for (string imgName : vBtnImg)
	{
		string temp = path + imgName;
		_controlBtnImg[index] = IMAGEMANAGER->addImage(imgName, temp.c_str(), 48, 48);
		index++;
	}

	path = "Resource/Images/mp3player/";
	_vMp3ImgStr = getFilesInDirectory(path, "*.bmp");
	index = 0;
	for (string imgName : _vMp3ImgStr)
	{
		string temp = path + imgName;
		IMAGEMANAGER->addImage(imgName, temp.c_str(), WINSIZE_X, WINSIZE_X);
		index++;
	}

	_progressBar = new ProgressBar;
	_progressBar->init(0, WINSIZE_Y - 78, WINSIZE_X, 20);
	_progressRc = RectMake(0, WINSIZE_Y - 68, WINSIZE_X, 20);

	_controlBtnRect[PREVIUS] = RectMake(0, WINSIZE_Y - 48, 48, 48);
	_controlBtnRect[PLAY] = RectMake(48, WINSIZE_Y - 48, 48, 48);
	_controlBtnRect[PAUSE] = RectMake(48, WINSIZE_Y - 48, 48, 48);
	_controlBtnRect[NEXT] = RectMake(48 * 2, WINSIZE_Y - 48, 48, 48);
	_controlBtnRect[STOP] = RectMake(48 * 4, WINSIZE_Y - 48, 48, 48);
	_controlBtnRect[VOLUME_DOWN] = RectMake(48 * 5, WINSIZE_Y - 48, 48, 48);
	_controlBtnRect[VOLUME_UP] = RectMake(48 * 6, WINSIZE_Y - 48, 48, 48);

	_rcBottomBar = RectMake(0, WINSIZE_Y - 48, WINSIZE_X, 55);
	_whiteBox = IMAGEMANAGER->addImage("whiteBox", "Resource/Images/Object/white.bmp", WINSIZE_X, 48);

	return S_OK;

}

void SoundScene::release(void)
{
	SAFE_DELETE(_progressBar);
}

void SoundScene::update(void)
{
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (PtInRect(&_controlBtnRect[PLAY], _ptMouse))
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

		else if (PtInRect(&_controlBtnRect[NEXT], _ptMouse))
		{
			nextSound();
			_isPause = false;
		}

		else if (PtInRect(&_controlBtnRect[PREVIUS], _ptMouse))
		{
			previusSound();
			_isPause = false;
		}

		else if (PtInRect(&_controlBtnRect[STOP], _ptMouse))
		{
			stop();
			_isPlay = false;
			_isPause = true;
			_score = 0.0f;
			_maxScore = 1.0f;
		}

		else if (PtInRect(&_controlBtnRect[VOLUME_DOWN], _ptMouse))
		{
			volumeDown();
		}

		else if (PtInRect(&_controlBtnRect[VOLUME_UP], _ptMouse))
		{
			volumeUp();
		}
		else if (PtInRect(&_progressRc, _ptMouse))
		{
			float temp = (float)_ptMouse.x / (float)WINSIZE_X;
			temp = temp * SOUNDMANAGER->getLength(_vMp3Name[_playIndex]);
			SOUNDMANAGER->setPosition(_vMp3Name[_playIndex], temp);
		}
	}

	SOUNDMANAGER->update();

	if (_isPlay && !_isPause)
	{
		if (_score >= _maxScore)
		{
			nextSound();
		}
		_score = SOUNDMANAGER->getPosition(_vMp3Name[_playIndex]);
		_maxScore = SOUNDMANAGER->getLength(_vMp3Name[_playIndex]);
	}

	_progressBar->setGauge(_score, _maxScore);
	_progressBar->update();

}

void SoundScene::render(void)
{
	IMAGEMANAGER->render(_vMp3ImgStr[_playIndex], getMemDC());
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

	_controlBtnImg[NEXT]->render(getMemDC(), _controlBtnRect[NEXT].left, _controlBtnRect[NEXT].top);

	_controlBtnImg[PREVIUS]->render(getMemDC(), _controlBtnRect[PREVIUS].left, _controlBtnRect[PREVIUS].top);

	_controlBtnImg[STOP]->render(getMemDC(), _controlBtnRect[STOP].left, _controlBtnRect[STOP].top);

	_controlBtnImg[VOLUME_DOWN]->render(getMemDC(), _controlBtnRect[VOLUME_DOWN].left, _controlBtnRect[VOLUME_DOWN].top);

	_controlBtnImg[VOLUME_UP]->render(getMemDC(), _controlBtnRect[VOLUME_UP].left, _controlBtnRect[VOLUME_UP].top);


	/*char* cstr = new char[_vMp3Name[_playIndex].size() + 1];
	copy(_vMp3Name[_playIndex].begin(), _vMp3Name[_playIndex].end(), cstr);
	cstr[_vMp3Name[_playIndex].size()] = '\0';

	FONTMANAGER->drawText(getMemDC(), 0, WINSIZE_Y - 88, "µÕ±Ù¸ð²Ã", 20, 100, cstr, strlen(cstr), RGB(255, 255, 255));
	SAFE_DELETE_ARRAY(cstr);

	char volumeStr[32];
	sprintf(volumeStr, "%d", static_cast<int>(_soundVolume * 100));
	FONTMANAGER->drawText(getMemDC(), 48 * 7, WINSIZE_Y - 48, "µÕ±Ù¸ð²Ã", 48, 100, volumeStr, strlen(volumeStr), RGB(0, 0, 0));*/
}


void SoundScene::resumeSound()
{
	cout << "PAUSE" << endl;
	SOUNDMANAGER->resume(_vMp3Name[_playIndex]);
}

void SoundScene::pauseSound()
{
	cout << "RESUME" << endl;
	SOUNDMANAGER->pause(_vMp3Name[_playIndex]);
}

void SoundScene::playSound()
{
	cout << "PLAY" << endl;
	SOUNDMANAGER->play(_vMp3Name[_playIndex], 1.0f);
}

void SoundScene::nextSound()
{
	cout << "NEXT" << endl;
	SOUNDMANAGER->stop(_vMp3Name[_playIndex]);
	if (_playIndex < _vMp3Name.size() - 1)
	{
		_playIndex++;
	}
	else
	{
		_playIndex = _vMp3Name.size() - 1;
	}
	SOUNDMANAGER->play(_vMp3Name[_playIndex], _soundVolume);
}

void SoundScene::previusSound()
{
	cout << "PREVIUS" << endl;
	SOUNDMANAGER->stop(_vMp3Name[_playIndex]);
	if (_playIndex > 0)
	{
		_playIndex--;
	}
	else
	{
		_playIndex = 0;
	}
	SOUNDMANAGER->play(_vMp3Name[_playIndex], _soundVolume);
}

void SoundScene::stop()
{
	cout << "STOP" << endl;
	SOUNDMANAGER->stop(_vMp3Name[_playIndex]);
}

void SoundScene::volumeDown()
{
	cout << "VOLUME_DOWN" << endl;
	_soundVolume -= 0.1f;
	if (_soundVolume >= 1.0f)
	{
		_soundVolume = 1.0f;
	}
	else if (_soundVolume <= 0)
	{
		_soundVolume = 0.0f;
	}
	SOUNDMANAGER->setAllVolume(_soundVolume);
}

void SoundScene::volumeUp()
{
	cout << "VOLUME_UP" << endl;
	_soundVolume += 0.1f;
	if (_soundVolume >= 1.0f)
	{
		_soundVolume = 1.0f;
	}
	else if (_soundVolume <= 0)
	{
		_soundVolume = 0.0f;
	}
	SOUNDMANAGER->setAllVolume(_soundVolume);
}