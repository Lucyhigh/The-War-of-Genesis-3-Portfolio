#pragma once
#include <sdkddkver.h>

#define WIN32_LEAN_AND_MEAN 

#pragma warning(disable:4244)

#include <Windows.h>

#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib,"lib/FMOD/fmodex_vc.lib")
#pragma comment (lib, "Jsoncpp/lib/json_vc71_libmtd.lib")

#include "inc/FMOD/fmod.hpp"
#include "Jsoncpp/inc/json.h"

#pragma comment (lib,"msimg32.lib")

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <mmsystem.h>
#include <mciapi.h>

//! C++ 
#include <iostream>
#include <random>
#include <bitset>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>
// bind 
#include <functional>
#include <fstream>
#include <queue>
using namespace std;
#include <bitset>
#include <list>
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
#include "AnimationManager.h"
#include "SoundManager.h"
#include "JsonSaveLoader.h"

using namespace MY_UTIL;

//========================
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define TEMPSOUNDMANAGER TempSoundManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define TEXTDATAMANAGER TextDataManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define ANIMATIONMANAGER AnimationManager::getSingleton()
#define SOUNDMANAGER SoundManager::getSingleton()
#define JSONDATAMANAGER JsonSaveLoader::getSingleton()
//============================

#define WINNAME		 (LPTSTR)(TEXT("WindowsAPI"))

#define WINSTART_X	 200
#define WINSTART_Y	 0
#define WINSIZE_X	 960
#define WINSIZE_Y	 720
#define WINSTYLE	 WS_CAPTION  | WS_SYSMENU   // WS_CAPTION  | WS_SYSMENU |WS_POPUP | WS_BORDER | WS_SYSMENU 

#define CENTER_X WINSIZE_X/2
#define CENTER_Y WINSIZE_Y/2
#define MGT true,RGB(255,0,255)

#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

////델리게이트 필요 콜백언제시킬지 정함
//#define SAFE_RELEASE(p)	 \
//{                        \
////언제호출될지정하기
//}
//


extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;


//#include "TurnSystem.h"
//#include "Player.h"
//Player _player;
//TurnSystem _turnSystem;
