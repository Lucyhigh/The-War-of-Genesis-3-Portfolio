#pragma once
#include "GameNode.h"
#include "Animation.h"
class AniTestScene : public GameNode
{
private:
    Image* _image;
    Animation* _ani;
public:
    HRESULT init(void);
    void release(void);
    void update(void);
    void render(void);
	AniTestScene() {}
	~AniTestScene() {}
};

