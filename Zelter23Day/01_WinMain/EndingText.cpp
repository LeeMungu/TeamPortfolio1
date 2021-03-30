#include "pch.h"
#include "EndingText.h"
#include "Image.h"

EndingText::EndingText(int indexY)
{
	mIndexY = indexY;
}

void EndingText::Init()
{
	IMAGEMANAGER->LoadFromFile(L"TestEndingCredit", Resources(L"/01_UI/TestEndingCredit.png"), 1, 55);
	mImage = IMAGEMANAGER->FindImage(L"TestEndingCredit");
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mX = WINSIZEX / 2;
	mY = WINSIZEY + mSizeY / 2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mSpeed = 5.f;
	mReduseSizeX = 2.8f;
	mReduseSizeY = mReduseSizeX / mSizeX * mSizeY;
}

void EndingText::Release()
{
}

void EndingText::Update()
{
	if (mRect.bottom < 0)
	{
		mIsDestroy = true;
	}
	mY -= mSpeed;
	if (mSpeed > 0)
	{
		mSpeed -= 0.015f;
	}
	mSizeX -= mReduseSizeX;
	mSizeY -= mReduseSizeY;

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

}

void EndingText::Render(HDC hdc)
{
	mImage->ScaleFrameRender(hdc, mRect.left, mRect.top, 0, mIndexY, mSizeX, mSizeY);
}
