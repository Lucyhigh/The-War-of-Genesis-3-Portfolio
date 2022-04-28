#include "Stdafx.h"
#include "Image.h" // 그려주기 위한 셋팅, 추상화만 진행하고 상속을 해줄 예정. 
#include "Animation.h"

// 동적할당을 통해 상속받은 클래스에서 생성자 호출할때 
// 이니셜라이저 초기화를 통해 최우선적으로 초기화를 하라는 의미 . 
Image::Image() : _imageInfo(NULL)
				,_fileName(NULL)
				,_isTrans(FALSE)
				,_transColor(RGB(0,0,0))
				,_blendImage(NULL)
				
{
}

// 이미지 초기화
HRESULT Image::init(int width, int height)
{
	// 포인터를 사용하기때문에 if로 한번 더 확인한다. 
	// 재초기화 방지 -> 이미지 정보에 값이 들어있다면 릴리즈부터 하겠다.
	if (_imageInfo != NULL) this->release();

	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 새로 생성 후 초기화
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);//1
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);//2
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// 파일 이름
	_fileName = NULL;
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	// 리소스를 얻어오는데 실패했으면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	// DC해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const DWORD resID, int width, int height, BOOL isTrans, COLORREF transColor)
{
	// 재초기화 방지 -> 이미지 정보에 값이 들어있다면 릴리즈부터 하겠다.
	if (_imageInfo != NULL) this->release();

	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 새로 생성 후 초기화
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE; //
	_imageInfo->resID = resID; // 사용할 리소스ID
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance,MAKEINTRESOURCE(_imageInfo)); // _imageInfo res에서 변경
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// 파일 이름 - 리소스 사용으로 없음. 
	_fileName = NULL;
	_isTrans = isTrans;
	_transColor = transColor;

	// 리소스를 얻어오는데 실패했으면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	// DC해제
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT Image::init(const char* fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	// 재초기화 방지 -> 이미지 정보에 값이 들어있다면 릴리즈부터 하겠다.
	if (_imageInfo != NULL) this->release();

	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 새로 생성 후 초기화
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; // 파일로드 
	_imageInfo->resID = 0; // 리소스 아이디는 없음
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName,IMAGE_BITMAP,
		width,height,LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// 파일 이름 - 문자/문자열 확인 
	// _fileName = fileName; ->const로 그대로 사용할 수 없기때문에, 아래처럼 기재.

	int len = strlen(fileName);
	_fileName = new CHAR[len + 1]; // 파일 경로 뒤 공백 1칸 실수 방지용
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	// 리소스를 얻어오는데 실패했으면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	// DC해제
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}


// 프레임 이미지 초기화
HRESULT Image::init(const char * fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{

	// 재초기화 방지 -> 이미지 정보에 값이 들어있다면 릴리즈부터 하겠다.
	if (_imageInfo != NULL) this->release();

	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 새로 생성 후 초기화
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; // 파일로드 
	_imageInfo->resID = 0; // 리소스 아이디는 없음
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	// 파일 이름 - 문자/문자열 확인 
	// _fileName = fileName; ->const로 그대로 사용할 수 없기때문에, 아래처럼 기재.

	int len = strlen(fileName);
	_fileName = new CHAR[len + 1]; // 파일 경로 뒤 공백 1칸 실수 방지용
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	// 리소스를 얻어오는데 실패했으면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	// DC해제
	ReleaseDC(_hWnd, hdc);
	return S_OK;
	
}

HRESULT Image::init(const char * fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	// 재초기화 방지 -> 이미지 정보에 값이 들어있다면 릴리즈부터 하겠다.
	if (_imageInfo != NULL) this->release();

	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 새로 생성 후 초기화
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; // 파일로드 
	_imageInfo->resID = 0; // 리소스 아이디는 없음
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX-1;
	_imageInfo->maxFrameY = maxFrameY-1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	// 파일 이름 - 문자/문자열 확인 
	// _fileName = fileName; ->const로 그대로 사용할 수 없기때문에, 아래처럼 기재.

	int len = strlen(fileName);
	_fileName = new CHAR[len + 1]; // 파일 경로 뒤 공백 1칸 실수 방지용
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	// 리소스를 얻어오는데 실패했으면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	// DC해제
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT Image::init(const char * fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	// 재초기화 방지 -> 이미지 정보에 값이 들어있다면 릴리즈부터 하겠다.
	if (_imageInfo != NULL) this->release();

	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 새로 생성 후 초기화
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; // 파일로드 
	_imageInfo->resID = 0; // 리소스 아이디는 없음
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	// 파일 이름 - 문자/문자열 확인 
	// _fileName = fileName; ->const로 그대로 사용할 수 없기때문에, 아래처럼 기재.

	int len = strlen(fileName);
	_fileName = new CHAR[len + 1]; // 파일 경로 뒤 공백 1칸 실수 방지용
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	// 리소스를 얻어오는데 실패했으면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	// DC해제
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

// 알파블렌드 초기화
HRESULT Image::initForAlphaBlend(void)
{

	HDC hdc = GetDC(_hWnd);

	_blendFunc.BlendFlags = 0; // 혼합비율 사용안함
	_blendFunc.AlphaFormat = 0; // 이미지 + 소스 제어 or 이미지 제어 여부
	_blendFunc.BlendOp = AC_SRC_OVER; // 비트맵 이미지 비트 수 24 or 32 사용함
	

	// 이미지 정보 새로 생성 후 초기화
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE; // 파일로드 
	_blendImage->resID = 0; // 리소스 아이디는 없음
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap	(hdc,_imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZE_X;
	_blendImage->height = WINSIZE_Y;

	
	// DC해제
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

void Image::setTransColor(BOOL isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}

void Image::release(void)
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}

	if (_blendImage)
	{
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);
		SAFE_DELETE(_blendImage);
	}
}

void Image::render(HDC hdc)
{
	if (_isTrans)
	{
		GdiTransparentBlt 
		(
			hdc,					
			0, 0,					
			_imageInfo->width,		
			_imageInfo->height,
			_imageInfo->hMemDC,		
			0,0,					
			_imageInfo->width,		
			_imageInfo->height,
			_transColor				
		);
	}
	else 
	{
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void Image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		GdiTransparentBlt
		(
			hdc,					
			destX, destY,			
			_imageInfo->width,		
			_imageInfo->height,
			_imageInfo->hMemDC,		
			0, 0,					
			_imageInfo->width,		
			_imageInfo->height,
			_transColor				
		);
	}

	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void Image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
    if (_isTrans)
    {
        GdiTransparentBlt
        (
            hdc,					
            destX, destY,			
            sourWidth,				
            sourHeight,
            _imageInfo->hMemDC,		
            sourX, sourY,			
            sourWidth,				
            sourHeight,
            _transColor				
        );
    }

    else
    {
        BitBlt(hdc, destX, destY, sourWidth, sourHeight,
            _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
    }
}

void Image::alphaRender(HDC hdc, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();
	
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc, 0, 0, SRCCOPY);
		GdiTransparentBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
		);
		AlphaBlend
		(
		hdc,
			0,0,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC, 
			0,0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc 
		);
	}
	else
	{
		AlphaBlend
		(
			hdc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc 
		);
	}
}

