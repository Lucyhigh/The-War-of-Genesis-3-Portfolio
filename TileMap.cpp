#include "Stdafx.h"
#include "TileMap.h"

HRESULT TileMap::init(void)
{
	tileNum =3;

	for (int i = 0; i < tileNum; i++)
	{
		tagTile tile;
		ZeroMemory(&tile, sizeof(tagTile));

		tile.img = new Image;
		tile.img->init("Resources/Images/Object/Tile01.bmp",0,0, 100, 100, true, RGB(255, 0, 255));
		tile.rc = RectMake(100,100,100,100);
		tile.onTile = true;
		tile.x = 0; tile.y = 0;

		_vTileMap.push_back(tile);
	}


	return S_OK;
}



void TileMap::release(void)
{
}

void TileMap::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		tileNum = 3;
		//cout << "tileNum " << tileNum << endl;

	}



	for (_viTileMap=_vTileMap.begin() ; _viTileMap != _vTileMap.end(); ++_viTileMap)
	{

		for (int i = 0; i < tileNum; i++)
		{
			for (int j = 0; j < tileNum; j++)
			{
				_viTileMap->rc = RectMake(100 + j * 100, 100 + i * 100, 100, 100);
			}
		}
			_viTileMap->img->setX(_viTileMap->rc.left);
			_viTileMap->img->setY(_viTileMap->rc.top);
		//	cout << "이터 rc.top "<< _viTileMap->rc.top << endl;


	}

}

void TileMap::render(void)
{
	for (_viTileMap = _vTileMap.begin(); _viTileMap != _vTileMap.end(); ++_viTileMap)
	{
		if (_viTileMap->onTile) 
		{
			_viTileMap->img->render(getMemDC(), _viTileMap->img->getX(), _viTileMap->img->getY() );
			//cout << "그림  rc.top / getY() " << _viTileMap->rc.top  << "," << _viTileMap->img->getY() << endl;
		}

		rcMake(getMemDC(), _viTileMap->rc);
	}

}
