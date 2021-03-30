#include "pch.h"
#include "Button.h"
#include "Image.h"

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
	mButtonType = Type::OnOffButton;
}

Button::Button(wstring imageKey, int indexY, wstring text, float x, float y, float sizeX, float sizeY, function<void(void)> func)
{
	mImage = ImageManager::GetInstance()->FindImage(imageKey);
	mIndexY = indexY;
	mIndexX = 0;
	mText = text;
	mX = x;
	mY = y;
	mSizeX = sizeX;
	mSizeY = sizeY;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mFunc = func;
	mState = State::Normal;
	mButtonType = Type::SelectButton;
	mIsSelect = false;
	mIsMaking = false;
}

Button::Button(wstring imageKey, float x, float y, float multiply, function<void(void)> func)
{
	mImage = ImageManager::GetInstance()->FindImage(imageKey);
	mX = x;
	mY = y;
	mSizeX = mImage->GetFrameWidth()*multiply;
	mSizeY = mImage->GetFrameHeight()* multiply;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mFunc = func;
	mState = State::Normal;
	mButtonType = Type::SelectButton;
	mIsSelect = false;
	mIsMaking = true;
}

Button::Button(wstring imageKey, float x, float y, function<void(void)> func)
{
	mImage = ImageManager::GetInstance()->FindImage(imageKey);
	mSizeX = mImage->GetFrameWidth() - 50;
	mSizeY = mImage->GetHeight() - 40;
	mX = x;
	mY = y;
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
	mFunc = func;
	mState = State::Normal;
	mButtonType = Type::MenuButton;
}

void Button::Update()
{
	if (mButtonType == Type::OnOffButton)
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
	else if(mButtonType == Type::SelectButton)
	{
		if (mState == State::Normal)
		{
			if (mIsMaking)
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
				mIndexX = 0;
				if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
				{
					if (PtInRect(&mRect, _mousePosition))
					{
						mState = State::Push;
					}
				}
			}
			
		}
		else if(mState == State::Push)
		{
			if (mIsMaking)
			{
				if (Input::GetInstance()->GetKeyUp(VK_LBUTTON))
				{
					mState = State::Select;
					if (mFunc != nullptr)
					{
						mFunc();
					}
					//mIsSelect = true;
				}
			}
			else
			{
				mIndexX = 1;
				if (Input::GetInstance()->GetKeyUp(VK_LBUTTON))
				{
					mState = State::Select;
					if (mFunc != nullptr)
					{
						mFunc();
					}
					mIsSelect = true;
				}
			}
		}
		//다른것이 선택되었다면<-어쩔수없이 외부에서 반응 할 수밖에없다. <-버튼관리자? 후에 생각해보기
		if (mState == State::Select)
		{
			if (mIsMaking)
			{
				if (mIsSelect == false)
				{
					mState = State::Normal;
				}
			}
			else
			{
				mIndexX = 2;
				if (mIsSelect == false)
				{
					mState = State::Normal;
				}
			}
			
		}
	}
	else if (mButtonType == Type::MenuButton)
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
}

void Button::Render(HDC hdc)
{
	if (mButtonType != Type::MenuButton)
	{
		//버튼 랙트 
		//if (mState == State::Normal)
		//{
		//	RenderRect(hdc, mRect);
		//}
		//else
		//{
		//	float sizeX = mSizeX * 0.75f;
		//	float sizeY = mSizeY * 0.75f;
		//	RECT rc = RectMakeCenter(mX, mY, sizeX, sizeY);
		//	RenderRect(hdc, rc);
		//}
		if (mImage != nullptr)
			mImage->ScaleFrameRender(hdc, mRect.left, mRect.top, mIndexX, mIndexY, mSizeX, mSizeY);
		else
		{
			D2DRenderer::GetInstance()
				->RenderText(mX - mSizeX / 3, mY - mSizeY / 4, mText.c_str(), 20);
		}
	}
	else if(mButtonType == Type::MenuButton)
	{
		if (mState == State::Normal) {
			mImage->FrameRender(hdc, mRect.left - 20, mRect.top - 20, 0, 0);
		}
		else
		{
			mImage->FrameRender(hdc, mRect.left - 20, mRect.top - 20, 1, 0);
		}
	}
}

void Button::Move(float x, float y)
{
	mX = x;
	mY = y;

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}
