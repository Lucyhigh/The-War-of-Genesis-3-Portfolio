#include "stdafx.h"
#include "mapTool.h"

void mapTool::tempSave()
{// 마우스 딱 누를때만 타일이 그려지기전 발동함. temp에 저장
	_tempSaved = true;
	HANDLE file;
	DWORD write;

	file = CreateFile("temp.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &write, NULL);

	CloseHandle(file);
}

void mapTool::tempLoad()
{// temp를 불러옴
	if (!_tempSaved) return;
	HANDLE file;
	DWORD read;

	file = CreateFile("temp.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &read, NULL);

	for (int i = 0; i < 900; ++i)
	{
		if (_isoTile[i].name == PLAYERFLAG) _playerTile = i;
		else if (_isoTile[i].name == ENEMYFLAG) _enemyTile = i;
	}

	CloseHandle(file);
}

void mapTool::save()
{
	if (PtInRect(&_saveBt, _cameraPtMouse))
	{
		if (_playerTile != -1 && _enemyTile != -1)	aStarPath(_playerTile, _enemyTile);
		if (_path.empty() || _playerTile == -1 || _enemyTile == -1)
		{
			_savePopUp = 2;
			_popUpCount = 120;
			return;
		}
		_seePath = true;
		_currentStage = 1;
		HANDLE file;
		DWORD write;

		file = CreateFile("stage1.map", GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _isoTile, sizeof(isoTile) * TILEX * TILEY, &write, NULL);

		CloseHandle(file);
		_savePopUp = 1;
		_popUpCount = 120;
	}

	if (PtInRect(&_saveBt2, _cameraPtMouse))
	{
		if (_playerTile != -1 && _enemyTile != -1)	aStarPath(_playerTile, _enemyTile);
		if (_path.empty() || _playerTile == -1 || _enemyTile == -1)
		{
			_savePopUp = 2;
			_popUpCount = 120;
			return;
		}
		_seePath = true;
		_currentStage = 2;
		HANDLE file;
		DWORD write;

		file = CreateFile("stage2.map", GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _isoTile, sizeof(isoTile) * TILEX * TILEY, &write, NULL);

		CloseHandle(file);
		_savePopUp = 1;
		_popUpCount = 120;
	}

	if (PtInRect(&_saveBt3, _cameraPtMouse))
	{
		if (_playerTile != -1 && _enemyTile != -1)	aStarPath(_playerTile, _enemyTile);
		if (_path.empty() || _playerTile == -1 || _enemyTile == -1)
		{
			_savePopUp = 2;
			_popUpCount = 120;
			return;
		}
		_seePath = true;
		_currentStage = 3;
		HANDLE file;
		DWORD write;

		file = CreateFile("stage3.map", GENERIC_WRITE, NULL, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(file, _isoTile, sizeof(isoTile) * TILEX * TILEY, &write, NULL);

		CloseHandle(file);
		_savePopUp = 1;
		_popUpCount = 120;
	}
}

void mapTool::load()
{
	if (PtInRect(&_loadBt, _cameraPtMouse))
	{
		HANDLE file;
		DWORD read;

		file = CreateFile("stage1.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX * TILEY, &read, NULL);

		CloseHandle(file);
		_currentStage = 1;
		_playerTile = _enemyTile = -1;
		for (int i = 0; i < 900; ++i)
		{
			if (_isoTile[i].name == PLAYERFLAG) _playerTile = i;
			else if (_isoTile[i].name == ENEMYFLAG) _enemyTile = i;
		}
	}

	if (PtInRect(&_loadBt2, _cameraPtMouse))
	{
		HANDLE file;
		DWORD read;

		file = CreateFile("stage2.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX * TILEY, &read, NULL);

		CloseHandle(file);
		_currentStage = 2;

		_playerTile = _enemyTile = -1;
		for (int i = 0; i < 900; ++i)
		{
			if (_isoTile[i].name == PLAYERFLAG) _playerTile = i;
			else if (_isoTile[i].name == ENEMYFLAG) _enemyTile = i;
		}
	}

	if (PtInRect(&_loadBt3, _cameraPtMouse))
	{
		HANDLE file;
		DWORD read;

		file = CreateFile("stage3.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX * TILEY, &read, NULL);

		CloseHandle(file);
		_currentStage = 3;

		_playerTile = _enemyTile = -1;
		for (int i = 0; i < 900; ++i)
		{
			if (_isoTile[i].name == PLAYERFLAG) _playerTile = i;
			else if (_isoTile[i].name == ENEMYFLAG) _enemyTile = i;
		}
	}
}