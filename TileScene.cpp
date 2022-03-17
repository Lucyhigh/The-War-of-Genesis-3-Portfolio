#include "Stdafx.h"
#include "TileScene.h"

HRESULT TileScene::init(void)
{
	_mapTileInfo = new MapTileInfo;
	_mapTileInfo->init();
	_image = IMAGEMANAGER->addImage("초원", "Resources/Images/BackGround/Field.bmp", 2120, 1536);

	IMAGEMANAGER->addFrameImage("타일 표시", "Resources/Images/UI/Tile.bmp", 240, 32, 6, 1, true);
	IMAGEMANAGER->addImage("타일 표시2", "Resources/Images/UI/1.bmp", 40, 32);

	numX =53;
	numY = 48;//_image/TileSize
	index = x = y = 0;

	for (x = 0; x < numX; x++)
	{
		for (y = 0; y < numY; y++)
		{
			tagTile tileInfo = { x, y };
			_tile.push_back(tileInfo);
		}
	}

	_player = new Player;
	_player->init();
	_player->setPlayerPosX(250);
	_player->setPlayerPosY(WINSIZE_Y - 200);

	_camera = new Camera;
	_camera->init();
	_camera->setLimitsX(CENTER_X, _image->getWidth());
	_camera->setLimitsY(CENTER_Y, _image->getHeight());
	
	return S_OK;
}

void TileScene::release(void)
{
	_tile.clear();
	_player->release();
	_camera->release();
}

void TileScene::update(void)
{
	_tIter = _tile.begin();
	for (; _tIter != _tile.end(); _tIter++)
	{
		if (PtInRect(&node->getRect(), _ptMouse) )//&&  node->getType() ==0)
		{
			_mouseRc = node->getRect();
			
			//cout << _mouseRc.left << " , " << _mouseRc.top << endl;
			break;
		}
	}

	POINT cameraPos;
	cameraPos.x = _player->getPlayerPosX();
	cameraPos.y = _player->getPlayerPosY();
	_camera->setCameraPos(cameraPos);
	_camera->update();
	_player->setCameraRect(_camera->getScreenRect());
	_player->update();

}

void TileScene::render(void)
{
	drawMapCellInfo();
	_camera->render();

	char pos[256];
	SetTextColor(getMemDC(), RGB(0, 0, 0));

	IMAGEMANAGER->render("초원", getMemDC(), 0, 0,
								_camera->getScreenRect().left,
								_camera->getScreenRect().top,
								WINSIZE_X, WINSIZE_Y);
	_tIter = _tile.begin();
	for (; _tIter != _tile.end(); _tIter++)
	{
		if (KEYMANAGER->isToggleKey(VK_F2))
		{
			Rectangle(getMemDC(), node->getRect().left - _camera->getScreenRect().left,
								  node->getRect().top - _camera->getScreenRect().top,
								  node->getRect().right- _camera->getScreenRect().left,
								  node->getRect().bottom - _camera->getScreenRect().top);
	
			sprintf(pos, "%d, %d", _tIter->x, _tIter->y);
			TextOut(getMemDC(), _tIter->x * TILESIZEX - _camera->getScreenRect().left,
								_tIter->y * TILESIZEY - _camera->getScreenRect().top,
								pos, strlen(pos));
		}
		//카메라 달면 위치이상해짐
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
	IMAGEMANAGER->render("타일 표시2", getMemDC(), _mouseRc.left, _mouseRc.top);//카메라 달면 위치이상해짐

	_player->render();
}

void TileScene::drawMapCellInfo()
{
	char cellIndex[256];
	vector<Cell*>* temp = _mapTileInfo->getCell();
	Cell* node = temp->front();

	sprintf(cellIndex, "X : %d, Y : %d", node->getCellX(), node->getCellY());
	TextOut(getMemDC(), node->getRect().left - _camera->getScreenRect().left,
						node->getRect().top - _camera->getScreenRect().top,
						cellIndex, strlen(cellIndex));
}

void TileScene::curMap()
{
}
