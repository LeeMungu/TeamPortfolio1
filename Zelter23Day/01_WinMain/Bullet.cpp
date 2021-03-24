#include "pch.h"
#include "Bullet.h"
#include "Image.h"
#include "Camera.h"

Bullet::Bullet(float x, float y, float angle)
{
	mX = x;
	mY = y;
	mStartX = mX;
	mStartY = mY;
	mSpeed = 800.f;
	mAngle = angle;
	mResize = 8.f;
}

void Bullet::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Bullet");
	mSizeX = mImage->GetFrameHeight();
	mSizeY = mImage->GetFrameWidth();
	mRect = RectMakeCenter(mX, mY, mSizeX- mResize, mSizeY- mResize);
	mIsShot = false;
}

void Bullet::Release()
{
}


void Bullet::Update()
{
	mX -= mSpeed * cosf(mAngle) * Time::GetInstance()->DeltaTime();
	mY += mSpeed * sinf(mAngle) * Time::GetInstance()->DeltaTime();
	mRect = RectMakeCenter(mX, mY, mSizeX- mResize, mSizeY- mResize);
	if (Math::GetDistance(mX, mY, mStartX, mStartY) > 1000 || mIsShot == true)
	{
		mIsDestroy = true;
	}
}

void Bullet::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, 0, 0, mSizeX, mSizeY);

}


