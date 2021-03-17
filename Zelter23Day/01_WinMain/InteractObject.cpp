#include "pch.h"
#include "InteractObject.h"
#include "Image.h"
#include "Camera.h"
//Ÿ�� ������ ������
#include "Tile.h"

InteractObject::InteractObject(const wstring imageKey, float x, float y, int hp, int tileCountX, int tileCountY)
{
	//��ġ �������ֱ�
	mTileIndexX = x/TileSize;
	mTileIndexY = y/TileSize;
	//��ǲ�� ����
	mInputY = y;
	mHp = hp;
	mImageKey = imageKey;
	mImage = IMAGEMANAGER->FindImage(mImageKey);
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mTileCountX = tileCountX;
	mTileCountY = tileCountY;
	if (mTileCountX % 2 == 1)//X���� Ȧ�� Ÿ��
	{
		mX = mTileIndexX * TileSize + TileSize / 2 + mTileCountX / 2 * TileSize;
	}
	else if (mTileCountX % 2 == 0)//X���� ¦�� Ÿ��
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
		//�浹 ��Ʈ
		CameraManager::GetInstance()->GetMainCamera()
			->RenderRect(hdc, mInteractRect);
		//�̹��� ��Ʈ
		CameraManager::GetInstance()->GetMainCamera()
			->RenderRect(hdc, mRect);
		//�̹���
		CameraManager::GetInstance()->GetMainCamera()
			->FrameRender(hdc, mImage, mRect.left, mRect.top, mIndexX, mIndexY);
	}
}
