#include "pch.h"
#include "NonInteractObject.h"
#include "Image.h"
#include "Animation.h"

NonInteractObject::NonInteractObject(const string name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void NonInteractObject::Init()
{

	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	   	 
}

void NonInteractObject::Release()
{

}


void NonInteractObject::Render(HDC hdc)
{
	mImage->Render(hdc, mX, mY);
}
