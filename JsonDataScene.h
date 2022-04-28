#pragma once
#include "GameNode.h"

class JsonDataScene : public GameNode
{
private:
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void questPopUp();
	void currentQuest();

	JsonDataScene() {}
	~JsonDataScene() {}
};

