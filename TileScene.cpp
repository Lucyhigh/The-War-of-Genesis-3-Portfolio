#include "Stdafx.h"
#include "TileScene.h"

HRESULT TileScene::init(void)
{
	_mapTileInfo = new MapTileInfo;
	_mapTileInfo->init();
	_image = IMAGEMANAGER->findImage("Field");
	_cells = _mapTileInfo->getCell();

	_player = new Player;
	_player->init();
	_player->setPlayerPosX(250);
	_player->setPlayerPosY(WINSIZE_Y - 200);

	_camera = new Camera;
	_camera->init();
	_camera->setLimitsX(CENTER_X, _image->getWidth());
	_camera->setLimitsY(CENTER_Y, _image->getHeight());

	//_ani = new AniTestScene;
	//_ani->init();
	return S_OK;
}

void TileScene::release(void)
{
	_player->release();
	SAFE_DELETE(_player);
	_camera->release();
	SAFE_DELETE(_camera);
}

void TileScene::update(void)
{

	POINT cameraPos;
	cameraPos.x = _player->getPlayerPosX();
	cameraPos.y = _player->getPlayerPosY();
	_camera->setCameraPos(cameraPos);
	_camera->update();
	_player->setCameraRect(_camera->getScreenRect());
	_player->update();

	POINT playerPoint = { _player->getPlayerPosX(),_player->getPlayerPosY() };

	for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)
	{
		Cell* cell = (*cellsIter);

		if (PtInRect(&cell->getRect(), playerPoint))
		{
			//_mouseIndex = (int)cell->getType();
			if (cell->getType() != CELL_TYPE::WALL)
			{
				cell->setType(CELL_TYPE::START);
			}
			cout << playerPoint.x << " , " << playerPoint.y << endl;
		}
		else if (cell->getType() == CELL_TYPE::START)
		{
			cell->setType(CELL_TYPE::NORMAL);
		}

		POINT cameraMouse = { 
							  _ptMouse.x + _camera->getScreenRect().left,
							  _ptMouse.y + _camera->getScreenRect().top 
							};
		if (PtInRect(&cell->getRect(), cameraMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (cell->getType() == CELL_TYPE::NORMAL)
					cell->setType(CELL_TYPE::GOAL);
			}
			
			break;
		}
	}

	//Astar::Coordinate A(0, 0);
	//Astar::Coordinate B(5, 4);

	//Astar astar(A, B);

	//astar.PrintNavi();
	

}

void TileScene::render(void)
{
	_camera->render();

	int cameraLeft = _camera->getScreenRect().left;
	int cameraTop = _camera->getScreenRect().top;
	IMAGEMANAGER->render("Field", getMemDC(), 0, 0,
		cameraLeft,
		cameraTop,
		WINSIZE_X, WINSIZE_Y);
	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		drawMapCellInfo();
	}


	for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)
	{
		Cell* cell = (*cellsIter);
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0)); // 색 설정
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);

		int left = cell->getRect().left - cameraLeft;
		int top = cell->getRect().top - cameraTop;
		RECT rect = RectMake(left, top, TILESIZEX, TILESIZEY);
		switch (cell->getType())
		{
		case(CELL_TYPE::NORMAL):
			break;
		case(CELL_TYPE::WALL):
			oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
			FillRect(getMemDC(), &rect, brush); // 사각형에 브러쉬색으로 채우기
			break;
		case(CELL_TYPE::START):
			brush = CreateSolidBrush(RGB(0, 0, 255)); // 색 설정
			oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
			FillRect(getMemDC(), &rect, brush); // 사각형에 브러쉬색으로 채우기
			SelectObject(getMemDC(), oldBrush);
			break;
		case(CELL_TYPE::GOAL):
			brush = CreateSolidBrush(RGB(120, 120, 120)); // 색 설정
			oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
			FillRect(getMemDC(), &rect, brush); // 사각형에 브러쉬색으로 채우기
			break;
		}
		DeleteObject(brush);
	}

	_player->render();
}

void TileScene::drawMapCellInfo()
{
	char cellIndex[1024];
	SetTextColor(getMemDC(), RGB(0, 0, 0));

	for (auto cellsIter = _cells->begin(); cellsIter != _cells->end(); ++cellsIter)
	{
		Cell* cell = (*cellsIter);
		sprintf(cellIndex, "%d,%d", cell->getCellX(), cell->getCellY());
		TextOut(getMemDC(), cell->getRect().left - _camera->getScreenRect().left,
							cell->getRect().top - _camera->getScreenRect().top,
							cellIndex, strlen(cellIndex));
	}
}

void TileScene::curMap()
{
}