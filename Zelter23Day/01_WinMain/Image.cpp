#include "pch.h"
#include "Image.h"

Image::Image(ID2D1Bitmap* const bitmap, const TagLoadedImageInfo& loadinfo)
	:mBitmap(bitmap), mLoadInfo(loadinfo), mScale(1.f), mAlpha(1.f), mAngle(0.f), mMaxFrameX(1), mMaxFrameY(1)
{
	this->mSize.X = (float)this->mBitmap->GetPixelSize().width;
	this->mSize.Y = (float)this->mBitmap->GetPixelSize().height;

	FrameRect rc;
	rc.x = 0;
	rc.y = 0;
	rc.width = mSize.X;
	rc.height = mSize.Y;
	this->mFrameInfo.push_back(rc);
	this->ResetRenderOption();
}

Image::Image(ID2D1Bitmap* const bitmap, const TagLoadedImageInfo& loadinfo, const int maxFrameX, const int maxFrameY)
	:mBitmap(bitmap), mLoadInfo(loadinfo), mMaxFrameX(maxFrameX), mMaxFrameY(maxFrameY), mScale(1.f), mAlpha(1.f), mAngle(0.f)
{
	this->mSize.X = (float)mBitmap->GetPixelSize().width;
	this->mSize.Y = (float)mBitmap->GetPixelSize().height;

	float frameX = mSize.X / (float)this->mMaxFrameX;
	float frameY = mSize.Y / (float)this->mMaxFrameY;

	FrameRect rc;
	for (int j = 0; j < maxFrameY; ++j)
	{
		for (int i = 0; i < maxFrameX; ++i)
		{
			rc.x = (float)i * (frameX);
			rc.y = (float)j * (frameY);
			rc.width = frameX;
			rc.height = frameY;
			this->mFrameInfo.push_back(rc);
		}
	}

	this->ResetRenderOption();
}

Image::~Image()
{
	mBitmap->Release();
}
/********************************************************************************
## PerfeactRender ##
*********************************************************************************/
void Image::Render(const Vector2& position)
{
	//testing
	//Vector2 size = mSize * mScale;
	Vector2 size = mSize;

	//스케일 행렬을 만들어준다
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//회전 행렬을 만들어준다. 
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//이동 행렬을 만들어준다.
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(position.X - size.X / 2.f, position.Y - size.Y / 2.f);

	D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, size.X, size.Y);

	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha);
	ResetRenderOption();
}

/********************************************************************************
## PerfeactFrameRender ##
*********************************************************************************/
void Image::FrameRender(const Vector2& position, const int frameX, const int frameY)
{
	//현재 프레임인덱스 
	int frame = frameY * mMaxFrameX + frameX;
	Vector2 size = mSize;

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(position.X - size.X / 2.f, position.Y - size.Y / 2.f);

	//그릴 영역 세팅 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, size.X, size.Y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x, (float)mFrameInfo[frame].y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));
	//최종행렬 세팅
	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//렌더링 요청
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);

	this->ResetRenderOption();
}

void Image::Render(HDC hdc, int x, int y)
{
	this->Render(Vector2((int)(x + this->GetWidth()/2), (int)(y + this->GetHeight()/2)));
}

void Image::Render(HDC hdc, int x, int y, int tempX, int tempY, int tempWidth, int tempHeight)
{
	//float ratioX = ((float)tempWidth) / mSize.X;
	float ratioY = ((float)mFrameInfo[0].height)/((float)tempHeight);
	mSize.X = (float)tempWidth;
	mSize.Y = (float)tempHeight;

	//원래 사이즈
	Vector2 size = mSize;
	//그릴 영역 세팅 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, size.X, size.Y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[0].x, 
		((float)mFrameInfo[0].y)+ ((float)tempY)*ratioY/2.f, //시작점(
		(float)(mFrameInfo[0].x + mFrameInfo[0].width), //뒷점
		(float)(mFrameInfo[0].y + mFrameInfo[0].height)); 
	//스케일 행렬을 만들어준다
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//회전 행렬을 만들어준다. 
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//이동 행렬을 만들어준다.
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(x, y);

	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//렌더링 요청
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(
		mBitmap,	//우리가 렌더링 작업을 수행할 이미지
		dxArea,		//렌더링 작업을 수행할 화면의 영역을 설정 NULL 설정 시 렌더타겟의 원점에 그리게 됨
		mAlpha,		//알파 값
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,	//이미지가 회전을 하거나 크기가 조정되었을 때,
															//어떻게 부드럽게 보일 것인가에 대한 옵션을 설정하는 부분입니다.
															//즉, 보간(interpolation) 옵션
		&dxSrc);	//원본 이미지에서 일정 영역을 보여주고 싶을 때 영역을 입력하는 옵션
					//해당 이미지 파일의 사이즈를 기준으로 영역을 설정
	ResetRenderOption();
}

