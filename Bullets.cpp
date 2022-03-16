#include "Stdafx.h"
#include "Bullets.h"

HRESULT Missile::init(int bulletMax, float range)
{
    _range = range;

    for (int i = 0; i < bulletMax; i++)
    {
        tagBullet bullet;
        // �޸𸮸� 0���� �ʱ�ȭ(�޸� �ּ�, �޸� �� ������) : �޸� �� �� ��ŭ, �޸� �ּ��� �޸𸮸� 0���� �ʱ�ȭ
        ZeroMemory(&bullet, sizeof(tagBullet));

        bullet.img = new Image;
        bullet.img->init("Resources/Images/Object/Missile.bmp", 0.0f, 0.0f,
            416, 64, 13, 1, true, RGB(255, 0, 255));
        bullet.fire = false;
        bullet.speed = 5.0f;
        _vBullet.push_back(bullet);
    }
    _bulletTick = 7.0f;

    return S_OK;
}

void Missile::release(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        SAFE_DELETE(_viBullet->img);
    }

    _vBullet.clear();
}

void Missile::update(void)
{
    move();
}

void Missile::render(void)
{
    draw();
}

void Missile::fire(float x, float y)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        if (_viBullet->fire) continue;
        // ����Ʈ�� �Ϲ� �̻��� + �⺻��ġ 
        _viBullet->fire = true;
        _viBullet->x = _viBullet->fireX = x - 15;
        _viBullet->y = _viBullet->fireY = y - 90;

        _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
            _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

        break;
    }
}

void Missile::draw(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        if (!_viBullet->fire)continue;
        _viBullet->img->frameRender(getMemDC(), _viBullet->x, _viBullet->y);
    }
}

void Missile::removeBullet(int arrNum)
{
    SAFE_DELETE(_vBullet[arrNum].img);
    _vBullet.erase(_vBullet.begin() + arrNum);
}

void Missile::move(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        if (!_viBullet->fire) continue;

        // ������ ������ 
        if (_bulletTick <= GetTickCount())
        {
            _bulletTick = GetTickCount();
            _viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
            if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
            {
                _viBullet->img->setFrameX(0);
            }
        }

        // ��ġ �ű��
        _viBullet->y -= _viBullet->speed;

        _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
            _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
        //��Ÿ� ������ ������
        if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
            _viBullet->x, _viBullet->y))
        {
            _viBullet->fire = false;
        }
    }
}
// �̻��� M1 ------------------------------------------------------------------------------
HRESULT MissileM1::init(int bulletMax, float range)
{
    _range = range;
    _bulletMax = bulletMax;

    return S_OK;
}

void MissileM1::release(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        SAFE_DELETE(_viBullet->img);
    }

    _vBullet.clear();
}

void MissileM1::update(void)
{
    move();
}

void MissileM1::render(void)
{
    draw();
}
void MissileM1::fire(float x, float y)
{
    if (_bulletMax <= _vBullet.size()) return;

    tagBullet bullet;
    ZeroMemory(&bullet, sizeof(tagBullet));

    bullet.img = new Image;
    bullet.img->init("Resources/Images/Object/Missile.bmp", 0.0f, 0.0f, 416, 64, 13, 1, true, RGB(255, 0, 255));

    bullet.fire = false;
    bullet.speed = 4.0f;
    bullet.x = bullet.fireX = x;
    bullet.y = bullet.fireY = y - 70;
    bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

    _vBullet.push_back(bullet);
}

void MissileM1::move(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
    {
        // ��ġ �ű��
        _viBullet->y -= _viBullet->speed;

        _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
            _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

        //��Ÿ� ������ ������
        if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
            _viBullet->x, _viBullet->y))
        {
            SAFE_DELETE(_viBullet->img);
            _viBullet = _vBullet.erase(_viBullet);
        }
        else ++_viBullet;
    }
}

void MissileM1::draw(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        _viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
        _viBullet->count++;
        if (_viBullet->count % 3 == 0)
        {
            _viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
            if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
            {
                _viBullet->img->setFrameX(0);
            }
            _viBullet->count = 0;
        }
    }
}

void MissileM1::removeBullet(int arrNum)
{
    SAFE_DELETE(_vBullet[arrNum].img);
    _vBullet.erase(_vBullet.begin() + arrNum);
}

