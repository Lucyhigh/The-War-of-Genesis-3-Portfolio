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
        make_pair("아이템 이름", "붉은 심장"),
        make_pair("아이템 설명", "단장이 가졌던 심장"),
        make_pair("아이템 가격", 100),
        make_tuple("아이템 효과", "HP 증가 + ", 10),
        make_tuple("아이템 효과", "데미지 증가 + ", 10),
        1, 0 
    };
    tagItemInfo itemB =
    {
        make_pair("아이템 이름", "가시 박힌 심장"),
        make_pair("아이템 설명", "이시도라가 가졌던 심장"),
        make_pair("아이템 가격", 500),
        make_tuple("아이템 효과", "HP 증가 + ", 20),
        make_tuple("아이템 효과", "데미지 증가 + ", 20),
        2, 0
    };
    tagItemInfo itemC =
    {
        make_pair("아이템 이름", "단단한 심장"),
        make_pair("아이템 설명", "참회자가 가졌던 심장"),
        make_pair("아이템 가격", 1000),
        make_tuple("아이템 효과", "HP 증가 + ", 30),
        make_tuple("아이템 효과", "데미지 증가 + ", 30),
        3, 0
    };
    _vItems.push_back(itemA);
    _vItems.push_back(itemB);
    _vItems.push_back(itemC);
        
}

Item::~Item()
{
}
