#include "stdafx.h"
#include "JsonDataScene.h"

HRESULT JsonDataScene::init(void)
{
	_questSample = new QuestSample;
	_questSample->init();

	return S_OK;
}

void JsonDataScene::release(void)
{
}

void JsonDataScene::update(void)
{
	//! Do Nothing
}

void JsonDataScene::render(void)
{
	questPopUp();
}

void JsonDataScene::questPopUp()
{
	char str[256];
	queue<Quest*>* temp = _questSample->getQuest();
	Quest* node = temp->front();

	sprintf(str, "이름: %s", node->getName().c_str());
	TextOut(getMemDC(), 200, 150, str, strlen(str));

	sprintf(str, "퀘스트 정보: %s", node->getDescription().c_str());
	TextOut(getMemDC(), 200, 200, str, strlen(str));

	sprintf(str, "몬스터 이름: %s", node->getMonsterName().c_str());
	TextOut(getMemDC(), 200, 250, str, strlen(str));

	sprintf(str, "처치 대상: %d", node->getMonster());
	TextOut(getMemDC(), 200, 300, str, strlen(str));

	sprintf(str, "퀘스트 체크: %s", node->getQuestCheck().c_str());
	TextOut(getMemDC(), 200, 350, str, strlen(str));

	sprintf(str, "보상 경험치: %d", node->getExp());
	TextOut(getMemDC(), 200, 400, str, strlen(str));

	sprintf(str, "보상 아이템: %s", node->getItem().c_str());
	TextOut(getMemDC(), 200, 450, str, strlen(str));

	sprintf(str, "보상 골드: %d", node->getGold());
	TextOut(getMemDC(), 200, 500, str, strlen(str));
}

void JsonDataScene::currentQuest()
{
}
