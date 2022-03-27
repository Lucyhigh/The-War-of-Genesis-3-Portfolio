#pragma once
#include <sdkddkver.h>

// ���� ������ �ʴ� ������ Windows ������� ����
#define WIN32_LEAN_AND_MEAN 

// ����ȯ ������ �ս� 
#pragma warning(disable:4244)

//! Windows ��� ����
#include <Windows.h>

// ������ �ܼ�â
//!���̺귯��
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib,"Winmm.lib")
//#pragma comment(lib,"lib/FMOD/fmodex_vc.lib")
#pragma comment (lib, "Jsoncpp/lib/json_vc71_libmtd.lib")
//#pragma comment (lib, "lib/FMOD/fmodex64_vc.lib")
//!�ܺ� ��� ����
//#include "inc/FMOD/fmod.hpp"
#include "Jsoncpp/inc/json.h"

// ���� ����带 ����ϱ� ���� ���̺귯�� �߰� 
#pragma comment (lib,"msimg32.lib")
//
//! C ��Ÿ�� ��� ����
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>

// ������ ���� ��� ���̺귯�� 
// PlaySound()�� ����ϱ� ���� 
#include <mmsystem.h>

// Media Control Interface(��ġ������) API 
// mciSendString()�� ����ϱ� ���� 
#include <mciapi.h>

//! C++ ��Ÿ�� ��� ����
#include <iostream>
#include <random>
#include <bitset>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>
// bind �Լ� ��� �����ִ�
#include <functional>
#include <fstream>
#include <queue>
using namespace std;
#include <bitset>

//===================================
// # ���� ���� ��������� �̰��� �߰� #
//===================================
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "TempSoundManager.h"
#include "Utils.h"
#include "TimeManager.h"
#include "TextDataManager.h"
#include "SceneManager.h"
//#include "SoundManager.h"
#include "JsonSaveLoader.h"


using namespace MY_UTIL;



//========================
// # �̱����� �̰��� �߰� #
//========================
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define TEMPSOUNDMANAGER TempSoundManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define TEXTDATAMANAGER TextDataManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
//#define SOUNDMANAGER SoundManager::getSingleton()
#define JSONDATAMANAGER JsonSaveLoader::getSingleton()
//============================
// # ��ũ�� # (������â �ʱ�ȭ)
//============================
#define WINNAME		 (LPTSTR)(TEXT("WindowsAPI"))

//#define FULLSCREEN

#ifdef FULLSCREEN
#define WINSTART_X	 1920 // ����Ϳ� ���� �ٸ� 
#define WINSTART_Y	 1080
// GetSystemMetrics ���ڷ� ���޵Ǵ� �ý��� ���� ���� ��Ȳ
// ��SM_CXSCREEN / SM_CYSCREEN :  ���� ȭ�� �ػ� X, Y�� ��ȯ 
#define WINSIZE_X	 GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y	 GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE	 WS_POPUPWINDOW | WS_MAXWIZE
//1200*800
#else
#define WINSTART_X	 200
#define WINSTART_Y	 0
#define WINSIZE_X	 960
#define WINSIZE_Y	 720
#define WINSTYLE	 WS_CAPTION  | WS_SYSMENU   // WS_CAPTION  | WS_SYSMENU |WS_POPUP | WS_BORDER | WS_SYSMENU 
//=========================�̰� �ٲ��ָ� ��ȭ���� �����÷��̾�ó��
#endif 


//============================
// # ��ũ�� # (��� �� ȿ��)
//============================
#define CENTER_X WINSIZE_X/2
#define CENTER_Y WINSIZE_Y/2
#define MGT true,RGB(255,0,255)

//===============================================
// # ��ũ�� �Լ� # (Ŭ�������� �����Ҵ�� �κ� ����)
//===============================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

//=============
// # �������� #
//=============
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;


////����Ŭ���� 
//#include "TurnSystem.h"
//#include "Player.h"
//Player _player;
//TurnSystem _turnSystem;