void Image::FrameRender(HDC hdc, int x, int y, int frameX, int frameY)
{

	//현재 프레임인덱스 
	int frame = frameY * mMaxFrameX + frameX;
	Vector2 size =mSize;

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//이미지 시작점?
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(x , y );

	//그릴 영역 세팅 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, size.X, size.Y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x, (float)mFrameInfo[frame].y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));
	//최종행렬 세팅
	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//렌더링 요청
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);
	
	this->ResetRenderOption();
}

void Image::AlphaRender(HDC hdc, int x, int y, float alpha)
{
	this->SetAlpha(alpha);
	this->Render(Vector2((int)(x + this->GetWidth() / 2), (int)(y + this->GetHeight() / 2)));
}

void Image::AlphaFrameRender(HDC hdc, int x, int y, int frameX, int frameY, float alpha)
{
	this->SetAlpha(alpha);
	this->FrameRender(Vector2((int)(x + this->GetFrameWidth() / 2), (int)(y + this->GetFrameHeight() / 2)), frameX, frameY);
}

void Image::ScaleRender(HDC hdc, int x, int y, int width, int height)
{
	Vector2 size = Vector2(mSize.X * width/this->GetWidth(), mSize.Y * height/this->GetHeight());

	//원래 사이즈
	//Vector2 size = mSize * mScale;

	//스케일 행렬을 만들어준다
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//회전 행렬을 만들어준다. 
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//이동 행렬을 만들어준다.
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(x, y);

	D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, size.X, size.Y);

	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha);
	ResetRenderOption();
}

void Image::ScaleFrameRender(HDC hdc, int x, int y, int frameX, int frameY, int width, int height)
{
	//현재 프레임인덱스 
	int frame = frameY * mMaxFrameX + frameX;
	Vector2 size = Vector2(mSize.X * width / this->GetFrameWidth(), mSize.Y * height / this->GetFrameHeight());

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(x, y);

	//그릴 영역 세팅 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, size.X, size.Y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x, (float)mFrameInfo[frame].y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));
	//최종행렬 세팅
	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//렌더링 요청
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);

	this->ResetRenderOption();
}

void Image::AlphaScaleRender(HDC hdc, int x, int y, int width, int height, float alpha)
{
	this->SetAlpha(alpha);

	Vector2 size = Vector2(mSize.X * width / this->GetWidth(), mSize.Y * height / this->GetHeight());

	//원래 사이즈
	//Vector2 size = mSize * mScale;

	//스케일 행렬을 만들어준다
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//회전 행렬을 만들어준다. 
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//이동 행렬을 만들어준다.
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(x , y );

	D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, size.X, size.Y);

	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha);
	ResetRenderOption();
}

void Image::AlphaScaleFrameRender(HDC hdc, int x, int y, int frameX, int frameY, int width, int height, float alpha)
{
	this->SetAlpha(alpha);
	//현재 프레임인덱스 
	int frame = frameY * mMaxFrameX + frameX;
	Vector2 size = Vector2(mSize.X * width / this->GetFrameWidth(), mSize.Y * height / this->GetFrameHeight());

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(x, y);

	//그릴 영역 세팅 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, size.X, size.Y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x, (float)mFrameInfo[frame].y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));
	//최종행렬 세팅
	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//렌더링 요청
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);

	this->ResetRenderOption();
}

void Image::ActivitScaleRender(HDC hdc, int x, int y, int width, int height, float angleX, float angleY)
{
	Vector2 size = Vector2(mSize.X * width / this->GetWidth(), mSize.Y * height / this->GetHeight());

	//원래 사이즈
	//Vector2 size = mSize * mScale;

	//스케일 행렬을 만들어준다
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, 
		//중심 좌표
		D2D1::Point2F(size.X / 2.f, size.Y));
	//회전 행렬을 만들어준다. 
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//이동 행렬을 만들어준다.
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(x, y);

	D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, size.X, size.Y);
	
	D2D_MATRIX_3X2_F skewMatrix = D2D1::Matrix3x2F::Skew(angleX, angleY, 
		//회전기준->좌하단이란 의미
		D2D1::Point2F(0.f,size.Y)); // centre being the origin of the screen
	
	//만들어진 사각형
	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(skewMatrix * scaleMatrix * rotateMatrix * translateMatrix);

	//그려주는 애
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha);

	//리셋
	ResetRenderOption();
}