void Image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc, 
			destX, destY, SRCCOPY
		);

		GdiTransparentBlt
		(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
		);
		AlphaBlend
		(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC, 
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc 
		);
	}
	else{
		AlphaBlend
		(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc);
	}
}

void Image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			destX, destY, SRCCOPY
		);

		GdiTransparentBlt
		(
			hdc,
			destX, destY,
			sourWidth,
			sourHeight,
			_imageInfo->hMemDC,
			sourX, sourY,
			sourWidth,
			sourHeight,
			_transColor
		);

		AlphaBlend
		(
			hdc,
			destX, destY,
			sourWidth,
			sourHeight,
			_blendImage->hMemDC, 
			0, 0,
			sourWidth,
			sourHeight,
			_blendFunc
		);
	}
	else {
		AlphaBlend
		(
			hdc,
			destX, destY,
			sourWidth,
			sourHeight,
			_imageInfo->hMemDC,
			0, 0,
			sourWidth,
			sourHeight,
			_blendFunc);
	}
}

void Image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (!_blendImage) this->initForAlphaBlend();
	_blendFunc.SourceConstantAlpha = alpha;
	if (_isTrans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, hdc, destX, destY, SRCCOPY);
		GdiTransparentBlt(
			_blendImage->hMemDC,
			0,0,
			_imageInfo->frameWidth,  
			_imageInfo->frameHeight, 
			_imageInfo->hMemDC,      
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,  
			_imageInfo->frameWidth,   
			_imageInfo->frameHeight,  
			_transColor);         

		GdiAlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else
	{
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
}

void Image::frameRender(HDC hdc, int destX, int destY)
{
    if (_isTrans)
    {
        GdiTransparentBlt
        (
            hdc,						
            destX, destY,				
            _imageInfo->frameWidth,		
            _imageInfo->frameHeight,
            _imageInfo->hMemDC,			
            _imageInfo->currentFrameX * _imageInfo->frameWidth,	
            _imageInfo->currentFrameY * _imageInfo->frameHeight,
            _imageInfo->frameWidth,		
            _imageInfo->frameHeight,
            _transColor					
        );
    }

    else
    {
        BitBlt(hdc, destX, destY,
            _imageInfo->frameWidth,
            _imageInfo->frameHeight,
            _imageInfo->hMemDC,
            _imageInfo->currentFrameX * _imageInfo->frameWidth,
            _imageInfo->currentFrameY * _imageInfo->frameHeight,
            SRCCOPY);
    }
}

void Image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans)
	{
		GdiTransparentBlt
		(
			hdc,					
			destX, destY,			
			_imageInfo->frameWidth,	
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,		
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,				
			_imageInfo->frameHeight,
			_transColor				
		);
	}

	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void Image::loopRender(HDC hdc, const LPRECT dramArea, int offsetX, int offsetY)
{
	if (offsetX < 0)offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0)offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	RECT rcSour;
	int sourWidth;
	int sourHeight;
	RECT rcDest;

	int dramAreaX = dramArea->left;
	int dramAreaY = dramArea->top;
	int dramAreaW = dramArea->right - dramArea->left;
	int dramAreaH = dramArea->bottom - dramArea->top;

	for (int y = 0; y < dramAreaH; y += sourHeight)
	{
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		if (y + sourHeight > dramAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - dramAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		rcDest.top = y + dramAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < dramAreaW; x += sourWidth)
		{
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > dramAreaW)
			{
				rcSour.right -= (x + sourWidth) - dramAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + dramAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top,
				sourWidth, sourHeight);
		}
	}
}

void Image::aniRender(HDC hdc, int destX, int destY, Animation* ani)
{
    render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y,
                              ani->getFrameWidth(), ani->getFrameHeight());
}

void Image::aniAlphaRender(HDC hdc, int destX, int destY,BYTE alpha, Animation* ani)
{
	alphaRender(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y,
								   ani->getFrameWidth(), ani->getFrameHeight(),alpha);
}
