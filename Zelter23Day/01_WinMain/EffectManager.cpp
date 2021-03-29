#include "pch.h"
#include "EffectManager.h"
#include "Image.h"
#include "Animation.h"
#include "Animations.h"
#include "Camera.h"


EffectManager::EffectManager(wstring imagename, RECT temp, int frameStartX, int frameEndX, float frameTime)
{
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Effect, this);
	mImage = IMAGEMANAGER->FindImage(imagename);


	if (mImage->GetKey() ==L"Effect_blood_L" )
	{
		mX = temp.left;
		mY = temp.top + (temp.bottom - temp.top) / 2;
		mSizeX = mImage->GetFrameWidth()*2;
		mSizeY = mImage->GetFrameHeight()*2;
	}
	else if (mImage->GetKey() == L"Effect_blood_R")
	{
		mX = temp.right;
		mY = temp.top + (temp.bottom - temp.top) / 2;
		mSizeX = mImage->GetFrameWidth() * 2;
		mSizeY = mImage->GetFrameHeight() * 2;
	}
	else
	{
		mX = temp.left + (temp.right - temp.left) / 2;
		mY = temp.top + (temp.bottom - temp.top) / 2;
		mSizeX = mImage->GetFrameWidth();
		mSizeY = mImage->GetFrameHeight();
	}

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mAnimation = new Animation();
	mAnimation->InitFrameByStartEnd(frameStartX, 0, frameEndX, 0, false);
	mAnimation->SetFrameUpdateTime(frameTime);
	mAnimation->SetIsLoop(false);
	mAnimation->SetCallbackFunc([this]() {mIsDestroy = true; });

	mCurrentAnimation = mAnimation;
	mCurrentAnimation->Play();
}

void EffectManager::Release()
{
	SafeDelete(mAnimation);
}

void EffectManager::Update()
{
	mCurrentAnimation->Update();
}

void EffectManager::Render(HDC hdc)
{

	CameraManager::GetInstance()->GetMainCamera()->
		ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), mSizeX, mSizeY);


}

