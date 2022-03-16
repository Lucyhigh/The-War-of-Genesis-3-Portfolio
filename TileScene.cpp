#include "Stdafx.h"
#include "TileScene.h"

HRESULT TileScene::init(void)
{
	_image = IMAGEMANAGER->addImage("초원", "Resources/Images/BackGround/Field.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addFrameImage("타일 표시", "Resources/Images/UI/Tile.bmp", 240, 32,6,1,true);
	IMAGEMANAGER->addImage("타일 표시2", "Resources/Images/Object/buttomE.bmp", 35, 38);
	numX = WINSIZE_X / TILESIZEX;
	numY = WINSIZE_Y / TILESIZEY;
	index = x = y = 0;
	

	for (x = 0; x < numX; x++)
	{
		for (y = 0; y < numY; y++)
		{
			tagTile tileInfo = {x, y,RectMake(x*TILESIZEX, y*TILESIZEY,TILESIZEX,TILESIZEY),0 };
			_tile.push_back(tileInfo);
		}
	}

	//_player = new Player;
	//_player->init();
	//_player->setPlayerPosX(150);

	//_camera = new Camera;
	//_camera->init();
	//_camera->setLimitsX(CENTER_X, _image->getWidth());
	//_camera->setLimitsY(CENTER_Y, _image->getHeight());

	return S_OK;
}

void TileScene::release(void)
{
	_tile.clear();
}

void TileScene::update(void)
{
	/*if (KEYMANAGER->isOnceKeyDown('W'))
	{
	}
*/
	_tIter = _tile.begin();
	for (; _tIter != _tile.end(); _tIter++)
	{
		if (PtInRect(&_tIter->rect, _ptMouse))
		{
				_mouseRc = _tIter->rect;
				cout << _mouseRc.left << " , " << _mouseRc.top << endl;
				break;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_tIter->info++;


			}
		}
	}
}

void TileScene::render(void)
{
	char pos[258];
	SetTextColor(getMemDC(), RGB(0,0,0));
	//IMAGEMANAGER->render("초원", getMemDC());
	_tIter = _tile.begin();
	for (; _tIter !=_tile.end(); _tIter++)
	{
		Rectangle(getMemDC(),_tIter->rect.left, _tIter->rect.top, _tIter->rect.right, _tIter->rect.bottom);
	/*	if (KEYMANAGER->isOnceKeyDown(VK_F1))
		{

		}*/
		if(KEYMANAGER->isToggleKey(VK_F2))
		{
			sprintf(pos, "%d, %d", _tIter->x, _tIter->y);
			TextOut(getMemDC(), _tIter->x * TILESIZEX, _tIter->y * TILESIZEY, pos, strlen(pos));
		}

		
		
		//HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0)); // 색 설정
		//switch (_tIter->info)
		//{
		//case(0):
		//	break;
		//case(1):
		//	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		//	Rectangle(getMemDC(), _tIter->rect.left, _tIter->rect.top, _tIter->rect.right, _tIter->rect.bottom);
		//	FillRect(getMemDC(), &_tIter->rect, brush); // 사각형에 브러쉬색으로 채우기
		//	DeleteObject(brush);
		//	break;
		//case(2):
		//	brush = CreateSolidBrush(RGB(0, 0, 255)); // 색 설정
		//	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		//	Rectangle(getMemDC(), _tIter->rect.left, _tIter->rect.top, _tIter->rect.right, _tIter->rect.bottom);
		//	FillRect(getMemDC(), &_tIter->rect, brush); // 사각형에 브러쉬색으로 채우기
		//	SelectObject(getMemDC(), oldBrush);
		//	DeleteObject(brush);
		//	break;
		//case(3):
		//	brush = CreateSolidBrush(RGB(120, 120, 120)); // 색 설정
		//	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		//	Rectangle(getMemDC(), _tIter->rect.left, _tIter->rect.top, _tIter->rect.right, _tIter->rect.bottom);
		//	FillRect(getMemDC(), &_tIter->rect, brush); // 사각형에 브러쉬색으로 채우기
		//	DeleteObject(brush);
		//	break;
		//}
	}
	IMAGEMANAGER->render("타일 표시2", getMemDC(), _mouseRc.left, _mouseRc.top);

}
