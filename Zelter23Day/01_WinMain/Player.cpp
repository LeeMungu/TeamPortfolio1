#include "pch.h"
#include "Player.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"
#include "Tile.h"
#include "MapToolScene.h"

Player::Player(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
	mSpeed = 3.f;
	mDirection = Direction::Left;
}

void Player::Init()
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"Player", Resources(L"wa.bmp"), 92, 120, 4, 4, true);
	mImage = IMAGEMANAGER->FindImage(L"Player");
	mSizeX = mImage->GetFrameWidth() / 2;
	mSizeY = mImage->GetFrameHeight() / 3;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mUpAnimation = new Animation();
	mUpAnimation->InitFrameByStartEnd(0, 3, 3, 3, true);
	mUpAnimation->SetIsLoop(true);
	mUpAnimation->SetFrameUpdateTime(0.1f);

	mLeftAnimation = new Animation();
	mLeftAnimation->InitFrameByStartEnd(0, 1, 3, 1, true);
	mLeftAnimation->SetIsLoop(true);
	mLeftAnimation->SetFrameUpdateTime(0.1f);

	mRightAnimation = new Animation();
	mRightAnimation->InitFrameByStartEnd(0, 2, 3, 2, true);
	mRightAnimation->SetIsLoop(true);
	mRightAnimation->SetFrameUpdateTime(0.1f);

	mDownAnimation = new Animation();
	mDownAnimation->InitFrameByStartEnd(0, 0, 3, 0, true);
	mDownAnimation->SetIsLoop(true);
	mDownAnimation->SetFrameUpdateTime(0.1f);


	mCurrentAnimation = mDownAnimation;
}

void Player::Release()
{
	SafeDelete(mUpAnimation);
	SafeDelete(mLeftAnimation);
	SafeDelete(mRightAnimation);
	SafeDelete(mDownAnimation);
}

void Player::Update()
{
	//for (int y = 0; y < TileCountY; ++y)
	//{
	//	for (int x = 0; x < TileCountX; ++x)
	//	{
	//		RECT temp;
	//		RECT tileRect = mTileList[y][x]->GetRect();
	//		if (IntersectRect(&temp, &tileRect, &mRect))
	//		{
	//			if (mTileList[y][x]->GetTileLayer() == TileLayer::slow)
	//			{
	//				mSpeed = 1.f;
	//			}
	//			else if (mTileList[y][x]->GetTileLayer() == TileLayer::nomal)
	//			{
	//				mSpeed = 3.f;
	//			}
	//			else if (mTileList[y][x]->GetTileLayer() == TileLayer::wall)
	//			{
	//				float tempW = temp.right - temp.left;
	//				float tempH = temp.bottom - temp.top;
	//				float tempX = temp.left + tempW / 2;
	//				float tempY = temp.top + tempW / 2;

	//				float tileRectX = tileRect.left + (tileRect.right - tileRect.left) / 2;
	//				float tileRectY = tileRect.top + (tileRect.bottom - tileRect.top) / 2;

	//				if (tempW < tempH && tempX > tileRectX && mRect.left < tileRect.right)
	//				{
	//					mX = tileRect.right + mImage->GetFrameWidth() / 2;
	//				}

	//				if (tempW < tempH && tempX < tileRectX && mRect.right > tileRect.left)
	//				{
	//					mX = tileRect.left - mImage->GetFrameWidth() / 2;
	//				}

	//				if (tempW > tempH && tempY > tileRectY && mRect.top < tileRect.bottom)
	//				{
	//					mY = tileRect.bottom + mImage->GetFrameHeight() / 2;
	//				}

	//				if (tempW > tempH && tempY < tileRectY && mRect.bottom > tileRect.top)
	//				{
	//					mY = tileRect.top - mImage->GetFrameHeight() / 2;
	//				}

	//			}
	//		}
	//	}
	//}


	if (Input::GetInstance()->GetKey(VK_UP))
	{
		mCurrentAnimation = mUpAnimation;
		mY = mY - mSpeed;
		mCurrentAnimation->Play();
	}
	else if (Input::GetInstance()->GetKey(VK_LEFT))
	{
		mCurrentAnimation = mLeftAnimation;
		mX = mX - mSpeed;
		mCurrentAnimation->Play();
	}
	else if (Input::GetInstance()->GetKey(VK_RIGHT))
	{
		mCurrentAnimation = mRightAnimation;
		mX = mX + mSpeed;
		mCurrentAnimation->Play();
	}
	else if (Input::GetInstance()->GetKey(VK_DOWN))
	{
		mCurrentAnimation = mDownAnimation;
		mY = mY + mSpeed;
		mCurrentAnimation->Play();
	}
	else
	{
		mCurrentAnimation->Stop();
	}

	mCurrentAnimation->Update();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Player::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->
		FrameRender(hdc, mImage, mX-10, mY-25, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
	if (Input::GetInstance()->GetKey(VK_LSHIFT))
	{
		RenderRect(hdc, mRect);
	}
}
