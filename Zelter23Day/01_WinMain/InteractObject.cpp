#include "pch.h"
#include "InteractObject.h"
#include "Image.h"
#include "Camera.h"
//타일 사이즈 때문에
#include "Tile.h"

InteractObject::InteractObject(const wstring imageKey, float x, float y, int hp, int tileCountX, int tileCountY)
{
	//위치 판정해주기
	mTileIndexX = x/TileSize;
	mTileIndexY = y/TileSize;
	//인풋값 저장
	mInputY = y;
	mHp = hp;
	mImageKey = imageKey;
	mImage = IMAGEMANAGER->FindImage(mImageKey);
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mTileCountX = tileCountX;
	mTileCountY = tileCountY;
	if (mTileCountX % 2 == 1)//X방향 홀수 타일
	{
		mX = mTileIndexX * TileSize + TileSize / 2 + mTileCountX / 2 * TileSize;
	}
	else if (mTileCountX % 2 == 0)//X방향 짝수 타일
	{
		mX = mTileIndexX * TileSize + mTileCountX/2 * TileSize;
	}
	mY = mTileIndexY * TileSize + TileSize / 2 - mSizeY / 2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	
	mInteractRect = RectMakeCenter(mX, mRect.bottom-TileSize*(mTileCountY-1),
		(TileSize / 2)* mTileCountX, (TileSize / 2)* mTileCountY);
}

void InteractObject::Init()
{
	
	mIsInteractive = true;
	mIndexX = 0;
	mIndexY = 0;
}

void InteractObject::Release()
{
}

void InteractObject::Update()
{
	if (mImage->GetMaxFrameX()>1&& mHp <= 5)
	{
		mIndexX = 1;
	}
	if (mHp <= 0)
	{
		mIsDestroy = true;
	}
}

void InteractObject::Render(HDC hdc)
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
		//충돌 렉트
		CameraManager::GetInstance()->GetMainCamera()
			->RenderRect(hdc, mInteractRect);
		//이미지 렉트
		CameraManager::GetInstance()->GetMainCamera()
			->RenderRect(hdc, mRect);
		//이미지
		CameraManager::GetInstance()->GetMainCamera()
			->FrameRender(hdc, mImage, mRect.left, mRect.top, mIndexX, mIndexY);
	}
}
