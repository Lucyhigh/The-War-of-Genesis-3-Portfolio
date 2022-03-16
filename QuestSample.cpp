#include "stdafx.h"
#include "QuestSample.h"
#include "Quest.h"

void QuestSample::init(void)
{
	questSetup();
}

void QuestSample::questSetup(Quest * pQuest)
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("Quest.json");
	for (auto it = root["Quest"].begin(); it != root["Quest"].end(); it++)
	{
		if ((*it).isObject())
		{
			Quest* qQuest = new Quest;
			qQuest->init
			(
				(*it)["_name"].asString(),
				(*it)["_gold"].asInt(),
				(*it)["_exp"].asInt(),
				(*it)["_description"].asString(),
				(*it)["_item"].asString(),
				(*it)["_monster"].asInt(),
				(*it)["_questionCheck"].asString(),
				(*it)["_monsterName"].asString(),
				(*it)["_questStage"].asString()
			);
			_quest.push(qQuest);
		}
	}
	/*
	asString():
	asString ������ string�� �ƴϰų�, NULL���� ��������� ������ ���� ���� �׳� NULL��ȯ

	ToString():
	���� ������ NULL���� ������ ������ ���� �߻�
	*/
}