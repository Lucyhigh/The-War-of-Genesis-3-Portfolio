#pragma once
#include "GameNode.h"

class StartScean : public GameNode
{

private:
	float _alpha;
	float _bgAlpha;
	bool _isAlphaIncrese;

	RECT startButton;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	StartScean() {}
	~StartScean() {}
};

