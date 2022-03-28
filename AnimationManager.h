#pragma once
#include "SingletonBase.h"
#include "Animation.h"
/*
	이미지 구간반복 - 다른 함수가 범위 내 적파악할 동안 시간을 끌기위한 구간 반복
	이미지 구간마다의 조건 - 이미지 일정 범위 이후로는 다른 캐릭터들이 공격 // 피격 되는 조건으로
	이미지 구간 속도 조절
	애니메이션 자동 재생

	*/
class AnimationManager : public SingletonBase <AnimationManager>
{
private: 
	Animation animation;
public:

	// 애니메이션 렌더 / 띄울 위치, 특수 구간, 재생 시작시간?, 재생 속도
	void playAnimation(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		string animationKey, int length, COLORREF color);

	// 애니메이션 리스트
	void playAniarr(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		string* animationKeyArr, int length, COLORREF color);
	void playAnimation();
	
public:
	AnimationManager() {}
	~AnimationManager() {}
};

