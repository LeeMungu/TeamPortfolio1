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
	mImage = IMAGEMANAGER->FindImage(mImageKey);
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mTileCountX = tileCountX;
	mTileCountY = tileCountY;

	if ((mTileCountX) % 2 == 1)//X���� Ȧ�� Ÿ��
	{
		mX = mTileIndexX * TileSize + TileSize / 2 + mTileCountX / 2 * TileSize;
	}
	else if ((mTileCountX) % 2 == 0)//X���� ¦�� Ÿ��
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
}

void HousingObject::Release()
{

}

void HousingObject::Update()
{

}

void HousingObject::Render(HDC hdc)
{
	if (CameraManager::GetInstance()->GetMainCamera()->IsInCameraArea(mRect))
	{
		//Ÿ�� ��Ʈ
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
			//�̹��� ��Ʈ
			CameraManager::GetInstance()->GetMainCamera()
				->RenderRect(hdc, mRect);
		}

		//�̹���
		CameraManager::GetInstance()->GetMainCamera()
			->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mIndexX, mIndexY, mSizeX, mSizeY);
	}
}
