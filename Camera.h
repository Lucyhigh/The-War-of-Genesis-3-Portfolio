#pragma once
#include "GameNode.h"

class Camera : public GameNode
{
private:
	POINT _trace;
	RECT _screen;
	int _count;
	float _leftLimit;
	float _rightLimit;
	float _topLimit;
	float _bottomLimit;

	POINT   _beforeShakingPt;
	int      _shakingOffsetCount;
	float   _shakingStartTime;
	float   _shakingTime;
	bool   _isShakingIncrease;
	bool   _isShaking;

public:
	Camera();
	~Camera() {}
	POINT getCameraPos();
	RECT getScreenRect();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void setCameraPos(POINT cameraPos);
	void setScreenRect(RECT screenRect);
	void setLimitsX(float leftLimit, float rightLimit);
	void setLimitsY(float topLimit, float bottomLimit);
	void shakeStart(float time);
	float getLeftLimit() { return _leftLimit; }
	float getTopLImit() { return _topLimit; }
};