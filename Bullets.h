#pragma once
#include "GameNode.h"

struct tagBullet
{
    Image* img;
    RECT rc;
    int radius;
    int count;
    float x, y;
    float fireX, fireY;
    float angle;
    float speed;
    bool fire;
    int index;
};

// 배열처럼 미리 장전해두고 발사 
class Missile : public GameNode
{
private:
    vector<tagBullet> _vBullet;
    vector<tagBullet>::iterator _viBullet;

    float _range;
    float _bulletTick;
public:
    HRESULT init(int bulletMax, float range);
    void release(void);
    void update(void);
    void render(void);
    void fire(float x, float y);
    void move(void);
    void draw(void);

    //접근자 설정
    vector<tagBullet> getBullet(void) { return _vBullet; }
    //총알 삭제
    void removeBullet(int arrNum);
public:
    Missile() {};
    ~Missile() {};
};

// 공용 총알(쏠때마다 만들고 삭제)=========================================================================
class Bullet : public GameNode
{
private:
    vector<tagBullet> _vBullet;
    vector<tagBullet>::iterator _viBullet;

    const char* _imageName;
    float _range;
    float _bulletMax;
public:
    HRESULT init(const char* imageName, int bulletMax, float range);
    void release(void);
    void update(void);
    void render(void);

    void fire(float x, float y, float angle, float speed);
    void move(void);
    void draw(void);

    //접근자 설정
    vector<tagBullet> getBullet(void) { return _vBullet; }
    //총알 삭제
    void removeBullet(int arrNum);
public:
    Bullet(void) {}
    virtual ~Bullet(void) {}
};

// 발사 할 때마다 만들고 삭제 (메모리 이득)
class MissileM1 :public GameNode
{
    vector<tagBullet> _vBullet;
    vector<tagBullet>::iterator _viBullet;

    float _range;
    int _bulletMax;
public:
    HRESULT init(int bulletMax, float range);
    void release(void);
    void update(void);
    void render(void);
    void fire(float x, float y);
    void move(void);
    void draw(void);

    vector<tagBullet> getBullet(void) { return _vBullet; }
    void removeBullet(int arrNum);
public:
    MissileM1() {};
    ~MissileM1() {};
};

class MissileM2 : public GameNode
{
private:
    vector<tagBullet> _vBullet;
    vector<tagBullet>::iterator _viBullet;

    float _range;
    float _bulletTick;
    int _bulletMax;
    int _bulletIndex;
public:
    HRESULT init(int bulletMax, float range);
    void release(void);
    void update(void);
    void render(void);
    void fire(float x, float y);
    void move(void);
    void draw(void);

    vector<tagBullet> getBullet(void) { return _vBullet; }
    void removeBullet(int arrNum);
public:
    MissileM2() {};
    ~MissileM2() {};
};

class MissileM3 : public GameNode
{
private:
    vector<tagBullet> _vBullet;
    vector<tagBullet>::iterator _viBullet;

    float _range;
    float _bulletTick;
    int _bulletMax;
    int _bulletIndex;

public:
    HRESULT init(int bulletMax, float range);
    void release(void);
    void update(void);
    void render(void);
    void fire(float x, float y);
    void move(void);
    void draw(void);

    vector<tagBullet> getBullet(void) { return _vBullet; }
    void removeBullet(int arrNum);
public:
    MissileM3() {};
    ~MissileM3() {};
};

class Beam : public GameNode
{
private:
    vector<tagBullet> _vBullet;
    vector<tagBullet>::iterator _viBullet;
    typedef vector<tagBullet>::iterator iterBullet;

    float _range;
    int _bulletMax;
public:
    HRESULT init(int bulletMax, float range);
    void release(void);
    void update(void);
    void render(void);
    void fire(float x, float y);
    void move(void);
    void draw(void);

    //접근자 설정
    vector<tagBullet> getBullet(void) { return _vBullet; }
public:
    Beam() {};
    ~Beam() {};
};

