#pragma once
#include "Quest.h"

class Quest;

/*
ť (queue)
ť�� ����Ʈ�� �������� ���ð� �ٸ��� ���� ó���� �� �����Ͱ� ó���� ������ FIFO �ڷᱸ��  ������ �Ͼ�� ���� ��(rear) , ������ �Ͼ�� ���� ��(front)��� �ϴ�

����Ʈ ť, cpu �����ٸ�, ������ ����, BFS(�ʺ� �켱 Ž��) ���� �Ҷ� ����� ���� �Ѵ�.

front()
back()
push()
size()
empty()
*/

class QuestSample
{
private:
	//BFS / DFS (�ð����� �˻�)
	queue <Quest*> _quest;

public:
	void init(void);
	void questSetup(Quest* pQuest = nullptr);

	queue<Quest*>* getQuest() { return &this->_quest; }

	QuestSample() {}
	~QuestSample() {}
};

