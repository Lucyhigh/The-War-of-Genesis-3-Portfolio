#pragma once
//===========================================================
// # commomMacroFunction # (필요한 함수는 직접 만들어 추가하자)
//===========================================================
/*
인라인 단점
- 메모리 많이 먹음
- 자료형에 독립적이지 못함
ㄴ 그래서 템플릿으로 물림
*/
inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void rcMake(HDC hdc, RECT &rc) // 0126add
{
	Rectangle(hdc, rc.left,rc.top,rc.right,rc.bottom);
}

inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

inline RECT CollisionAreaResizing(RECT &rcDest, int width, int height)
{
	RECT rc = { rcDest.left + width / 2, rcDest.top + height / 2,
	rcDest.right - width / 2,rcDest.bottom - height / 2 };

	return rc;
}