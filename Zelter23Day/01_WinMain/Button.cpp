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
			mIndexX = 0;
			if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
			{
				if (PtInRect(&mRect, _mousePosition))
				{
					mState = State::Push;
				}
			}
		}
		else if(mState == State::Push)
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
		//�ٸ����� ���õǾ��ٸ�<-��¿������ �ܺο��� ���� �� ���ۿ�����. <-��ư������? �Ŀ� �����غ���
		if (mState == State::Select)
		{
			mIndexX = 2;
			if (mIsSelect == false)
			{
				mState = State::Normal;
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
	D2DRenderer::GetInstance()
		->RenderText( mX - mSizeX / 3, mY - mSizeY / 4, mText.c_str(), 20);
	if (mImage != nullptr)
		mImage->ScaleFrameRender(hdc, mRect.left, mRect.top, mIndexX, mIndexY, mSizeX,mSizeY);
}

void Button::Move(float x, float y)
{
	mX = x;
	mY = y;

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}