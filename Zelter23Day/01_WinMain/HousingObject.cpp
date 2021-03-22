#include "pch.h"
#include "HousingObject.h"
#include "Tile.h"
#include "Image.h"
#include <fstream>
#include "Camera.h"


HousingObject::HousingObject(const wstring& name, float x, float y, int tileCountX, int tileCountY)
{
	mTileIndexX = x / TileSize;
	mTileIndexY = y / TileSize;

	mImageKey = name;
	if (mImageKey == L"House1" || mImageKey == L"House4" || mImageKey == L"House7" || mImageKey == L"police1" || mImageKey== L"shop1")
	{
		mHouselayer = HouseLayer::Floor;
	}
	else if (mImageKey == L"House2" || mImageKey == L"House5" || mImageKey == L"House8" || mImageKey == L"police2" || mImageKey == L"shop2")
	{
		mHouselayer = HouseLayer::HouseWall;
	}
	else if (mImageKey == L"House3" || mImageKey == L"House6" || mImageKey == L"House9" || mImageKey == L"police3" || mImageKey == L"shop3")
	{
		mHouselayer = HouseLayer::Roof;
	}
	mImage = IMAGEMANAGER->FindImage(mImageKey);
	mSizeX = mImage->GetFrameWidth()*2;
	mSizeY = mImage->GetFrameHeight()*2;
	mTileCountX = tileCountX;
	mTileCountY = tileCountY;

	if ((mTileCountX) % 2 == 1)//X방향 홀수 타일
	{
		mX = mTileIndexX * TileSize + TileSize / 2 + mTileCountX / 2 * TileSize;
	}
	else if ((mTileCountX) % 2 == 0)//X방향 짝수 타일
	{
		mX = mTileIndexX * TileSize + mTileCountX / 2 * TileSize;
	}
	mY = mTileIndexY * TileSize - mSizeY / 2 + TileSize / 2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

}

void HousingObject::Init()
{
	mIndexX = 0;
	mIndexY = 0;
	mAlpha = 1.f;
}

void HousingObject::Release()
{

}

void HousingObject::Update()
{
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	if (mHouselayer == HouseLayer::Floor)
	{
		mRect.bottom = mRect.bottom-2;
	}
	else if (mHouselayer == HouseLayer::HouseWall)
	{
		mRect.bottom = mRect.bottom - 1;
	}
	else if(mHouselayer == HouseLayer::Roof)
	{
		mRect.bottom = mRect.bottom ;
	}

}

void HousingObject::Render(HDC hdc)
{
	if (CameraManager::GetInstance()->GetMainCamera()->IsInCameraArea(mRect))
	{
		//타일 렉트
		for (int y = 0; y < mTileCountY; ++y)
		{
			for (int x = 0; x < mTileCountX; ++x)
			{
				RECT rc = RectMakeCenter(
					mTileIndexX * TileSize + TileSize / 2 + x * TileSize,
					mRect.bottom - y * TileSize,
					TileSize, TileSize);
				CameraManager::GetInstance()->GetMainCamera()
					->RenderRect(hdc, rc);
			}
		}

		if (Input::GetInstance()->GetKey(VK_LCONTROL))
		{
			//이미지 렉트
			CameraManager::GetInstance()->GetMainCamera()
				->RenderRect(hdc, mRect);
		}



		//이미지
		if (mHouselayer == HouseLayer::Roof)
		{
			CameraManager::GetInstance()->GetMainCamera()
				->AlphaScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mIndexX, mIndexY, mSizeX, mSizeY,mAlpha);
		}
		else
		{
			CameraManager::GetInstance()->GetMainCamera()
			->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mIndexX, mIndexY, mSizeX, mSizeY);
		}
		
	}
}
