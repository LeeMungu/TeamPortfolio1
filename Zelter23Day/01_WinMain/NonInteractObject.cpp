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
	//후에 스케일랜더로 뽀숑뽀숑 만들예정
}

void NonInteractObject::Render(HDC hdc)
{
	//카메라렌더 해줘야 하지 않나?<-실험해보자<-카메라로 해야함
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mRect.left, mRect.top, mIndexX, mIndexY);
}
