#pragma once
#include "GameNode.h"
#include "ProgressBar.h"

//��Ʈ���������� �ʹ� ū �ڽŰ��� �ִ� Ŭ�����̸�..�θ�Ŭ������ �̸����� ���̾��̱⿡ �Ļ��ɰŶ�� ������
//�߻�ȭ�ؼ� ����Ѵ�.
//�θ�Ŭ���� : �� Ŭ������ ������� ����, �Ϲ� ���͵��� ����ٰ� ���� �� ������ ������ ������ �ؾ��Ѵ�.
//��ũ , ����, �� :�����ǰ�ü�� �� �ٸ����� ������ �߻�ȭ�ڵ尡 �������̴�. 
//�浹üũ, rect, ��������, ��������? hp�� �߻�ȭ���� ���� - �޸𸮼��� �������õ� �����ؾ��� 
//Ȯ�强�� �׻� �����ؾ��Ѵ�
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

