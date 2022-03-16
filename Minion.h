#pragma once
#include "Enemy.h"
#include "ProgressBar.h"
class Minion :public Enemy
{
public:
    virtual void move(void);
    Minion();
    virtual ~Minion();
};

class Minion2 :public Enemy
{
public:
    virtual void move(void);
    Minion2() {}
    virtual ~Minion2() {}
};

class Minion3 :public Enemy
{
public:
    virtual void move(void);
    Minion3() {}
    virtual ~Minion3() {}
};