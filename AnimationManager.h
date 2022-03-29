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
	// �ִϸ��̼� ���� / ��� ��ġ, ��� �ε��� ���� -�� ����, ��� �ӵ�
	HRESULT init(string animationKey, Animation* ani, int start, int end, bool loop);
	void release(void);
	void frameUpdate();

	// �ִϸ��̼� ����Ʈ�޾Ƽ� ���� �����Ű��?
	void playAniarr(string animationKeyArr, Animation* ani, int start, int end, bool loop);

	void AnimationChange(Animation* changeAnimation,string animationKeyArr, string animationKeyArr2, int index );

	//�̹��� ���������� ���� - �̹��� ���� ���� ���ķδ� �ٸ� ĳ���͵��� ���� // �ǰ� �Ǵ� ��������

	// �ִϸ��̼� Ű������ ã��
    Animation* findAnimation(string animationKeyName);
    bool deleteAniamation(string strKey);
    bool deleteAll();

    // �ִϸ��̼��� �ִ°� �����ͼ� �Լ� ���� ���
	void addAnimation(string animationKeyName, char * imageKeyName, int fps, bool reverse, bool loop);

	void addAnimation(string animationKeyName, char* imageKeyName, int start, int end, int fps, bool reverse, bool loop);
	
	//�̹��� �����ݺ�
    void addAnimationArray(string animationKeyName, char* imageKeyName, int* playArr,
        int arrLen, int fps, bool loop = false);

    /*void addAnimationList(string animationKeyName, char* imageKeyName,
        multimap<vector<int>, string, list<int>, string>,
        int listLen, int fps, bool loop = false);*/

	//�ִϸ��̼� �ڵ� ���
    void PlayAnimation();

public:
    AnimationManager() {}
    ~AnimationManager() {}
};
