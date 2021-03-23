#include "pch.h"
#include "HousingObject.h"
#include "Tile.h"
#include "Image.h"
#include <fstream>
#include "Camera.h"
#include "Player.h"


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

	if (mImageKey == L"House3")
	{
		mHouse01Rect1 = RectMakeCenter(mX, mY-20, mSizeX/2+100, mSizeY / 2-18);
		mHouse01Rect2 = RectMakeCenter(mX+140, mY+230, mSizeX/4, mSizeY/4);
	}
	if (mImageKey == L"House6")
	{
		mHouse04Rect1 = RectMakeCenter(mX, mY+50, mSizeX/2+280, mSizeY / 2+20);
	}
	if (mImageKey == L"House9")
	{
		mHouse07Rect1 = RectMakeCenter(mX, mY, mSizeX/1.5, mSizeY/1.5);
	}
	if (mImageKey == L"police3")
	{
		mPoliceRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}
	if (mImageKey == L"shop3")
	{
		mShopRect1 = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		mShopRect2 = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}


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
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");

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
	if (mImageKey == L"House3")
	{
		mHouse01Rect1 = RectMakeCenter(mX, mY - 20, mSizeX / 2 + 100, mSizeY / 2 - 18);
		mHouse01Rect2 = RectMakeCenter(mX + 140, mY + 230, mSizeX / 4, mSizeY / 4);
	}
	if (mImageKey == L"House6")
	{
		mHouse04Rect1 = RectMakeCenter(mX, mY + 50, mSizeX / 2 + 280, mSizeY / 2 + 20);
	}
	if (mImageKey == L"House9")
	{
		mHouse07Rect1 = RectMakeCenter(mX, mY, mSizeX / 1.5, mSizeY /1.5+100);
	}
	if (mImageKey == L"police3")
	{
		mPoliceRect = RectMakeCenter(mX, mY+80, mSizeX-250, mSizeY-250);
	}
	if (mImageKey == L"shop3")
	{
		mShopRect1 = RectMakeCenter(mX+220, mY+150, mSizeX/2-70, mSizeY/2);
		mShopRect2 = RectMakeCenter(mX-200, mY-150, mSizeX/2-50, mSizeY/3-50);
	}

	
	if (ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Player).size() != NULL)
	{
		RECT tempRc;
		RECT playerRc = mPlayer->GetRect();
		if (IntersectRect(&tempRc, &mHouse01Rect1, &playerRc) || IntersectRect(&tempRc, &mHouse01Rect2, &playerRc)|| 
			IntersectRect(&tempRc, &mHouse04Rect1, &playerRc) || IntersectRect(&tempRc, &mHouse07Rect1, &playerRc)||
			IntersectRect(&tempRc, &mPoliceRect, &playerRc)|| IntersectRect(&tempRc, &mShopRect1, &playerRc)||
			IntersectRect(&tempRc, &mShopRect2, &playerRc))
		{
			mAlpha = 0.f;
		}
		else
		{
			mAlpha = 1.f;
		}
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

		//이미지
		if (mHouselayer == HouseLayer::Roof)
		{
			CameraManager::GetInstance()->GetMainCamera()
				->AlphaScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mIndexX, mIndexY, mSizeX, mSizeY, mAlpha);
		}
		else
		{
			CameraManager::GetInstance()->GetMainCamera()
				->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mIndexX, mIndexY, mSizeX, mSizeY);

		}

		if (Input::GetInstance()->GetKey(VK_LCONTROL))
		{
			//이미지 렉트
			CameraManager::GetInstance()->GetMainCamera()
				->RenderRect(hdc, mRect);

			CameraManager::GetInstance()->GetMainCamera()
				->RenderRect(hdc, mHouse01Rect1, Gizmo::Color::Blue2);
			CameraManager::GetInstance()->GetMainCamera()
				->RenderRect(hdc, mHouse01Rect2, Gizmo::Color::Blue2);

			CameraManager::GetInstance()->GetMainCamera()
				->RenderRect(hdc, mHouse04Rect1, Gizmo::Color::Blue2);
			CameraManager::GetInstance()->GetMainCamera()
				->RenderRect(hdc, mHouse07Rect1, Gizmo::Color::Blue2);
			CameraManager::GetInstance()->GetMainCamera()
				->RenderRect(hdc, mPoliceRect, Gizmo::Color::Blue2);

			CameraManager::GetInstance()->GetMainCamera()
				->RenderRect(hdc, mShopRect1, Gizmo::Color::Blue2);
			CameraManager::GetInstance()->GetMainCamera()
				->RenderRect(hdc, mShopRect2, Gizmo::Color::Blue2);
		}
	}

	
}
