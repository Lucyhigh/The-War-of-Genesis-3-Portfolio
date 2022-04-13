#pragma once
#include "SingletonBase.h"
#include "Animation.h"

class AnimationManager : public SingletonBase<AnimationManager>
{
private:
    typedef map<string,Animation*> mAnimationList;
    typedef map<string,Animation*>::iterator mapAnimationIter;

    mAnimationList _mAnimationList;

public:
    HRESULT init(void);
    void release(void);
    void update(void);

    Animation* findAnimation(string strKey);
    bool deleteAniamation(string strKey);
    bool deleteAll();

    // 애니메이션이 있는거 가져와서 함수 형태 잡고
	void addAnimation(string animationKeyName, char * imageKeyName, int fps, bool reverse, bool loop);
	
	void addAnimation(string animationKeyName, char * imageKeyName, int fps, bool reverse, bool loop, Animation* anim);
	
	void addAnimation(string animationKeyName, char * imageKeyName, int start, int end, int fps, bool reverse, bool loop);

	void addAnimationArray(string animationKeyName, char * imageKeyName, int *playArr, int arrLen, int fps, bool loop);

	void PlayAnimation();
public:
    AnimationManager() {}
    ~AnimationManager() {}
};
