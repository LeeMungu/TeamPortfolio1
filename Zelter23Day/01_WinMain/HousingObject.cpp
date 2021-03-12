#include "pch.h"
#include "HousingObject.h"
#include "Tile.h"
#include "Image.h"
#include <fstream>

HousingObject::HousingObject(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;

	mRoofSideImage = IMAGEMANAGER->FindImage(L"HouseRoof");
	mAlpha = 1.f;

}

void HousingObject::Init()
{
}

void HousingObject::Release()
{
	
}

void HousingObject::Update()
{
}

void HousingObject::Render(HDC hdc)
{
	mRoofSideImage->AlphaRender(hdc,mX,mY, mAlpha);
}
