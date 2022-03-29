#include "Stdafx.h"
#include "AnimationManager.h"

HRESULT AnimationManager::init(void)
{
    return S_OK;
}

void AnimationManager::release(void)
{
    this->deleteAll();
}

Animation* AnimationManager::findAnimation(string strKey)
{
    auto key = _mAnimationList.find(strKey);
    if (key != _mAnimationList.end())
    {
		return key->second.first;
    }
    return nullptr;
}

Image* AnimationManager::findImage(string strKey)
{
	auto key = _mAnimationList.find(strKey);
	if (key != _mAnimationList.end())
	{
		return key->second.second;
	}
	return nullptr;
}

bool AnimationManager::deleteAniamation(string strKey)
{
    auto key = _mAnimationList.find(strKey);

    if (key != _mAnimationList.end())
    {
        key->second.first->release();
        SAFE_DELETE(key->second.first);
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
        if (iter->second.first != NULL)
        {
            iter->second.first->release();
            SAFE_DELETE(iter->second.first);
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

void AnimationManager::addAnimation(string animationKeyName, char* imageKeyName, int frameWidth, int frameHeight, int start, int end, int fps, bool reverse, bool loop)
{
    // 초기화 하고
    Image* img = IMAGEMANAGER->findImage(imageKeyName);
    Animation* ani = new Animation;

    ani->init(img->getWidth(), img->getHeight(), frameWidth, frameHeight);
    ani->setDefPlayFrame(reverse, loop);
    ani->setFPS(fps);

    _mAnimationList.insert(make_pair(animationKeyName, make_pair(ani, img)));
}

void AnimationManager::frameUpdate(string strKey)
{
	auto ani = findAnimation(strKey);
	if (ani == nullptr)
		return;
	
	/*if (KEYMANAGER->isOnceKeyDown('T'))
		ani->AniStart();*/

	ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
}

void AnimationManager::aniRender(string strKey, HDC hdc, int destX, int destY)
{
	auto ani = findAnimation(strKey);
	auto image = findImage(strKey);
	if (ani == nullptr || image == nullptr)
		return;
	image->aniRender(hdc, destX, destY, ani);
}

//void AnimationManager::addAnimationArray(string animationKeyName, char* imageKeyName, int* playArr, int arrLen, int fps, bool loop)
//{
//    //arrLen?
//    Image* img = IMAGEMANAGER->findImage(imageKeyName);
//    Animation* ani = new Animation;
//
//    ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
//    ani->setPlayFrame(playArr, arrLen, loop);
//    ani->setFPS(fps);
//
//    _mAnimationList.insert(make_pair(animationKeyName, ani));
//}
//
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

//void AnimationManager::PlayAnimation()
//{
//    // 찾아서 갱신하고
//    mapAnimationIter iter = _mAnimationList.begin();
//    for (iter; iter != _mAnimationList.end(); ++iter)
//    {
//        if (!iter->second->getIsPlay()) continue;
//        iter->second->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
//    }
//    // 이미지 넣고
//    // 넣은 이미지 찾은 다음 구간별로 짜른다.
//}
//
//void AnimationManager::update(void)
//{
//    this->PlayAnimation();
//}
