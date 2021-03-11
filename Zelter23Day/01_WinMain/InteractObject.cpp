#include "pch.h"
#include "InteractObject.h"
#include "Image.h"
#include "Camera.h"


InteractObject::InteractObject(const string name, float x, float y, int hp)
	:GameObject(name)
{
	mX = x;
	mY = y;
	mHp = hp;
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
	if (mHp <= 0 && mIsInteractive == true)
	{
		mIsInteractive = false;
		mIndexX = 1;
	}
}

void InteractObject::Render(HDC hdc)
{
	mImage->FrameRender(hdc, mX, mY, mIndexX, mIndexY);
}
