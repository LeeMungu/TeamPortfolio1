#include "pch.h"
#include "EffectImpact.h"
#include "Image.h"
#include "Camera.h"
#include "Animation.h"

#define effectscale 2
EffectImpact::EffectImpact(int x, int y, int indexX, int indexY)
{
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Effect, this);
	mImage = IMAGEMANAGER->GetInstance()->FindImage(L"effect_impact");
	mX = x;
	mY = y;	
	mSizeX = mImage->GetFrameWidth() * effectscale;
	mSizeY = mImage->GetFrameHeight() * effectscale;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mIndexX = indexX;
	mIndexY = indexY;
	mAngle = Random::GetInstance()->RandomInt(70, 240) * 0.01f;
	mSpeed = Random::GetInstance()->RandomInt(100, 130);
	mGravity = 150.f;
}

void EffectImpact::Init()
{
}

void EffectImpact::Release()
{
}

void EffectImpact::Update()
{
	mX += cosf(mAngle) * mSpeed * Time::GetInstance()->DeltaTime();
	mY -= sinf(mAngle) * mSpeed * Time::GetInstance()->DeltaTime();
	mSpeed -= mGravity * Time::GetInstance()->DeltaTime();
	if (mSpeed <= 0)
	{
		mIsDestroy = true;
	}

}

void EffectImpact::Render(HDC hdc)
{
	//CameraManager::GetInstance()->GetMainCamera()->Render(hdc, mImage, mX, mY, mIndexX, mIndexY, mSizeX, mSizeY);

	CameraManager::GetInstance()->GetMainCamera()->FrameRender(hdc, mImage, mX, mY, mIndexX, mIndexY);
}
