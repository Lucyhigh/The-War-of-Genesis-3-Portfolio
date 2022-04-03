#pragma once
struct tagText
{
	LPCWSTR name;
	vector<string> imageVec;
	LPCWSTR script;
};

struct tagBgImage
{
	int _textIndex;
	string _fileName;
};