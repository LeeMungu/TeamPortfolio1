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
	
}

void Weapon::Release()
{
}

void Weapon::Update()
{

}

void Weapon::Render(HDC hdc)
{
	
}
