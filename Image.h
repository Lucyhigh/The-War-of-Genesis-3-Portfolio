#pragma once
class Animation;
class Image
{
public:
	// 자주 사용하는 API 자료형
	// DWORD : Unsigened long
	// WORD : Unsigened short
	// BYTE : Unsigend char : 음수없이 256 (char = 128 -> *2)
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0, // 리소스 필터에서 가져오기
		LOAD_FILE, // 디렉토리로 파일읽기
		LOAD_EMPTY, // 빈 비트맵
		LOAD_END // 아무것도
	};

	typedef struct tagImage
	{
		DWORD resID; // 리소스 ID
		HDC hMemDC; // 메모리 DC : 맵 나오면 메모리
		HBITMAP hBit; // 비트맵 가져옴
		HBITMAP hOBit; // 올드 비트맵 : 데이터 병목현상 방지용
		int x;
		int y;
		int width; // 이미지 가로 
		int height; // 이미지 세로 
		int maxFrameX;
		int maxFrameY;
		int currentFrameX;
		int currentFrameY;
		int frameWidth;
		int frameHeight;
		BYTE loadType; // 이미지 로드 타입 정의함

		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit=NULL;
			hOBit = NULL;
			x =0;
			y=0;
			width = 0;
			height = 0;
			maxFrameX=0;
			maxFrameY=0;
			currentFrameX=0;
			currentFrameY=0;
			frameWidth=0;
			frameHeight=0;
			loadType = LOAD_RESOURCE;
		}

	}	IMAGE_INFO, *LPIMAGE_INFO; 

private:
	LPIMAGE_INFO _imageInfo;
	CHAR* _fileName;
	BOOL _isTrans;
	COLORREF _transColor; 
	BLENDFUNCTION _blendFunc;
	LPIMAGE_INFO _blendImage;

public:

	HRESULT init(int width, int height);
	HRESULT init(const DWORD resID, int width, int height, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y,int width, int height, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));

	HRESULT initForAlphaBlend(void);
	void setTransColor(BOOL isTrans, COLORREF transColor);
	void release(void);
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX,int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY,int sourX,int sourY, int sourWidth, int sourHeight, BYTE alpha);
	void alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void loopRender(HDC hdc, const LPRECT dramArea, int offsetX, int offsetY);
    void aniRender(HDC hdc, int destX, int destY, Animation* ani);
	void aniAlphaRender(HDC hdc, int destX, int destY, BYTE alpha, Animation* ani);
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x=x; }
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y=y; }
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }
	inline RECT boundingBox(void)
	{
		RECT rc =
		{
		(int)_imageInfo->x,
		(int)_imageInfo->y,
		(int)_imageInfo->x + _imageInfo->width,
		(int)_imageInfo->y + _imageInfo->height
		};
		return rc;
	}
	inline RECT boundingBoxWithFrame(void)
	{
		RECT rc =
		{
		(int)_imageInfo->x,
		(int)_imageInfo->y,
		(int)_imageInfo->x + _imageInfo->frameWidth,
		(int)_imageInfo->y + _imageInfo->frameHeight
		};
		return rc;
	}
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	
	}
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	Image();
	~Image() {};
};

