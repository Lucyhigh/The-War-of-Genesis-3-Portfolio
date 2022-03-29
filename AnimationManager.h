#pragma once
#include "SingletonBase.h"
#include "Animation.h"

class AnimationManager : public SingletonBase<AnimationManager>
{
private:
    typedef map<string, Animation*> mAnimationList;
    typedef map<string, Animation*>::iterator mapAnimationIter;

    mAnimationList _mAnimationList;

public:
	// 애니메이션 렌더 / 띄울 위치, 재생 인덱스 시작 -끝 구간, 재생 속도
	HRESULT init(string animationKey, Animation* ani, int start, int end, bool loop);
	void release(void);
	void frameUpdate();

	// 애니메이션 리스트받아서 연속 재생시키기?
	void playAniarr(string animationKeyArr, Animation* ani, int start, int end, bool loop);

	void AnimationChange(Animation* changeAnimation,string animationKeyArr, string animationKeyArr2, int index );

	//이미지 구간마다의 조건 - 이미지 일정 범위 이후로는 다른 캐릭터들이 공격 // 피격 되는 조건으로

	// 애니메이션 키값으로 찾기
    Animation* findAnimation(string animationKeyName);
    bool deleteAniamation(string strKey);
    bool deleteAll();

    // 애니메이션이 있는거 가져와서 함수 형태 잡고
	void addAnimation(string animationKeyName, char * imageKeyName, int fps, bool reverse, bool loop);

	void addAnimation(string animationKeyName, char* imageKeyName, int start, int end, int fps, bool reverse, bool loop);
	
	//이미지 구간반복
    void addAnimationArray(string animationKeyName, char* imageKeyName, int* playArr,
        int arrLen, int fps, bool loop = false);

    /*void addAnimationList(string animationKeyName, char* imageKeyName,
        multimap<vector<int>, string, list<int>, string>,
        int listLen, int fps, bool loop = false);*/

	//애니메이션 자동 재생
    void PlayAnimation();

public:
    AnimationManager() {}
    ~AnimationManager() {}
};
