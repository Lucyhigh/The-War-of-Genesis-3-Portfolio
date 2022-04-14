#include "Stdafx.h"
#include "Utils.h"

namespace MY_UTIL
{
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrt(x*x + y * y);
	
	}

	float getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;
		float d = sqrt(x*x + y * y);
		float angle = acos(x / d);

		if (y > 0)angle = PI_2 - angle;
	
		return angle;
	}

	vector<string> getFilesInDirectory(const string& _path, const string& _filter)
	{
		string searching = _path + _filter;

		vector<string> vfileNameList;

		WIN32_FIND_DATA fd;
		HANDLE hFind = FindFirstFile(searching.c_str(), &fd);  //현재 폴더 내 모든 파일을 찾는다.

		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					vfileNameList.push_back(fd.cFileName);
				}
			} while (FindNextFile(hFind, &fd));
			FindClose(hFind);
		}

		return vfileNameList;
	}
}
