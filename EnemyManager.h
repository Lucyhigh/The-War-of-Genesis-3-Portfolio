#pragma once
#include "GameNode.h"
#include "Enemy.h"
#include "Bullets.h"

class Rocket;

class EnemyManager : public GameNode
{
private:
    typedef vector<Enemy*> vEnemy;
    typedef vector<Enemy*>::iterator viEnemy;

    vEnemy _vMinion;
    viEnemy _viMinion;
    ProgressBar* _minionHpBar;
    Bullet* _bullet;
    Rocket* _rocket;

    float _x, _y;
public:
    HRESULT init(void);
    void release(void);
    void update(void);
    void render(void);

    void setMinion(void);
    void removeMinion(int arrNum);

    void minionBulletFire(void);
    void collision(void);

    //������ ���� ���͸���
    //������ ��� ���� �������� �˼������� �˼�����
    vector<Enemy*> getMinion(void) { return _vMinion; }

    Bullet* getBullet(void) { return _bullet; }
    void setRocketMemoryAddress(Rocket* rk) { _rocket = rk; }
public:
    EnemyManager() {}
    ~EnemyManager() {}
};

