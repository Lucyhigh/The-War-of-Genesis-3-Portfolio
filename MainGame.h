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
�ȳ��ϼ��� �ۿ����� â������ ��Ʈ�������Դϴ�.
x86�� �����Ͽ� �÷��� �����մϴ�.
���丮 ������ �����̽��ٷ� �����մϴ�. �����մϴ�.
���� �� ������ Ŭ������ UIâ�� ����
���� Ŭ������ �̵� �����մϴ�.
*/