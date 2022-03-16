#pragma once
#include "SingletonBase.h"

class FontManager : public SingletonBase <FontManager>
{
public:
	FontManager() {}
	~FontManager() {}

	// 파일경로 읽어올때
	void dramText(HDC hdc, int destX, int destY, char* fileName, char* fontName, int fontSize, int fontWidth,
		char* printString, int length, COLORREF color);

	void dramText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		char* printString, int length, COLORREF color);

	// LPCWSTR : W -> multy char -> Unicode;
	void dramText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		LPCWSTR printString, int length, COLORREF color);

	// 문자열로 찾음 -> 반복문으로 돈다
	void dramText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
		LPCWSTR* printStringArr, int length, COLORREF color);


};

