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
��Ű����?
-�����ͺ��̽� ���� � ������ �����Ͱ� ����Ǵ°��� ��Ÿ���� �����ͺ��̽� ����
�� ��ü�� Ư�� : �Ӽ�
�� �Ӽ����� ���� : ������ ��ü
�� ��ü�� ���̿� �����ϴ� '����'

��Ű���� ����
��Ű���� ����,�ܺ�,���� ��Ű���� �ִ�.

*/
/*
����
ĳ���� ���� ����
-ĳ���Ϳ� ���� ����
�� �̹���, ���� ����, ü��,�� ĳ���� ���̽����Ͽ� �־����
�� ĳ���� ���������� �̹��� �ٲ�� �ϴ°͵� ���� �о�ü��ְԲ�...


*/