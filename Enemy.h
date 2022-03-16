#pragma once
#include "GameNode.h"
#include "ProgressBar.h"

//포트폴리오에선 너무 큰 자신감이 있는 클래스이름..부모클래스의 이름으로 많이쓰이기에 파생될거라고 생각함
//추상화해서 써야한다.
//부모클래스 : 이 클래스를 기반으로 보스, 일반 몬스터등을 만들다고 했을 때 문제가 없는지 생각을 해야한다.
//오크 , 도적, 용 :각각의객체는 다 다르지만 공통의 추상화코드가 있을것이다. 
//충돌체크, rect, 렌더문제, 몇프레임? hp는 추상화에서 안함 - 메모리손해 비전투시도 생각해야함 
//확장성을 항상 생각해야한다
class Enemy : public GameNode
{
protected:
    Image* _image;
    RECT _rc;
    ProgressBar* _minionHpBar;

    float _x, _y;
    float _speed;
    float _rndTimeCount;
    float _worldTimeCount;
    int _currentFrameX;
    int _currentFrameY;
    float _currentHp;
    float _maxHp;

    float _rndFireCount;
    float _bulletFireCount;
    HRESULT init(const char* imageName, POINT position, float speed);

public:
    HRESULT init(void);
    HRESULT init(const char* imageName, POINT position);
    HRESULT init(const char* imageName, float speed);
    void release(void);
    void update(void);
    void render(void);
    bool bulletCountFire(void);
    virtual void move(void);
    void draw(void);
    void animation(void);
    inline void hitDamage(float damage)
    {
        if (_currentHp <= 0)
        {
            _currentHp = 0;
            return;
        }
        _currentHp -= damage;
    }
    RECT getRect(void) { return _rc; }
public:
    Enemy(void);
    virtual ~Enemy(void);
};

