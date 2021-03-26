#include "pch.h"
#include "Rain.h"

Rain::Rain(float x, float y, float sizeX, float sizeY, float angle, float speed, float limitDistance)
{
	mX = x;
	mY = y;
	mAngle = angle;
	mSpeed = speed;
	mImage = ImageManager::GetInstance()->FindImage(L"Rain");
	mSizeX = sizeX;
	mSizeY = sizeY;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mStartX = mX;
	mStartY = mY;
	mLimitDistance = limitDistance;
}

void Rain::Init()
{

}

void Rain::Release()
{

}

void Rain::Update()
{
	mX += mSpeed * cosf((90.f-mAngle)/180.f*PI);
	mY += mSpeed * sinf((90.f-mAngle)/180.f*PI);
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	if (
		//mRect.right<0 || mRect.left>WINSIZEX || mRect.bottom<0 || mRect.top>WINSIZEY||
		Math::GetDistance(mStartX,mStartY,mX,mY)>mLimitDistance)
	{
		mIsDestroy = true;
	}
}

void Rain::Render(HDC hdc)
{
	mImage->ActivitScaleRender(hdc, mRect.left, mRect.top, mSizeX, mSizeY, mAngle / 2, 0);
}
