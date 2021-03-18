#include "pch.h"
#include "InteractObject.h"
#include "Image.h"
#include "Camera.h"
//Ÿ�� ������ ������
#include "Tile.h"

#define InteractObjectSize 2

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
	mSizeX = mImage->GetFrameWidth()* InteractObjectSize;
	mSizeY = mImage->GetFrameHeight()* InteractObjectSize;
	mTileCountX = tileCountX;
	mTileCountY = tileCountY;
	if ((mTileCountX * InteractObjectSize) % 2 == 1)//X���� Ȧ�� Ÿ��
	{
		mX = mTileIndexX * InteractObjectSize * TileSize + TileSize / 2 + mTileCountX * InteractObjectSize / 2 * TileSize;
	}
	else if ((mTileCountX * InteractObjectSize) % 2 == 0)//X���� ¦�� Ÿ��
	{
		mX = mTileIndexX * InteractObjectSize * TileSize + mTileCountX * InteractObjectSize /2 * TileSize;
	}
	mY = mTileIndexY * InteractObjectSize * TileSize + TileSize / 2 - mSizeY / 2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	
	int interactRectSizeX, interactRectSizeY;
	if (mTileCountX == 1)
	{
		interactRectSizeX = TileSize / 2;
	}
	else
	{
		interactRectSizeX = TileSize * (mTileCountX * InteractObjectSize - 1);
	}
	if (mTileCountY == 1)
	{
		interactRectSizeY = TileSize / 2;
	}
	else
	{
		interactRectSizeY = TileSize * (mTileCountY * InteractObjectSize - 1);
	}
	mInteractRect = RectMakeCenter(mX, mRect.bottom-TileSize/2*(mTileCountY * InteractObjectSize -1),
		interactRectSizeX, interactRectSizeY);
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
		for (int y = 0; y < mTileCountY * InteractObjectSize; ++y)
		{
			for (int x = 0; x < mTileCountX * InteractObjectSize; ++x)
			{
				RECT rc = RectMakeCenter(
					mTileIndexX * InteractObjectSize * TileSize + TileSize / 2 + x * TileSize,
					mRect.bottom - y * TileSize,
					TileSize, TileSize);
				//CameraManager::GetInstance()->GetMainCamera()
				//	->RenderRect(hdc, rc);
			}
		}

		if (Input::GetInstance()->GetKey(VK_LCONTROL))
		{
			//�浹 ��Ʈ
			CameraManager::GetInstance()->GetMainCamera()
				->RenderRect(hdc, mInteractRect);
			//�̹��� ��Ʈ
			CameraManager::GetInstance()->GetMainCamera()
				->RenderRect(hdc, mRect);
		}

		//�̹���
		CameraManager::GetInstance()->GetMainCamera()
			->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mIndexX, mIndexY,mSizeX,mSizeY);
	}
}