void Image::ShadowRender(HDC hdc, int x, int y, int frameX, int frameY, int width, int height, float alpha, float time)
{
	//회전하는 경우 
	//mAngle = 360.f / (60.f * 24.f) *time;
	
	this->SetAlpha(alpha);
	//현재 프레임인덱스 
	int frame = frameY * mMaxFrameX + frameX;
	//시간에 따른 길이 조정 : 0~1.f <-  1.f~0~1.f로 만들고 싶다.
	float heightSize = ((float)((((int)time) % (60 * 24))*100) / (60 * 24))/100.f;
	Vector2 size = Vector2(mSize.X * width / this->GetFrameWidth(),
		mSize.Y * height / this->GetFrameHeight());// *heightSize);
	

	//
	//ID2D1RenderTarget* renderTarget = D2DRenderer::GetInstance()->GetRenderTarget();
	//ID2D1SolidColorBrush* brush;
	//D2D1_COLOR_F color;
	////r,g,b,a
	//color = { 0.0f,0.0f,0.0f,1.0f };
	//renderTarget->CreateSolidColorBrush(color, &brush);
	//

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, 
		//사이즈 중심
		D2D1::Point2F(size.X / 2.f, size.Y/2.f));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, 
		//앵글 돌리는 회전 중심점
		D2D1::Point2F(size.X / 2.f, size.Y));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(x, y); //중점 잡기
	
	D2D_MATRIX_3X2_F skewMatrix = D2D1::Matrix3x2F::Skew(
		//회전앵글0~180.f : 조건은 0~30, 150~180
		-40.f+80.f* heightSize, 0,
		//회전기준->좌하단이란 의미
		D2D1::Point2F(0.f, size.Y));


	//그릴 영역 세팅 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, size.X, size.Y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x, (float)mFrameInfo[frame].y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));
	//최종행렬 세팅
	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(skewMatrix * scaleMatrix * rotateMatrix * translateMatrix);

	//그려
	//{
	ID2D1SolidColorBrush* brush;
	D2D1_COLOR_F color;
	//r,g,b,a
	color = { 0.0f,0.0f,0.0f,alpha };
	D2DRenderer::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(color, &brush);
	D2DRenderer::GetInstance()->GetRenderTarget()
		->FillOpacityMask(mBitmap, brush, D2D1_OPACITY_MASK_CONTENT::D2D1_OPACITY_MASK_CONTENT_GRAPHICS,
			dxArea,
			dxSrc);
		//DrawRectangle(rect, brush);
	brush->Release();
	//}

	//렌더링 요청
	//D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(
	//	mBitmap,	//우리가 렌더링 작업을 수행할 이미지
	//	dxArea,		//렌더링 작업을 수행할 화면의 영역을 설정 NULL 설정 시 렌더타겟의 원점에 그리게 됨
	//	mAlpha,		//알파 값
	//	D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,	//이미지가 회전을 하거나 크기가 조정되었을 때,
	//														//어떻게 부드럽게 보일 것인가에 대한 옵션을 설정하는 부분입니다.
	//														//즉, 보간(interpolation) 옵션
	//	&dxSrc);	//원본 이미지에서 일정 영역을 보여주고 싶을 때 영역을 입력하는 옵션
	//				//해당 이미지 파일의 사이즈를 기준으로 영역을 설정
				
	//리셋
	this->ResetRenderOption();
}

/********************************************************************************
## ResetRenderOption ##
이미지 클래스 렌더 관련 옵션들 전부 초기화
*********************************************************************************/
void Image::ResetRenderOption()
{
	this->mAlpha = 1.0f;
	this->mScale = 1.0f;
	this->mAngle = 0.f;
	if (mFrameInfo.size() <= 1)
	{
		this->mSize.X = (float)mBitmap->GetPixelSize().width;
		this->mSize.Y = (float)mBitmap->GetPixelSize().height;
	}
	else
	{
		this->mSize.X = mFrameInfo[0].width;
		this->mSize.Y = mFrameInfo[0].height;
	}
}


