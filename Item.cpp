#include "Stdafx.h"
#include "Item.h"

vector<tagItemInfo> Item::getItemInfo(void)
{
    return _vItems;
}

Item::Item()
{
    tagItemInfo itemA =
    {
        make_pair("������ �̸�", "���� ����"),
        make_pair("������ ����", "������ ������ ����"),
        make_pair("������ ����", 100),
        make_tuple("������ ȿ��", "HP ���� + ", 10),
        make_tuple("������ ȿ��", "������ ���� + ", 10),
        1, 0 
    };
    tagItemInfo itemB =
    {
        make_pair("������ �̸�", "���� ���� ����"),
        make_pair("������ ����", "�̽õ��� ������ ����"),
        make_pair("������ ����", 500),
        make_tuple("������ ȿ��", "HP ���� + ", 20),
        make_tuple("������ ȿ��", "������ ���� + ", 20),
        2, 0
    };
    tagItemInfo itemC =
    {
        make_pair("������ �̸�", "�ܴ��� ����"),
        make_pair("������ ����", "��ȸ�ڰ� ������ ����"),
        make_pair("������ ����", 1000),
        make_tuple("������ ȿ��", "HP ���� + ", 30),
        make_tuple("������ ȿ��", "������ ���� + ", 30),
        3, 0
    };
    _vItems.push_back(itemA);
    _vItems.push_back(itemB);
    _vItems.push_back(itemC);
        
}

Item::~Item()
{
}
