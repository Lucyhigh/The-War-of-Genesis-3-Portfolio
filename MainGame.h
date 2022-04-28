#pragma once
#include "GameNode.h"

class MainGame : public GameNode
{
private:
public:
    HRESULT init(void);
    void release(void);
    void update(void);
    void render(void);

public:
    MainGame() {}
    ~MainGame() {}
};

/*
안녕하세요 송예은의 창세기전 포트폴리오입니다.
x86로 설정하여 플레이 가능합니다.
스토리 진행은 스페이스바로 가능합니다. 감사합니다.
*/