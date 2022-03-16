#pragma once
//struct Item
//{
//     // = make_pair("name", "∫”¿∫ µπ");
//     pair<string, string> _itemStrInfo;
//     pair<string, int> _itemIntInfo;
//     
//};
//enum class ITEMINFO
//{
//    NAME, INFO, PRICE, FRAMEX, FRAMEY       //+OPTION
//};
//struct OPTION
//{
//    int _hp;
//    int _damage;
//};
struct tagItemInfo
{
    pair<string, string> name;
    pair<string, string> description;
    pair<string, int> price;
    tuple<string, string, int> _itemHpOption;
    tuple<string, string, int> _itemDamageOption;
    int frameX;
    int frameY;

};
class Item
{
private:
    vector<tagItemInfo> _vItems;

public:
    vector<tagItemInfo> getItemInfo(void);

public:
    Item();
    ~Item();
};
