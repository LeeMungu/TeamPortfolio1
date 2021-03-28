#include "pch.h"
#include "Item.h"
#include "Image.h"
#include "Camera.h"
#include "Inventory.h"
Item::Item(wstring imageKey, float x, float y, int count, ItemKind kind) {
	mKeyName = imageKey;
	mX = x;
	mY = y;
	mCount = count;
	mItemKind = kind;

}
Item::Item(wstring imageKey, string name, float x, float y, int count, ItemKind kind) : GameObject(name)
{
	mKeyName = imageKey;
	mX = x;
	mY = y;
	mCount = count;
	mItemKind = kind;

}
void Item::Init()
{
	mImage = IMAGEMANAGER->FindImage(mKeyName);
	mType = ItemManager::GetInstance()->SetItemType(mKeyName);

	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mNumImage = IMAGEMANAGER->FindImage(L"SW_num");

	mIsClicking = false;
	mIsSeleted = false;
	mPrePosition.x = mX;
	mPrePosition.y = mY;

	mSpeed = 80.f;
	mGravity = 150.f;
	mIsFirst = true;

	mAngle = Random::GetInstance()->RandomInt(70, 240) * 0.01f;
	mIsPossiblePick = true;

	mCreatedTime = Time::GetInstance()->GetSceneTime();
	mAlpha = 1.f;
}

void Item::Release() {
}

void Item::Update()
{
	

	if (mItemKind == ItemKind::drop)
	{
		DropMovement();

		float mNowTime = Time::GetInstance()->GetSceneTime();
		float timer = mNowTime - mCreatedTime;
		if (timer > 10)
		{
			mAlpha -= 0.005f;
		}

		if(mAlpha <= 0)
		{
			this->SetIsDestroy(true);
		}
	}

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Item::Render(HDC hdc)
{
	if (mItemKind == ItemKind::drop) { //¶¥¿¡ ¶³¾îÁ®ÀÖÀ» ¶© Ä«¸Þ¶ó ·£´õ
		CameraManager::GetInstance()->GetMainCamera()->AlphaScaleRender(hdc, mImage, mRect.left, mRect.top, 27, 27, mAlpha);

		if (mCount != 1)
		{
			CameraManager::GetInstance()->GetMainCamera()->
				ScaleFrameRender(hdc, mNumImage, mX, mY + 5, mCount / 10 % 10, 0, 10, 10);
			CameraManager::GetInstance()->GetMainCamera()->
				ScaleFrameRender(hdc, mNumImage, mX + 6, mY + 5, mCount % 10, 0, 10, 10);
		}

	}
	else if (mItemKind == ItemKind::inventory)
	{
		mImage->Render(hdc, mRect.left, mRect.top);
		RenderRect(hdc, mRect);

		mNumImage->ScaleFrameRender(hdc, mX, mY + 5, mCount / 10 % 10, 0, 10, 10);
		mNumImage->ScaleFrameRender(hdc, mX + 6, mY + 5, mCount % 10, 0, 10, 10);
	}
	else { //ÀÎº¥Åä¸®, Äü½½·ÔÀº ±×³É ·£´õ
		mImage->Render(hdc, mRect.left, mRect.top);

		mNumImage->ScaleFrameRender(hdc, mX , mY + 5, mCount / 10 % 10, 0, 10, 10);
		mNumImage->ScaleFrameRender(hdc, mX + 6, mY + 5, mCount % 10, 0, 10, 10);
	}

	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, mRect, Gizmo::Color::Blue2);
	}
}

void Item::DropMovement()
{
	if (mIsFirst == true)
	{
		if (mSpeed > 0)
		{
			mX += cosf(mAngle) * mSpeed * Time::GetInstance()->DeltaTime() * 2.f;
			mY += sinf(mAngle) * mSpeed * Time::GetInstance()->DeltaTime();
			mSpeed -= mGravity * Time::GetInstance()->DeltaTime();
			mIsPossiblePick = false;
		}
		else
		{
			mIsFirst = false;
			mIsPossiblePick = true;
		}
	}
}

void Item::NoPickUp()
{

}

void Item::SetCountMinus(int n)
{
	if (mCount >= n)
	{
		mCount -= n;
	}
}
