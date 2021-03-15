#include "pch.h"
#include "Mouse.h"
#include "Image.h"
#include "Tile.h"

Mouse::Mouse(wstring imageKey)
{
	mImage = IMAGEMANAGER->FindImage(imageKey);
	mX = _mousePosition.x;
	mY = _mousePosition.y;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Mouse::Init()
{
}

void Mouse::Release()
{
}

void Mouse::Update()
{
	mX = _mousePosition.x;
	mY = _mousePosition.y;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Mouse::Render(HDC hdc)
{
	mImage->Render(hdc, mRect.left, mRect.top);
}

