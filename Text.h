#pragma once

struct tagTextWithSound
{
    LPCWSTR name;
    string soundVec;
    LPCWSTR script;
};

struct tagTextWithImage
{
	LPCWSTR name;
	vector<string> ImageVec;
	LPCWSTR script;
};