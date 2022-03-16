#include "Stdafx.h"
#include "Enemy.h"

Enemy::Enemy() : _rc(RectMake(0, 0, 0, 0)),
_currentFrameX(0), _currentFrameY(0),
_x(0.0f), _y(0.0f),
_rndTimeCount(0.0f), _worldTimeCount(0.0f), _bulletFireCount(0.0f), _rndFireCount(0.0f)
{
}

Enemy::~Enemy() {
}

HRESULT Enemy::init(void)
{
    //������� ����
    return S_OK;
}

HRESULT Enemy::init(const char * imageName, POINT position, float speed)
{
    _worldTimeCount = TIMEMANAGER->getWorldTime();
    _rndTimeCount = RND->getFromFloatTo(0.04f, 0.1f);

    _image = IMAGEMANAGER->findImage(imageName);
    _rc = RectMakeCenter(position.x, position.y,
        _image->getFrameWidth(), _image->getFrameHeight());
    _bulletFireCount = TIMEMANAGER->getWorldTime();
    _rndFireCount = RND->getFromFloatTo(0.5f, 4.5f);
    _x = position.x;
    _y = position.y;
    _speed = speed;
    _minionHpBar = new ProgressBar;
    _minionHpBar->init(_x, _y, 52, 4);
    return S_OK;
}

HRESULT Enemy::init(const char * imageName, POINT position)
{
    init(imageName, position, 0.0f);
    return S_OK;
}
HRESULT Enemy::init(const char * imageName, float speed)
{
    init(imageName, PointMake(0, 0), speed);
    return S_OK;
}

void Enemy::release(void)
{
    //_image->release();
    _minionHpBar->release();
    SAFE_DELETE(_minionHpBar);
}

void Enemy::update(void)
{
    move();
    _minionHpBar->setX(_x - (_rc.right - _rc.left) / 2);
    _minionHpBar->setY(_y - 10 - (_rc.bottom - _rc.top) / 2);
    _minionHpBar->update();
    _minionHpBar->setGauge(_currentHp, _maxHp);
}

void Enemy::render(void)
{
    draw();
    animation();
}

bool Enemy::bulletCountFire(void)
{
    if (_rndFireCount + _bulletFireCount <= TIMEMANAGER->getWorldTime())
    {
        _bulletFireCount = TIMEMANAGER->getWorldTime();
        _rndFireCount = RND->getFromFloatTo(2.0f, 6.0f);
        return true;
    }
    return false;
}

// ��
// ���� ������-������ ���� ū Ư¡�̴�. 
// ����ȭ�� �ؼ� ������ �ɱ �����غ����Ѵ�.
// ������ �������� �ٸ��� ����� �޾� �ڽĿ��� ����
void Enemy::move(void)
{
    //_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void Enemy::draw(void)
{
    _image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
    _minionHpBar->render();
}

void Enemy::animation(void)
{
    if (_rndTimeCount + _worldTimeCount <= TIMEMANAGER->getWorldTime())
    {
        _worldTimeCount = TIMEMANAGER->getWorldTime();
        _currentFrameX++;
        if (_image->getMaxFrameX() < _currentFrameX)
        {
            _currentFrameX = 0;
        }
    }
}