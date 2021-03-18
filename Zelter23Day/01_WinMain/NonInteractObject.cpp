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
	mAngleX = 0;
	mIsAnglePlus = true;
}

void NonInteractObject::Release()
{

}

void NonInteractObject::Update()
{
	//�����Ϸ����� �Ǽ��Ǽ�
	if(mAngleX>3)
	{
		mIsAnglePlus = false;
	}
	else if (mAngleX < -3)
	{
		mIsAnglePlus = true;
	}

	if (mIsAnglePlus==true)
	{
		mAngleX += 10*Time::GetInstance()->DeltaTime();
	}
	else if (mIsAnglePlus == false)
	{
		mAngleX -= 10*Time::GetInstance()->DeltaTime();
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
			->ActivitScaleRender(hdc, mImage, mRect.left, mRect.top, mSizeX, mSizeY,mAngleX,0);
		//Time::GetInstance()->GetSceneTime();�̿��ؼ� �׸��� �غ���
	}
}
