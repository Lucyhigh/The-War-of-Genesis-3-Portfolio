#pragma once
#include "GameNode.h"
typedef void(*CALLBACK_FUNCTION)(void);

enum BUTTON_DIRECTION
{
	BUTTON_DIRECTION_NULL,
	BUTTON_DIRECTION_UP,
	BUTTON_DIRECTION_DOWN,
};
// ���̵� ������ �ʿ� -> ��ư �⺻������ 3���� ���� - �Լ��� 3��  ���� /������Ʈ / ��ư ���� ->����ġ�� ���� ����
// �־��ټ��մ� ���´� 2�� ��ư����.�� - ����ġ�� ���� 3���� �� 2���� �Ӽ����� �������ְڴ�..! ���̵� �����͸� �ݹ����� �θ��ڴ�.
// �� 5�� ���߿� ��ư�� �������� ��������..
class CButtonState: public GameNode
{
private:
	BUTTON_DIRECTION _direction;
	Image* _image;

	RECT _rc;
	float _x, _y;
	const char* _imageName;
	//��ư�� �ᱹ ���������� ������
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