// �̻��� M2 ------------------------------------------------------------------------------
HRESULT MissileM2::init(int bulletMax, float range)
{
    _range = range;
    _bulletMax = bulletMax;
    _bulletIndex = 0;
    for (int i = 0; i < bulletMax; i++)
    {
        tagBullet bullet;
        ZeroMemory(&bullet, sizeof(tagBullet));

        bullet.img = new Image;
        bullet.img->init("Resources/Images/Object/Missile.bmp", 0.0f, 0.0f,
            416, 64, 13, 1, true, RGB(255, 0, 255));
        bullet.fire = false;
        bullet.speed = 5.0f;
        bullet.index = i;
        _vBullet.push_back(bullet);
    }
    _bulletTick = 7.0f;
    return S_OK;
}

void MissileM2::release(void)
{
    _viBullet = _vBullet.begin();
    for (; _viBullet != _vBullet.end(); ++_viBullet)
    {
        SAFE_DELETE(_viBullet->img);
    }
    _vBullet.clear();
}

void MissileM2::update(void)
{
    move();
}

void MissileM2::render(void)
{
    draw();
}

void MissileM2::fire(float x, float y)
{
    _viBullet = _vBullet.begin();
    for (; _viBullet != _vBullet.end(); ++_viBullet)
    {
        if (_viBullet->fire) continue;
        _viBullet->fire = true;
        _viBullet->x = _viBullet->fireX = x - 15;
        _viBullet->y = _viBullet->fireY = y - 90;

        _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
            _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
    }
}

void MissileM2::move(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        if (!_viBullet->fire) continue;

        // ������ ������ 
        if (_bulletTick <= GetTickCount())
        {
            _bulletTick = GetTickCount();
            _viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
            if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
            {
                _viBullet->img->setFrameX(0);
            }
        }

        _viBullet->x = cosf((_viBullet->index *(120 / _bulletMax) + 35)*PI / 180.0f) * _viBullet->speed + _viBullet->x;
        _viBullet->y = -sinf((_viBullet->index*(120 / _bulletMax) + 35)*PI / 180.0f) * _viBullet->speed + _viBullet->y;
        _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
            _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
        //��Ÿ� ������ ������
        if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
            _viBullet->x, _viBullet->y))
        {
            _viBullet->fire = false;
        }
    }
}

void MissileM2::draw(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        if (!_viBullet->fire)continue;
        _viBullet->img->frameRender(getMemDC(), _viBullet->x, _viBullet->y);
    }
}

void MissileM2::removeBullet(int arrNum)
{
    SAFE_DELETE(_vBullet[arrNum].img);
    _vBullet.erase(_vBullet.begin() + arrNum);
}
//============================================================================================mini
HRESULT MissileM3::init(int bulletMax, float range)
{
    _range = range;
    _bulletMax = bulletMax;
    _bulletIndex = 0;
    for (int i = 0; i < bulletMax; i++)
    {
        tagBullet bullet;
        ZeroMemory(&bullet, sizeof(tagBullet));

        bullet.img = new Image;
        bullet.img->init("Resources/Images/Object/Missile.bmp", 0.0f, 0.0f,
            416 / 2, 64 / 2, 13, 1, true, RGB(255, 0, 255));
        bullet.fire = false;
        bullet.speed = 10.0f;
        bullet.index = i;
        _vBullet.push_back(bullet);
    }
    _bulletTick = 7.0f;
    return S_OK;
}

void MissileM3::release(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        SAFE_DELETE(_viBullet->img);
    }
    _vBullet.clear();
}

void MissileM3::update(void)
{
    move();
}

void MissileM3::render(void)
{
    draw();
}

void MissileM3::fire(float x, float y)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        if (_viBullet->fire) continue;
        _viBullet->fire = true;
        _viBullet->x = _viBullet->fireX = x + 15 - 25 * _viBullet->index;
        _viBullet->y = _viBullet->fireY = y - 90;

        _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
            _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
    }
}

void MissileM3::move(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        if (!_viBullet->fire) continue;

        if (_bulletTick <= GetTickCount())
        {
            _bulletTick = GetTickCount();
            _viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
            if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
            {
                _viBullet->img->setFrameX(0);
            }
        }

        _viBullet->y -= _viBullet->speed;
        _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
            _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
        if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
            _viBullet->x, _viBullet->y))
        {
            _viBullet->fire = false;
        }
    }
}

