#include "stdafx.h"
#include "mapTool.h"

vector<int> mapTool::aStarPath(int fromTileNum, int toTileNum)
{
	_path.clear();
	_vTotalList.clear();
	_vOpenList.clear();
	_vCloseList.clear();
	for (int i = 0; i < 900; ++i)
	{
		tagMAStarTile* aStarTile = new tagMAStarTile;
		aStarTile->tileNum = i;
		aStarTile->parentNodeTileNum = -1;
		aStarTile->totalCost = 0;
		aStarTile->costFromStart = 0;
		aStarTile->costToGoal = 0;
		aStarTile->isOpen = true;
		_vTotalList.push_back(aStarTile);
	}
	_stop = 0;
	_startTile = fromTileNum;
	_endTile = toTileNum;
	_currentTile = _startTile;
	pathFinder(_currentTile);

	return _path;
}

// #############################################################

vector<tagMAStarTile*> mapTool::addOpenList(int currentTile)
{
	int startX = currentTile % 30 - 1;
	int startY = currentTile / 30 - 1;

	for (int i = 0; i < 3; ++i)
	{
		//// ############ 벡터 안터지게 #####################
		if (startY + i < 0)			continue;
		if (startY + i >= 30)		continue;
		for (int j = 0; j < 3; ++j)
		{
			if (startX + j < 0)		continue;
			if (startX + j >= 30)	continue;

			int checkIndex = (startY + i) * 30 + (startX + j);
			tagMAStarTile* aStarTile = _vTotalList[checkIndex];

			//예외처리!
			if (!aStarTile->isOpen) continue;
			if (_isoTile[checkIndex].MUM == UNMOVE) continue;
			if (checkIndex == _startTile) continue;

			// ##################월담 방지#############################
			int nodeTop;
			if (startY < 0)				nodeTop = 1;
			else nodeTop = _isoTile[(startY * 30) + startX + 1].MUM;
			// 위막혀있으면 왼쪽위와 오른쪽 위를 못가게함 i==0위 i==2아래 j==0왼 j==2오른
			if (i == 0 && nodeTop == 1)	continue;
			int nodeBottom;
			if (startY + 2 >= 30)	nodeBottom = 1;
			else nodeBottom = _isoTile[(startY * 30) + startX + 61].MUM;
			// 아래막혀있으면 왼쪽아래와 오른쪽 아래를 못가게함
			if (i == 2 && nodeBottom == 1)	continue;
			int nodeLeft;
			if (startX < 0)				nodeLeft = 1;
			else nodeLeft = _isoTile[(startY * 30) + startX + 30].MUM;
			// 왼쪽막혀있으면 왼쪽위와 왼쪽아래를 못가게함
			if (j == 0 && nodeLeft == 1)	continue;
			int nodeRight;
			if (startX + 2 >= 30)	nodeRight = 1;
			else nodeRight = _isoTile[(startY * 30) + startX + 32].MUM;
			// 오른쪽막혀있으면 오른쪽위와 오른쪽 아래로 못가게함
			if (j == 2 && nodeRight == 1)	continue;


			//현재 타일을 계속 갱신해준다
			aStarTile->parentNodeTileNum = _currentTile;

			bool addObj = true;
			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				if (*_viOpenList == aStarTile)
				{ // 있는거면 추가안함
					addObj = false;
					break;
				}
			}
			if (!addObj) continue;

			_vOpenList.push_back(aStarTile);
		}
	}

	return _vOpenList;
}

void mapTool::pathFinder(int currentTile)
{
	//경로비용을 매우 쉽게 하기 위해서 임의의 경로비용을 둠
	int tempTotalCost = 5000;
	tagMAStarTile* tempTile = nullptr;

	bool changed = false;

	//갈수 있는 길을 담은 벡터 내부에서 가장 빠른 경로를 뽑아야한다
	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{ // 여기서 주변방향 넣음과 동시에 리턴으로 총오픈리스트를 가져오는거
		_vOpenList[i]->costToGoal = (abs(_endTile % 30 - _vOpenList[i]->tileNum % 30) +
			abs(_endTile / 30 - _vOpenList[i]->tileNum / 30)) * 11;

		int cost;

		if (_vOpenList[i]->tileNum + 1 == _vOpenList[i]->parentNodeTileNum
			|| _vOpenList[i]->tileNum - 1 == _vOpenList[i]->parentNodeTileNum
			|| _vOpenList[i]->tileNum + 30 == _vOpenList[i]->parentNodeTileNum
			|| _vOpenList[i]->tileNum - 30 == _vOpenList[i]->parentNodeTileNum) cost = 9;
		else if (_vOpenList[i]->tileNum + 31 == _vOpenList[i]->parentNodeTileNum
			|| _vOpenList[i]->tileNum - 31 == _vOpenList[i]->parentNodeTileNum) cost = 8;
		else if (_vOpenList[i]->tileNum + 29 == _vOpenList[i]->parentNodeTileNum
			|| _vOpenList[i]->tileNum - 29 == _vOpenList[i]->parentNodeTileNum) cost = 16;

		_vOpenList[i]->costFromStart = cost;

		//F = G + H 니까~ 
		_vOpenList[i]->totalCost = _vOpenList[i]->costToGoal + _vOpenList[i]->costFromStart;

		//경로비용(F)이 가장 작은 애로 계속 갱신해준다
		if (tempTotalCost > _vOpenList[i]->totalCost)
		{
			tempTotalCost = _vOpenList[i]->totalCost;
			tempTile = _vOpenList[i];
		} // 열린리스트중 경로비용 가장작은애가 탐색되어 템프타일로 들어옴

		bool addObj = true;
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == tempTile)
			{ // 열린리스트에 템프타일이 있다면 -> 새로 열린놈들중에서도 비용값이 작은게 없다?
				addObj = false;
				changed = true;
				break;
			} // 불값만들고 포문에서 잡히면 false로 만드니 이중포문 안돌릴수있음
		}
		_vOpenList[i]->isOpen = false; // 닫음
		if (!addObj) continue;

		_vOpenList.push_back(tempTile); // 추가해야된다고 했으니 추가하는거
	}

	// ############## 경로 못찾으면 끝내는 함수 #####################
	if (!changed)
	{// 아무것도 변경안하고 포문이 무사히(?) 돌았다면 끝낸다
		_stop = true;
		return;
	}

	//도착했다면
	if (tempTile->tileNum == _endTile)
	{
		while (_currentTile != _startTile)
		{
			_path.push_back(_currentTile);
			_currentTile = _vTotalList[_currentTile]->parentNodeTileNum;
		}
		_stop = true;
		return;
	}

	_vCloseList.push_back(tempTile);
	// 템프타일을 닫힌리스트에 넣고 오픈리스트에선 빼줌. 그리고 현재타일로 해줌
	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_currentTile = tempTile->tileNum;

	if (!_stop) pathFinder(_currentTile);
}