#include "pch.h"
#include "InteractObject.h"
#include "Image.h"
#include "Camera.h"

InteractObject::InteractObject(const wstring imageKey, float x, float y, int hp)
{
	mX = x;
	mY = y;
	mHp = hp;
	mImageKey = imageKey;
	mImage = IMAGEMANAGER->FindImage(mImageKey);
}

void InteractObject::Init()
{
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mIsInteractive = true;
	mIndexX = 0;
	mIndexY = 0;
}

void InteractObject::Release()
{
}

void InteractObject::Update()
{
	//if (mHp <= 0 && mIsInteractive == true)
	//{
	//	mIsInteractive = false;
	//	mIndexX = 1;
	//}
	if (mHp <= 0)
	{
		mIsDestroy = true;
	}
}

void InteractObject::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mRect.left, mRect.top, mIndexX, mIndexY);
}