void MissileM3::draw(void)
{
    for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
    {
        if (!_viBullet->fire)continue;
        _viBullet->img->frameRender(getMemDC(), _viBullet->x, _viBullet->y);
    }
}
void MissileM3::removeBullet(int arrNum)
{
    SAFE_DELETE(_vBullet[arrNum].img);
    _vBullet.erase(_vBullet.begin() + arrNum);
}
//============================================================================================

HRESULT Beam::init(int bulletMax, float range)
{
    _range = range;
    _bulletMax = bulletMax;
    return S_OK;
}
//void Beam::release(void)
//{
//	//1
//	for (_viBullet = _vBullet.begin(); _viBullet < _vBullet.end(); ++_viBullet)
//	{
//		SAFE_DELETE(_viBullet->img);
//	}
//
//	//2
//	_viBullet = _vBullet.begin();
//	for (; _viBullet < _vBullet.end(); ++_viBullet)
//	{
//		SAFE_DELETE(_viBullet->img);
//	}
//
//	//3 --->> ���ÿ��� ��õ
//	iterBullet iterBullet = _vBullet.begin();
//	for (; iterBullet != _vBullet.end(); ++iterBullet)
//	{
//		SAFE_DELETE(_viBullet->img);
//	}
//
//	//4 --->> ���ÿ����� �ظ��ϸ� �����ض�
//	for (auto iter = _vBullet.begin(); iter != _vBullet.end(); ++iter)
//	{
//		SAFE_DELETE(iter->img);
//	}
//
//	//5 ~~ 8 ���ٽ� (�˾Ƶθ� ������ �츮�� ���� �� �ʿ�� ����. ������ ���ʿ����δ� ����)
//	for (auto iter : _vBullet)
//	{
//		SAFE_DELETE(iter.img);
//	}
//
//	//6
//	for each(auto iter in _vBullet)
//	{
//		SAFE_DELETE(iter.img)
//	}
//
//	//7 ---->>>> �ݺ����� ���۰� ��, �׸��� �Լ��� ���ڷ� �޴´�
//	for_each(_vBullet.begin(), _vBullet.end(), update);
//
//	//8
//	int Value = 0;  //----> ĸó�� ����
//	for_each(_vBullet.begin(), _vBullet.end(), [&Value](auto& number) {Value += number; });
//	//�� �̰� ���ٴ�....
//
//	/*
//	- ����
//	-> [] () {} ()
//	=== [ĸó] (�Ű�����) {(��ȯ) �Լ� ����} (ȣ�� ����(���� ����))
//
//	*/
//
//	int numberA = 10;
//	int numberB = 10;
//
//	auto resultA = [](int numA, int numB) {return numA + numB; } (10, 10);
//	auto resultB = [&]()->int {return numberA + numberB; } ();
//	auto resultC = [=, &numberA]()->int {return numberA + numberB; } ();
//	// ---> ���ٿ��� ���� ���� ���̴� �� ���� ���
//
//	/*
//	[] : ���� ������ �ִ� ��� ������ ���� �Ұ��ϴ�
//	[&] : ���� ������ �ִ� ��� ������ ������ ĸó
//	[=] : ���� ������ �ִ� ��� ������ ������ ĸó
//	[&, ����] : ���� ������ �ִ� ��� ������ ĸó�ϵ� �� ������ ���� ������ ĸó
//	[=, &����] : ���� ������ �ִ� ��� ������ ĸó�ϵ� �� ������ ���� ĸó
//
//	*/
//
//	//8. �ݺ��ڸ� �̿��� �ݺ��� (����� �ٸ� �����̳ʿ� �����ϰ� ���� �����̳ʿ��� ����)
//
//	// ����Ʈ ������(����)
//	vector<int> vBulletReload;
//	transform(_vBullet.begin(), _vBullet.end(), vBulletReload.begin(), update);
//	transform(_vBullet.begin(), _vBullet.end(), vBulletReload.begin(),
//		[](__int64 numA)-> auto { return numA; });
//	//�����ٰ� ������ ���δ�
//
//	_vBullet.clear();
//}

