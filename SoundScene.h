#pragma once
#include "GameNode.h"
#include "ProgressBar.h"



class SoundScene : public GameNode
{
private:
	enum BUTTON_IMG
	{
		PAUSE = 0,
		PLAY,
		NEXT,
		STOP,
		BUTTON_END
	};

	vector<string> _vMp3Name;
	vector<string> _vMp3ImgStr;

	ProgressBar* _progressBar;
	RECT _progressRc;
	RECT _rcBottomBar;

	Image* _whiteBox;
	Image* _controlBtnImg[BUTTON_END];
	RECT _controlBtnRect[BUTTON_END];

	float _soundVolume;
	float _score;
	float _maxScore;
	int _playIndex;
	bool _isPause;
	bool _isPlay;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void resumeSound();
	void pauseSound();
	void playSound();
	void nextSound();
};

