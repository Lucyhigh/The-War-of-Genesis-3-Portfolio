#include "Stdafx.h"
#include "AnimationManager.h"

HRESULT init(string animationKey, Animation* ani, int start, int end, bool loop)
{
    return S_OK;
}

void AnimationManager::release(void)
{
    this->deleteAll();
}

bool AnimationManager::deleteAniamation(string strKey)
{
    auto key = _mAnimationList.find(strKey);

    if (key != _mAnimationList.end())
    {
        key->second->release();
        SAFE_DELETE(key->second);
        _mAnimationList.erase(key);
        return true;
    }

    return false;
}

bool AnimationManager::deleteAll()
{
    auto iter = _mAnimationList.begin();

    for (; iter != _mAnimationList.end();)
    {
        if (iter->second != NULL)
        {
            iter->second->release();
            SAFE_DELETE(iter->second);
            iter = _mAnimationList.erase(iter);
        }
        else
        {
            ++iter;
        }
    }

    _mAnimationList.clear();

    return true;
}

void AnimationManager::addAnimation(string animationKeyName, char* imageKeyName, int fps, bool reverse, bool loop)
{
	// 초기화 하고
	Image* img = IMAGEMANAGER->findImage(imageKeyName);
	Animation* ani = new Animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);

	_mAnimationList.insert(make_pair(animationKeyName, ani));
}

void AnimationManager::addAnimation(string animationKeyName, char* imageKeyName, int start, int end, int fps, bool reverse, bool loop)
{
    // 초기화 하고
    Image* img = IMAGEMANAGER->findImage(imageKeyName);
    Animation* ani = new Animation;

    ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop);

    ani->setFPS(fps);

    _mAnimationList.insert(make_pair(animationKeyName, ani));
}

void AnimationManager::addAnimationArray(string animationKeyName, char* imageKeyName, int* playArr, int arrLen, int fps, bool loop)
{
    //arrLen?
    Image* img = IMAGEMANAGER->findImage(imageKeyName);
    Animation* ani = new Animation;

    ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
    ani->setPlayFrame(playArr, arrLen, loop);
    ani->setFPS(fps);

    _mAnimationList.insert(make_pair(animationKeyName, ani));
}

//void AnimationManager::addAnimationList(string animationKeyName, char* imageKeyName, 
//    multimap<vector<int>, string, list<int>, string>, int listLen, int fps, bool loop)
//{
//    Image* img = IMAGEMANAGER->findImage(imageKeyName);
//    Animation* ani = new Animation;
//
//    ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
//    //ani->setPlayFrame(reverse, loop);
//    ani->setFPS(fps);
//
//    _mAnimationList.insert(make_pair(animationKeyName, ani));
//}

Animation* AnimationManager::findAnimation(string strKey)
{
	auto key = _mAnimationList.find(strKey);
	if (key != _mAnimationList.end())
	{
		return key->second;
	}
	return nullptr;
}

void AnimationManager::PlayAnimation()
{
    // 찾아서 갱신하고
    mapAnimationIter iter = _mAnimationList.begin();
    for (iter; iter != _mAnimationList.end(); ++iter)
    {
        if (!iter->second->getIsPlay()) continue;
        iter->second->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
    }
    // 이미지 넣고
    // 넣은 이미지 찾은 다음 구간별로 짜른다.
}

void AnimationManager::frameUpdate(void)
{
    this->PlayAnimation();
}
