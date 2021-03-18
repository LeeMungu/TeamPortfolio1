#include "pch.h"
#include "Item.h"
#include "Image.h"

void Item::Init(float x, float y, ItemType type)
{
	IMAGEMANAGER->LoadFromFile(L"Zombie01", Resources(L"/06_Zombie/zombie01.png"), 5, 6);
}

void Item::Release()
{
}

void Item::Update()
{
}

void Item::Render(HDC hdc, float cameraX, float cameraY)
{
}
