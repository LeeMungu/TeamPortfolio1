#include "pch.h"
#include "Weapon.h"
#include "Image.h"
#include "Tile.h"
#include "MapToolScene.h"

void Weapon::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Weapon_pistol");
	mRect = RectMakeCenter(GetX(), GetY(), GetSizeX(), GetSizeY());
}

void Weapon::Release()
{
}

void Weapon::Update()
{

}

void Weapon::Render(HDC hdc)
{
	RenderRect(hdc, mRect);
}
