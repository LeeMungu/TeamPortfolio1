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
}

void NonInteractObject::Release()
{

}

void NonInteractObject::Update()
{
	//ÈÄ¿¡ ½ºÄÉÀÏ·£´õ·Î »Ç¼õ»Ç¼õ ¸¸µé¿¹Á¤
}

void NonInteractObject::Render(HDC hdc)
{
	if (CameraManager::GetInstance()->GetMainCamera()->IsInCameraArea(mRect))
	{
		CameraManager::GetInstance()->GetMainCamera()
			->FrameRender(hdc, mImage, mRect.left, mRect.top, mIndexX, mIndexY);
	}
}
