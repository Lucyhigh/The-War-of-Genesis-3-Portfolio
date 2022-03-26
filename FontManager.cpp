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
		����ũ��, ������, ���� ��ü ����, ���� ����, ���� ����,
		����(true, false), ����(true, false), ��Ҽ�(true, false),
		���ڼ���, ��� ��Ȯ��, Ŭ���� ��Ȯ��, ����� ��, �ڰ�, ��Ʈ
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
			����ũ��, ������, ���� ��ü ����, ���� ����, ���� ����,
			����(true, false), ����(true, false), ��Ҽ�(true, false),
			���ڼ���, ��� ��Ȯ��, Ŭ���� ��Ȯ��, ����� ��, �ڰ�, ��Ʈ
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
	// ��������
	int arraySize = sizeof(printStringArr) / sizeof(*printStringArr);
} // <-���Ǵ� cpp���� ������ �� 
