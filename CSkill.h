#pragma once
#include "GameNode.h"

typedef void(*CALLBACK_FUNCTION)(void);

enum SKILL_INDEX
{
	SKILL_INDEX_NULL,
	SKILL_INDEX_START,
	SKILL_INDEX_SECOND,
	SKILL_INDEX_THIRD,
	SKILL_INDEX_FOURTH,
	SKILL_INDEX_END
};

class CSkill:public GameNode
{
private:
	SKILL_INDEX _skillIndex;
	Image* _image;

	int _index;
	float _x, _y;
	const char* _imageName;
	CALLBACK_FUNCTION _callBackFunction;
public:
	CSkill()
		:_callBackFunction(nullptr)
	{}
	~CSkill(){}
	HRESULT init(const char* skillAniName, int fX, int fY,
		POINT btnDownFramePoint, POINT btnUpFramePoint);
	HRESULT init(const char* skillAniName, int fX, int fY,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		CALLBACK_FUNCTION cbFunction);

	void release(void);
	void update(void);
	void render(void);
};

//callBack _cSkill* 스킬이름(char* _ skillName, int fX, int fY,,,,,const[image operating]);