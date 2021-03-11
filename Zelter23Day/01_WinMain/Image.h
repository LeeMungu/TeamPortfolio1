#pragma once
class Image
{
public:
	struct TagLoadedImageInfo
	{
		wstring key;
		wstring directory;

		TagLoadedImageInfo() {}
		TagLoadedImageInfo(const wstring& key, const wstring& directory)
			:key(key), directory(directory) {}
	};
	struct FrameRect
	{
		float x;
		float y;
		float width;
		float height;
	};
private:
	ID2D1Bitmap* mBitmap;		//HBitmap같은 비트맵 파일 불러온 녀석
	float				mAlpha;			//그릴 알파값

	Vector2				mSize;			//그릴 사이즈 
	float				mScale;			//그릴 스케일
	float				mAngle;			//그릴 각도

	TagLoadedImageInfo	mLoadInfo;		//이미지 불러오는 정보

	vector<Image::FrameRect>	mFrameInfo;	//프레임정보
	int							mMaxFrameX;	//가로프레임 수
	int							mMaxFrameY;	//세로 프레임 수 
private:
	friend class ImageManager;
	//기본 생성자 못쓰게 없애버리는 방법!!!!
	Image() = delete;
	Image(ID2D1Bitmap* const bitmap, const TagLoadedImageInfo& loadinfo);
	Image(ID2D1Bitmap* const bitmap, const TagLoadedImageInfo& loadinfo, const int maxFrameX, const int maxFrameY);
	virtual ~Image();
	Image operator = (const Image& image) {}
public:
	void Render(const Vector2& position);
	void FrameRender(const Vector2& position, const int frameX, const int frameY);

	//기본렌더링
	void Render(HDC hdc, int x, int y);
	//요거 영역 지정해서 그리는거
	void Render(HDC hdc, int x, int y, int tempX, int tempY, int tempWidth, int tempHeight);
	//프레임렌더
	void FrameRender(HDC hdc, int x, int y, int frameX, int frameY);
	//알파값주는 렌더링
	void AlphaRender(HDC hdc,int x, int y, float alpha);
	//알파값주는 프레임 렌더링
	void AlphaFrameRender(HDC hdc, int x, int y, int frameX, int frameY, float alpha);
	//크기 조정해주는 렌더링
	void ScaleRender(HDC hdc, int x, int y, int width, int height);
	//크기 조정해주는 프레임 렌더링
	void ScaleFrameRender(HDC hdc, int x, int y, int frameX, int frameY, int width, int height);
	//알파값에 크기 조정하는 렌더링
	void AlphaScaleRender(HDC hdc, int x, int y, int width, int height, float alpha);
	//알파값 + 프레임렌더링 + 크기 조정
	void AlphaScaleFrameRender(HDC hdc, int x, int y, int frameX, int frameY, int width, int height, float alpha);

	void ResetRenderOption();

	void SetSize(const Vector2& vec) { this->mSize = vec; }
	void SetAlpha(const float alpha) { this->mAlpha = alpha; }
	void SetScale(const float scale) { this->mScale = scale; }
	void SetAngle(const float angle) { this->mAngle = angle; }

	const int GetMaxFrameX()const { return mMaxFrameX; }
	const int GetMaxFrameY()const { return mMaxFrameY; }
	const wstring GetKey() const { return this->mLoadInfo.key; }
	const UINT GetWidth() const { return mBitmap->GetPixelSize().width; }
	const UINT GetHeight()const { return mBitmap->GetPixelSize().height; }
	const Vector2 GetSize()const { return this->mSize; }
	Vector2 GetFrameSize(const int& frame = 0) const { return Vector2(mFrameInfo[frame].width, mFrameInfo[frame].height); }
	float GetFrameWidth()const { return mFrameInfo[0].width; }
	float GetFrameHeight()const { return mFrameInfo[0].height; }
	const TagLoadedImageInfo& GetLoadInfo() const { return mLoadInfo; }

	inline ID2D1Bitmap* GetBitmap()const { return mBitmap; }
};



//#pragma once
//class Image
//{
//private:
//	enum class LoadType : int
//	{
//		Resource,
//		File, 
//		Empty,
//		End
//	};
//
//	struct ImageBuffer
//	{
//		ULONG registerID;
//		HDC hdc; 
//		HBITMAP bitmap;
//		HBITMAP oldBitmap;
//		int width; 
//		int height;
//		int frameX;
//		int frameY;
//		int frameWidth;
//		int frameHeight;
//		LoadType loadType;
//
//		ImageBuffer() :registerID(0), hdc(nullptr), bitmap(nullptr), oldBitmap(nullptr), width(0), height(0),
//			frameX(0), frameY(0), frameWidth(0), frameHeight(0), loadType(LoadType::End) {}
//	};
//private:
//	ImageBuffer* mImageBuffer;
//	wstring mFileName;
//	wstring mKeyName;
//	bool mIsTrans;
//	COLORREF mTransColor;
//
//	ImageBuffer* mBlendImageBuffer;
//	BLENDFUNCTION* mBlendFunc;
//public:
//	Image();
//	~Image();
//
//	void ReleaseBuffer();
//public:// 생성관련 ~
//	bool CreateEmpty(int width, int height);
//	bool LoadFromFile(wstring keyName,wstring fileName, int width, int height, bool isTrans, COLORREF transColor = RGB(255,0,255));
//	bool LoadFromFile(wstring keyName,wstring fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor = RGB(255,0,255));
//public://렌더링 관련 ~
//	//기본렌더링
//	void Render(HDC hdc, int x, int y);
//	//요거 영역 지정해서 그리는거
//	void Render(HDC hdc, int x, int y, int tempX, int tempY, int tempWidth, int tempHeight);
//	//프레임렌더
//	void FrameRender(HDC hdc, int x, int y, int frameX, int frameY);
//	//알파값주는 렌더링
//	void AlphaRender(HDC hdc,int x, int y, float alpha);
//	//알파값주는 프레임 렌더링
//	void AlphaFrameRender(HDC hdc, int x, int y, int frameX, int frameY, float alpha);
//	//크기 조정해주는 렌더링
//	void ScaleRender(HDC hdc, int x, int y, int width, int height);
//	//크기 조정해주는 프레임 렌더링
//	void ScaleFrameRender(HDC hdc, int x, int y, int frameX, int frameY, int width, int height);
//	//알파값에 크기 조정하는 렌더링
//	void AlphaScaleRender(HDC hdc, int x, int y, int width, int height, float alpha);
//	//알파값 + 프레임렌더링 + 크기 조정
//	void AlphaScaleFrameRender(HDC hdc, int x, int y, int frameX, int frameY, int width, int height, float alpha);
//public:// 접근 관련~
//	inline HDC GetHDC()const { return mImageBuffer->hdc; }
//	inline int GetFrameX()const { return mImageBuffer->frameX; }
//	inline int GetFrameY()const { return mImageBuffer->frameY; }
//	inline int GetFrameWidth()const { return mImageBuffer->frameWidth; }
//	inline int GetFrameHeight()const { return mImageBuffer->frameHeight; }
//	inline int GetWidth()const { return mImageBuffer->width; }
//	inline int GetHeight()const { return mImageBuffer->height; }
//	inline wstring GetKeyName()const { return mKeyName; }
//};
//
