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

	//������ ����� ������ش�
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//ȸ�� ����� ������ش�. 
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//�̵� ����� ������ش�.
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
	//���� �������ε��� 
	int frame = frameY * mMaxFrameX + frameX;
	Vector2 size = mSize;

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(position.X - size.X / 2.f, position.Y - size.Y / 2.f);

	//�׸� ���� ���� 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, size.X, size.Y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x, (float)mFrameInfo[frame].y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));
	//������� ����
	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//������ ��û
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

	//���� ������
	Vector2 size = mSize;
	//�׸� ���� ���� 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, size.X, size.Y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[0].x, 
		((float)mFrameInfo[0].y)+ ((float)tempY)*ratioY/2.f, //������(
		(float)(mFrameInfo[0].x + mFrameInfo[0].width), //����
		(float)(mFrameInfo[0].y + mFrameInfo[0].height)); 
	//������ ����� ������ش�
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//ȸ�� ����� ������ش�. 
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//�̵� ����� ������ش�.
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(x, y);

	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//������ ��û
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(
		mBitmap,	//�츮�� ������ �۾��� ������ �̹���
		dxArea,		//������ �۾��� ������ ȭ���� ������ ���� NULL ���� �� ����Ÿ���� ������ �׸��� ��
		mAlpha,		//���� ��
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,	//�̹����� ȸ���� �ϰų� ũ�Ⱑ �����Ǿ��� ��,
															//��� �ε巴�� ���� ���ΰ��� ���� �ɼ��� �����ϴ� �κ��Դϴ�.
															//��, ����(interpolation) �ɼ�
		&dxSrc);	//���� �̹������� ���� ������ �����ְ� ���� �� ������ �Է��ϴ� �ɼ�
					//�ش� �̹��� ������ ����� �������� ������ ����
	ResetRenderOption();
}

void Image::FrameRender(HDC hdc, int x, int y, int frameX, int frameY)
{

	//���� �������ε��� 
	int frame = frameY * mMaxFrameX + frameX;
	Vector2 size =mSize;

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//�̹��� ������?
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(x , y );

	//�׸� ���� ���� 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, size.X, size.Y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x, (float)mFrameInfo[frame].y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));
	//������� ����
	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//������ ��û
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

	//���� ������
	//Vector2 size = mSize * mScale;

	//������ ����� ������ش�
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//ȸ�� ����� ������ش�. 
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//�̵� ����� ������ش�.
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(x, y);

	D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, size.X, size.Y);

	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha);
	ResetRenderOption();
}

void Image::ScaleFrameRender(HDC hdc, int x, int y, int frameX, int frameY, int width, int height)
{
	//���� �������ε��� 
	int frame = frameY * mMaxFrameX + frameX;
	Vector2 size = Vector2(mSize.X * width / this->GetFrameWidth(), mSize.Y * height / this->GetFrameHeight());

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(x, y);

	//�׸� ���� ���� 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, size.X, size.Y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x, (float)mFrameInfo[frame].y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));
	//������� ����
	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//������ ��û
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);

	this->ResetRenderOption();
}

void Image::AlphaScaleRender(HDC hdc, int x, int y, int width, int height, float alpha)
{
	this->SetAlpha(alpha);

	Vector2 size = Vector2(mSize.X * width / this->GetWidth(), mSize.Y * height / this->GetHeight());

	//���� ������
	//Vector2 size = mSize * mScale;

	//������ ����� ������ش�
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//ȸ�� ����� ������ش�. 
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//�̵� ����� ������ش�.
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(x , y );

	D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, size.X, size.Y);

	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha);
	ResetRenderOption();
}

void Image::AlphaScaleFrameRender(HDC hdc, int x, int y, int frameX, int frameY, int width, int height, float alpha)
{
	this->SetAlpha(alpha);
	//���� �������ε��� 
	int frame = frameY * mMaxFrameX + frameX;
	Vector2 size = Vector2(mSize.X * width / this->GetFrameWidth(), mSize.Y * height / this->GetFrameHeight());

	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(x, y);

	//�׸� ���� ���� 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, size.X, size.Y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x, (float)mFrameInfo[frame].y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));
	//������� ����
	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(scaleMatrix * rotateMatrix * translateMatrix);
	//������ ��û
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, &dxSrc);

	this->ResetRenderOption();
}

void Image::ActivitScaleRender(HDC hdc, int x, int y, int width, int height, float angleX, float angleY)
{
	Vector2 size = Vector2(mSize.X * width / this->GetWidth(), mSize.Y * height / this->GetHeight());

	//���� ������
	//Vector2 size = mSize * mScale;

	//������ ����� ������ش�
	D2D1::Matrix3x2F scaleMatrix = D2D1::Matrix3x2F::Scale(mScale, mScale, 
		//�߽� ��ǥ
		D2D1::Point2F(size.X / 2.f, size.Y));
	//ȸ�� ����� ������ش�. 
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, D2D1::Point2F(size.X / 2.f, size.Y / 2.f));
	//�̵� ����� ������ش�.
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(x, y);

	D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, size.X, size.Y);
	
	D2D_MATRIX_3X2_F skewMatrix = D2D1::Matrix3x2F::Skew(angleX, angleY, 
		//ȸ������->���ϴ��̶� �ǹ�
		D2D1::Point2F(0.f,size.Y)); // centre being the origin of the screen
	
	//������� �簢��
	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(skewMatrix * scaleMatrix * rotateMatrix * translateMatrix);

	//�׷��ִ� ��
	D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(mBitmap, dxArea, mAlpha);

	//����
	ResetRenderOption();
}

