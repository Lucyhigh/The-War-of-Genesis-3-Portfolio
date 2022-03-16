#include "Stdafx.h"
#include "TileScene.h"

HRESULT TileScene::init(void)
{
	numX = 10;
	numY = 10;
	index = x = y = 0;
	
	for (x = 0; x < numX; x++)
	{
		for (y = 0; y < numY; y++)
		{
			tagTile tileInfo = { x, y, TILESIZE, TILESIZE,
				Rectangle(getMemDC(), x*TILESIZE, y*TILESIZE,
									  x*TILESIZE + TILESIZE,
									  y*TILESIZE + TILESIZE) };
			_tile.push_back(tileInfo);
		}
	}

	return S_OK;
}

void TileScene::release(void)
{
	_tile.clear();
}

void TileScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		numX++;
		numY++;
		for (x = 0; x < numX; x++)
		{
			for (y = 0; y < numY; y++)
			{
				tagTile tileInfo = { x, y, TILESIZE, TILESIZE,
				Rectangle(getMemDC(), x*TILESIZE, y*TILESIZE,
									  x*TILESIZE + TILESIZE,
									  y*TILESIZE + TILESIZE)};
				_tile.push_back(tileInfo);
			}
		}
	}


	
}

void TileScene::render(void)
{
	char pos[258];
	SetTextColor(getMemDC(), RGB(0,0,0));

	_tIter = _tile.begin();
	for (; _tIter !=_tile.end(); _tIter++)
	{
		Rectangle(getMemDC(),_tIter->rect.left, _tIter->rect.top, _tIter->rect.right, _tIter->rect.bottom);

		sprintf(pos, "%d, %d", _tIter->x, _tIter->y);
		TextOut(getMemDC(), _tIter->x * 50, _tIter->y * 50, pos, strlen(pos));
		//cout << numX << " , " << numY << endl;
		if (PtInRect(&_tIter->rect, pt))
		{

		}
	}

}
