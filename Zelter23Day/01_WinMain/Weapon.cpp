#include "pch.h"
#include "Weapon.h"
#include "Image.h"
#include "Tile.h"
#include "MapToolScene.h"

Weapon::Weapon(const float x, float y, float sizeX, float sizeY)
{
	mX = x;
	mY = y;
	mSizeX = sizeX;
	mSizeY = sizeY;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Weapon::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Weapon_pistol");
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mStartImageX = mImageX;
	mStartImageY = mImageY;
	mStartX = mX;
	mStartY = mY;
	mRect = RectMake(mX, mY, mSizeX, mSizeY);

}

void Weapon::Release()
{
}

void Weapon::Update()
{
	mNowPlayerX = mPlayer->GetX();
	mNowPlayerY = mPlayer->GetY();

	mX = mStartX + mNowPlayerX;
	mY = mStartY + mNowPlayerY;
	mImageX = mStartImageX + mNowPlayerX;
	mImageY = mStartImageY + mNowPlayerY;

	mRect = RectMake(mX, mY, mSizeX, mSizeY);

}

void Weapon::Render(HDC hdc)
{
	mImage->Render(hdc, mImageX, mImageY);
}
