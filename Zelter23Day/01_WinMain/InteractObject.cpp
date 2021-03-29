#include "pch.h"
#include "InteractObject.h"
#include "Image.h"
#include "Camera.h"
//타일 사이즈 때문에
#include "Tile.h"



InteractObject::InteractObject(const wstring imageKey, float x, float y, int hp, int tileCountX, int tileCountY)
{
	mName.assign(imageKey.begin(), imageKey.end());
	//위치 판정해주기
	mTileIndexX = x/TileSize;
	mTileIndexY = y/TileSize;
	//인풋값 저장
	mInputX = x;
	mInputY = y;
	mHp = hp;
	mImageKey = imageKey;
	mImage = IMAGEMANAGER->FindImage(mImageKey);
	
	mSizeX = mImage->GetFrameWidth() * InteractObjectSize;
	mSizeY = mImage->GetFrameHeight() * InteractObjectSize;

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

	if (mImage->GetKey() == L"Door1")
	{
		mX -= 32;
		mY -= 35;
		mSizeX = mImage->GetFrameWidth() * InteractObjectSize * 2 + 5;
		mSizeY = mImage->GetFrameHeight() * InteractObjectSize * 1.7;
	}
	else if (mImage->GetKey() == L"Door2")
	{
		mX += 1;
		mY -= 22;
		mSizeX = mImage->GetFrameWidth() * InteractObjectSize +6;
		mSizeY = mImage->GetFrameHeight() * InteractObjectSize +4;
	}
	else if (mImage->GetKey() == L"Door3")
	{
		mX += 34;
		mY -= 52;
		mSizeX = mImage->GetFrameWidth() * InteractObjectSize *1.9 -2;
		mSizeY = mImage->GetFrameHeight() * InteractObjectSize + 20;
	}
	else if (mImage->GetKey() == L"Door4")
	{
		mX -= 18;
		mY -= 46;
		mSizeX = mImage->GetFrameWidth() * InteractObjectSize +8;
		mSizeY = mImage->GetFrameHeight() * InteractObjectSize ;
	}
	
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
	mIsDoorOpen = false;
	mChangeDoor = false;
	mDoorTime = 0.f;
}

void InteractObject::Release()
{
}

void InteractObject::Update()
{
	//피격 판정 딜레이 확인.
	if (mIsInvincible == true && mImage->GetKey().substr(0,4) != L"Door")
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
	if (mIsInvincible == false && mImage->GetKey().substr(0, 4) != L"Door")
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

	wstring tempKey = mImageKey.substr(0, 4);

	if (tempKey == L"Door")
	{
		GameObject* player = ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
		if (player != NULL)
		{
			RECT tempRc;
			RECT playerRc = player->GetRect();
			if (IntersectRect(&tempRc, &playerRc, &mRect))
			{
				if (Input::GetInstance()->GetKeyDown('E'))
				{
					mChangeDoor = true;
				}
			}
			if (mChangeDoor)
			{
				mDoorTime += Time::GetInstance()->DeltaTime();
				if (mDoorTime > 1)
				{
					if (mIsDoorOpen == true) mIsDoorOpen = false;
					else if (mIsDoorOpen == false) mIsDoorOpen = true;
					mDoorTime = 0.f;
					mChangeDoor = false;
				}
			}
		}
	}
}

void InteractObject::Render(HDC hdc)
{
	if (CameraManager::GetInstance()->GetMainCamera()->IsInCameraArea(mRect))
	{
		////타일 렉트
		//for (int y = 0; y < mTileCountY * InteractObjectSize; ++y)
		//{
		//	for (int x = 0; x < mTileCountX * InteractObjectSize; ++x)
		//	{
		//		RECT rc = RectMakeCenter(
		//			mTileIndexX * TileSize + TileSize / 2 + x * TileSize,
		//			mRect.bottom - y * TileSize,
		//			TileSize, TileSize);
		//		CameraManager::GetInstance()->GetMainCamera()
		//			->RenderRect(hdc, rc);
		//	}
		//}

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
				Time::GetInstance()->GetSceneTime());
		//이미지
		wstring tempKey = mImageKey.substr(0, 4);

		if (tempKey != L"Door")
		{
			CameraManager::GetInstance()->GetMainCamera()
				->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mIndexX, mIndexY,mSizeX,mSizeY);
		}
		else if (tempKey == L"Door")
		{
			if (mIsDoorOpen == false)
			{
				CameraManager::GetInstance()->GetMainCamera()
					->DoorScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mIndexX, mIndexY, mSizeX, mSizeY, mDoorTime);
			}
			else if (mIsDoorOpen == true)
			{
				//열린 문 이미지 넣어줄예정
				if (mChangeDoor == false)
				{
					CameraManager::GetInstance()->GetMainCamera()
						->DoorScaleFrameRender(hdc, mImage, mRect.left, mRect.top, 1, mIndexY, mSizeX, mSizeY, mDoorTime);
				}
				else if (mChangeDoor == true)
				{
					CameraManager::GetInstance()->GetMainCamera()
						->DoorScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mIndexX, mIndexY, mSizeX, mSizeY, 1.f-mDoorTime);
				}
			}
		}
	}
}
