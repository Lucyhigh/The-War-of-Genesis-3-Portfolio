#pragma once
#include "Quest.h"

class Quest;

/*
큐 (queue)
큐는 리스트의 일종으로 스택과 다르게 가장 처음에 들어간 데이터가 처음에 나오는 FIFO 자료구조  삽입이 일어나는 쪽을 뒤(rear) , 삭제가 일어나는 쪽을 앞(front)라고 하다

프린트 큐, cpu 스케줄링, 데이터 버퍼, BFS(너비 우선 탐색) 등을 할때 고려해 봐야 한다.

front()
back()
push()
size()
empty()
*/

class QuestSample
{
private:
	//BFS / DFS (시간나면 검색)
	queue <Quest*> _quest;

public:
	void init(void);
	void questSetup(Quest* pQuest = nullptr);

	queue<Quest*>* getQuest() { return &this->_quest; }

	QuestSample() {}
	~QuestSample() {}
};

