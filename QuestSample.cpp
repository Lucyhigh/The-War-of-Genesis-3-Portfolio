#include "Stdafx.h"
#include "QuestSample.h"

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
	asString 변수가 string이 아니거나, NULL값이 들어있으면 별도의 예외 없이 그냥 NULL반환

	ToString():
	만약 변수가 NULL값을 가지고 있으면 예외 발생
	*/
}
