#pragma once
#include "GameNode.h"
typedef void(*CALLBACK_FUNCTION)(void);

enum BUTTON_DIRECTION
{
	BUTTON_DIRECTION_NULL,
	BUTTON_DIRECTION_UP,
	BUTTON_DIRECTION_DOWN,
};
// 보이드 포인터 필요 -> 버튼 기본적으로 3가지 상태 - 함수를 3개  렌더 /업데이트 / 버튼 누름 ->스위치로 묶음 가능
// 넣어줄수잇는 상태는 2개 버튼누름.뗌 - 스위치로 묶은 3개는 이 2가지 속성으로 누를수있겠다..! 보이드 포인터를 콜백으로 부르겠다.
// 총 5개 나중에 버튼이 많아질때 문제생김..
class CButtonState: public GameNode
{
private:
	BUTTON_DIRECTION _direction;
	Image* _image;

	RECT _rc;
	float _x, _y;
	const char* _imageName;
	//버튼도 결국 프레임으로 구성됨
	POINT _btnDownFramePoint;
	POINT _btnUpFramePoint;

	CALLBACK_FUNCTION _callBackFunction;
public:
	HRESULT init(const char* imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint);
	HRESULT init(const char* imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, CALLBACK_FUNCTION cbFunction);

	void release(void);
	void update(void);
	void render(void);

	CButtonState(): _callBackFunction(nullptr){}
	~CButtonState() {}
};

