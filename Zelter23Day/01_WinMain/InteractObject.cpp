#include "pch.h"
#include "InteractObject.h"
#include "Image.h"
#include "Camera.h"
//타일 사이즈 때문에
#include "Tile.h"

InteractObject::InteractObject(const wstring imageKey, float x, float y, int hp, int tileCountX, int tileCountY)
{
	//위치 판정해주기
	mX = x;
	mY = y;
	mHp = hp;
	mImageKey = imageKey;
	mImage = IMAGEMANAGER->FindImage(mImageKey);
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mTileCountX = tileCountX;
	mTileCountY = tileCountY;
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
	//if (mHp <= 0 && mIsInteractive == true)
	//{
	//	mIsInteractive = false;
	//	mIndexX = 1;
	//}
	if (mHp <= 0)
	{
		mIsDestroy = true;
	}
}

void InteractObject::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mRect.left, mRect.top, mIndexX, mIndexY);
}
