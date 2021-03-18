#include "pch.h"
#include "Inventory.h"

Inventory::Inventory(const string & name) : UI(name)
{
}

void Inventory::Init()
{
	mBaseImage = IMAGEMANAGER->FindImage(L"Inventory_base");
	mIsOpened = false;
}

void Inventory::Release()
{
}

void Inventory::Update()
{
}

void Inventory::Render(HDC hdc)
{
}
