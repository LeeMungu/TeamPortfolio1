#include "pch.h"
#include "HousingObject.h"
#include "Tile.h"
#include <fstream>

HousingObject::HousingObject(const string& name, float x, float y, SideType type)
	:GameObject(name)
{
	mX = x;
	mY = y;

	mTileList.assign(TileCountY, vector<Tile*>());
	for (int y = 0; y < mTileList.size(); ++y)
	{
		for (int x = 0; x < TileCountX; ++x)
		{
			mTileList[y].push_back(new Tile
			(
				nullptr,
				TileSize * x,
				TileSize * y,
				TileSize,
				TileSize,
				0,
				0
			));
		}
	}
	sidetype = type;

	Load();
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

void HousingObject::Load()
{

}
