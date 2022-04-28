#pragma once
#include "GameNode.h"
#include "CEffect.h"
class EffectManager: public GameNode
{
private:
	typedef vector<CEffect*> vEffect;
	typedef vector<CEffect*>::iterator viEffect;

private:
	vEffect _vEffect;
    viEffect _viEffect;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void createEffect(const char* fileName, RECT rc);
	void createEffect(const char* fileName, POINT point);
	void createEffect(const char* fileName, POINT point, int FPS);
	void createEffect(const char* fileName, POINT point, int FPS,BYTE alpha);
	void createEffect(const char* fileName, POINT point, int FPS, bool isAlphaIncrease, BYTE startAlpha, BYTE endAlpha, float alphaOffset);

	EffectManager() {}
	~EffectManager() {}
};

