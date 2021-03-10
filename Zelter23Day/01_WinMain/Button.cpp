#include "pch.h"
#include "Button.h"

Button::Button(wstring text,float x, float y, float sizeX, float sizeY, function<void(void)> func)
{
	mText = text;
	mX = x;
	mY = y;
	mSizeX = sizeX;
	mSizeY = sizeY;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mFunc = func;
	mState = State::Normal;
}

void Button::Update()
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

void Button::Render(HDC hdc)
{
	if(mState == State::Normal)
		RenderRect(hdc, mRect);
	else
	{
		float sizeX = mSizeX * 0.75f;
		float sizeY = mSizeY * 0.75f;
		RECT rc = RectMakeCenter(mX, mY, sizeX, sizeY);
		RenderRect(hdc, rc);
	}

	TextOut(hdc, mX - mSizeX / 4, mY - mSizeY / 4, mText.c_str(), mText.length());
}

void Button::Move(float x, float y)
{
	mX = x;
	mY = y;

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}