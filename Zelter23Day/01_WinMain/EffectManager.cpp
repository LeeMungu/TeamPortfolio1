#include "pch.h"
#include "EffectManager.h"
#include "Image.h"
#include "Animation.h"
#include "Animations.h"
#include "Camera.h"

void EffectManager::Init(wstring imageKey, RECT temp, int frameStartX, int frameEndX, float frameUpdateTime)
{
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Effect, this);
	mImage = IMAGEMANAGER->FindImage(imageKey);
	mX = temp.right - temp.left;
	mY = temp.bottom - temp.top;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mAnimation = new Animation();
	mAnimation->InitFrameByStartEnd(frameStartX, 0, frameEndX, 0, false);
	mAnimation->SetIsLoop(false);
	mAnimation->SetFrameUpdateTime(frameUpdateTime);

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
		ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), mSizeX*0.5, mSizeY*0.5);
}

