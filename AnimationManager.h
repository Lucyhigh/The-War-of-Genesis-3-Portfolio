#pragma once
#include "SingletonBase.h"
#include "Animation.h"

class AnimationManager : public SingletonBase<AnimationManager>
{
private:
    typedef map<string, pair<Animation*, Image*>> mAnimationList;
    typedef map<string, pair<Animation*, Image*>>::iterator mapAnimationIter;

    mAnimationList _mAnimationList;

public:
    HRESULT init(void);
    void release(void);
    //void update(void);

    Animation* findAnimation(string strKey);
	Image* findImage(string strKey);
    bool deleteAniamation(string strKey);
    bool deleteAll();

    // 애니메이션이 있는거 가져와서 함수 형태 잡고

    void addAnimation(string animationKeyName, char* imageKeyName, int frameWidth, int frameHeight, int start, int end,
        int fps, bool reverse = false, bool loop = false);

	void frameUpdate(string strKey);

	void aniRender(string strKey, HDC hdc, int destX, int destY);

    //void addAnimationArray(string animationKeyName, char* imageKeyName, int* playArr,
    //    int arrLen, int fps, bool loop = false);

    //void addAnimationList(string animationKeyName, char* imageKeyName,
    //    multimap<vector<int>, string, list<int>, string>,
    //    int listLen, int fps, bool loop = false);

    //void PlayAnimation();

public:
    AnimationManager() {}
    ~AnimationManager() {}
};
