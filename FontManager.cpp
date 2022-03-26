#include "Stdafx.h"
#include "FontManager.h"


void FontManager::drawText(HDC hdc, int destX, int destY, char* fileName, char* fontName, int fontSize, int fontWidth, char* printString, int length, COLORREF color)
{
}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth, char* printString, int length, COLORREF color)
{
}
void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth, LPCWSTR printString, int length, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);

	/*
	font = CreateFont
	(
		문자크기, 문자폭, 문자 전체 기울기, 문자 방향, 문자 굵기,
		기울기(true, false), 밑줄(true, false), 취소선(true, false),
		문자세팅, 출력 정확도, 클리핑 정확도, 출력의 질, 자간, 폰트
	)*/

	HFONT hFont = CreateFont
	(
		fontSize, 0, 0, 5, fontWidth,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN | FW_BOLD, TEXT(fontName)
	);

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);

	SetTextColor(hdc, color);
	TextOutW(hdc, destX, destY, printString, length);
}
void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth, LPCWSTR printString, int length,UINT textAlign,  COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);

		/*
		font = CreateFont
		(
			문자크기, 문자폭, 문자 전체 기울기, 문자 방향, 문자 굵기,
			기울기(true, false), 밑줄(true, false), 취소선(true, false),
			문자세팅, 출력 정확도, 클리핑 정확도, 출력의 질, 자간, 폰트
		)*/

		HFONT hFont = CreateFont
		(
			fontSize,0,0,5,fontWidth,
			0,0,0,
			HANGEUL_CHARSET, 0,0,0,
			VARIABLE_PITCH|FF_ROMAN| FW_BOLD, TEXT(fontName)
		);

		auto oldFont = (HFONT)SelectObject(hdc, hFont);
		auto oldColor = GetTextColor(hdc);

		SetTextColor(hdc, color);
		TextOutW(hdc, destX, destY, printString, length);
		SetTextAlign(hdc, textAlign);

}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth,
	LPCWSTR* printStringArr, int length, COLORREF color)
{
	// 터짐방지
	int arraySize = sizeof(printStringArr) / sizeof(*printStringArr);
} // <-정의는 cpp에서 수정할 것 