void Beam::release(void)
{
    //3 ���� ���� �� �۾� ���
    // ���ͷ����� ��� 
    //��������� ���̴� ������ ������������ �� ���� ��� �� �Ⱥ��δ�
    _viBullet = _vBullet.begin();
    for (; _viBullet != _vBullet.end(); ++_viBullet)
    {
        SAFE_DELETE(_viBullet->img);
    }
    _vBullet.clear();
}

void Beam::update(void)
{
    move();
}

void Beam::render(void)
{
    draw();
}

void Beam::fire(float x, float y)
{
    if (_bulletMax <= _vBullet.size()) return;
    tagBullet bullet;
    ZeroMemory(&bullet, sizeof(tagBullet));

    bullet.img = new Image;
    bullet.img->init("Resources/Images/Object/Beam.bmp",
        0.0f, 0.0f, 412, 801, 4, 1, true, RGB(255, 0, 255));

    bullet.fire = false;
    bullet.speed = 0.1f;
    bullet.x = bullet.fireX = x;
    bullet.y = bullet.fireY = y - 440;
    bullet.rc = RectMakeCenter(bullet.x, bullet.y,
        bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

    _vBullet.push_back(bullet);
}

void Beam::move(void)
{
    _viBullet = _vBullet.begin();
    for (; _viBullet != _vBullet.end();)
    {
        // ��ġ �ű��
        _viBullet->y -= _viBullet->speed;

        _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
            _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

        //��Ÿ� ������ ������
        if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
            _viBullet->x, _viBullet->y))
        {
            SAFE_DELETE(_viBullet->img);
            _viBullet = _vBullet.erase(_viBullet);
        }
        else ++_viBullet;
    }
}

void Beam::draw(void)
{
    _viBullet = _vBullet.begin();
    for (; _viBullet != _vBullet.end(); ++_viBullet)
    {
        _viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);

        _viBullet->count++;
        if (_viBullet->count % 5 == 0)
        {
            _viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
            if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
            {
                _viBullet->img->setFrameX(0);
            }
            _viBullet->count = 0;
        }
    }
}


//���� �Ѿ�==============================================================
HRESULT Bullet::init(const char * imageName, int bulletMax, float range)
{
    _imageName = imageName;
    _range = range;
    _bulletMax = bulletMax;
    return S_OK;
}

void Bullet::release(void)
{
    _vBullet.clear();//������ �����
    //_viBullet = _vBullet.begin();
    //for (; _viBullet != _vBullet.end(); ++_viBullet)
    //{
    //    //SAFE_DELETE(_viBullet->img);
    //    //_viBullet = _vBullet.erase(_viBullet);
    //    //�� �̰� ������ ����....!
    //    //�� �̰� ������ ������������ ��������
    //    
    //}
}

void Bullet::update(void)
{
    move();
}

void Bullet::render(void)
{
    draw();
}

void Bullet::fire(float x, float y, float angle, float speed)
{
    //�ִ� �߻� ������ ���´�.
    if (_bulletMax <= _vBullet.size())return;

    tagBullet bullet;
    ZeroMemory(&bullet, sizeof(tagBullet));
    bullet.img = IMAGEMANAGER->findImage(_imageName);
    bullet.speed = speed;
    bullet.angle = angle;
    bullet.x = bullet.fireX = x;
    bullet.y = bullet.fireY = y;
    bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());

    _vBullet.push_back(bullet);
}
//�����̱⿡ ���갡 �߿� 
void Bullet::move(void)
{
    _viBullet = _vBullet.begin();
    for (; _viBullet != _vBullet.end();)
    {
        _viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
        _viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

        _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
            _viBullet->img->getWidth(), _viBullet->img->getHeight());

        //��Ÿ� ������ ������
        if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
            _viBullet->x, _viBullet->y))
        {
            //SAFE_DELETE(_viBullet->img);>>�̰� �����ȵ�
            _viBullet = _vBullet.erase(_viBullet);
        }
        else ++_viBullet;
    }
}

void Bullet::draw(void)
{
    _viBullet = _vBullet.begin();
    for (; _viBullet != _vBullet.end(); ++_viBullet)
    {
        _viBullet->img->render(getMemDC(), _viBullet->rc.left,
            _viBullet->rc.top);
    }
}

void Bullet::removeBullet(int arrNum)
{
    _vBullet.erase(_vBullet.begin() + arrNum);
}