void Image::ShadowRender(HDC hdc, int x, int y, int frameX, int frameY, int width, int height, float alpha, float time)
{
	//ȸ���ϴ� ��� 
	//mAngle = 360.f / (60.f * 24.f) *time;
	
	this->SetAlpha(alpha);
	//���� �������ε��� 
	int frame = frameY * mMaxFrameX + frameX;
	//�ð��� ���� ���� ���� : 0~1.f <-  1.f~0~1.f�� ����� �ʹ�.
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
		//������ �߽�
		D2D1::Point2F(size.X / 2.f, size.Y/2.f));
	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(mAngle, 
		//�ޱ� ������ ȸ�� �߽���
		D2D1::Point2F(size.X / 2.f, size.Y));
	D2D1::Matrix3x2F translateMatrix = D2D1::Matrix3x2F::Translation(x, y); //���� ���
	
	D2D_MATRIX_3X2_F skewMatrix = D2D1::Matrix3x2F::Skew(
		//ȸ���ޱ�0~180.f : ������ 0~30, 150~180
		-40.f+80.f* heightSize, 0,
		//ȸ������->���ϴ��̶� �ǹ�
		D2D1::Point2F(0.f, size.Y));


	//�׸� ���� ���� 
	D2D1_RECT_F dxArea = D2D1::RectF(0.0f, 0.0f, size.X, size.Y);
	D2D1_RECT_F dxSrc = D2D1::RectF((float)mFrameInfo[frame].x, (float)mFrameInfo[frame].y,
		(float)(mFrameInfo[frame].x + mFrameInfo[frame].width),
		(float)(mFrameInfo[frame].y + mFrameInfo[frame].height));
	//������� ����
	D2DRenderer::GetInstance()->GetRenderTarget()->SetTransform(skewMatrix * scaleMatrix * rotateMatrix * translateMatrix);

	//�׷�
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

	//������ ��û
	//D2DRenderer::GetInstance()->GetRenderTarget()->DrawBitmap(
	//	mBitmap,	//�츮�� ������ �۾��� ������ �̹���
	//	dxArea,		//������ �۾��� ������ ȭ���� ������ ���� NULL ���� �� ����Ÿ���� ������ �׸��� ��
	//	mAlpha,		//���� ��
	//	D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,	//�̹����� ȸ���� �ϰų� ũ�Ⱑ �����Ǿ��� ��,
	//														//��� �ε巴�� ���� ���ΰ��� ���� �ɼ��� �����ϴ� �κ��Դϴ�.
	//														//��, ����(interpolation) �ɼ�
	//	&dxSrc);	//���� �̹������� ���� ������ �����ְ� ���� �� ������ �Է��ϴ� �ɼ�
	//				//�ش� �̹��� ������ ����� �������� ������ ����
				
	//����
	this->ResetRenderOption();
}

/********************************************************************************
## ResetRenderOption ##
�̹��� Ŭ���� ���� ���� �ɼǵ� ���� �ʱ�ȭ
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
//	//�̹� �̹��� ���۰� �ִٸ� ����
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
//	mImageBuffer->hdc = CreateCompatibleDC(hdc);	//�� HDC����
//	mImageBuffer->bitmap = (HBITMAP)CreateCompatibleBitmap(hdc, width, height); //�� ��Ʈ�� ����
//	mImageBuffer->oldBitmap = (HBITMAP)SelectObject(mImageBuffer->hdc, mImageBuffer->bitmap);	//���� ��Ʈ�� ����
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
//hdc : �׸� HDC
//x : �׸� ��ǥX
//y : �׸� ��ǥY
//*/
//void Image::Render(HDC hdc, int x, int y)
//{
//	if (mIsTrans)
//	{
//		GdiTransparentBlt(
//			hdc,					//�׸� ����(HDC)
//			x,						//�׸� ��ǥX
//			y,						//�׸� ��ǥY
//			mImageBuffer->width,	//�׸� ���α���
//			mImageBuffer->height,	//�׸� ���α���
//			mImageBuffer->hdc,		//�׸� HDC
//			0,						//�����ؿ� ���� ������ǥX
//			0,						//�����ؿ� ���� ������ǥY
//			mImageBuffer->width,	//�����ؿ� ���� ���α���
//			mImageBuffer->height,	//�����ؿ� ���� ���α���
//			mTransColor				//Transó���� ����
//		);
//	}
//	else
//	{
//		//HDC�� ���۸� �ٸ� HDC���ۿ� ��� �������ִ� �Լ�
//		BitBlt(hdc, x, y, mImageBuffer->width, mImageBuffer->height, mImageBuffer->hdc, 0, 0, SRCCOPY);
//	}
//}
//
///*
//## Render ##
//hdc : �׸� HDC
//x : �׸� ��ǥ
//y : �׸� ��ǥ
//tempX : ����(�ؽ���)�κ��� �׸� �����ȼ�
//tempY : ����(�ؽ���)�κ��� �׸� �����ȼ�
//tempWidth : ������ tempX�κ��� �׸� �ʺ�
//tempHeight : ������ tempY�κ��� �׸� ����
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
//x : �׸� ��ǥ
//y : �׸� ��ǥ
//frameX : ����� ���� ������ �ε���
//frameY : ����� ���� ������ �ε��� 
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
