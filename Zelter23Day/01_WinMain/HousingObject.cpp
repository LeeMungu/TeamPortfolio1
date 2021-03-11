#include "pch.h"
#include "HousingObject.h"
#include "Tile.h"
#include "Image.h"
#include <fstream>

HousingObject::HousingObject(const string& name, float x, float y, SideType type)
	:GameObject(name)
{
	mX = x;
	mY = y;
	sidetype = type;
	if (sidetype == SideType::InSide)
	{
		mInSideImage = IMAGEMANAGER->FindImage(L"House");
		
		mTileList.assign(TileCountY, vector<Tile*>());
		for (int y = 0; y < mTileList.size(); ++y)
		{
			for (int x = 0; x < TileCountX; ++x)
			{
				mTileList[y].push_back(new Tile
				(
					mInSideImage,
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
	else
	{

	}

}

void HousingObject::Init()
{
}

void HousingObject::Release()
{
	for (int y = 0; y < TileCountY; ++y)
	{
		for (int x = 0; x < TileCountX; ++x)
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
	for (int y = 0; y < TileCountY; ++y)
	{
		for (int x = 0; x < TileCountX; ++x)
		{
			
			mTileList[y][x]->Render(hdc);
			
		}
	}
}
