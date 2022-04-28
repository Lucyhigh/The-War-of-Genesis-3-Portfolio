#pragma once
#include "GameNode.h"
class CEffect : public GameNode
{
private:
	Image* _image;
	RECT _rc;
	int _currentFrame;
	int _maxFrameX;
	int _maxFrameY;

	float _x, _y;
	float _offsetTimeCount;
	float _worldTimeCount;
	float _isActive;

	bool _useAlphaFrame;
	bool _isAlphaChange;
	bool _isAlphaIncrease;

	BYTE _alpha;
	BYTE _endAlpha;
	float _alphaOffset;

public:
	HRESULT init(void);
	virtual HRESULT init(const char* imageName, RECT rc);
	virtual HRESULT init(const char* imageName, POINT pt);
	virtual HRESULT init(const char* imageName, POINT pt, int FPS);
	virtual HRESULT init(const char* imageName, POINT pt, int FPS, BYTE alpha);
	virtual HRESULT init(const char* imageName, POINT pt, int FPS, bool isAlphaIncrease, BYTE startAlpha, BYTE endAlpha , float alphaOffset);

	void release(void);
	void update(void);
	void render(void);
	void draw(void);
	void animation(void);
	void alphaChange(void);

	bool getIsActive(void) { return _isActive; }

	CEffect(void);
	virtual~CEffect(void);
};