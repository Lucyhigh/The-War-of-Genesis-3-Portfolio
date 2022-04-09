#pragma once
#include "GameNode.h"
#include "Animation.h"

typedef void(*CALLBACKFUNCTION)(void);

enum SKILL_INDEX_NUMBER
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
	CALLBACKFUNCTION _callBackFunction;

	SKILL_INDEX_NUMBER _skillIndexNum;
	Image* _image;
    Animation* _currentAnimation;
	const char* skillAniName;
	int _skillIndex;
	int _attackIndex;
    int _behavior;
	float _x, _y;
    int frameX;
    int frameY;
    //SAFE_RELEASE(_callBackFunction)
public:
	CSkill() :_callBackFunction(nullptr){}
	~CSkill(){}
	//HRESULT init(const char* skillAniName, int frameX, int frameY, const[]);
	//HRESULT init(const char* skillAniName, int frameX, int frameY,const[], CALLBACK_FUNCTION cbFunction);

	void release(void);
	void update(void);
	void render(void);

    bool IsAttackIndex(void);
};

//callBack _cSkill* 스킬이름(char* _ skillName, int fX, int fY,,,,,const[image operating]);