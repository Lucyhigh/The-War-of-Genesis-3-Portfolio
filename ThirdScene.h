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
- 세번재 씬에서는 플레이어 머리위에 HP바가 출력된다.

- 그리고 입장과 동시에 HP는 계속 감소

- HP가 전부 감소되면 사망 문구 출력

- 사망 문구가 뜨고 일정 시간이 지나면 화면이 어두워 지고 스타트 씬으로 자동 전환

*/
