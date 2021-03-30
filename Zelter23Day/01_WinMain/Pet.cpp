#include "pch.h"
#include "Pet.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"
#include "Player.h"
#include "PathFinder.h"
#include "Gizmo.h"
#include "scene1.h"


Pet::Pet(float x, float y)

{
	mName = "Pet";
	mX = x;
	mY = y;

}

void Pet::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Pet");
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	mSizeX = mImage->GetFrameWidth() * 2;
	mSizeY = mImage->GetFrameHeight() * 2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mSpeed = 1.f;

	mCollisionBox = RectMakeCenter(mX, mY, mSizeX /2, mSizeY /2);

	mDownMove = new Animation;
	mDownMove->InitFrameByStartEnd(0, 0, 3, 0, true);
	mDownMove->SetIsLoop(true);
	mDownMove->SetFrameUpdateTime(0.1f);

	mRightMove = new Animation;
	mRightMove->InitFrameByStartEnd(0, 1, 3, 1, true);
	mRightMove->SetIsLoop(true);
	mRightMove->SetFrameUpdateTime(0.1f);

	mUpMove = new Animation;
	mUpMove->InitFrameByStartEnd(0, 2, 3, 2, true);
	mUpMove->SetIsLoop(true);
	mUpMove->SetFrameUpdateTime(0.1f);

	mLeftMove = new Animation;
	mLeftMove->InitFrameByStartEnd(0, 3, 3, 3, false);
	mLeftMove->SetIsLoop(true);
	mLeftMove->SetFrameUpdateTime(0.1f);

	mCurrentAnimation = mRightMove;
	mCurrentAnimation->Play();

	mPetState = PetState::Idle;
	mFollowDistance = 200.f;

	mIsCheck = false;
	mIsTarget = false;
}

void Pet::Release()
{
	SafeDelete(mLeftMove);
	SafeDelete(mRightMove);
	SafeDelete(mDownMove);
	SafeDelete(mUpMove);
}

void Pet::Update()
{

	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	mDistance = Math::GetDistance(mPlayer->GetX(), mPlayer->GetY(), mX, mY);

	//주인 인식
	if (mDistance < 30)
	{
		mIsCheck = true;
	}
	//인식후 거리가 벌어지면
	if (mDistance >= mFollowDistance && mIsCheck == true)
	{
		mPetState = PetState::Follow;
	}
	if (mPetState == PetState::Follow)
	{
		FollowPlayer();
	}
	//일정 거리 이하가 되면
	if (mDistance < 200)
	{
		mPetState = PetState::Idle;
	}

	mCollisionBox = RectMakeCenter(mX, mY, mSizeX / 2, mSizeY / 2);
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mCurrentAnimation->Update();
}

void Pet::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->AlphaScaleFrameRender(hdc, mImage, mRect.left, mRect.top,
		mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), mSizeX, mSizeY, 0.5);

	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, mRect);
		CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, mCollisionBox);
		if (ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Player).size() != NULL)
		{
			if (mPetState == PetState::Follow)
			{
				vector<Tile*> Path = PathFinder::GetInstance()->FindPath(mTileList, mX / TileSize, mY / TileSize, mPlayer->GetX() / TileSize, mPlayer->GetY() / TileSize);
				for (int i = 0; i < Path.size(); ++i)
				{
					CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, (Path[i]->GetRect()), Gizmo::Color::Blue2);
				}
			}
		}
	}
}

void Pet::FindPlayer()
{
	vector<Tile*> Path = PathFinder::GetInstance()->FindPath(mTileList, mX / TileSize, mY / TileSize, mPlayer->GetX() / TileSize, mPlayer->GetY() / TileSize);

}

void Pet::FollowPlayer()
{
	vector<Tile*> Path = PathFinder::GetInstance()->FindPath(mTileList, mX / TileSize, mY / TileSize, mPlayer->GetX() / TileSize, mPlayer->GetY() / TileSize);

	if (Path.size() != NULL  )
	{

		if (Path.size() > 3)
		{
			mAngle = Math::GetAngle(Path[2]->GetX(), Path[2]->GetY(), mX, mY);

		}
		mX -= cosf(mAngle) * mSpeed;
		mY -= -sinf(mAngle) * mSpeed;
	}
	if (mPlayer->GetRect().left > mRect.right)
	{
		mCurrentAnimation = mRightMove;
		mCurrentAnimation->Play();
	}
	else if (mPlayer->GetRect().left < mRect.left)
	{
		mCurrentAnimation = mLeftMove;
		mCurrentAnimation->Play();
	}
	else if (mPlayer->GetRect().top > mRect.bottom)
	{
		mCurrentAnimation = mDownMove;
		mCurrentAnimation->Play();
	}
	else if (mPlayer->GetRect().bottom < mRect.top)
	{
		mCurrentAnimation = mUpMove;
		mCurrentAnimation->Play();
	}

	
}
