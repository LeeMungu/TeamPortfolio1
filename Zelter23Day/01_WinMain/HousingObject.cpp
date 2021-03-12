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

	mTileList.assign(9, vector<Tile*>());
	for (int y = 0; y < mTileList.size(); ++y)
	{
		for (int x = 0; x < 9; ++x)
		{
			mTileList[y].push_back(new Tile
			(
				mRoofSideImage,
				TileSize * x,
				TileSize * y,
				TileSize,
				TileSize,
				x,
				y
			));
		}
	}



}

void HousingObject::Init()
{
}

void HousingObject::Release()
{
	for (int y = 0; y < 9; ++y)
	{
		for (int x = 0; x < 9; ++x)
		{
			SafeDelete(mTileList[y][x]);
		}
	}
}

void HousingObject::Update()
{
}

void HousingObject::Render(HDC hdc)
{
	for (int y = 0; y < 9; ++y)
	{
		for (int x = 0; x <  9; ++x)
		{
			mTileList[y][x]->Render(hdc);
		}
	}


}
