#pragma once
#include "GameNode.h"
class ProgressBar : public GameNode
{
private:
	Image* _progressBarUp;
    Image* _progressBarDown;

	RECT _rc;
	int _x;
	int _y;
	int _curIndex;
	int _pastIndex;
    int _hpIndex;
    int _cdt;
    int _count;
	float _width;

public:
	HRESULT init(int x, int y, int width, int height);
	void release(void);
	void update();
	void render(int x, int y);

	void setGauge(float currentScore, float maxScore);
	int getX() { return _x; }
	int getY() { return _y; }
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
	void setType(int index) { _curIndex = index; }
    void resetImgIdx();
public:
	ProgressBar() {}
	virtual ~ProgressBar() {}
};

