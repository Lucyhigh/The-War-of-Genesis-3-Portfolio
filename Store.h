#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Item.h"
class Store:public GameNode
{
private:
    Image* _image;
    Player* _player;
    Item* _item;
    vector<tagItemInfo> _itemIlst;
    int _moveY;
public:
   HRESULT init(void);
   void release(void);
   void update(void);
   void render(void);
public:
    Store();
    ~Store();
};

