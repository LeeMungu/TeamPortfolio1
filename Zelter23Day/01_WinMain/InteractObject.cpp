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
	mInputX = x;
	mInputY = y;
	mHp = hp;
	mImageKey = imageKey;
	mImage = IMAGEMANAGER->FindImage(mImageKey);
	mSizeX = mImage->GetFrameWidth()* InteractObjectSize;
	mSizeY = mImage->GetFrameHeight()* InteractObjectSize;
	mTileCountX = tileCountX;
	mTileCountY = tileCountY;
	if ((mTileCountX * InteractObjectSize) % 2 == 1)//X방향 홀수 타일
	{
		mX = mTileIndexX * TileSize + TileSize / 2 + mTileCountX * InteractObjectSize / 2 * TileSize;
	}
	else if ((mTileCountX * InteractObjectSize) % 2 == 0)//X방향 짝수 타일
	{
		mX = mTileIndexX * TileSize + mTileCountX * InteractObjectSize / 2 * TileSize;// -TileSize / 2;
	}
	mY = mTileIndexY * TileSize - mSizeY / 2 + TileSize/2;
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
	mIsInvincible = false;
	mInvincibleCount = 0.f;
	mIndexX = 0;
	mIndexY = 0;
}

void InteractObject::Release()
{
}

void InteractObject::Update()
{
	//피격 판정 딜레이 확인.
	if (mIsInvincible == true)
	{
		mInvincibleCount += Time::GetInstance()->DeltaTime();

		mSizeY -= 20 * Time::GetInstance()->DeltaTime();
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	}
	if (mInvincibleCount > 0.4f && mIsInvincible == true)
	{
		mIsInvincible = false;
		mInvincibleCount = 0.f;
	}
	if (mIsInvincible == false)
	{
		mSizeY = mImage->GetFrameHeight() * InteractObjectSize;
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}

	if (mImage->GetMaxFrameX()>1&& mHp <= 5)
	{
		mIndexX = 1;
	}
	if (mHp <= 0)
	{
		ItemManager::GetInstance()->randomItem(mImageKey, mX, mY);

		mIsDestroy = true;
	}
}

void InteractObject::Render(HDC hdc)
{
	if (CameraManager::GetInstance()->GetMainCamera()->IsInCameraArea(mRect))
	{
		//타일 렉트
		for (int y = 0; y < mTileCountY * InteractObjectSize; ++y)
		{
			for (int x = 0; x < mTileCountX * InteractObjectSize; ++x)
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
			//충돌 렉트
			CameraManager::GetInstance()->GetMainCamera()
				->RenderRect(hdc, mInteractRect);
			//이미지 렉트
			CameraManager::GetInstance()->GetMainCamera()
				->RenderRect(hdc, mRect);
		}
		//그림자
		CameraManager::GetInstance()->GetMainCamera()
			->ShadowRender(hdc, mImage, mRect.left, mRect.top, mIndexX, mIndexY, mSizeX, mSizeY, 0.3f,
				Time::GetInstance()->GetSceneTime()*100);
		//이미지
		CameraManager::GetInstance()->GetMainCamera()
			->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mIndexX, mIndexY,mSizeX,mSizeY);
	}
}
