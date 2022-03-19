#include "Stdafx.h"
#include "TileScene.h"

HRESULT TileScene::init(void)
{
	_mapTileInfo = new MapTileInfo;
	_mapTileInfo->init();
	_image = IMAGEMANAGER->addImage("초원", "Resources/Images/BackGround/Field.bmp", 2120, 1536);


	cells = _mapTileInfo->getCell();
	for (int i = 0; i < cells->size(); i++)
	{
		//cell의 정보 다 푸시해주기
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
	_player->release();
	_camera->release();
}

void TileScene::update(void)
{	
	for (auto cellsIter = cells->begin(); cellsIter != cells->end(); ++cellsIter)
	{
		Cell* cell = (*cellsIter);
		if (PtInRect(&cell->getRect(), _ptMouse))
		{
			_mouseRc = cell->getRect();
			cout << _mouseRc.left << " , " << _mouseRc.top << endl;
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
	_camera->render();

	IMAGEMANAGER->render("초원", getMemDC(), 0, 0,
								_camera->getScreenRect().left,
								_camera->getScreenRect().top,
								WINSIZE_X, WINSIZE_Y);
	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		drawMapCellInfo();
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
	
	IMAGEMANAGER->render("타일 표시2", getMemDC(), _mouseRc.left, _mouseRc.top);//카메라 달면 위치이상해짐

	_player->render();
}

void TileScene::drawMapCellInfo()
{
	char cellIndex[1024];
	SetTextColor(getMemDC(), RGB(0, 0, 0));

	for (auto cellsIter = cells->begin(); cellsIter != cells->end(); ++cellsIter)
	{
		Cell* cell = (*cellsIter);
		sprintf(cellIndex, "X : %d, Y : %d", cell->getCellX(), cell->getCellY());
		TextOut(getMemDC(), cell->getRect().left - _camera->getScreenRect().left,
							cell->getRect().top - _camera->getScreenRect().top,
							cellIndex, strlen(cellIndex));
	}
}

void TileScene::curMap()
{
}