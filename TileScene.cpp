#include "Stdafx.h"
#include "TileScene.h"

HRESULT TileScene::init(void)
{
	numX = 10;
	numY = 10;
	index = x = y = 0;
	return S_OK;
}

void TileScene::release(void)
{
}

void TileScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		numX++;
		numY++;
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		numX--;
		numY--;
	}
}

void TileScene::render(void)
{
	char pos[258];
	SetTextColor(getMemDC(), RGB(0,0,0));

	for (x = 0; x < numX; x++)
	{
		for (y = 0; y < numY; y++)
		{
			Rectangle(getMemDC(), x * 100, y * 100, x * 100 + 100, y * 100 + 100);
			sprintf(pos, "%d, %d",x,y);
			TextOut(getMemDC(), x * 100, y * 100, pos, strlen(pos));
			cout << numX << " , " << numY << endl;
		}
	}

}
