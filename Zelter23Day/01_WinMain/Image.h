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
	ID2D1Bitmap* mBitmap;		//HBitmap���� ��Ʈ�� ���� �ҷ��� �༮
	float				mAlpha;			//�׸� ���İ�

	Vector2				mSize;			//�׸� ������ 
	float				mScale;			//�׸� ������
	float				mAngle;			//�׸� ����

	TagLoadedImageInfo	mLoadInfo;		//�̹��� �ҷ����� ����

	vector<Image::FrameRect>	mFrameInfo;	//����������
	int							mMaxFrameX;	//���������� ��
	int							mMaxFrameY;	//���� ������ �� 
private:
	friend class ImageManager;
	//�⺻ ������ ������ ���ֹ����� ���!!!!
	Image() = delete;
	Image(ID2D1Bitmap* const bitmap, const TagLoadedImageInfo& loadinfo);
	Image(ID2D1Bitmap* const bitmap, const TagLoadedImageInfo& loadinfo, const int maxFrameX, const int maxFrameY);
	virtual ~Image();
	Image operator = (const Image& image) {}
public:
	void Render(const Vector2& position);
	void FrameRender(const Vector2& position, const int frameX, const int frameY);

	//�⺻������
	void Render(HDC hdc, int x, int y);
	//��� ���� �����ؼ� �׸��°�
	void Render(HDC hdc, int x, int y, int tempX, int tempY, int tempWidth, int tempHeight);
	//�����ӷ���
	void FrameRender(HDC hdc, int x, int y, int frameX, int frameY);
	//���İ��ִ� ������
	void AlphaRender(HDC hdc,int x, int y, float alpha);
	//���İ��ִ� ������ ������
	void AlphaFrameRender(HDC hdc, int x, int y, int frameX, int frameY, float alpha);
	//ũ�� �������ִ� ������
	void ScaleRender(HDC hdc, int x, int y, int width, int height);
	//ũ�� �������ִ� ������ ������
	void ScaleFrameRender(HDC hdc, int x, int y, int frameX, int frameY, int width, int height);
	//���İ��� ũ�� �����ϴ� ������
	void AlphaScaleRender(HDC hdc, int x, int y, int width, int height, float alpha);
	//���İ� + �����ӷ����� + ũ�� ����
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
//public:// �������� ~
//	bool CreateEmpty(int width, int height);
//	bool LoadFromFile(wstring keyName,wstring fileName, int width, int height, bool isTrans, COLORREF transColor = RGB(255,0,255));
//	bool LoadFromFile(wstring keyName,wstring fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor = RGB(255,0,255));
//public://������ ���� ~
//	//�⺻������
//	void Render(HDC hdc, int x, int y);
//	//��� ���� �����ؼ� �׸��°�
//	void Render(HDC hdc, int x, int y, int tempX, int tempY, int tempWidth, int tempHeight);
//	//�����ӷ���
//	void FrameRender(HDC hdc, int x, int y, int frameX, int frameY);
//	//���İ��ִ� ������
//	void AlphaRender(HDC hdc,int x, int y, float alpha);
//	//���İ��ִ� ������ ������
//	void AlphaFrameRender(HDC hdc, int x, int y, int frameX, int frameY, float alpha);
//	//ũ�� �������ִ� ������
//	void ScaleRender(HDC hdc, int x, int y, int width, int height);
//	//ũ�� �������ִ� ������ ������
//	void ScaleFrameRender(HDC hdc, int x, int y, int frameX, int frameY, int width, int height);
//	//���İ��� ũ�� �����ϴ� ������
//	void AlphaScaleRender(HDC hdc, int x, int y, int width, int height, float alpha);
//	//���İ� + �����ӷ����� + ũ�� ����
//	void AlphaScaleFrameRender(HDC hdc, int x, int y, int frameX, int frameY, int width, int height, float alpha);
//public:// ���� ����~
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
