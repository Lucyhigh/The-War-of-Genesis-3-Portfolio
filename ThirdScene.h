#pragma once
#include "GameNode.h"
#include "Player.h"
#include "ProgressBar.h"
class ThirdScene : public GameNode
{
private:
	Player* _player;
	int _bgAlpha;
	int _count;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	ThirdScene() {}
	~ThirdScene() {}
};
/*
- ������ �������� �÷��̾� �Ӹ����� HP�ٰ� ��µȴ�.

- �׸��� ����� ���ÿ� HP�� ��� ����

- HP�� ���� ���ҵǸ� ��� ���� ���

- ��� ������ �߰� ���� �ð��� ������ ȭ���� ��ο� ���� ��ŸƮ ������ �ڵ� ��ȯ

*/
