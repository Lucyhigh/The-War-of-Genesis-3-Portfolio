#include "Stdafx.h"
#include "AnimationManager.h"

void AnimationManager::playAnimation(HDC hdc, int destX, int destY, char * fontName, int fontSize, int fontWidth, string animationKey, int length, COLORREF color)
{

	
	void frameUpdate(float elpasedTime);
}

void AnimationManager::playAniarr(HDC hdc, int destX, int destY, char * fontName, int fontSize, int fontWidth, string * animationKeyArr, int length, COLORREF color)
{

}

void AnimationManager::playAnimation()
{
	if (animation.isPlay())
	{
		animation.AniStart();
	};
}

void setPlayFrame(int start, int end, bool reverse = false, bool loop = false);
void setPlayReverseFrame(int start, int end, int framX, bool loop);


// 초당 프레임 갱신 횟수
void setFPS(int framePerSec);
void setFPS(int framePerSec, int maxSec);

// 프레임 업데이트 
void frameUpdate(float elpasedTime);
void AniStart(void);
void AniStop(void);
void AniPause(void);
void AniResume(void);

// 플레이 중?
inline bool isPlay(void) { return _isPlay; }

inline POINT getFramePos(void)
{
	if (0 > _nowPlayIdx || _nowPlayIdx >= size(_playList))
		return POINT{ 0,0 };
	int frameListIndex = _playList[_nowPlayIdx];
	if (0 > frameListIndex || frameListIndex >= size(_frameList))
		return POINT{ 0,0 };

	return _frameList[_playList[_nowPlayIdx]];
}

inline int getFrame(void) { return _nowPlayIdx; }

// 현재 에니메이션의 프레임 위치 순서 얻기
inline int getFrameIdx(void)
{
	POINT ptPOS = getFramePos();
	int frameX = ptPOS.x / _frameWidth;
	int frameY = ptPOS.y / _frameHeight;

	return frameX + frameY * _frameNumWidth;
}

//프레임 가로 세로 크기를 얻어온다
inline int getFrameWidth(void) { return _frameWidth; }
inline int getFrameHeight(void) { return _frameHeight; }
inline DWORD getNowPlayIdx(void) { return _nowPlayIdx; }
