#pragma once
#include "SingletonBase.h"
#include "Animation.h"
/*
	�̹��� �����ݺ� - �ٸ� �Լ��� ���� �� ���ľ��� ���� �ð��� �������� ���� �ݺ�
	�̹��� ���������� ���� - �̹��� ���� ���� ���ķδ� �ٸ� ĳ���͵��� ���� // �ǰ� �Ǵ� ��������
	�̹��� ���� �ӵ� ����
	�ִϸ��̼� �ڵ� ���

	*/
class AnimationManager : public SingletonBase <AnimationManager>
{
private: 
	Animation animation;
public:

	// �ִϸ��̼� ���� / ��� ��ġ, Ư�� ����, ��� ���۽ð�?, ��� �ӵ�
	void playAnimation(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		string animationKey, int length, COLORREF color);

	// �ִϸ��̼� ����Ʈ
	void playAniarr(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		string* animationKeyArr, int length, COLORREF color);
	void playAnimation();
	
public:
	AnimationManager() {}
	~AnimationManager() {}
};

