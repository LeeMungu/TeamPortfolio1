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
	mThick = 30;
	mImageKey = name;
	mName.assign(name.begin(), name.end());
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

		mHouse01Rect1_Left = RectMakeCenter(mHouse01Rect1.left, mY - 20, mThick, mSizeY / 2 - 18);
		mCollisionList.push_back(mHouse01Rect1_Left);
		mHouse01Rect1_Right = RectMakeCenter(mHouse01Rect1.right, mY - 20, mThick, mSizeY / 2 - 18);
		mCollisionList.push_back(mHouse01Rect1_Right);
		mHouse01Rect1_Top = RectMakeCenter(mX -79, mHouse01Rect1.top, mSizeX / 2 -28, mThick);
		mCollisionList.push_back(mHouse01Rect1_Top);

		RECT mHouse01Rect1_Top2 = RectMakeCenter(mX + 195, mHouse01Rect1.top, mSizeX / 5 - 48, mThick);
		mCollisionList.push_back(mHouse01Rect1_Top2);
		mHouse01Rect1_Bottom = RectMakeCenter(mX -18 , mHouse01Rect1.bottom-10, mSizeX / 3  -30 , mThick);	// 수정필요
		mCollisionList.push_back(mHouse01Rect1_Bottom);

		mHouse01Rect2 = RectMakeCenter(mX+140, mY+230, mSizeX/4, mSizeY/4);

		mHouse01Rect2_Left = RectMakeCenter(mHouse01Rect2.left, mY + 230, mThick, mSizeY / 4);
		mCollisionList.push_back(mHouse01Rect2_Left);
		mHouse01Rect2_Right = RectMakeCenter(mHouse01Rect2.right, mY + 230, mThick, mSizeY / 4);
		mCollisionList.push_back(mHouse01Rect2_Right);
		mHouse01Rect2_Top = RectMakeCenter(mX + 195, mHouse01Rect2.top, mSizeX / 6 -20, mThick);	// 수정필요
		mCollisionList.push_back(mHouse01Rect2_Top);
		mHouse01Rect2_Bottom = RectMakeCenter(mX + 140, mHouse01Rect2.bottom, mSizeX / 4, mThick);
		mCollisionList.push_back(mHouse01Rect2_Bottom);
	}
	if (mImageKey == L"House6")
	{
		mHouse04Rect1 = RectMakeCenter(mX, mY+50, mSizeX/2+280, mSizeY / 2+20);

		mHouse04Rect1_Left = RectMakeCenter(mHouse04Rect1.left, mY + 50, mThick, mSizeY / 2 + 20);
		mCollisionList.push_back(mHouse04Rect1_Left);
		mHouse04Rect1_Right = RectMakeCenter(mHouse04Rect1.right, mY + 70, mThick, mSizeY / 2 + 40);
		mCollisionList.push_back(mHouse04Rect1_Right);
		mHouse04Rect1_Top = RectMakeCenter(mX, mHouse04Rect1.top, mSizeX / 2 + 280, mThick);
		mCollisionList.push_back(mHouse04Rect1_Top);
		mHouse04Rect1_Bottom = RectMakeCenter(mX - 245, mHouse04Rect1.bottom, mSizeX / 3 +5 , mThick);
		mCollisionList.push_back(mHouse04Rect1_Bottom);

		RECT mHouse04Rect1_Bottom2 = RectMakeCenter(mX -5 , mHouse04Rect1.bottom+32, mSizeX / 10 - 5, mThick);
		mCollisionList.push_back(mHouse04Rect1_Bottom2);
		RECT mHouse04Rect1_Bottom3 = RectMakeCenter(mX + 275, mHouse04Rect1.bottom+32, mSizeX / 5 +96, mThick);
		mCollisionList.push_back(mHouse04Rect1_Bottom3);
	}
	if (mImageKey == L"House9")
	{
		mHouse07Rect1 = RectMakeCenter(mX, mY, mSizeX/1.5, mSizeY/1.5);

		mHouse07Rect1_Left = RectMakeCenter(mHouse07Rect1.left, mY+32, mThick, mSizeY / 1.5 + 98);
		mCollisionList.push_back(mHouse07Rect1_Left);
		mHouse07Rect1_Right = RectMakeCenter(mHouse07Rect1.right, mY+32, mThick, mSizeY / 1.5 + 98);
		mCollisionList.push_back(mHouse07Rect1_Right);
		mHouse07Rect1_Top = RectMakeCenter(mX, mHouse07Rect1.top, mSizeX / 1.5, mThick);
		mCollisionList.push_back(mHouse07Rect1_Top);

		RECT mHouse07Rect1_Top2 = RectMakeCenter(mX - 170, mHouse07Rect1.top + 305, mSizeX / 3 , mThick);
		mCollisionList.push_back(mHouse07Rect1_Top2);

		mHouse07Rect1_Bottom = RectMakeCenter(mX-230, mHouse07Rect1.bottom + 64 , mSizeX / 5, mThick);
		mCollisionList.push_back(mHouse07Rect1_Bottom);

		RECT mHouse07Rect1_Bottom2 = RectMakeCenter(mX + 230, mHouse07Rect1.bottom + 64, mSizeX / 5, mThick);
		mCollisionList.push_back(mHouse07Rect1_Bottom2);
		RECT mHouse07Rect1_Bottom3 = RectMakeCenter(mX + 115, mHouse07Rect1.bottom + 100, mSizeX / 5 -32, mThick*2);
		mCollisionList.push_back(mHouse07Rect1_Bottom3);
		RECT mHouse07Rect1_Bottom4 = RectMakeCenter(mX - 115, mHouse07Rect1.bottom + 100, mSizeX / 5 - 32, mThick*2);
		mCollisionList.push_back(mHouse07Rect1_Bottom4);
	}
	if (mImageKey == L"police3")
	{
		mPoliceRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

		mPoliceRect_Left = RectMakeCenter(mPoliceRect.left+120, mY + 70, mThick, mSizeY - 220);
		mCollisionList.push_back(mPoliceRect_Left);
		mPoliceRect_Right = RectMakeCenter(mPoliceRect.right-123, mY + 80, mThick, mSizeY - 245);
		mCollisionList.push_back(mPoliceRect_Right);
		mPoliceRect_Top = RectMakeCenter(mX, mPoliceRect.top+196, mSizeX - 218, mThick);
		mCollisionList.push_back(mPoliceRect_Top);

		RECT mPoliceRect_Top2 = RectMakeCenter(mX+ 170, mPoliceRect.top + 370, mSizeX /2 + 140, mThick);
		mCollisionList.push_back(mPoliceRect_Top2);

		mPoliceRect_Bottom = RectMakeCenter(mX - 245, mPoliceRect.bottom -55, mSizeX /2 , mThick);
		mCollisionList.push_back(mPoliceRect_Bottom);

		RECT mPoliceRect_Bottom2 = RectMakeCenter(mX + 400, mPoliceRect.bottom - 55, mSizeX / 4, mThick);
		mCollisionList.push_back(mPoliceRect_Bottom2);
	}
	if (mImageKey == L"shop3")
	{


		mShopRect1 = RectMakeCenter(mX + 220, mY + 150, mSizeX / 2 - 70, mSizeY / 2);
		
		mShopRect1_Left = RectMakeCenter(mShopRect1.left -10, mY + 230 , mThick, mSizeY / 2);
		mCollisionList.push_back(mShopRect1_Left);
		mShopRect1_Right = RectMakeCenter(mShopRect1.right, mY + 190, mThick, mSizeY / 2 +30);
		mCollisionList.push_back(mShopRect1_Right);
		mShopRect1_Top = RectMakeCenter(mX + 280, mShopRect1.top + 50, mSizeX / 2 - 170, mThick);
		mCollisionList.push_back(mShopRect1_Top);
		mShopRect1_Bottom = RectMakeCenter(mX + 70, mShopRect1.bottom+60, mSizeX / 5 -50, mThick);
		mCollisionList.push_back(mShopRect1_Bottom);

		RECT mShopRect1_Bottom2 = RectMakeCenter(mX + 370, mShopRect1.bottom + 60, mSizeX / 5 -40, mThick);
		mCollisionList.push_back(mShopRect1_Bottom2);

		mShopRect2 = RectMakeCenter(mX - 200, mY - 150, mSizeX / 2 - 50, mSizeY / 3 - 50);

		mShopRect2_Left = RectMakeCenter(mShopRect2.left, mY - 150, mThick, mSizeY / 3 - 50);
		mCollisionList.push_back(mShopRect2_Left);
		mShopRect2_Right = RectMakeCenter(mShopRect2.right +40, mY - 170, mThick, mSizeY / 3 - 70);
		mCollisionList.push_back(mShopRect2_Right);
		mShopRect2_Top = RectMakeCenter(mX - 180, mShopRect2.top, mSizeX / 2 - 30, mThick);
		mCollisionList.push_back(mShopRect2_Top);
		mShopRect2_Bottom = RectMakeCenter(mX - 250, mShopRect2.bottom+20, mSizeX / 2 - 140, mThick);
		mCollisionList.push_back(mShopRect2_Bottom);
	}


	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mZotherRect.clear();
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

	if (mImageKey == L"House3" || mImageKey == L"House2")
	{
		mHouse01Rect1 = RectMakeCenter(mX, mY - 20, mSizeX / 2 + 100, mSizeY / 2 - 18);
		mHouse01Rect2 = RectMakeCenter(mX + 140, mY + 230, mSizeX / 4, mSizeY / 4);
		mZotherRect.push_back(mHouse01Rect1);
		mZotherRect.push_back(mHouse01Rect2);
	}
	else if (mImageKey == L"House6" || mImageKey == L"House5")
	{
		mHouse04Rect1 = RectMakeCenter(mX, mY + 50, mSizeX / 2 + 280, mSizeY / 2 + 20);
		mZotherRect.push_back(mHouse04Rect1);
	}
	else if (mImageKey == L"House9" || mImageKey == L"House8")
	{
		mHouse07Rect1 = RectMakeCenter(mX, mY, mSizeX / 1.5, mSizeY /1.5+100);
		mZotherRect.push_back(mHouse07Rect1);
	}
	else if (mImageKey == L"police3" || mImageKey == L"police2")
	{
		mPoliceRect = RectMakeCenter(mX, mY+80, mSizeX-250, mSizeY-250);
		mZotherRect.push_back(mPoliceRect);
	}
	else if (mImageKey == L"shop3" || mImageKey == L"shop2")
	{
		mShopRect1 = RectMakeCenter(mX+220, mY+150, mSizeX/2-70, mSizeY/2);
		mShopRect2 = RectMakeCenter(mX-200, mY-150, mSizeX/2-50, mSizeY/3-50);
		mZotherRect.push_back(mShopRect1);
		mZotherRect.push_back(mShopRect2);
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


	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	if (mHouselayer == HouseLayer::Floor)
	{
		mRect.bottom = mRect.bottom - 2;
	}
	else if (mHouselayer == HouseLayer::HouseWall)
	{
		mRect.bottom = mZotherRect[0].bottom;
		RECT tempRc;
		RECT playerRc = mPlayer->GetRect();
		if (IntersectRect(&tempRc, &playerRc, &mZotherRect[0]))
		{
			if (mRect.bottom > mRect.top + 100 && mRect.bottom < mRect.top + mSizeY)
			{
				mRect.bottom = mZotherRect[0].top;
			}
		}
	}
	else if (mHouselayer == HouseLayer::Roof)
	{
		mRect.bottom = mRect.bottom;
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

			if (mZotherRect.size() != NULL)
			{
				for (int i = 0; i < mZotherRect.size(); ++i)
				{
					CameraManager::GetInstance()->GetMainCamera()
						->RenderRect(hdc, mZotherRect[i], Gizmo::Color::Blue2);
				}
			}
			//CameraManager::GetInstance()->GetMainCamera()
			//	->RenderRect(hdc, mHouse01Rect1, Gizmo::Color::Blue2);
			//CameraManager::GetInstance()->GetMainCamera()
			//	->RenderRect(hdc, mHouse01Rect2, Gizmo::Color::Blue2);
			//
			//CameraManager::GetInstance()->GetMainCamera()
			//	->RenderRect(hdc, mHouse04Rect1, Gizmo::Color::Blue2);
			//CameraManager::GetInstance()->GetMainCamera()
			//	->RenderRect(hdc, mHouse07Rect1, Gizmo::Color::Blue2);
			//CameraManager::GetInstance()->GetMainCamera()
			//	->RenderRect(hdc, mPoliceRect, Gizmo::Color::Blue2);
			//
			//CameraManager::GetInstance()->GetMainCamera()
			//	->RenderRect(hdc, mShopRect1, Gizmo::Color::Blue2);
			//CameraManager::GetInstance()->GetMainCamera()
			//	->RenderRect(hdc, mShopRect2, Gizmo::Color::Blue2);


			for (int i = 0; i < mCollisionList.size(); ++i)
			{
				CameraManager::GetInstance()->GetMainCamera()
					->RenderRect(hdc, mCollisionList[i], Gizmo::Color::Blue2);
			}
		}
	}

	
}
