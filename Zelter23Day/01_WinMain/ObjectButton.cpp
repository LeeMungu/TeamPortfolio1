#include "pch.h"
#include "ObjectButton.h"
#include "Image.h"

ObjectButton::ObjectButton(wstring imageKey, float x, float y, function<void(void)> func)
{
	mImage = ImageManager::GetInstance()->FindImage(imageKey);
	mX = x;
	mY = y;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mFunc = func;
	mState = State::Normal;
}

void ObjectButton::Update()
{
	if (mState == State::Normal)
	{
		if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
		{
			if (PtInRect(&mRect, _mousePosition))
			{
				mState = State::Push;
			}
		}
	}
	else
	{
		if (Input::GetInstance()->GetKeyUp(VK_LBUTTON))
		{
			mState = State::Normal;
			if (mFunc != nullptr)
			{
				mFunc();
			}
		}
	}
}

void ObjectButton::Render(HDC hdc)
{
	mImage->ScaleFrameRender(hdc, mRect.left, mRect.top, mIndexX, mIndexY, mSizeX, mSizeY);
}
