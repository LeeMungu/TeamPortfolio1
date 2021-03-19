#include "pch.h"
#include "NonInteractObject.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"

NonInteractObject::NonInteractObject(const wstring imageKey, float x, float y)
{
	mX = x;
	mY = y;
	mImageKey = imageKey;
	mImage = IMAGEMANAGER->FindImage(mImageKey);
}

void NonInteractObject::Init()
{
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mIndexX = 0;
	mIndexY = 0;
	mAngleX = ((float)Random::GetInstance()->RandomInt(-30, 30)) / ((float)10);
	mIsAnglePlus = true;
	mUpDownRatio = 0.9f + ((float)Random::GetInstance()->RandomInt(0,100))*0.2f/100.f;
	mIsUp = true;
}

void NonInteractObject::Release()
{

}

void NonInteractObject::Update()
{
	//½ºÄÉÀÏ·£´õ·Î »Ç¼õ»Ç¼õ
	//À§¾Æ·¡ »Ç¼õ»Ç¼õ
	if(mUpDownRatio > 1.1f)
	{
		mIsUp = false;
	}
	else if (mUpDownRatio < 0.9f)
	{
		mIsUp = true;
	}
	if(mIsUp == true)
	{
		mUpDownRatio += 0.05f * Time::GetInstance()->DeltaTime();
	}
	else if(mIsUp == false)
	{ 
		mUpDownRatio -= 0.05f * Time::GetInstance()->DeltaTime();
	}

	//ÁÂ¿ì »Ç¼õ»Ç¼õ
	if(mAngleX>5)
	{
		mIsAnglePlus = false;
	}
	else if (mAngleX < -5)
	{
		mIsAnglePlus = true;
	}
	if (mIsAnglePlus==true)
	{
		mAngleX += 8*Time::GetInstance()->DeltaTime();
	}
	else if (mIsAnglePlus == false)
	{
		mAngleX -= 8*Time::GetInstance()->DeltaTime();
	}
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void NonInteractObject::Render(HDC hdc)
{
	if (CameraManager::GetInstance()->GetMainCamera()->IsInCameraArea(mRect))
	{
		//CameraManager::GetInstance()->GetMainCamera()
		//	->FrameRender(hdc, mImage, mRect.left, mRect.top, mIndexX, mIndexY);
		CameraManager::GetInstance()->GetMainCamera()
			->ActivitScaleRender(hdc, mImage, mRect.left, mRect.top + mSizeY*(1.f-mUpDownRatio), mSizeX, mSizeY*mUpDownRatio,mAngleX,0);
		//Time::GetInstance()->GetSceneTime();ÀÌ¿ëÇØ¼­ ±×¸²ÀÚ ÇØº¸±â
	}
}