//#include "pch.h"
//#include "Image.h"
//
//#pragma comment(lib, "msimg32.lib")
//
//Image::Image()
//	:mImageBuffer(nullptr),mIsTrans(false),mBlendFunc(nullptr), mBlendImageBuffer(nullptr)
//{
//}
//
//
//Image::~Image()
//{
//	ReleaseBuffer();
//}
//
//void Image::ReleaseBuffer()
//{
//	if (mImageBuffer != nullptr)
//	{
//		SelectObject(mImageBuffer->hdc, mImageBuffer->oldBitmap);
//		DeleteObject(mImageBuffer->bitmap);
//		DeleteDC(mImageBuffer->hdc);
//
//		SelectObject(mBlendImageBuffer->hdc, mBlendImageBuffer->oldBitmap);
//		DeleteObject(mBlendImageBuffer->bitmap);
//		DeleteDC(mBlendImageBuffer->hdc);
//
//		SafeDelete(mImageBuffer);
//		SafeDelete(mBlendImageBuffer);
//	}
//}
//
//bool Image::CreateEmpty(int width, int height)
//{
//	//이미 이미지 버퍼가 있다면 삭제
//	if (mImageBuffer != nullptr)
//	{
//		ReleaseBuffer();
//	}
//
//	HDC hdc = GetDC(_hWnd);
//
//	mImageBuffer = new ImageBuffer();
//	mImageBuffer->loadType = LoadType::Empty;
//	mImageBuffer->registerID = 0;
//	mImageBuffer->hdc = CreateCompatibleDC(hdc);	//빈 HDC생성
//	mImageBuffer->bitmap = (HBITMAP)CreateCompatibleBitmap(hdc, width, height); //빈 비트맵 생성
//	mImageBuffer->oldBitmap = (HBITMAP)SelectObject(mImageBuffer->hdc, mImageBuffer->bitmap);	//이전 비트맵 저장
//	mImageBuffer->width = width;
//	mImageBuffer->height = height;
//
//	mBlendFunc = new BLENDFUNCTION();
//	mBlendFunc->BlendFlags = 0;
//	mBlendFunc->AlphaFormat = 0;
//	mBlendFunc->BlendOp = AC_SRC_OVER;
//
//	mBlendImageBuffer = new ImageBuffer();
//	mBlendImageBuffer->loadType = LoadType::Empty;
//	mBlendImageBuffer->registerID = 0;
//	mBlendImageBuffer->hdc = CreateCompatibleDC(hdc);
//	mBlendImageBuffer->bitmap = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
//	mBlendImageBuffer->oldBitmap = (HBITMAP)SelectObject(mBlendImageBuffer->hdc, mBlendImageBuffer->bitmap);
//	mBlendImageBuffer->width = WINSIZEX;
//	mBlendImageBuffer->height = WINSIZEY;
//
//	if (mImageBuffer->bitmap == nullptr)
//	{
//		ReleaseBuffer();
//		return false;
//	}
//
//	ReleaseDC(_hWnd, hdc);
//
//	return true;
//}
//
//bool Image::LoadFromFile(wstring keyName,wstring fileName, int width, int height, bool isTrans, COLORREF transColor)
//{
//	if (fileName.empty() == true)
//	{
//		return false;
//	}
//
//	if (mImageBuffer != nullptr)
//	{
//		ReleaseBuffer();
//	}
//
//	HDC hdc = GetDC(_hWnd);
//
//	mImageBuffer = new ImageBuffer();
//	mImageBuffer->loadType = LoadType::File;
//	mImageBuffer->registerID = 0;
//	mImageBuffer->hdc = CreateCompatibleDC(hdc);
//	mImageBuffer->bitmap = (HBITMAP)LoadImage(_hInstance, fileName.c_str(), IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
//	mImageBuffer->oldBitmap = (HBITMAP)SelectObject(mImageBuffer->hdc, mImageBuffer->bitmap);
//	mImageBuffer->width = width;
//	mImageBuffer->height = height;
//	mImageBuffer->frameWidth = width;
//	mImageBuffer->frameHeight = height;
//
//	mBlendFunc = new BLENDFUNCTION();
//	mBlendFunc->BlendFlags = 0;
//	mBlendFunc->AlphaFormat = 0;
//	mBlendFunc->BlendOp = AC_SRC_OVER;
//
//	mBlendImageBuffer = new ImageBuffer();
//	mBlendImageBuffer->loadType = LoadType::Empty;
//	mBlendImageBuffer->registerID = 0;
//	mBlendImageBuffer->hdc = CreateCompatibleDC(hdc);
//	mBlendImageBuffer->bitmap = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
//	mBlendImageBuffer->oldBitmap = (HBITMAP)SelectObject(mBlendImageBuffer->hdc, mBlendImageBuffer->bitmap);
//	mBlendImageBuffer->width = WINSIZEX;
//	mBlendImageBuffer->height = WINSIZEY;
//
//	mFileName = fileName;
//	mKeyName = keyName;
//
//	mIsTrans = isTrans;
//	mTransColor = transColor;
//
//	if (mImageBuffer->bitmap == nullptr)
//	{
//		ReleaseBuffer();
//
//		return false;
//	}
//
//	ReleaseDC(_hWnd, hdc);
//
//	return true;
//}
//
//bool Image::LoadFromFile(wstring keyName, wstring fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
//{
//	if (fileName.empty() == true)
//	{
//		return false;
//	}
//
//	if (mImageBuffer != nullptr)
//	{
//		ReleaseBuffer();
//	}
//
//	HDC hdc = GetDC(_hWnd);
//
//	mImageBuffer = new ImageBuffer();
//	mImageBuffer->loadType = LoadType::File;
//	mImageBuffer->registerID = 0;
//	mImageBuffer->hdc = CreateCompatibleDC(hdc);
//	mImageBuffer->bitmap = (HBITMAP)LoadImage(_hInstance, fileName.c_str(), IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
//	mImageBuffer->oldBitmap = (HBITMAP)SelectObject(mImageBuffer->hdc, mImageBuffer->bitmap);
//	mImageBuffer->width = width;
//	mImageBuffer->height = height;
//	mImageBuffer->frameX = frameX;
//	mImageBuffer->frameY = frameY;
//	mImageBuffer->frameWidth = width / frameX;
//	mImageBuffer->frameHeight = height / frameY;
//
//	mBlendFunc = new BLENDFUNCTION();
//	mBlendFunc->BlendFlags = 0;
//	mBlendFunc->AlphaFormat = 0;
//	mBlendFunc->BlendOp = AC_SRC_OVER;
//
//	mBlendImageBuffer = new ImageBuffer();
//	mBlendImageBuffer->loadType = LoadType::Empty;
//	mBlendImageBuffer->registerID = 0;
//	mBlendImageBuffer->hdc = CreateCompatibleDC(hdc);
//	mBlendImageBuffer->bitmap = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
//	mBlendImageBuffer->oldBitmap = (HBITMAP)SelectObject(mBlendImageBuffer->hdc, mBlendImageBuffer->bitmap);
//	mBlendImageBuffer->width = WINSIZEX;
//	mBlendImageBuffer->height = WINSIZEY;
//
//	mFileName = fileName;
//	mKeyName = keyName;
//	mIsTrans = isTrans;
//	mTransColor = transColor;
//
//	if (mImageBuffer->bitmap == nullptr)
//	{
//		ReleaseBuffer();
//
//		return false;
//	}
//
//	ReleaseDC(_hWnd, hdc);
//
//	return true;
//}
//
//
///*
//## Render ##
//hdc : 그릴 HDC
//x : 그릴 좌표X
//y : 그릴 좌표Y
//*/
//void Image::Render(HDC hdc, int x, int y)
//{
//	if (mIsTrans)
//	{
//		GdiTransparentBlt(
//			hdc,					//그릴 버퍼(HDC)
//			x,						//그릴 좌표X
//			y,						//그릴 좌표Y
//			mImageBuffer->width,	//그릴 가로길이
//			mImageBuffer->height,	//그릴 세로길이
//			mImageBuffer->hdc,		//그릴 HDC
//			0,						//복사해올 버퍼 시작좌표X
//			0,						//복사해올 버퍼 시작좌표Y
//			mImageBuffer->width,	//복사해올 버퍼 가로길이
//			mImageBuffer->height,	//복사해올 버퍼 세로길이
//			mTransColor				//Trans처리할 색상
//		);
//	}
//	else
//	{
//		//HDC의 버퍼를 다른 HDC버퍼에 고속 복사해주는 함수
//		BitBlt(hdc, x, y, mImageBuffer->width, mImageBuffer->height, mImageBuffer->hdc, 0, 0, SRCCOPY);
//	}
//}
//
///*
//## Render ##
//hdc : 그릴 HDC
//x : 그릴 좌표
//y : 그릴 좌표
//tempX : 버퍼(텍스쳐)로부터 그릴 시작픽셀
//tempY : 버퍼(텍스쳐)로부터 그릴 시작픽셀
//tempWidth : 버퍼의 tempX로부터 그릴 너비
//tempHeight : 버퍼의 tempY로부터 그릴 높이
//*/
//
//void Image::Render(HDC hdc, int x, int y, 
//	int tempX, int tempY, int tempWidth, int tempHeight)
//{
//	if (mIsTrans)
//	{
//		GdiTransparentBlt
//		(
//			hdc,
//			x,
//			y,
//			tempWidth,
//			tempHeight,
//			mImageBuffer->hdc,
//			tempX,
//			tempY,
//			tempWidth,
//			tempHeight,
//			mTransColor
//		);
//	}
//	else
//	{
//		BitBlt
//		(
//			hdc, x, y,
//			tempWidth,
//			tempHeight,
//			mImageBuffer->hdc,
//			tempX,
//			tempY,
//			SRCCOPY
//		);
//	}
//}
//
///*
//## FrameRender ##
//x : 그릴 좌표
//y : 그릴 좌표
//frameX : 출력할 가로 프레임 인덱스
//frameY : 출력할 세로 프레임 인덱스 
//*/
//void Image::FrameRender(HDC hdc, int x, int y, int frameX, int frameY)
//{
//	if (mIsTrans)
//	{
//		GdiTransparentBlt
//		(
//			hdc,
//			x,
//			y,
//			mImageBuffer->frameWidth,
//			mImageBuffer->frameHeight,
//			mImageBuffer->hdc,
//			mImageBuffer->frameWidth * frameX,
//			mImageBuffer->frameHeight * frameY,
//			mImageBuffer->frameWidth,
//			mImageBuffer->frameHeight,
//			mTransColor
//		);
//	}
//	else
//	{
//		BitBlt
//		(
//			hdc,
//			x,
//			y,
//			mImageBuffer->frameWidth,
//			mImageBuffer->frameHeight,
//			mImageBuffer->hdc,
//			mImageBuffer->frameWidth * frameX,
//			mImageBuffer->frameHeight * frameY,
//			SRCCOPY
//		);
//	}
//}
//
//void Image::AlphaRender(HDC hdc,int x, int y, float alpha)
//{
//	mBlendFunc->SourceConstantAlpha = (BYTE)(alpha * 255.f);
//
//	if (mIsTrans)
//	{
//		BitBlt(mBlendImageBuffer->hdc, 0, 0, mImageBuffer->width, mImageBuffer->height,
//			hdc, x,y, SRCCOPY);
//
//		GdiTransparentBlt(mBlendImageBuffer->hdc, 0, 0, mImageBuffer->width, mImageBuffer->height,
//			mImageBuffer->hdc, 0, 0, mImageBuffer->width, mImageBuffer->height, mTransColor);
//
//		AlphaBlend(hdc, x,y, mImageBuffer->width, mImageBuffer->height,
//			mBlendImageBuffer->hdc, 0, 0, mImageBuffer->width, mImageBuffer->height, *mBlendFunc);
//	}
//	else
//	{
//		AlphaBlend(hdc, x, y, mImageBuffer->width, mImageBuffer->height,
//			mImageBuffer->hdc, 0, 0, mImageBuffer->width, mImageBuffer->height, *mBlendFunc);
//	}
//}
//
//void Image::AlphaFrameRender(HDC hdc, int x, int y, int frameX, int frameY, float alpha)
//{
//	mBlendFunc->SourceConstantAlpha = (BYTE)(alpha * 255.f);
//
//	if (mIsTrans)
//	{
//		BitBlt(mBlendImageBuffer->hdc, 0, 0, mImageBuffer->frameWidth, mImageBuffer->frameHeight,
//			hdc, x, y, SRCCOPY);
//
//		GdiTransparentBlt(mBlendImageBuffer->hdc, 0, 0, mImageBuffer->frameWidth, mImageBuffer->frameHeight,
//			mImageBuffer->hdc, mImageBuffer->frameWidth * frameX, mImageBuffer->frameHeight * frameY, 
//			mImageBuffer->frameWidth, mImageBuffer->frameHeight, mTransColor);
//
//		AlphaBlend(hdc, x, y, mImageBuffer->frameWidth, mImageBuffer->frameHeight,
//			mBlendImageBuffer->hdc, 0,0,
//			mImageBuffer->frameWidth, mImageBuffer->frameHeight, *mBlendFunc);
//	}
//	else
//	{
//		AlphaBlend(hdc, x, y, mImageBuffer->frameWidth, mImageBuffer->frameHeight,
//			mImageBuffer->hdc, 0, 0, mImageBuffer->frameWidth, mImageBuffer->frameHeight, *mBlendFunc);
//	}
//}
//
//void Image::ScaleRender(HDC hdc, int x, int y, int width, int height)
//{
//	if (mIsTrans)
//	{
//		GdiTransparentBlt(hdc, x, y, width, height,
//			mImageBuffer->hdc, 0, 0, mImageBuffer->width, mImageBuffer->height,
//			mTransColor);
//	}
//	else
//	{
//		StretchBlt(hdc, x, y, width, height, mImageBuffer->hdc, 0, 0, mImageBuffer->width, mImageBuffer->height,
//			SRCCOPY);
//	}
//}
//
//void Image::ScaleFrameRender(HDC hdc, int x, int y, int frameX, int frameY, int width, int height)
//{
//	if (mIsTrans)
//	{
//		GdiTransparentBlt(hdc, x, y, width, height,
//			mImageBuffer->hdc, mImageBuffer->frameWidth * frameX, mImageBuffer->frameHeight * frameY,
//			mImageBuffer->frameWidth, mImageBuffer->frameHeight, mTransColor);
//	}
//	else
//	{
//		BitBlt(hdc, x, y, width, height, mImageBuffer->hdc, mImageBuffer->frameWidth * frameX,
//			mImageBuffer->frameHeight * frameY, SRCCOPY);
//	}
//}
//
//void Image::AlphaScaleRender(HDC hdc, int x, int y, int width, int height, float alpha)
//{
//	mBlendFunc->SourceConstantAlpha = (BYTE)(alpha * 255.0f);
//
//	if (mIsTrans)
//	{
//		BitBlt(mBlendImageBuffer->hdc, 0, 0,
//			width, height,
//			hdc, x, y, SRCCOPY);
//
//		GdiTransparentBlt(mBlendImageBuffer->hdc, 0, 0, width, height,
//			mImageBuffer->hdc,
//			0, 0,
//			mImageBuffer->width, mImageBuffer->height,
//			mTransColor);
//
//		AlphaBlend(hdc, x, y, width, height,
//			mBlendImageBuffer->hdc,
//			0, 0,
//			width, height,
//			*mBlendFunc);
//	}
//	else
//	{
//		AlphaBlend
//		(
//			hdc, x, y, width, height,
//			mImageBuffer->hdc,
//			0,0,
//			mImageBuffer->width, mImageBuffer->frameHeight,
//			*mBlendFunc
//		);
//	}
//}
//
//void Image::AlphaScaleFrameRender(HDC hdc, int x, int y, int frameX, int frameY, int width, int height, float alpha)
//{
//	mBlendFunc->SourceConstantAlpha = (BYTE)(alpha * 255.0f);
//
//	if (mIsTrans)
//	{
//		BitBlt(mBlendImageBuffer->hdc, 0, 0,
//			width, height,
//			hdc, x, y, SRCCOPY);
//
//		GdiTransparentBlt(mBlendImageBuffer->hdc, 0, 0, width, height,
//			mImageBuffer->hdc,
//			frameX * mImageBuffer->frameWidth, frameY * mImageBuffer->frameHeight,
//			mImageBuffer->frameWidth, mImageBuffer->frameHeight,
//			mTransColor);
//
//		AlphaBlend(hdc, x, y, width, height,
//			mBlendImageBuffer->hdc,
//			0, 0,
//			width, height,
//			*mBlendFunc);
//	}
//	else
//	{
//		AlphaBlend
//		(
//			hdc, x, y, width, height,
//			mImageBuffer->hdc, 
//			mImageBuffer->frameWidth * frameX, mImageBuffer->frameHeight * frameY, 
//			mImageBuffer->frameWidth, mImageBuffer->frameHeight,
//			*mBlendFunc
//		);
//	}
//}
//
//
