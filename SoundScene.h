#pragma once
#include "GameNode.h"
class SoundScene:public GameNode
{
private:
    float _volume;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
public:
	SoundScene();
	~SoundScene() {}
};

